------------------------------------------------------------------------------------
--Name:			[征服][活动脚本]VIP福利大赠送
--Purpose:		2015暑期活动-VIP福利大赠送
--Creator: 		郑鋆
--Created:		2015/4/17
------------------------------------------------------------------------------------
-- 命名规则
-- VipWelfareGifts2015_

-- 活动时间：2015年7月15日到7月22日

-- 掩码说明
-- 134,24	记录当天是否签到
-- 134,25	记录签到次数
-- 134,26	记录当天是否领取过福利
-- 12000086

-- 常量表
local tVipWelfareGifts2015_Constant = {}
	-- 活动时间
	tVipWelfareGifts2015_Constant["BeforeActivityTime"] = "2015-03-17 00:00 2015-07-14 23:59"
	tVipWelfareGifts2015_Constant["ActivityTime"] = "2015-07-15 00:00 2015-07-22 23:59"
	tVipWelfareGifts2015_Constant["UseItemTime"] = "2015-07-15 00:00 2015-07-31 23:59"

	tVipWelfareGifts2015_Constant["CompleteData"] = 1
	
	-- 签到需要的背包空间
	tVipWelfareGifts2015_Constant["SignItemSpace"] = 3
	-- 福利需要的背包空间
	tVipWelfareGifts2015_Constant["WelfareSpace"] =2
	
	tVipWelfareGifts2015_Constant["SaveTime"] = 1440
	
	tVipWelfareGifts2015_Constant["MinTime"] = 3
	tVipWelfareGifts2015_Constant["MidTime"] = 5
	tVipWelfareGifts2015_Constant["MaxTime"] = 7

	tVipWelfareGifts2015_Constant["MinVip"] = 3
	tVipWelfareGifts2015_Constant["MidVip"] = 4
	tVipWelfareGifts2015_Constant["MaxVip"] = 5
	
	-- 清心符礼包打开价格
	tVipWelfareGifts2015_Constant["Emoney"] = 30
	tVipWelfareGifts2015_Constant["HeartSpace"] = 9
	tVipWelfareGifts2015_Constant["HeartItem"] = 720128
	
-- stc掩码表
local tVipWelfareGifts2015_Stc = {}
	tVipWelfareGifts2015_Stc["EventType"] = 134
	
	tVipWelfareGifts2015_Stc[1] = {}
	tVipWelfareGifts2015_Stc[2] = {}
	tVipWelfareGifts2015_Stc[3] = {}
	tVipWelfareGifts2015_Stc[1]["DataType"] = 24
	tVipWelfareGifts2015_Stc[2]["DataType"] = 25
	tVipWelfareGifts2015_Stc[3]["DataType"] = 26

-- 签到奖励表
local tVipWelfareGifts2015_Sign = {}
	tVipWelfareGifts2015_Sign[1] = {}
	tVipWelfareGifts2015_Sign[1][1] = {}
	tVipWelfareGifts2015_Sign[1][1]["ItemId"] = 3002308
	tVipWelfareGifts2015_Sign[1][1]["IsTime"] = false
	tVipWelfareGifts2015_Sign[1][2] = {}
	tVipWelfareGifts2015_Sign[1][2]["ItemId"] = 3004027
	tVipWelfareGifts2015_Sign[1][2]["IsTime"] = false
	
	tVipWelfareGifts2015_Sign[2] = {}
	tVipWelfareGifts2015_Sign[2][1] = {}
	tVipWelfareGifts2015_Sign[2][1]["ItemId"] = 3002308
	tVipWelfareGifts2015_Sign[2][1]["IsTime"] = false
	tVipWelfareGifts2015_Sign[2][2] = {}
	tVipWelfareGifts2015_Sign[2][2]["ItemId"] = 3004117
	tVipWelfareGifts2015_Sign[2][2]["IsTime"] = true
	
	tVipWelfareGifts2015_Sign[3] = {}
	tVipWelfareGifts2015_Sign[3][1] = {}
	tVipWelfareGifts2015_Sign[3][1]["ItemId"] = 3002308
	tVipWelfareGifts2015_Sign[3][1]["IsTime"] = false
	tVipWelfareGifts2015_Sign[3][2] = {}
	tVipWelfareGifts2015_Sign[3][2]["ItemId"] = 3004027
	tVipWelfareGifts2015_Sign[3][2]["IsTime"] = false
	tVipWelfareGifts2015_Sign[3][3] = {}
	tVipWelfareGifts2015_Sign[3][3]["ItemId"] = 3004028
	tVipWelfareGifts2015_Sign[3][3]["IsTime"] = true
	
	tVipWelfareGifts2015_Sign[4] = {}
	tVipWelfareGifts2015_Sign[4][1] = {}
	tVipWelfareGifts2015_Sign[4][1]["ItemId"] = 3002308
	tVipWelfareGifts2015_Sign[4][1]["IsTime"] = false
	tVipWelfareGifts2015_Sign[4][2] = {}
	tVipWelfareGifts2015_Sign[4][2]["ItemId"] = 3004117
	tVipWelfareGifts2015_Sign[4][2]["IsTime"] = true
	tVipWelfareGifts2015_Sign[4][3] = {}
	tVipWelfareGifts2015_Sign[4][3]["ItemId"] = 3004028
	tVipWelfareGifts2015_Sign[4][3]["IsTime"] = true
	
	tVipWelfareGifts2015_Sign[5] = {}
	tVipWelfareGifts2015_Sign[5][1] = {}
	tVipWelfareGifts2015_Sign[5][1]["ItemId"] = 3002308
	tVipWelfareGifts2015_Sign[5][1]["IsTime"] = false
	tVipWelfareGifts2015_Sign[5][2] = {}
	tVipWelfareGifts2015_Sign[5][2]["ItemId"] = 3004027
	tVipWelfareGifts2015_Sign[5][2]["IsTime"] = false
	tVipWelfareGifts2015_Sign[5][3] = {}
	tVipWelfareGifts2015_Sign[5][3]["ItemId"] = 3004029
	tVipWelfareGifts2015_Sign[5][3]["IsTime"] = true
	
	tVipWelfareGifts2015_Sign[6] = {}
	tVipWelfareGifts2015_Sign[6][1] = {}
	tVipWelfareGifts2015_Sign[6][1]["ItemId"] = 3002308
	tVipWelfareGifts2015_Sign[6][1]["IsTime"] = false
	tVipWelfareGifts2015_Sign[6][2] = {}
	tVipWelfareGifts2015_Sign[6][2]["ItemId"] = 3004117
	tVipWelfareGifts2015_Sign[6][2]["IsTime"] = true
	tVipWelfareGifts2015_Sign[6][3] = {}
	tVipWelfareGifts2015_Sign[6][3]["ItemId"] = 3004029
	tVipWelfareGifts2015_Sign[6][3]["IsTime"] = true
	
	tVipWelfareGifts2015_Sign[7] = {}
	tVipWelfareGifts2015_Sign[7][1] = {}
	tVipWelfareGifts2015_Sign[7][1]["ItemId"] = 3002308
	tVipWelfareGifts2015_Sign[7][1]["IsTime"] = false
	tVipWelfareGifts2015_Sign[7][2] = {}
	tVipWelfareGifts2015_Sign[7][2]["ItemId"] = 3004027
	tVipWelfareGifts2015_Sign[7][2]["IsTime"] = false
	tVipWelfareGifts2015_Sign[7][3] = {}
	tVipWelfareGifts2015_Sign[7][3]["ItemId"] = 3004030
	tVipWelfareGifts2015_Sign[7][3]["IsTime"] = true
	
	tVipWelfareGifts2015_Sign[8] = {}
	tVipWelfareGifts2015_Sign[8][1] = {}
	tVipWelfareGifts2015_Sign[8][1]["ItemId"] = 3002308
	tVipWelfareGifts2015_Sign[8][1]["IsTime"] = false
	tVipWelfareGifts2015_Sign[8][2] = {}
	tVipWelfareGifts2015_Sign[8][2]["ItemId"] = 3004117
	tVipWelfareGifts2015_Sign[8][2]["IsTime"] = true
	tVipWelfareGifts2015_Sign[8][3] = {}
	tVipWelfareGifts2015_Sign[8][3]["ItemId"] = 3004030
	tVipWelfareGifts2015_Sign[8][3]["IsTime"] = true

-- 福利奖励表
local tVipWelfareGifts2015_Welfare = {}
	tVipWelfareGifts2015_Welfare[1] = {}
	tVipWelfareGifts2015_Welfare[1]["Item"] = {}
	tVipWelfareGifts2015_Welfare[1]["Item"][1] = {}
	tVipWelfareGifts2015_Welfare[1]["Item"][1]["Id"] = 3004032
	tVipWelfareGifts2015_Welfare[1]["Item"][1]["Num"] = 1
	tVipWelfareGifts2015_Welfare[1]["Item"][2] = {}
	tVipWelfareGifts2015_Welfare[1]["Item"][2]["Id"] = 3004031
	tVipWelfareGifts2015_Welfare[1]["Item"][2]["Num"] = 1
	tVipWelfareGifts2015_Welfare[1]["Cultivation"] = 50
	tVipWelfareGifts2015_Welfare[1]["Strengthvalue"] = 100
	tVipWelfareGifts2015_Welfare[1]["Percent"] = 200
	tVipWelfareGifts2015_Welfare[1]["Time"] = 10800
	
	tVipWelfareGifts2015_Welfare[2] = {}
	tVipWelfareGifts2015_Welfare[2]["Item"] = {}
	tVipWelfareGifts2015_Welfare[2]["Item"][1] = {}
	tVipWelfareGifts2015_Welfare[2]["Item"][1]["Id"] = 3004032
	tVipWelfareGifts2015_Welfare[2]["Item"][1]["Num"] = 1
	tVipWelfareGifts2015_Welfare[2]["Cultivation"] = 50
	tVipWelfareGifts2015_Welfare[2]["Strengthvalue"] = 100
	tVipWelfareGifts2015_Welfare[2]["Percent"] = 200
	tVipWelfareGifts2015_Welfare[2]["Time"] = 10800
	
	tVipWelfareGifts2015_Welfare[3] = {}
	tVipWelfareGifts2015_Welfare[3]["Item"] = {}
	tVipWelfareGifts2015_Welfare[3]["Item"][1] = {}
	tVipWelfareGifts2015_Welfare[3]["Item"][1]["Id"] = 3004032
	tVipWelfareGifts2015_Welfare[3]["Item"][1]["Num"] = 2
	tVipWelfareGifts2015_Welfare[3]["Item"][2] = {}
	tVipWelfareGifts2015_Welfare[3]["Item"][2]["Id"] = 3004031
	tVipWelfareGifts2015_Welfare[3]["Item"][2]["Num"] = 2
	tVipWelfareGifts2015_Welfare[3]["Cultivation"] = 100
	tVipWelfareGifts2015_Welfare[3]["Strengthvalue"] = 300
	tVipWelfareGifts2015_Welfare[3]["Percent"] = 200
	tVipWelfareGifts2015_Welfare[3]["Time"] = 14400
	
	tVipWelfareGifts2015_Welfare[4] = {}
	tVipWelfareGifts2015_Welfare[4]["Item"] = {}
	tVipWelfareGifts2015_Welfare[4]["Item"][1] = {}
	tVipWelfareGifts2015_Welfare[4]["Item"][1]["Id"] = 3004032
	tVipWelfareGifts2015_Welfare[4]["Item"][1]["Num"] = 2
	tVipWelfareGifts2015_Welfare[4]["Cultivation"] = 100
	tVipWelfareGifts2015_Welfare[4]["Strengthvalue"] = 300
	tVipWelfareGifts2015_Welfare[4]["Percent"] = 200
	tVipWelfareGifts2015_Welfare[4]["Time"] = 14400
	
	tVipWelfareGifts2015_Welfare[5] = {}
	tVipWelfareGifts2015_Welfare[5]["Item"] = {}
	tVipWelfareGifts2015_Welfare[5]["Item"][1] = {}
	tVipWelfareGifts2015_Welfare[5]["Item"][1]["Id"] = 3004032
	tVipWelfareGifts2015_Welfare[5]["Item"][1]["Num"] = 3
	tVipWelfareGifts2015_Welfare[5]["Item"][2] = {}
	tVipWelfareGifts2015_Welfare[5]["Item"][2]["Id"] = 3004031
	tVipWelfareGifts2015_Welfare[5]["Item"][2]["Num"] = 3
	tVipWelfareGifts2015_Welfare[5]["Cultivation"] = 150
	tVipWelfareGifts2015_Welfare[5]["Strengthvalue"] = 400
	tVipWelfareGifts2015_Welfare[5]["Percent"] = 200
	tVipWelfareGifts2015_Welfare[5]["Time"] = 18000
	
	tVipWelfareGifts2015_Welfare[6] = {}
	tVipWelfareGifts2015_Welfare[6]["Item"] = {}
	tVipWelfareGifts2015_Welfare[6]["Item"][1] = {}
	tVipWelfareGifts2015_Welfare[6]["Item"][1]["Id"] = 3004032
	tVipWelfareGifts2015_Welfare[6]["Item"][1]["Num"] = 3
	tVipWelfareGifts2015_Welfare[6]["Cultivation"] = 150
	tVipWelfareGifts2015_Welfare[6]["Strengthvalue"] = 400
	tVipWelfareGifts2015_Welfare[6]["Percent"] = 200
	tVipWelfareGifts2015_Welfare[6]["Time"] = 18000
	
	tVipWelfareGifts2015_Welfare[7] = {}
	tVipWelfareGifts2015_Welfare[7]["Item"] = {}
	tVipWelfareGifts2015_Welfare[7]["Item"][1] = {}
	tVipWelfareGifts2015_Welfare[7]["Item"][1]["Id"] = 3004032
	tVipWelfareGifts2015_Welfare[7]["Item"][1]["Num"] = 4
	tVipWelfareGifts2015_Welfare[7]["Item"][2] = {}
	tVipWelfareGifts2015_Welfare[7]["Item"][2]["Id"] = 3004031
	tVipWelfareGifts2015_Welfare[7]["Item"][2]["Num"] = 4
	tVipWelfareGifts2015_Welfare[7]["Cultivation"] = 200
	tVipWelfareGifts2015_Welfare[7]["Strengthvalue"] = 500
	tVipWelfareGifts2015_Welfare[7]["Percent"] = 200
	tVipWelfareGifts2015_Welfare[7]["Time"] = 21600
	
	tVipWelfareGifts2015_Welfare[8] = {}
	tVipWelfareGifts2015_Welfare[8]["Item"] = {}
	tVipWelfareGifts2015_Welfare[8]["Item"][1] = {}
	tVipWelfareGifts2015_Welfare[8]["Item"][1]["Id"] = 3004032
	tVipWelfareGifts2015_Welfare[8]["Item"][1]["Num"] = 4
	tVipWelfareGifts2015_Welfare[8]["Cultivation"] = 200
	tVipWelfareGifts2015_Welfare[8]["Strengthvalue"] = 500
	tVipWelfareGifts2015_Welfare[8]["Percent"] = 200
	tVipWelfareGifts2015_Welfare[8]["Time"] = 21600

-- 物品奖励表
local tVipWelfareGifts2015_RewardItem = {}
	-- VIP夏日炎炎礼包
	tVipWelfareGifts2015_RewardItem[3004028] = {}
	tVipWelfareGifts2015_RewardItem[3004028][1] = {}
	tVipWelfareGifts2015_RewardItem[3004028][1]["Space"] = 1
	tVipWelfareGifts2015_RewardItem[3004028][1]["Item"] = {}
	tVipWelfareGifts2015_RewardItem[3004028][1]["Item"][1] = {}
	tVipWelfareGifts2015_RewardItem[3004028][1]["Item"][1]["Id"] = 3002308
	tVipWelfareGifts2015_RewardItem[3004028][1]["Item"][1]["Num"] = 1
	tVipWelfareGifts2015_RewardItem[3004028][1]["Item"][1]["IsTime"] = false
	tVipWelfareGifts2015_RewardItem[3004028][1]["Item"][2] = {}
	tVipWelfareGifts2015_RewardItem[3004028][1]["Item"][2]["Id"] = 3004027
	tVipWelfareGifts2015_RewardItem[3004028][1]["Item"][2]["Num"] = 3
	tVipWelfareGifts2015_RewardItem[3004028][1]["Item"][2]["IsTime"] = false
	
	tVipWelfareGifts2015_RewardItem[3004028][2] = {}
	tVipWelfareGifts2015_RewardItem[3004028][2]["Space"] = 1
	tVipWelfareGifts2015_RewardItem[3004028][2]["Item"] = {}
	tVipWelfareGifts2015_RewardItem[3004028][2]["Item"][1] = {}
	tVipWelfareGifts2015_RewardItem[3004028][2]["Item"][1]["Id"] = 3002308
	tVipWelfareGifts2015_RewardItem[3004028][2]["Item"][1]["Num"] = 1
	tVipWelfareGifts2015_RewardItem[3004028][2]["Item"][1]["IsTime"] = false
	tVipWelfareGifts2015_RewardItem[3004028][2]["Item"][2] = {}
	tVipWelfareGifts2015_RewardItem[3004028][2]["Item"][2]["Id"] = 3004117
	tVipWelfareGifts2015_RewardItem[3004028][2]["Item"][2]["Num"] = 1
	tVipWelfareGifts2015_RewardItem[3004028][2]["Item"][2]["IsTime"] = true
	
	tVipWelfareGifts2015_RewardItem[3004028][3] = {}
	tVipWelfareGifts2015_RewardItem[3004028][3]["Space"] = 2
	tVipWelfareGifts2015_RewardItem[3004028][3]["Item"] = {}
	tVipWelfareGifts2015_RewardItem[3004028][3]["Item"][1] = {}
	tVipWelfareGifts2015_RewardItem[3004028][3]["Item"][1]["Id"] = 3002308
	tVipWelfareGifts2015_RewardItem[3004028][3]["Item"][1]["Num"] = 2
	tVipWelfareGifts2015_RewardItem[3004028][3]["Item"][1]["IsTime"] = false
	tVipWelfareGifts2015_RewardItem[3004028][3]["Item"][2] = {}
	tVipWelfareGifts2015_RewardItem[3004028][3]["Item"][2]["Id"] = 3004027
	tVipWelfareGifts2015_RewardItem[3004028][3]["Item"][2]["Num"] = 4
	tVipWelfareGifts2015_RewardItem[3004028][3]["Item"][2]["IsTime"] = false
	
	tVipWelfareGifts2015_RewardItem[3004028][4] = {}
	tVipWelfareGifts2015_RewardItem[3004028][4]["Space"] = 2
	tVipWelfareGifts2015_RewardItem[3004028][4]["Item"] = {}
	tVipWelfareGifts2015_RewardItem[3004028][4]["Item"][1] = {}
	tVipWelfareGifts2015_RewardItem[3004028][4]["Item"][1]["Id"] = 3002308
	tVipWelfareGifts2015_RewardItem[3004028][4]["Item"][1]["Num"] = 2
	tVipWelfareGifts2015_RewardItem[3004028][4]["Item"][1]["IsTime"] = false
	tVipWelfareGifts2015_RewardItem[3004028][4]["Item"][2] = {}
	tVipWelfareGifts2015_RewardItem[3004028][4]["Item"][2]["Id"] = 3004117
	tVipWelfareGifts2015_RewardItem[3004028][4]["Item"][2]["Num"] = 1
	tVipWelfareGifts2015_RewardItem[3004028][4]["Item"][2]["IsTime"] = true
	
	tVipWelfareGifts2015_RewardItem[3004028][5] = {}
	tVipWelfareGifts2015_RewardItem[3004028][5]["Space"] = 3
	tVipWelfareGifts2015_RewardItem[3004028][5]["Item"] = {}
	tVipWelfareGifts2015_RewardItem[3004028][5]["Item"][1] = {}
	tVipWelfareGifts2015_RewardItem[3004028][5]["Item"][1]["Id"] = 3002308
	tVipWelfareGifts2015_RewardItem[3004028][5]["Item"][1]["Num"] = 3
	tVipWelfareGifts2015_RewardItem[3004028][5]["Item"][1]["IsTime"] = false
	tVipWelfareGifts2015_RewardItem[3004028][5]["Item"][2] = {}
	tVipWelfareGifts2015_RewardItem[3004028][5]["Item"][2]["Id"] = 3004027
	tVipWelfareGifts2015_RewardItem[3004028][5]["Item"][2]["Num"] = 5
	tVipWelfareGifts2015_RewardItem[3004028][5]["Item"][2]["IsTime"] = false
	
	tVipWelfareGifts2015_RewardItem[3004028][6] = {}
	tVipWelfareGifts2015_RewardItem[3004028][6]["Space"] = 3
	tVipWelfareGifts2015_RewardItem[3004028][6]["Item"] = {}
	tVipWelfareGifts2015_RewardItem[3004028][6]["Item"][1] = {}
	tVipWelfareGifts2015_RewardItem[3004028][6]["Item"][1]["Id"] = 3002308
	tVipWelfareGifts2015_RewardItem[3004028][6]["Item"][1]["Num"] = 3
	tVipWelfareGifts2015_RewardItem[3004028][6]["Item"][1]["IsTime"] = false
	tVipWelfareGifts2015_RewardItem[3004028][6]["Item"][2] = {}
	tVipWelfareGifts2015_RewardItem[3004028][6]["Item"][2]["Id"] = 3004117
	tVipWelfareGifts2015_RewardItem[3004028][6]["Item"][2]["Num"] = 1
	tVipWelfareGifts2015_RewardItem[3004028][6]["Item"][2]["IsTime"] = true
	
	tVipWelfareGifts2015_RewardItem[3004028][7] = {}
	tVipWelfareGifts2015_RewardItem[3004028][7]["Space"] = 4
	tVipWelfareGifts2015_RewardItem[3004028][7]["Item"] = {}
	tVipWelfareGifts2015_RewardItem[3004028][7]["Item"][1] = {}
	tVipWelfareGifts2015_RewardItem[3004028][7]["Item"][1]["Id"] = 3002308
	tVipWelfareGifts2015_RewardItem[3004028][7]["Item"][1]["Num"] = 4
	tVipWelfareGifts2015_RewardItem[3004028][7]["Item"][1]["IsTime"] = false
	tVipWelfareGifts2015_RewardItem[3004028][7]["Item"][2] = {}
	tVipWelfareGifts2015_RewardItem[3004028][7]["Item"][2]["Id"] = 3004027
	tVipWelfareGifts2015_RewardItem[3004028][7]["Item"][2]["Num"] = 6
	tVipWelfareGifts2015_RewardItem[3004028][7]["Item"][2]["IsTime"] = false
	
	tVipWelfareGifts2015_RewardItem[3004028][8] = {}
	tVipWelfareGifts2015_RewardItem[3004028][8]["Space"] = 4
	tVipWelfareGifts2015_RewardItem[3004028][8]["Item"] = {}
	tVipWelfareGifts2015_RewardItem[3004028][8]["Item"][1] = {}
	tVipWelfareGifts2015_RewardItem[3004028][8]["Item"][1]["Id"] = 3002308
	tVipWelfareGifts2015_RewardItem[3004028][8]["Item"][1]["Num"] = 4
	tVipWelfareGifts2015_RewardItem[3004028][8]["Item"][1]["IsTime"] = false
	tVipWelfareGifts2015_RewardItem[3004028][8]["Item"][2] = {}
	tVipWelfareGifts2015_RewardItem[3004028][8]["Item"][2]["Id"] = 3004117
	tVipWelfareGifts2015_RewardItem[3004028][8]["Item"][2]["Num"] = 1
	tVipWelfareGifts2015_RewardItem[3004028][8]["Item"][2]["IsTime"] = true

	-- VIP夏日蝉鸣礼包
	tVipWelfareGifts2015_RewardItem[3004029] = {}
	tVipWelfareGifts2015_RewardItem[3004029][1] = {}
	tVipWelfareGifts2015_RewardItem[3004029][1]["Space"] = 2
	tVipWelfareGifts2015_RewardItem[3004029][1]["Item"] = {}
	tVipWelfareGifts2015_RewardItem[3004029][1]["Item"][1] = {}
	tVipWelfareGifts2015_RewardItem[3004029][1]["Item"][1]["Id"] = 3002308
	tVipWelfareGifts2015_RewardItem[3004029][1]["Item"][1]["Num"] = 2
	tVipWelfareGifts2015_RewardItem[3004029][1]["Item"][1]["IsTime"] = false
	tVipWelfareGifts2015_RewardItem[3004029][1]["Item"][2] = {}
	tVipWelfareGifts2015_RewardItem[3004029][1]["Item"][2]["Id"] = 3004027
	tVipWelfareGifts2015_RewardItem[3004029][1]["Item"][2]["Num"] = 5
	tVipWelfareGifts2015_RewardItem[3004029][1]["Item"][2]["IsTime"] = false
	
	tVipWelfareGifts2015_RewardItem[3004029][2] = {}
	tVipWelfareGifts2015_RewardItem[3004029][2]["Space"] = 2
	tVipWelfareGifts2015_RewardItem[3004029][2]["Item"] = {}
	tVipWelfareGifts2015_RewardItem[3004029][2]["Item"][1] = {}
	tVipWelfareGifts2015_RewardItem[3004029][2]["Item"][1]["Id"] = 3002308
	tVipWelfareGifts2015_RewardItem[3004029][2]["Item"][1]["Num"] = 2
	tVipWelfareGifts2015_RewardItem[3004029][2]["Item"][1]["IsTime"] = false
	tVipWelfareGifts2015_RewardItem[3004029][2]["Item"][2] = {}
	tVipWelfareGifts2015_RewardItem[3004029][2]["Item"][2]["Id"] = 3004117
	tVipWelfareGifts2015_RewardItem[3004029][2]["Item"][2]["Num"] = 1
	tVipWelfareGifts2015_RewardItem[3004029][2]["Item"][2]["IsTime"] = true
	
	tVipWelfareGifts2015_RewardItem[3004029][3] = {}
	tVipWelfareGifts2015_RewardItem[3004029][3]["Space"] = 3
	tVipWelfareGifts2015_RewardItem[3004029][3]["Item"] = {}
	tVipWelfareGifts2015_RewardItem[3004029][3]["Item"][1] = {}
	tVipWelfareGifts2015_RewardItem[3004029][3]["Item"][1]["Id"] = 3002308
	tVipWelfareGifts2015_RewardItem[3004029][3]["Item"][1]["Num"] = 3
	tVipWelfareGifts2015_RewardItem[3004029][3]["Item"][1]["IsTime"] = false
	tVipWelfareGifts2015_RewardItem[3004029][3]["Item"][2] = {}
	tVipWelfareGifts2015_RewardItem[3004029][3]["Item"][2]["Id"] = 3004027
	tVipWelfareGifts2015_RewardItem[3004029][3]["Item"][2]["Num"] = 6
	tVipWelfareGifts2015_RewardItem[3004029][3]["Item"][2]["IsTime"] = false
	
	tVipWelfareGifts2015_RewardItem[3004029][4] = {}
	tVipWelfareGifts2015_RewardItem[3004029][4]["Space"] = 3
	tVipWelfareGifts2015_RewardItem[3004029][4]["Item"] = {}
	tVipWelfareGifts2015_RewardItem[3004029][4]["Item"][1] = {}
	tVipWelfareGifts2015_RewardItem[3004029][4]["Item"][1]["Id"] = 3002308
	tVipWelfareGifts2015_RewardItem[3004029][4]["Item"][1]["Num"] = 3
	tVipWelfareGifts2015_RewardItem[3004029][4]["Item"][1]["IsTime"] = false
	tVipWelfareGifts2015_RewardItem[3004029][4]["Item"][2] = {}
	tVipWelfareGifts2015_RewardItem[3004029][4]["Item"][2]["Id"] = 3004117
	tVipWelfareGifts2015_RewardItem[3004029][4]["Item"][2]["Num"] = 1
	tVipWelfareGifts2015_RewardItem[3004029][4]["Item"][2]["IsTime"] = true
	
	tVipWelfareGifts2015_RewardItem[3004029][5] = {}
	tVipWelfareGifts2015_RewardItem[3004029][5]["Space"] = 4
	tVipWelfareGifts2015_RewardItem[3004029][5]["Item"] = {}
	tVipWelfareGifts2015_RewardItem[3004029][5]["Item"][1] = {}
	tVipWelfareGifts2015_RewardItem[3004029][5]["Item"][1]["Id"] = 3002308
	tVipWelfareGifts2015_RewardItem[3004029][5]["Item"][1]["Num"] = 4
	tVipWelfareGifts2015_RewardItem[3004029][5]["Item"][1]["IsTime"] = false
	tVipWelfareGifts2015_RewardItem[3004029][5]["Item"][2] = {}
	tVipWelfareGifts2015_RewardItem[3004029][5]["Item"][2]["Id"] = 3004027
	tVipWelfareGifts2015_RewardItem[3004029][5]["Item"][2]["Num"] = 7
	tVipWelfareGifts2015_RewardItem[3004029][5]["Item"][2]["IsTime"] = false
	
	tVipWelfareGifts2015_RewardItem[3004029][6] = {}
	tVipWelfareGifts2015_RewardItem[3004029][6]["Space"] = 4
	tVipWelfareGifts2015_RewardItem[3004029][6]["Item"] = {}
	tVipWelfareGifts2015_RewardItem[3004029][6]["Item"][1] = {}
	tVipWelfareGifts2015_RewardItem[3004029][6]["Item"][1]["Id"] = 3002308
	tVipWelfareGifts2015_RewardItem[3004029][6]["Item"][1]["Num"] = 4
	tVipWelfareGifts2015_RewardItem[3004029][6]["Item"][1]["IsTime"] = false
	tVipWelfareGifts2015_RewardItem[3004029][6]["Item"][2] = {}
	tVipWelfareGifts2015_RewardItem[3004029][6]["Item"][2]["Id"] = 3004117
	tVipWelfareGifts2015_RewardItem[3004029][6]["Item"][2]["Num"] = 1
	tVipWelfareGifts2015_RewardItem[3004029][6]["Item"][2]["IsTime"] = true
	
	tVipWelfareGifts2015_RewardItem[3004029][7] = {}
	tVipWelfareGifts2015_RewardItem[3004029][7]["Space"] = 5
	tVipWelfareGifts2015_RewardItem[3004029][7]["Item"] = {}
	tVipWelfareGifts2015_RewardItem[3004029][7]["Item"][1] = {}
	tVipWelfareGifts2015_RewardItem[3004029][7]["Item"][1]["Id"] = 3002308
	tVipWelfareGifts2015_RewardItem[3004029][7]["Item"][1]["Num"] = 5
	tVipWelfareGifts2015_RewardItem[3004029][7]["Item"][1]["IsTime"] = false
	tVipWelfareGifts2015_RewardItem[3004029][7]["Item"][2] = {}
	tVipWelfareGifts2015_RewardItem[3004029][7]["Item"][2]["Id"] = 3004027
	tVipWelfareGifts2015_RewardItem[3004029][7]["Item"][2]["Num"] = 8
	tVipWelfareGifts2015_RewardItem[3004029][7]["Item"][2]["IsTime"] = false
	
	tVipWelfareGifts2015_RewardItem[3004029][8] = {}
	tVipWelfareGifts2015_RewardItem[3004029][8]["Space"] = 5
	tVipWelfareGifts2015_RewardItem[3004029][8]["Item"] = {}
	tVipWelfareGifts2015_RewardItem[3004029][8]["Item"][1] = {}
	tVipWelfareGifts2015_RewardItem[3004029][8]["Item"][1]["Id"] = 3002308
	tVipWelfareGifts2015_RewardItem[3004029][8]["Item"][1]["Num"] = 5
	tVipWelfareGifts2015_RewardItem[3004029][8]["Item"][1]["IsTime"] = false
	tVipWelfareGifts2015_RewardItem[3004029][8]["Item"][2] = {}
	tVipWelfareGifts2015_RewardItem[3004029][8]["Item"][2]["Id"] = 3004117
	tVipWelfareGifts2015_RewardItem[3004029][8]["Item"][2]["Num"] = 1
	tVipWelfareGifts2015_RewardItem[3004029][8]["Item"][2]["IsTime"] = true

	-- VIP夏日倾情礼包
	tVipWelfareGifts2015_RewardItem[3004030] = {}
	tVipWelfareGifts2015_RewardItem[3004030][1] = {}
	tVipWelfareGifts2015_RewardItem[3004030][1]["Space"] = 3
	tVipWelfareGifts2015_RewardItem[3004030][1]["Item"] = {}
	tVipWelfareGifts2015_RewardItem[3004030][1]["Item"][1] = {}
	tVipWelfareGifts2015_RewardItem[3004030][1]["Item"][1]["Id"] = 3002308
	tVipWelfareGifts2015_RewardItem[3004030][1]["Item"][1]["Num"] = 3
	tVipWelfareGifts2015_RewardItem[3004030][1]["Item"][1]["IsTime"] = false
	tVipWelfareGifts2015_RewardItem[3004030][1]["Item"][2] = {}
	tVipWelfareGifts2015_RewardItem[3004030][1]["Item"][2]["Id"] = 3004027
	tVipWelfareGifts2015_RewardItem[3004030][1]["Item"][2]["Num"] = 7
	tVipWelfareGifts2015_RewardItem[3004030][1]["Item"][2]["IsTime"] = false
	
	tVipWelfareGifts2015_RewardItem[3004030][2] = {}
	tVipWelfareGifts2015_RewardItem[3004030][2]["Space"] = 3
	tVipWelfareGifts2015_RewardItem[3004030][2]["Item"] = {}
	tVipWelfareGifts2015_RewardItem[3004030][2]["Item"][1] = {}
	tVipWelfareGifts2015_RewardItem[3004030][2]["Item"][1]["Id"] = 3002308
	tVipWelfareGifts2015_RewardItem[3004030][2]["Item"][1]["Num"] = 3
	tVipWelfareGifts2015_RewardItem[3004030][2]["Item"][1]["IsTime"] = false
	tVipWelfareGifts2015_RewardItem[3004030][2]["Item"][2] = {}
	tVipWelfareGifts2015_RewardItem[3004030][2]["Item"][2]["Id"] = 3004117
	tVipWelfareGifts2015_RewardItem[3004030][2]["Item"][2]["Num"] = 1
	tVipWelfareGifts2015_RewardItem[3004030][2]["Item"][2]["IsTime"] = true
	
	tVipWelfareGifts2015_RewardItem[3004030][3] = {}
	tVipWelfareGifts2015_RewardItem[3004030][3]["Space"] = 4
	tVipWelfareGifts2015_RewardItem[3004030][3]["Item"] = {}
	tVipWelfareGifts2015_RewardItem[3004030][3]["Item"][1] = {}
	tVipWelfareGifts2015_RewardItem[3004030][3]["Item"][1]["Id"] = 3002308
	tVipWelfareGifts2015_RewardItem[3004030][3]["Item"][1]["Num"] = 4
	tVipWelfareGifts2015_RewardItem[3004030][3]["Item"][1]["IsTime"] = false
	tVipWelfareGifts2015_RewardItem[3004030][3]["Item"][2] = {}
	tVipWelfareGifts2015_RewardItem[3004030][3]["Item"][2]["Id"] = 3004027
	tVipWelfareGifts2015_RewardItem[3004030][3]["Item"][2]["Num"] = 8
	tVipWelfareGifts2015_RewardItem[3004030][3]["Item"][2]["IsTime"] = false
	
	tVipWelfareGifts2015_RewardItem[3004030][4] = {}
	tVipWelfareGifts2015_RewardItem[3004030][4]["Space"] = 4
	tVipWelfareGifts2015_RewardItem[3004030][4]["Item"] = {}
	tVipWelfareGifts2015_RewardItem[3004030][4]["Item"][1] = {}
	tVipWelfareGifts2015_RewardItem[3004030][4]["Item"][1]["Id"] = 3002308
	tVipWelfareGifts2015_RewardItem[3004030][4]["Item"][1]["Num"] = 4
	tVipWelfareGifts2015_RewardItem[3004030][4]["Item"][1]["IsTime"] = false
	tVipWelfareGifts2015_RewardItem[3004030][4]["Item"][2] = {}
	tVipWelfareGifts2015_RewardItem[3004030][4]["Item"][2]["Id"] = 3004117
	tVipWelfareGifts2015_RewardItem[3004030][4]["Item"][2]["Num"] = 1
	tVipWelfareGifts2015_RewardItem[3004030][4]["Item"][2]["IsTime"] = true
	
	tVipWelfareGifts2015_RewardItem[3004030][5] = {}
	tVipWelfareGifts2015_RewardItem[3004030][5]["Space"] = 5
	tVipWelfareGifts2015_RewardItem[3004030][5]["Item"] = {}
	tVipWelfareGifts2015_RewardItem[3004030][5]["Item"][1] = {}
	tVipWelfareGifts2015_RewardItem[3004030][5]["Item"][1]["Id"] = 3002308
	tVipWelfareGifts2015_RewardItem[3004030][5]["Item"][1]["Num"] = 5
	tVipWelfareGifts2015_RewardItem[3004030][5]["Item"][1]["IsTime"] = false
	tVipWelfareGifts2015_RewardItem[3004030][5]["Item"][2] = {}
	tVipWelfareGifts2015_RewardItem[3004030][5]["Item"][2]["Id"] = 3004027
	tVipWelfareGifts2015_RewardItem[3004030][5]["Item"][2]["Num"] = 9
	tVipWelfareGifts2015_RewardItem[3004030][5]["Item"][2]["IsTime"] = false
	
	tVipWelfareGifts2015_RewardItem[3004030][6] = {}
	tVipWelfareGifts2015_RewardItem[3004030][6]["Space"] = 5
	tVipWelfareGifts2015_RewardItem[3004030][6]["Item"] = {}
	tVipWelfareGifts2015_RewardItem[3004030][6]["Item"][1] = {}
	tVipWelfareGifts2015_RewardItem[3004030][6]["Item"][1]["Id"] = 3002308
	tVipWelfareGifts2015_RewardItem[3004030][6]["Item"][1]["Num"] = 5
	tVipWelfareGifts2015_RewardItem[3004030][6]["Item"][1]["IsTime"] = false
	tVipWelfareGifts2015_RewardItem[3004030][6]["Item"][2] = {}
	tVipWelfareGifts2015_RewardItem[3004030][6]["Item"][2]["Id"] = 3004117
	tVipWelfareGifts2015_RewardItem[3004030][6]["Item"][2]["Num"] = 1
	tVipWelfareGifts2015_RewardItem[3004030][6]["Item"][2]["IsTime"] = true
	
	tVipWelfareGifts2015_RewardItem[3004030][7] = {}
	tVipWelfareGifts2015_RewardItem[3004030][7]["Space"] = 6
	tVipWelfareGifts2015_RewardItem[3004030][7]["Item"] = {}
	tVipWelfareGifts2015_RewardItem[3004030][7]["Item"][1] = {}
	tVipWelfareGifts2015_RewardItem[3004030][7]["Item"][1]["Id"] = 3002308
	tVipWelfareGifts2015_RewardItem[3004030][7]["Item"][1]["Num"] = 6
	tVipWelfareGifts2015_RewardItem[3004030][7]["Item"][1]["IsTime"] = false
	tVipWelfareGifts2015_RewardItem[3004030][7]["Item"][2] = {}
	tVipWelfareGifts2015_RewardItem[3004030][7]["Item"][2]["Id"] = 3004027
	tVipWelfareGifts2015_RewardItem[3004030][7]["Item"][2]["Num"] = 10
	tVipWelfareGifts2015_RewardItem[3004030][7]["Item"][2]["IsTime"] = false
	
	tVipWelfareGifts2015_RewardItem[3004030][8] = {}
	tVipWelfareGifts2015_RewardItem[3004030][8]["Space"] = 6
	tVipWelfareGifts2015_RewardItem[3004030][8]["Item"] = {}
	tVipWelfareGifts2015_RewardItem[3004030][8]["Item"][1] = {}
	tVipWelfareGifts2015_RewardItem[3004030][8]["Item"][1]["Id"] = 3002308
	tVipWelfareGifts2015_RewardItem[3004030][8]["Item"][1]["Num"] = 6
	tVipWelfareGifts2015_RewardItem[3004030][8]["Item"][1]["IsTime"] = false
	tVipWelfareGifts2015_RewardItem[3004030][8]["Item"][2] = {}
	tVipWelfareGifts2015_RewardItem[3004030][8]["Item"][2]["Id"] = 3004117
	tVipWelfareGifts2015_RewardItem[3004030][8]["Item"][2]["Num"] = 1
	tVipWelfareGifts2015_RewardItem[3004030][8]["Item"][2]["IsTime"] = true

-- 清心符
local tVipWelfareGifts2015_Heart = {}
	tVipWelfareGifts2015_Heart[1] = {}
	tVipWelfareGifts2015_Heart[1]["ItemChanceSum"] = 10000
	
	tVipWelfareGifts2015_Heart[1][1] = {}
	tVipWelfareGifts2015_Heart[1][1]["RandomItemChanceType"] = 2
	tVipWelfareGifts2015_Heart[1][1]["ItemChance"] = 3700
	tVipWelfareGifts2015_Heart[1][1]["Item_1"] = 2
	tVipWelfareGifts2015_Heart[1][1]["ItemIndex"] = 1
	tVipWelfareGifts2015_Heart[1][1]["Log"] = "0,0,3004032,1,12000086,2,720128,2"	
	
	tVipWelfareGifts2015_Heart[1][2] = {}
	tVipWelfareGifts2015_Heart[1][2]["RandomItemChanceType"] = 2
	tVipWelfareGifts2015_Heart[1][2]["ItemChance"] = 4000
	tVipWelfareGifts2015_Heart[1][2]["Item_1"] = 3
	tVipWelfareGifts2015_Heart[1][2]["ItemIndex"] = 2
	tVipWelfareGifts2015_Heart[1][2]["Log"] = "0,0,3004032,1,12000086,2,720128,3"	
	
	tVipWelfareGifts2015_Heart[1][3] = {}
	tVipWelfareGifts2015_Heart[1][3]["RandomItemChanceType"] = 2
	tVipWelfareGifts2015_Heart[1][3]["ItemChance"] = 1000
	tVipWelfareGifts2015_Heart[1][3]["Item_1"] = 4
	tVipWelfareGifts2015_Heart[1][3]["ItemIndex"] = 3
	tVipWelfareGifts2015_Heart[1][3]["Log"] = "0,0,3004032,1,12000086,2,720128,4"	
	
	tVipWelfareGifts2015_Heart[1][4] = {}
	tVipWelfareGifts2015_Heart[1][4]["RandomItemChanceType"] = 2
	tVipWelfareGifts2015_Heart[1][4]["ItemChance"] = 700
	tVipWelfareGifts2015_Heart[1][4]["Item_1"] = 5
	tVipWelfareGifts2015_Heart[1][4]["ItemIndex"] = 4
	tVipWelfareGifts2015_Heart[1][4]["Log"] = "0,0,3004032,1,12000086,2,720128,5"	
	
	tVipWelfareGifts2015_Heart[1][5] = {}
	tVipWelfareGifts2015_Heart[1][5]["RandomItemChanceType"] = 2
	tVipWelfareGifts2015_Heart[1][5]["ItemChance"] = 500
	tVipWelfareGifts2015_Heart[1][5]["Item_1"] = 6
	tVipWelfareGifts2015_Heart[1][5]["ItemIndex"] = 5
	tVipWelfareGifts2015_Heart[1][5]["Log"] = "0,0,3004032,1,12000086,2,720128,6"	
	
	tVipWelfareGifts2015_Heart[1][6] = {}
	tVipWelfareGifts2015_Heart[1][6]["RandomItemChanceType"] = 2
	tVipWelfareGifts2015_Heart[1][6]["ItemChance"] = 75
	tVipWelfareGifts2015_Heart[1][6]["Item_1"] = 7
	tVipWelfareGifts2015_Heart[1][6]["ItemIndex"] = 6
	tVipWelfareGifts2015_Heart[1][6]["Log"] = "0,0,3004032,1,12000086,2,720128,7"	
	
	tVipWelfareGifts2015_Heart[1][7] = {}
	tVipWelfareGifts2015_Heart[1][7]["RandomItemChanceType"] = 2
	tVipWelfareGifts2015_Heart[1][7]["ItemChance"] = 20
	tVipWelfareGifts2015_Heart[1][7]["Item_1"] = 8
	tVipWelfareGifts2015_Heart[1][7]["ItemIndex"] = 7
	tVipWelfareGifts2015_Heart[1][7]["Log"] = "0,0,3004032,1,12000086,2,720128,8"	
	
	tVipWelfareGifts2015_Heart[1][8] = {}
	tVipWelfareGifts2015_Heart[1][8]["RandomItemChanceType"] = 2
	tVipWelfareGifts2015_Heart[1][8]["ItemChance"] = 4
	tVipWelfareGifts2015_Heart[1][8]["Item_1"] = 9
	tVipWelfareGifts2015_Heart[1][8]["ItemIndex"] = 8
	tVipWelfareGifts2015_Heart[1][8]["Log"] = "0,0,3004032,1,12000086,2,720128,9"	
	
	tVipWelfareGifts2015_Heart[1][9] = {}
	tVipWelfareGifts2015_Heart[1][9]["RandomItemChanceType"] = 2
	tVipWelfareGifts2015_Heart[1][9]["ItemChance"] = 1
	tVipWelfareGifts2015_Heart[1][9]["Item_1"] = 10
	tVipWelfareGifts2015_Heart[1][9]["ItemIndex"] = 9
	tVipWelfareGifts2015_Heart[1][9]["Log"] = "0,0,3004032,1,12000086,2,720128,10"	

-- VIP行走江湖礼包
local tVipWelfareGifts2015_WalkDead = {}	
	-- 60分钟经验
	tVipWelfareGifts2015_WalkDead[1] = {}
	tVipWelfareGifts2015_WalkDead[1]["Exp"] = 60
	tVipWelfareGifts2015_WalkDead[1]["Log"] = "0,0,3004117,1,12000086,2,4,60"
	-- 30点修行值
	tVipWelfareGifts2015_WalkDead[2] = {}
	tVipWelfareGifts2015_WalkDead[2]["Cultivation"] = 30
	tVipWelfareGifts2015_WalkDead[2]["Log"] = "0,0,3004117,1,12000086,2,6,30"
	-- 120分钟经验
	tVipWelfareGifts2015_WalkDead[3] = {}
	tVipWelfareGifts2015_WalkDead[3]["Exp"] = 120
	tVipWelfareGifts2015_WalkDead[3]["Log"] = "0,0,3004117,1,12000086,2,4,120"
	-- 100点修行值
	tVipWelfareGifts2015_WalkDead[4] = {}
	tVipWelfareGifts2015_WalkDead[4]["Cultivation"] = 100
	tVipWelfareGifts2015_WalkDead[4]["Log"] = "0,0,3004117,1,12000086,2,6,100"
	-- 200分钟经验
	tVipWelfareGifts2015_WalkDead[5] = {}
	tVipWelfareGifts2015_WalkDead[5]["Exp"] = 200
	tVipWelfareGifts2015_WalkDead[5]["Log"] = "0,0,3004117,1,12000086,2,4,200"
	-- 150点修行值
	tVipWelfareGifts2015_WalkDead[6] = {}
	tVipWelfareGifts2015_WalkDead[6]["Cultivation"] = 150
	tVipWelfareGifts2015_WalkDead[6]["Log"] = "0,0,3004117,1,12000086,2,6,150"
	-- 320分钟经验
	tVipWelfareGifts2015_WalkDead[7] = {}
	tVipWelfareGifts2015_WalkDead[7]["Exp"] = 320
	tVipWelfareGifts2015_WalkDead[7]["Log"] = "0,0,3004117,1,12000086,2,4,320"
	-- 220点修行值
	tVipWelfareGifts2015_WalkDead[8] = {}
	tVipWelfareGifts2015_WalkDead[8]["Cultivation"] = 220
	tVipWelfareGifts2015_WalkDead[8]["Log"] = "0,0,3004117,1,12000086,2,6,220"
	
-- log
local tVipWelfareGifts2015_Log = {}	
	tVipWelfareGifts2015_Log["Sign"] = {}
	tVipWelfareGifts2015_Log["Sign"][1] = "0,0,0,0,12000086,1[1],3002308[3004027],1[1]"
	tVipWelfareGifts2015_Log["Sign"][2] = "0,0,0,0,12000086,1[1],3002308[3004117],1[1]"
	tVipWelfareGifts2015_Log["Sign"][3] = "0,0,0,0,12000086,1[2],3002308[3004027][3004028],1[1][1]"
	tVipWelfareGifts2015_Log["Sign"][4] = "0,0,0,0,12000086,1[2],3002308[3004117][3004028],1[1][1]"
	tVipWelfareGifts2015_Log["Sign"][5] = "0,0,0,0,12000086,1[3],3002308[3004027][3004029],1[1][1]"
	tVipWelfareGifts2015_Log["Sign"][6] = "0,0,0,0,12000086,1[3],3002308[3004117][3004029],1[1][1]"
	tVipWelfareGifts2015_Log["Sign"][7] = "0,0,0,0,12000086,1[4],3002308[3004027][3004030],1[1][1]"
	tVipWelfareGifts2015_Log["Sign"][8] = "0,0,0,0,12000086,1[4],3002308[3004117][3004030],1[1][1]"
	
	tVipWelfareGifts2015_Log["Welfare"] = {}
	tVipWelfareGifts2015_Log["Welfare"][1] = "0,0,0,0,12000086,2,3004031[3004032][6][7][12],1[1][50][10800][100]"
	tVipWelfareGifts2015_Log["Welfare"][2] = "0,0,0,0,12000086,2,3004032[6][7][12],1[50][10800][100]"
	tVipWelfareGifts2015_Log["Welfare"][3] = "0,0,0,0,12000086,2,3004031[3004032][6][7][12],2[2][100][14400][300]"
	tVipWelfareGifts2015_Log["Welfare"][4] = "0,0,0,0,12000086,2,3004032[6][7][12],2[100][14400][300]"
	tVipWelfareGifts2015_Log["Welfare"][5] = "0,0,0,0,12000086,2,3004031[3004032][6][7][12],3[3][150][18000][400]"
	tVipWelfareGifts2015_Log["Welfare"][6] = "0,0,0,0,12000086,2,3004032[6][7][12],3[150][18000][400]"
	tVipWelfareGifts2015_Log["Welfare"][7] = "0,0,0,0,12000086,2,3004031[3004032][6][7][12],4[4][200][21600][500]"
	tVipWelfareGifts2015_Log["Welfare"][8] = "0,0,0,0,12000086,2,3004032[6][7][12],4[200][21600][500]"

	tVipWelfareGifts2015_Log[3004027] = "0,0,3004027,1,12000086,2,16,2"
	
	tVipWelfareGifts2015_Log[3004028] = {}
	tVipWelfareGifts2015_Log[3004028][1] = "0,0,3004028,1,12000086,2,3002308[3004027],1[3]"
	tVipWelfareGifts2015_Log[3004028][2] = "0,0,3004028,1,12000086,2,3002308[3004117],1[1]"
	tVipWelfareGifts2015_Log[3004028][3] = "0,0,3004028,1,12000086,2,3002308[3004027],2[4]"
	tVipWelfareGifts2015_Log[3004028][4] = "0,0,3004028,1,12000086,2,3002308[3004117],2[1]"
	tVipWelfareGifts2015_Log[3004028][5] = "0,0,3004028,1,12000086,2,3002308[3004027],3[5]"
	tVipWelfareGifts2015_Log[3004028][6] = "0,0,3004028,1,12000086,2,3002308[3004117],3[1]"
	tVipWelfareGifts2015_Log[3004028][7] = "0,0,3004028,1,12000086,2,3002308[3004027],4[6]"
	tVipWelfareGifts2015_Log[3004028][8] = "0,0,3004028,1,12000086,2,3002308[3004117],4[1]"

	tVipWelfareGifts2015_Log[3004028] = {}
	tVipWelfareGifts2015_Log[3004028][1] = "0,0,3004028,1,12000086,2,3002308[3004027],1[3]"
	tVipWelfareGifts2015_Log[3004028][2] = "0,0,3004028,1,12000086,2,3002308[3004117],1[1]"
	tVipWelfareGifts2015_Log[3004028][3] = "0,0,3004028,1,12000086,2,3002308[3004027],2[4]"
	tVipWelfareGifts2015_Log[3004028][4] = "0,0,3004028,1,12000086,2,3002308[3004117],2[1]"
	tVipWelfareGifts2015_Log[3004028][5] = "0,0,3004028,1,12000086,2,3002308[3004027],3[5]"
	tVipWelfareGifts2015_Log[3004028][6] = "0,0,3004028,1,12000086,2,3002308[3004117],3[1]"
	tVipWelfareGifts2015_Log[3004028][7] = "0,0,3004028,1,12000086,2,3002308[3004027],4[6]"
	tVipWelfareGifts2015_Log[3004028][8] = "0,0,3004028,1,12000086,2,3002308[3004117],4[1]"

	tVipWelfareGifts2015_Log[3004029] = {}
	tVipWelfareGifts2015_Log[3004029][1] = "0,0,3004029,1,12000086,2,3002308[3004027],2[5]"
	tVipWelfareGifts2015_Log[3004029][2] = "0,0,3004029,1,12000086,2,3002308[3004117],2[1]"
	tVipWelfareGifts2015_Log[3004029][3] = "0,0,3004029,1,12000086,2,3002308[3004027],3[6]"
	tVipWelfareGifts2015_Log[3004029][4] = "0,0,3004029,1,12000086,2,3002308[3004117],3[1]"
	tVipWelfareGifts2015_Log[3004029][5] = "0,0,3004029,1,12000086,2,3002308[3004027],4[7]"
	tVipWelfareGifts2015_Log[3004029][6] = "0,0,3004029,1,12000086,2,3002308[3004117],4[1]"
	tVipWelfareGifts2015_Log[3004029][7] = "0,0,3004029,1,12000086,2,3002308[3004027],5[8]"
	tVipWelfareGifts2015_Log[3004029][8] = "0,0,3004029,1,12000086,2,3002308[3004117],5[1]"

	tVipWelfareGifts2015_Log[3004030] = {}
	tVipWelfareGifts2015_Log[3004030][1] = "0,0,3004030,1,12000086,2,3002308[3004027],3[7]"
	tVipWelfareGifts2015_Log[3004030][2] = "0,0,3004030,1,12000086,2,3002308[3004117],3[1]"
	tVipWelfareGifts2015_Log[3004030][3] = "0,0,3004030,1,12000086,2,3002308[3004027],4[8]"
	tVipWelfareGifts2015_Log[3004030][4] = "0,0,3004030,1,12000086,2,3002308[3004117],4[1]"
	tVipWelfareGifts2015_Log[3004030][5] = "0,0,3004030,1,12000086,2,3002308[3004027],5[9]"
	tVipWelfareGifts2015_Log[3004030][6] = "0,0,3004030,1,12000086,2,3002308[3004117],5[1]"
	tVipWelfareGifts2015_Log[3004030][7] = "0,0,3004030,1,12000086,2,3002308[3004027],6[10]"
	tVipWelfareGifts2015_Log[3004030][8] = "0,0,3004030,1,12000086,2,3002308[3004117],6[1]"

	tVipWelfareGifts2015_Log[3004031] = "0,0,3004031,1,12000086,2,17,3"
	
--------------------------------------逻辑部分-----------------------------------------
-- 今日签到。
function VipWelfareGifts2015_Sign(nNpcId)
	-- 判断时间
	if not Sys_ChkFullTime(tVipWelfareGifts2015_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	local nVip = Get_UserVip()
	
	-- 判断是否是VIP玩家
	if nVip <= 0 then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	local nEventType = tVipWelfareGifts2015_Stc["EventType"]
	local nDataType = tVipWelfareGifts2015_Stc[1]["DataType"]
	local nCountData = tVipWelfareGifts2015_Stc[2]["DataType"]
	
	-- 判断当天是否签到过
	if not Task_StcInterval(nEventType,nDataType,1,4) then
		if Task_ChkStcValue(nEventType,nDataType,">=",tVipWelfareGifts2015_Constant["CompleteData"]) then
			LinkNpcGossipFunc_New(nNpcId,"2-2")
			return
		end
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(tVipWelfareGifts2015_Constant["SignItemSpace"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end
	
	-- 判断是否是连续签到
	if Task_StcInterval(nEventType,nDataType,2,4) then
		Task_SetStatistic(nEventType,nCountData,0,1)
	end
	
	-- 设掩码值
	Task_SetStatistic(nEventType,nDataType,tVipWelfareGifts2015_Constant["CompleteData"],1)
	Task_SetStcTimestamp(nEventType,nDataType,0)
	
	-- 签到次数+1
	Task_AddStatistic(nEventType,nCountData,1,1)
	Task_SetStcTimestamp(nEventType,nCountData,0)
	
	local nTime = 1
	-- 判断签到天数
	if Task_ChkStcValue(nEventType,nCountData,"==",tVipWelfareGifts2015_Constant["MinTime"]) then
		nTime = tVipWelfareGifts2015_Constant["MinTime"]
	elseif Task_ChkStcValue(nEventType,nCountData,"==",tVipWelfareGifts2015_Constant["MidTime"]) then
		nTime = tVipWelfareGifts2015_Constant["MidTime"]
	elseif Task_ChkStcValue(nEventType,nCountData,"==",tVipWelfareGifts2015_Constant["MaxTime"]) then
		nTime = tVipWelfareGifts2015_Constant["MaxTime"]
	end

	local nUserId = Get_UserId()
	-- 判断玩家是否开启自创武功
	if not User_IsAlreadyCreateGongFu(nUserId) then
		nTime = nTime + 1
	end

	for nIndex = 1,#tVipWelfareGifts2015_Sign[nTime] do
		local nItemId = tVipWelfareGifts2015_Sign[nTime][nIndex]["ItemId"]
		
		if tVipWelfareGifts2015_Sign[nTime][nIndex]["IsTime"] then
			Item_AddItem(nItemId,0,1,0,tVipWelfareGifts2015_Constant["SaveTime"],1)
		else
			Item_AddItem(nItemId)
		end
	end
	
	-- 打log
	Sys_SaveActionFestivalLog(tVipWelfareGifts2015_Log["Sign"][nTime])
	
	-- 提示
	Sys_MsgBox(tVipWelfareGifts2015_Text["RewardItem"][nTime])
end

-- 领取今日福利
function VipWelfareGifts2015_Welfare(nNpcId)
	-- 判断时间
	if not Sys_ChkFullTime(tVipWelfareGifts2015_Constant["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	local nVip = Get_UserVip()
	
	-- 判断是否是VIP玩家
	if nVip <= 0 then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	local nEventType = tVipWelfareGifts2015_Stc["EventType"]
	local nDataType = tVipWelfareGifts2015_Stc[3]["DataType"]
	
	-- 判断是否隔天
	if not Task_StcInterval(nEventType,nDataType,1,4) then
		if Task_ChkStcValue(nEventType,nDataType,">=",1) then
			LinkNpcGossipFunc_New(nNpcId,"3-1")
			return
		end
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(tVipWelfareGifts2015_Constant["WelfareSpace"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end
	
	-- 设掩码值
	Task_SetStatistic(nEventType,nDataType,1,1)
	Task_SetStcTimestamp(nEventType,nDataType,0)
	
	local nTime = 1

	if nVip == tVipWelfareGifts2015_Constant["MidVip"] then
		nTime = tVipWelfareGifts2015_Constant["MinTime"]
	elseif nVip == tVipWelfareGifts2015_Constant["MaxVip"] then
		nTime = tVipWelfareGifts2015_Constant["MidTime"]
	elseif nVip > tVipWelfareGifts2015_Constant["MinVip"] then
		nTime = tVipWelfareGifts2015_Constant["MaxTime"]
	end

	local nUserId = Get_UserId()
	-- 判断玩家是否开启自创武功
	if not User_IsAlreadyCreateGongFu(nUserId) then
		nTime = nTime + 1
	end

	-- 给奖励
	for nIndex = 1,#tVipWelfareGifts2015_Welfare[nTime]["Item"] do
		local nItemId = tVipWelfareGifts2015_Welfare[nTime]["Item"][nIndex]["Id"]
		local nItemNum = tVipWelfareGifts2015_Welfare[nTime]["Item"][nIndex]["Num"]
		
		Item_AddItem(nItemId,0,nItemNum)
	end
	
	-- 加气力值
	User_AddStrengthValue(tVipWelfareGifts2015_Welfare[nTime]["Strengthvalue"])
	-- 加修为值
	User_AddCultivation(tVipWelfareGifts2015_Welfare[nTime]["Cultivation"])
	-- 加经验
	User_SetExpControl(tVipWelfareGifts2015_Welfare[nTime]["Percent"],tVipWelfareGifts2015_Welfare[nTime]["Time"])
	-- 打log
	Sys_SaveActionFestivalLog(tVipWelfareGifts2015_Log["Welfare"][nTime])
	-- 提示
	Sys_MsgBox(tVipWelfareGifts2015_Text["Welfare"][nTime])
end

-- 物品过期删除
function VipWelfareGifts2015_BeOverdue(nItemId)
	-- 判断是否在使用时间
	if not Sys_ChkFullTime(tVipWelfareGifts2015_Constant["UseItemTime"]) then
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			Sys_MsgBox(tVipWelfareGifts2015_Text[nItemId]["BeOverdue"])
		end
		
		return true
	end
	
	return false
end

-- 物品使用
function VipWelfareGifts2015_UseItem(nItemId)
	-- 判断物品是否过期
	if VipWelfareGifts2015_BeOverdue(nItemId) then
		return
	end

	local nVip = Get_UserVip()
	local nTime = 1
	
	-- 判断玩家VIP等级
	if nVip == tVipWelfareGifts2015_Constant["MidVip"] then
		nTime = tVipWelfareGifts2015_Constant["MinTime"]
	elseif nVip == tVipWelfareGifts2015_Constant["MaxVip"] then
		nTime = tVipWelfareGifts2015_Constant["MidTime"]
	elseif nVip > tVipWelfareGifts2015_Constant["MinVip"] then
		nTime = tVipWelfareGifts2015_Constant["MaxTime"]
	end

	-- 判断玩家是否开启自创武功
	local nUserId = Get_UserId()
	if not User_IsAlreadyCreateGongFu(nUserId) then
		nTime = nTime + 1
	end

	local nSpace = tVipWelfareGifts2015_RewardItem[nItemId][nTime]["Space"]
	
	-- 判断背包空间
	if not User_CheckLeftSpace(nSpace) then
		Sys_MsgBox(tVipWelfareGifts2015_Text[nItemId]["Full"])
		return
	end
	
	-- 删除礼包
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		-- 给奖励
		for nIndex = 1,#tVipWelfareGifts2015_RewardItem[nItemId][nTime]["Item"] do
			local nAddItemId = tVipWelfareGifts2015_RewardItem[nItemId][nTime]["Item"][nIndex]["Id"]
			local nItemNum = tVipWelfareGifts2015_RewardItem[nItemId][nTime]["Item"][nIndex]["Num"]
			
			if tVipWelfareGifts2015_RewardItem[nItemId][nTime]["Item"][nIndex]["IsTime"] then
				Item_AddItem(nAddItemId,0,nItemNum,0,tVipWelfareGifts2015_Constant["SaveTime"],1)
			else
				Item_AddItem(nAddItemId,0,nItemNum)
			end
		end

		-- 打log
		Sys_SaveActionFestivalLog(tVipWelfareGifts2015_Log[nItemId][nTime])
		-- 给提示
		Sys_MsgBox(tVipWelfareGifts2015_Text[nItemId]["Msg"][nTime])
	end
end

-- 礼包打开对白
function VipWelfareGifts2015_UseItemText(nItemId,sIndex)
	-- 判断物品是否过期
	if VipWelfareGifts2015_BeOverdue(nItemId) then
		return
	end

	LinkItemGossipFunc_New(nItemId,sIndex)
end

-- 打开清心符礼包
function VipWelfareGifts2015_UseHeartPackage(nItemId)
	-- 判断物品是否过期
	if VipWelfareGifts2015_BeOverdue(nItemId) then
		return
	end
	
	local nEmoneyNum = Get_UserEMoney()
	
	-- 判断玩家天石数量
	if nEmoneyNum < tVipWelfareGifts2015_Constant["Emoney"] then
		LinkItemGossipFunc_New(nItemId,"1-3")
		return
	end
	
	-- 判断玩家背包空间
	if not User_CheckLeftSpace(tVipWelfareGifts2015_Constant["HeartSpace"]) then
		LinkItemGossipFunc_New(nItemId,"1-4")
		return
	end
	
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		-- 扣天石
		User_AddEMoney(-tVipWelfareGifts2015_Constant["Emoney"])
		
		local nFlat,tAward = Probabil_RandomAward(tVipWelfareGifts2015_Heart,1)
		local nItemNum = tAward[1]["tAward"][1]["Item_1"]
		local nItemIndex = tAward[1]["tAward"][1]["ItemIndex"]
		local sLog = tAward[1]["tAward"][1]["Log"]
		
		-- 添加物品
		local sAttr = string.format("0 %d %d 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 %d",nItemNum,3,3)
		Item_AddNewItem(tVipWelfareGifts2015_Constant["HeartItem"],sAttr)
		-- 打log
		Sys_SaveActionFestivalLog(sLog)
		-- 给提示
		Sys_MsgBox(tVipWelfareGifts2015_Text[nItemId]["Msg"][nItemIndex])
	end
end

-- VIP行走江湖礼包
function VipWelfareGifts2015_UseWalkDead(nItemId,nIndex)
	-- 判断物品是否过期
	if VipWelfareGifts2015_BeOverdue(nItemId) then
		return
	end
	
	-- 检测物品是否存在
	if not Item_ChkItem(nItemId) then
		Sys_MsgBox(tVipWelfareGifts2015_Text[nItemId]["NoItem"])
		return
	end
	
	if Item_DelItem(nItemId) then
		-- 加经验
		if tVipWelfareGifts2015_WalkDead[nIndex]["Exp"] ~= nil then
			local nLev = Get_UserLevel()
			
			if nLev < 140 then
				User_AddExpTime(tVipWelfareGifts2015_WalkDead[nIndex]["Exp"])
			end
		end
		
		-- 加修行值
		if tVipWelfareGifts2015_WalkDead[nIndex]["Cultivation"] ~= nil then
			User_AddCultivation(tVipWelfareGifts2015_WalkDead[nIndex]["Cultivation"])
		end
		
		-- 打log
		Sys_SaveActionFestivalLog(tVipWelfareGifts2015_WalkDead[nIndex]["Log"])
		-- 给提示
		Sys_MsgBox(tVipWelfareGifts2015_Text[nItemId]["Msg"][nIndex])
	end
end

--------------------------------------NPC模块-------------------------------------------
-- VIP福利宝贝狐
-- tNpcFace[3057] = 64
tNpcGossip[18466] = tNpcGossip[18466] or DefaultNpc:new{}
tNpcGossip[18466]["OptionHidden"] = 1

-- 活动前对白
tNpcGossip[18466]["Text1-1"] = {111,112,113}
tNpcGossip[18466]["Text111"] = tVipWelfareGifts2015_Text[18466]["111"]
tNpcGossip[18466]["Text112"] = tVipWelfareGifts2015_Text[18466]["112"]
tNpcGossip[18466]["Text113"] = tVipWelfareGifts2015_Text[18466]["113"]
tNpcGossip[18466]["tOption1-1"] = {1}
tNpcGossip[18466]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tVipWelfareGifts2015_Constant["BeforeActivityTime"])
end

-- 活动中对白
tNpcGossip[18466]["Text1-2"] = {121,122,123}
tNpcGossip[18466]["Text121"] = tVipWelfareGifts2015_Text[18466]["121"]
tNpcGossip[18466]["Text122"] = tVipWelfareGifts2015_Text[18466]["122"]
tNpcGossip[18466]["Text123"] = tVipWelfareGifts2015_Text[18466]["123"]
tNpcGossip[18466]["tOption1-2"] = {2,3,4,5}
tNpcGossip[18466]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tVipWelfareGifts2015_Constant["ActivityTime"])
end

-- 活动后对白
tNpcGossip[18466]["Text1-3"] = {131,132,133}
tNpcGossip[18466]["Text131"] = tVipWelfareGifts2015_Text[18466]["131"]
tNpcGossip[18466]["Text132"] = tVipWelfareGifts2015_Text[18466]["132"]
tNpcGossip[18466]["Text133"] = tVipWelfareGifts2015_Text[18466]["133"]
tNpcGossip[18466]["tOption1-3"] = {6}

-- 非VIP
tNpcGossip[18466]["Text2-1"] = {211,212}
tNpcGossip[18466]["Text211"] = tVipWelfareGifts2015_Text[18466]["211"]
tNpcGossip[18466]["Text212"] = tVipWelfareGifts2015_Text[18466]["212"]
tNpcGossip[18466]["tOption2-1"] = {7}

-- 签到过
tNpcGossip[18466]["Text2-2"] = {221}
tNpcGossip[18466]["Text221"] = tVipWelfareGifts2015_Text[18466]["221"]
tNpcGossip[18466]["tOption2-2"] = {8}

-- 背包满
tNpcGossip[18466]["Text2-3"] = {231}
tNpcGossip[18466]["Text231"] = tVipWelfareGifts2015_Text[18466]["231"]
tNpcGossip[18466]["tOption2-3"] = {9}

-- 领取今日福利
tNpcGossip[18466]["Text3-1"] = {311}
tNpcGossip[18466]["Text311"] = tVipWelfareGifts2015_Text[18466]["311"]
tNpcGossip[18466]["tOption3-1"] = {10}

-- 了解活动详情
tNpcGossip[18466]["Text4-1"] = {411,412,413}
tNpcGossip[18466]["Text411"] = tVipWelfareGifts2015_Text[18466]["411"]
tNpcGossip[18466]["Text412"] = tVipWelfareGifts2015_Text[18466]["412"]
tNpcGossip[18466]["Text413"] = tVipWelfareGifts2015_Text[18466]["413"]
tNpcGossip[18466]["tOption4-1"] = {11,12,13}

tNpcGossip[18466]["Text5-1"] = {511,512,513,514}
tNpcGossip[18466]["Text511"] = tVipWelfareGifts2015_Text[18466]["511"]
tNpcGossip[18466]["Text512"] = tVipWelfareGifts2015_Text[18466]["512"]
tNpcGossip[18466]["Text513"] = tVipWelfareGifts2015_Text[18466]["513"]
tNpcGossip[18466]["Text514"] = tVipWelfareGifts2015_Text[18466]["514"]
tNpcGossip[18466]["tOption5-1"] = {14,15}

tNpcGossip[18466]["Option1"] = tVipWelfareGifts2015_Text[18466]["Option1"]
tNpcGossip[18466]["Option2"] = tVipWelfareGifts2015_Text[18466]["Option2"]
tNpcGossip[18466]["OptionFunc2"]="VipWelfareGifts2015_Sign</N>18466"
tNpcGossip[18466]["Option3"] = tVipWelfareGifts2015_Text[18466]["Option3"]
tNpcGossip[18466]["OptionFunc3"]="VipWelfareGifts2015_Welfare</N>18466"
tNpcGossip[18466]["Option4"] = tVipWelfareGifts2015_Text[18466]["Option4"]
tNpcGossip[18466]["OptionPoint4"]="4"
tNpcGossip[18466]["Option5"] = tVipWelfareGifts2015_Text[18466]["Option5"]
tNpcGossip[18466]["Option6"] = tVipWelfareGifts2015_Text[18466]["Option6"]
tNpcGossip[18466]["Option7"] = tVipWelfareGifts2015_Text[18466]["Option7"]
tNpcGossip[18466]["Option8"] = tVipWelfareGifts2015_Text[18466]["Option8"]
tNpcGossip[18466]["Option9"] = tVipWelfareGifts2015_Text[18466]["Option9"]
tNpcGossip[18466]["Option10"] = tVipWelfareGifts2015_Text[18466]["Option10"]
tNpcGossip[18466]["Option11"] = tVipWelfareGifts2015_Text[18466]["Option11"]
tNpcGossip[18466]["OptionPoint11"]="5"
tNpcGossip[18466]["Option12"] = tVipWelfareGifts2015_Text[18466]["Option12"]
tNpcGossip[18466]["OptionPoint12"]="1"
tNpcGossip[18466]["Option13"] = tVipWelfareGifts2015_Text[18466]["Option13"]
tNpcGossip[18466]["Option14"] = tVipWelfareGifts2015_Text[18466]["Option14"]
tNpcGossip[18466]["OptionPoint14"]="4"
tNpcGossip[18466]["Option15"] = tVipWelfareGifts2015_Text[18466]["Option15"]

-- VIP真气礼包
tItem[3004027] = tItem[3004027] or {}
tItem[3004027]["Function"] = function(nItemId,sItemName)
	-- 判断物品是否过期
	if VipWelfareGifts2015_BeOverdue(nItemId) then
		return
	end

	local nQenuineqi = Get_UserGongFuQiLev()
	
	-- 判断真气是否满
	if nQenuineqi >= 4 then
		Sys_MsgBox(tVipWelfareGifts2015_Text[nItemId]["Full"])
		return
	end
	
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		User_AddGongFuQiLeve(2)
		Sys_SaveActionFestivalLog(tVipWelfareGifts2015_Log[nItemId])
		Sys_MsgBox(tVipWelfareGifts2015_Text[nItemId]["Msg"])
	end
end

-- VIP夏日炎炎礼包
tItem[3004028] = tItem[3004028] or {}
tItem[3004028]["Function"] = function(nItemId,sItemName)
	VipWelfareGifts2015_UseItem(nItemId)
end

-- VIP夏日蝉鸣礼包
tItem[3004029] = tItem[3004029] or {}
tItem[3004029]["Function"] = function(nItemId,sItemName)
	VipWelfareGifts2015_UseItem(nItemId)
end

-- VIP夏日倾情礼包
tItem[3004030] = tItem[3004030] or {}
tItem[3004030]["Function"] = function(nItemId,sItemName)
	VipWelfareGifts2015_UseItem(nItemId)
end

-- VIP修炼礼包
tItem[3004031] = tItem[3004031] or {}
tItem[3004031]["Function"] = function(nItemId,sItemName)
	-- 判断物品是否过期
	if VipWelfareGifts2015_BeOverdue(nItemId) then
		return
	end

	local nQenuineqi = Get_UserGongFureePractNum()
	
	-- 判断免费修炼次数
	if nQenuineqi >= 970000 then
		Sys_MsgBox(tVipWelfareGifts2015_Text[nItemId]["Full"])
		return
	end
	
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		User_AddGongFuFreePractNum(30000)
		Sys_SaveActionFestivalLog(tVipWelfareGifts2015_Log[nItemId])
		Sys_MsgBox(tVipWelfareGifts2015_Text[nItemId]["Msg"])
	end
end

-- VIP清心符礼包
tItem[3004032] = tItem[3004032] or {}
tItem[3004032]["Function"] = function(nItemId,sItemName)
	VipWelfareGifts2015_UseItemText(nItemId,"1-1")
end

tItem[3004032]["Text1-1"] = {111,112}
tItem[3004032]["Text111"] = tVipWelfareGifts2015_Text[3004032]["111"]
tItem[3004032]["Text112"] = tVipWelfareGifts2015_Text[3004032]["112"]
tItem[3004032]["tOption1-1"] = {1}

tItem[3004032]["Text1-2"] = {121}
tItem[3004032]["Text121"] = tVipWelfareGifts2015_Text[3004032]["121"]
tItem[3004032]["tOption1-2"] = {2,3}

tItem[3004032]["Text1-3"] = {131}
tItem[3004032]["Text131"] = tVipWelfareGifts2015_Text[3004032]["131"]
tItem[3004032]["tOption1-3"] = {4}

tItem[3004032]["Text1-4"] = {141}
tItem[3004032]["Text141"] = tVipWelfareGifts2015_Text[3004032]["141"]
tItem[3004032]["tOption1-4"] = {5}

tItem[3004032]["Option1"] = tVipWelfareGifts2015_Text[3004032]["Option1"]
tItem[3004032]["OptionFunc1"]="VipWelfareGifts2015_UseItemText</N>3004032</S>1-2"
tItem[3004032]["Option2"] = tVipWelfareGifts2015_Text[3004032]["Option2"]
tItem[3004032]["OptionFunc2"]="VipWelfareGifts2015_UseHeartPackage</N>3004032"
tItem[3004032]["Option3"] = tVipWelfareGifts2015_Text[3004032]["Option3"]
tItem[3004032]["Option4"] = tVipWelfareGifts2015_Text[3004032]["Option4"]
tItem[3004032]["Option5"] = tVipWelfareGifts2015_Text[3004032]["Option5"]

-- VIP行走江湖礼包
tItem[3004117] = tItem[3004117] or {}
tItem[3004117]["Function"] = function(nItemId,sItemName)
	-- 判断物品是否过期
	if VipWelfareGifts2015_BeOverdue(nItemId) then
		return
	end
	
	local nVip = Get_UserVip()
	
	if nVip <= 0 then
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			Sys_MsgBox(tVipWelfareGifts2015_Text[nItemId]["BeOverdue"])
		end
		
		return
	end
	
	-- 判断VIP等级
	if nVip == tVipWelfareGifts2015_Constant["MidVip"] then
		VipWelfareGifts2015_UseItemText(nItemId,"1-2")
	elseif nVip == tVipWelfareGifts2015_Constant["MaxVip"] then
		VipWelfareGifts2015_UseItemText(nItemId,"1-3")
	elseif nVip > tVipWelfareGifts2015_Constant["MinVip"] then
		VipWelfareGifts2015_UseItemText(nItemId,"1-4")
	else
		VipWelfareGifts2015_UseItemText(nItemId,"1-1")
	end
end

-- VIP1-3
tItem[3004117]["Text1-1"] = {111,112}
tItem[3004117]["Text111"] = tVipWelfareGifts2015_Text[3004117]["111"]
tItem[3004117]["Text112"] = tVipWelfareGifts2015_Text[3004117]["112"]
tItem[3004117]["tOption1-1"] = {1,2}
-- VIP4
tItem[3004117]["Text1-2"] = {111,112}
tItem[3004117]["Text121"] = tVipWelfareGifts2015_Text[3004117]["121"]
tItem[3004117]["Text122"] = tVipWelfareGifts2015_Text[3004117]["122"]
tItem[3004117]["tOption1-2"] = {3,4}
-- VIP5
tItem[3004117]["Text1-3"] = {131,132}
tItem[3004117]["Text131"] = tVipWelfareGifts2015_Text[3004117]["131"]
tItem[3004117]["Text132"] = tVipWelfareGifts2015_Text[3004117]["132"]
tItem[3004117]["tOption1-3"] = {5,6}
-- VIP6
tItem[3004117]["Text1-4"] = {141,142}
tItem[3004117]["Text141"] = tVipWelfareGifts2015_Text[3004117]["141"]
tItem[3004117]["Text142"] = tVipWelfareGifts2015_Text[3004117]["142"]
tItem[3004117]["tOption1-4"] = {7,8}
-- 60分钟经验
tItem[3004117]["Text2-1"] = {211,212}
tItem[3004117]["Text211"] = tVipWelfareGifts2015_Text[3004117]["211"]
tItem[3004117]["Text212"] = tVipWelfareGifts2015_Text[3004117]["212"]
tItem[3004117]["tOption2-1"] = {9,10}
-- 30点修行值
tItem[3004117]["Text2-2"] = {221}
tItem[3004117]["Text221"] = tVipWelfareGifts2015_Text[3004117]["221"]
tItem[3004117]["tOption2-2"] = {11,12}
-- 120分钟经验
tItem[3004117]["Text3-1"] = {311,312}
tItem[3004117]["Text311"] = tVipWelfareGifts2015_Text[3004117]["311"]
tItem[3004117]["Text312"] = tVipWelfareGifts2015_Text[3004117]["312"]
tItem[3004117]["tOption3-1"] = {13,14}
-- 100点修行值
tItem[3004117]["Text3-2"] = {321}
tItem[3004117]["Text321"] = tVipWelfareGifts2015_Text[3004117]["321"]
tItem[3004117]["tOption3-2"] = {15,16}
-- 200分钟经验
tItem[3004117]["Text4-1"] = {411,412}
tItem[3004117]["Text411"] = tVipWelfareGifts2015_Text[3004117]["411"]
tItem[3004117]["Text412"] = tVipWelfareGifts2015_Text[3004117]["412"]
tItem[3004117]["tOption4-1"] = {17,18}
-- 150点修行值
tItem[3004117]["Text4-2"] = {421}
tItem[3004117]["Text421"] = tVipWelfareGifts2015_Text[3004117]["421"]
tItem[3004117]["tOption4-2"] = {19,20}
-- 320分钟经验
tItem[3004117]["Text5-1"] = {511,512}
tItem[3004117]["Text511"] = tVipWelfareGifts2015_Text[3004117]["511"]
tItem[3004117]["Text512"] = tVipWelfareGifts2015_Text[3004117]["512"]
tItem[3004117]["tOption5-1"] = {21,22}
-- 220点修行值
tItem[3004117]["Text5-2"] = {521}
tItem[3004117]["Text521"] = tVipWelfareGifts2015_Text[3004117]["521"]
tItem[3004117]["tOption5-2"] = {23,24}

tItem[3004117]["Option1"] = tVipWelfareGifts2015_Text[3004117]["Option1"]
tItem[3004117]["OptionFunc1"]="VipWelfareGifts2015_UseItemText</N>3004117</S>2-1"
tItem[3004117]["Option2"] = tVipWelfareGifts2015_Text[3004117]["Option2"]
tItem[3004117]["OptionFunc2"]="VipWelfareGifts2015_UseItemText</N>3004117</S>2-2"
tItem[3004117]["Option3"] = tVipWelfareGifts2015_Text[3004117]["Option3"]
tItem[3004117]["OptionFunc3"]="VipWelfareGifts2015_UseItemText</N>3004117</S>3-1"
tItem[3004117]["Option4"] = tVipWelfareGifts2015_Text[3004117]["Option4"]
tItem[3004117]["OptionFunc4"]="VipWelfareGifts2015_UseItemText</N>3004117</S>3-2"
tItem[3004117]["Option5"] = tVipWelfareGifts2015_Text[3004117]["Option5"]
tItem[3004117]["OptionFunc5"]="VipWelfareGifts2015_UseItemText</N>3004117</S>4-1"
tItem[3004117]["Option6"] = tVipWelfareGifts2015_Text[3004117]["Option6"]
tItem[3004117]["OptionFunc6"]="VipWelfareGifts2015_UseItemText</N>3004117</S>4-2"
tItem[3004117]["Option7"] = tVipWelfareGifts2015_Text[3004117]["Option7"]
tItem[3004117]["OptionFunc7"]="VipWelfareGifts2015_UseItemText</N>3004117</S>5-1"
tItem[3004117]["Option8"] = tVipWelfareGifts2015_Text[3004117]["Option8"]
tItem[3004117]["OptionFunc8"]="VipWelfareGifts2015_UseItemText</N>3004117</S>5-2"
tItem[3004117]["Option9"] = tVipWelfareGifts2015_Text[3004117]["Option9"]
tItem[3004117]["OptionFunc9"]="VipWelfareGifts2015_UseWalkDead</N>3004117</N>1"
tItem[3004117]["Option10"] = tVipWelfareGifts2015_Text[3004117]["Option10"]
tItem[3004117]["Option11"] = tVipWelfareGifts2015_Text[3004117]["Option11"]
tItem[3004117]["OptionFunc11"]="VipWelfareGifts2015_UseWalkDead</N>3004117</N>2"
tItem[3004117]["Option12"] = tVipWelfareGifts2015_Text[3004117]["Option12"]
tItem[3004117]["Option13"] = tVipWelfareGifts2015_Text[3004117]["Option13"]
tItem[3004117]["OptionFunc13"]="VipWelfareGifts2015_UseWalkDead</N>3004117</N>3"
tItem[3004117]["Option14"] = tVipWelfareGifts2015_Text[3004117]["Option14"]
tItem[3004117]["Option15"] = tVipWelfareGifts2015_Text[3004117]["Option15"]
tItem[3004117]["OptionFunc15"]="VipWelfareGifts2015_UseWalkDead</N>3004117</N>4"
tItem[3004117]["Option16"] = tVipWelfareGifts2015_Text[3004117]["Option16"]
tItem[3004117]["Option17"] = tVipWelfareGifts2015_Text[3004117]["Option17"]
tItem[3004117]["OptionFunc17"]="VipWelfareGifts2015_UseWalkDead</N>3004117</N>5"
tItem[3004117]["Option18"] = tVipWelfareGifts2015_Text[3004117]["Option18"]
tItem[3004117]["Option19"] = tVipWelfareGifts2015_Text[3004117]["Option19"]
tItem[3004117]["OptionFunc19"]="VipWelfareGifts2015_UseWalkDead</N>3004117</N>6"
tItem[3004117]["Option20"] = tVipWelfareGifts2015_Text[3004117]["Option20"]
tItem[3004117]["Option21"] = tVipWelfareGifts2015_Text[3004117]["Option21"]
tItem[3004117]["OptionFunc21"]="VipWelfareGifts2015_UseWalkDead</N>3004117</N>7"
tItem[3004117]["Option22"] = tVipWelfareGifts2015_Text[3004117]["Option22"]
tItem[3004117]["Option23"] = tVipWelfareGifts2015_Text[3004117]["Option23"]
tItem[3004117]["OptionFunc23"]="VipWelfareGifts2015_UseWalkDead</N>3004117</N>8"
tItem[3004117]["Option24"] = tVipWelfareGifts2015_Text[3004117]["Option24"]