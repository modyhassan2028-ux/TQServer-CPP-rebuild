------------------------------------------------------------------------------------
--Name:		[征服][活动脚本]月卡包线上版制作
--Purpose:	月卡包线上版制作
--Creator: 	严振飞
--Created:	2015/07/08
------------------------------------------------------------------------------------
--(135,49)---(136,02)
--掩码说明
---[1]	stc(136,17)	记录A1礼包打开次数
---[1]	stc(136,18)	记录A2礼包打开次数
---[1]	stc(136,19)	记录A3礼包打开次数
---[1]	stc(136,25)	记录神魂特惠包总的打开次数
---[1]	stc(136,26)	记录经验特惠包总的打开次数
---[1]	stc(136,27)	记录龙珠特惠包总的打开次数
---[1]	stc(136,28)	记录宝石特惠包总的打开次数

---[2]	stc(136,20)	记录A系列礼包打开次数
---[2]	stc(136,21)	记录神魂特惠包打开次数
---[2]	stc(136,22)	记录经验特惠包打开次数
---[2]	stc(136,23)	记录龙珠特惠包打开次数
---[2]	stc(136,24)	记录宝石特惠包打开次数

---[3]	stc(136,29)	已购买优质月卡礼包
---[3]	stc(136,30)	已购买豪华月卡礼包
---[3]	stc(136,31)	已购买至尊月卡礼包
---[3]	stc(136,91)	已购买神魂特惠包
---[3]	stc(136,92)	已购买经验特惠包
---[3]	stc(136,93)	已购买龙珠特惠包
---[3]	stc(136,94)	已购买宝石特惠包

---		stc(136,37)	记录背包信是否获得

--动态存储表
--cq_dyna_global_data 50927
--data0		记录是否发布公告



--LOGid 12000035
------------------------------------------------------------------------------------
--命名规范
--FestivalMonthCardPackage__
------------------------------------------------------------------------------------
--STC掩码表
local tFestivalMonthCardPackage_Stc = {}
----------------------------------------
---------------------STC掩码记录A系列礼包单个开启次数
	tFestivalMonthCardPackage_Stc[1] = {}
	tFestivalMonthCardPackage_Stc[1]["Add"] = 1
	tFestivalMonthCardPackage_Stc[1]["Open14"] = 14
	tFestivalMonthCardPackage_Stc[1]["Complete"] = 15
	-- A1包开启次数
	tFestivalMonthCardPackage_Stc[1][3006930] = {}
	tFestivalMonthCardPackage_Stc[1][3006930]["EventData"] = 136
	tFestivalMonthCardPackage_Stc[1][3006930]["TypeData"] = 17
	-- A2包开启次数
	tFestivalMonthCardPackage_Stc[1][3006931] = {}
	tFestivalMonthCardPackage_Stc[1][3006931]["EventData"] = 136
	tFestivalMonthCardPackage_Stc[1][3006931]["TypeData"] = 18
	-- A3包开启次数
	tFestivalMonthCardPackage_Stc[1][3006932] = {}
	tFestivalMonthCardPackage_Stc[1][3006932]["EventData"] = 136
	tFestivalMonthCardPackage_Stc[1][3006932]["TypeData"] = 19
	-- 神魂特惠礼包
	tFestivalMonthCardPackage_Stc[1][3006933] = {}
	tFestivalMonthCardPackage_Stc[1][3006933]["EventData"] = 136
	tFestivalMonthCardPackage_Stc[1][3006933]["TypeData"] = 25
	-- 经验特惠礼包
	tFestivalMonthCardPackage_Stc[1][3006934] = {}
	tFestivalMonthCardPackage_Stc[1][3006934]["EventData"] = 136
	tFestivalMonthCardPackage_Stc[1][3006934]["TypeData"] = 26
	-- 龙珠特惠礼包
	tFestivalMonthCardPackage_Stc[1][3006935] = {}
	tFestivalMonthCardPackage_Stc[1][3006935]["EventData"] = 136
	tFestivalMonthCardPackage_Stc[1][3006935]["TypeData"] = 27
	-- 宝石特惠礼包
	tFestivalMonthCardPackage_Stc[1][3006936] = {}
	tFestivalMonthCardPackage_Stc[1][3006936]["EventData"] = 136
	tFestivalMonthCardPackage_Stc[1][3006936]["TypeData"] = 28


---------------------STC掩码记录A系列礼包总开启次数
	tFestivalMonthCardPackage_Stc[2] = {}
	tFestivalMonthCardPackage_Stc[2]["Add"] = 1
	tFestivalMonthCardPackage_Stc[2]["Open9"] = 9
	tFestivalMonthCardPackage_Stc[2]["Open10"] = 10
	-- A1包开启次数
	tFestivalMonthCardPackage_Stc[2][3006930] = {}
	tFestivalMonthCardPackage_Stc[2][3006930]["EventData"] = 136
	tFestivalMonthCardPackage_Stc[2][3006930]["TypeData"] = 20
	-- A2包开启次数
	tFestivalMonthCardPackage_Stc[2][3006931] = {}
	tFestivalMonthCardPackage_Stc[2][3006931]["EventData"] = 136
	tFestivalMonthCardPackage_Stc[2][3006931]["TypeData"] = 20
	-- A3包开启次数
	tFestivalMonthCardPackage_Stc[2][3006932] = {}
	tFestivalMonthCardPackage_Stc[2][3006932]["EventData"] = 136
	tFestivalMonthCardPackage_Stc[2][3006932]["TypeData"] = 20
	-- 神魂特惠礼包
	tFestivalMonthCardPackage_Stc[2][3006933] = {}
	tFestivalMonthCardPackage_Stc[2][3006933]["EventData"] = 136
	tFestivalMonthCardPackage_Stc[2][3006933]["TypeData"] = 21
	-- 经验特惠礼包
	tFestivalMonthCardPackage_Stc[2][3006934] = {}
	tFestivalMonthCardPackage_Stc[2][3006934]["EventData"] = 136
	tFestivalMonthCardPackage_Stc[2][3006934]["TypeData"] = 22
	-- 龙珠特惠礼包
	tFestivalMonthCardPackage_Stc[2][3006935] = {}
	tFestivalMonthCardPackage_Stc[2][3006935]["EventData"] = 136
	tFestivalMonthCardPackage_Stc[2][3006935]["TypeData"] = 23
	-- 宝石特惠礼包
	tFestivalMonthCardPackage_Stc[2][3006936] = {}
	tFestivalMonthCardPackage_Stc[2][3006936]["EventData"] = 136
	tFestivalMonthCardPackage_Stc[2][3006936]["TypeData"] = 24


---------------------STC掩码记录礼包购买阶段
	tFestivalMonthCardPackage_Stc[3] = {}
	tFestivalMonthCardPackage_Stc[3]["Complete"] = 1
	-- 已购买优质月卡礼包
	tFestivalMonthCardPackage_Stc[3][3006930] = {}
	tFestivalMonthCardPackage_Stc[3][3006930]["EventData"] = 136
	tFestivalMonthCardPackage_Stc[3][3006930]["TypeData"] = 29
	-- 已购买豪华月卡礼包
	tFestivalMonthCardPackage_Stc[3][3006931] = {}
	tFestivalMonthCardPackage_Stc[3][3006931]["EventData"] = 136
	tFestivalMonthCardPackage_Stc[3][3006931]["TypeData"] = 30
	-- 已购买至尊月卡礼包
	tFestivalMonthCardPackage_Stc[3][3006932] = {}
	tFestivalMonthCardPackage_Stc[3][3006932]["EventData"] = 136
	tFestivalMonthCardPackage_Stc[3][3006932]["TypeData"] = 31
	-- 已购买神魂特惠包
	tFestivalMonthCardPackage_Stc[3][3006933] = {}
	tFestivalMonthCardPackage_Stc[3][3006933]["EventData"] = 136
	tFestivalMonthCardPackage_Stc[3][3006933]["TypeData"] = 91
	-- 已购买经验特惠包
	tFestivalMonthCardPackage_Stc[3][3006934] = {}
	tFestivalMonthCardPackage_Stc[3][3006934]["EventData"] = 136
	tFestivalMonthCardPackage_Stc[3][3006934]["TypeData"] = 92
	-- 已购买龙珠特惠包
	tFestivalMonthCardPackage_Stc[3][3006935] = {}
	tFestivalMonthCardPackage_Stc[3][3006935]["EventData"] = 136
	tFestivalMonthCardPackage_Stc[3][3006935]["TypeData"] = 93
	-- 已购买宝石特惠包
	tFestivalMonthCardPackage_Stc[3][3006936] = {}
	tFestivalMonthCardPackage_Stc[3][3006936]["EventData"] = 136
	tFestivalMonthCardPackage_Stc[3][3006936]["TypeData"] = 94

	
--动态存储表
local tFestivalMonthCardPackage_DynaGlobal = {}
	tFestivalMonthCardPackage_DynaGlobal[1] = 50927
	
------------------------------------------------------------------------------------
--活动数据
local tFestivalMonthCardPackage_Data = {}
	-- 活动时间
	tFestivalMonthCardPackage_Data["Festival_BefTime"] = "2014-01-01 00:00 2015-09-09 23:59"
	tFestivalMonthCardPackage_Data["Festival_NowTime"] = "2015-09-10 00:00 2015-11-10 23:59"
	
	-- 网页链接
	tFestivalMonthCardPackage_Data["WebAddress"] = "http://co.99.com/guide/quest/2015/treasure_chest_hunting.shtml"

	
	-- 礼包购买间隔天数
	tFestivalMonthCardPackage_Data["DaysApart"] = 15
	
	-- 点天石上限
	tFestivalMonthCardPackage_Data["EMoneyTop"] = 999999999
	
	-- 礼包时效
	tFestivalMonthCardPackage_Data["SaveTime"] = 28800
	
	--寻路--月卡包贩售商(双龙城)
	tFestivalMonthCardPackage_Data[3006938] = {}
	tFestivalMonthCardPackage_Data[3006938]["NpcId"] = 18710
	tFestivalMonthCardPackage_Data[3006938]["MapId"] = 1002
	tFestivalMonthCardPackage_Data[3006938]["PosX"] = 295
	tFestivalMonthCardPackage_Data[3006938]["PosY"] = 295

	-- 背包空间
	tFestivalMonthCardPackage_Data["ChkSpace1"] = 1
	tFestivalMonthCardPackage_Data["ChkSpace2"] = 2
	tFestivalMonthCardPackage_Data["ChkSpace3"] = 3

	-- 月卡礼包ID
	tFestivalMonthCardPackage_Data["Package1"] = 3006930
	tFestivalMonthCardPackage_Data["Package2"] = 3006931
	tFestivalMonthCardPackage_Data["Package3"] = 3006932

	-- 宝石结晶兑换物品ID
	tFestivalMonthCardPackage_Data["GemCrystal"] = {}
	tFestivalMonthCardPackage_Data["GemCrystal"][1] = 700072	-- 良品玄元宝石
	tFestivalMonthCardPackage_Data["GemCrystal"][2] = 700013	-- 优质龙恨宝石
	tFestivalMonthCardPackage_Data["GemCrystal"][3] = 700003	-- 优质凤吟宝石
	tFestivalMonthCardPackage_Data["GemCrystal"][4] = 700102	-- 良品天怒宝石
	tFestivalMonthCardPackage_Data["GemCrystal"][5] = 700122	-- 良品地灵宝石
	tFestivalMonthCardPackage_Data["GemCrystal"][6] = 700073	-- 优质玄元宝石
	
	-- 背包信经验+修行值
	tFestivalMonthCardPackage_Data["LevelTop"] = 140
	tFestivalMonthCardPackage_Data["Type_Exp"] = 4
	tFestivalMonthCardPackage_Data["Type_Cul"] = 6
	tFestivalMonthCardPackage_Data["Letter_Exp"] = 30
	tFestivalMonthCardPackage_Data["Letter_Cul"] = 15

	-- 光效数据
	tFestivalMonthCardPackage_Data["EffectObj"] = "self"
	tFestivalMonthCardPackage_Data["Effect_1"] = "zf2-e280"
	tFestivalMonthCardPackage_Data["Effect_2"] = "angelwing"
	tFestivalMonthCardPackage_Data["Effect_3"] = "zf2-e300"

------------------------------------------------------------------------------------
-- 礼包奖励配置
local tFestivalMonthCardPackage_Reward = {}
	-- 优质月卡礼包
	tFestivalMonthCardPackage_Reward[3006930] = {}
	tFestivalMonthCardPackage_Reward[3006930]["ShenYou"] = 1 	--是否神佑（1为神佑，没配为没有）
	tFestivalMonthCardPackage_Reward[3006930]["Stone"] = 1 		--是否为+3赤炼石
	tFestivalMonthCardPackage_Reward[3006930]["Space1"] = 2		--背包空间（普通）
	tFestivalMonthCardPackage_Reward[3006930]["Space2"] = 3		--背包空间（第一次）
	tFestivalMonthCardPackage_Reward[3006930]["Space3"] = 4		--背包空间（第一次且第10次）
	tFestivalMonthCardPackage_Reward[3006930]["Space4"] = 3		--背包空间（第10次）

	--奖励
	tFestivalMonthCardPackage_Reward[3006930]["Reward-N"] = {} 	--普通奖励
	tFestivalMonthCardPackage_Reward[3006930]["Reward-N"][1] = 3005884		-- 赤炼石马匹可选包（赠）
	tFestivalMonthCardPackage_Reward[3006930]["Reward-N"][2] = 3005885		-- 极品马鞭碎片（赠）
	tFestivalMonthCardPackage_Reward[3006930]["Num-N"] = {}		-- 物品个数
	tFestivalMonthCardPackage_Reward[3006930]["Num-N"][1] = 1
	tFestivalMonthCardPackage_Reward[3006930]["Num-N"][2] = 1
	tFestivalMonthCardPackage_Reward[3006930]["Reward-1"] = {} 	--第一次奖励
	tFestivalMonthCardPackage_Reward[3006930]["Reward-1"][1] = 201009		-- 1%神佑极品凌霄扇（赠）
	tFestivalMonthCardPackage_Reward[3006930]["Num-1"] = {}
	tFestivalMonthCardPackage_Reward[3006930]["Num-1"][1] = 1
	tFestivalMonthCardPackage_Reward[3006930]["Reward-10"] = {} --第10次奖励
	tFestivalMonthCardPackage_Reward[3006930]["Reward-10"][1] = 730003		-- +3赤炼石（赠）
	tFestivalMonthCardPackage_Reward[3006930]["Num-10"] = {}
	tFestivalMonthCardPackage_Reward[3006930]["Num-10"][1] = 1

	
	-- 豪华月卡礼包
	tFestivalMonthCardPackage_Reward[3006931] = {}
	tFestivalMonthCardPackage_Reward[3006931]["ShenYou"] = 1 	--是否神佑（1为神佑，没配为没有）
	tFestivalMonthCardPackage_Reward[3006931]["Stone"] = 1 		--是否为+3赤炼石
	tFestivalMonthCardPackage_Reward[3006931]["Space1"] = 2		--背包空间（普通）
	tFestivalMonthCardPackage_Reward[3006931]["Space2"] = 3		--背包空间（第一次）
	tFestivalMonthCardPackage_Reward[3006931]["Space3"] = 4		--背包空间（第一次且第10次）
	tFestivalMonthCardPackage_Reward[3006931]["Space4"] = 3		--背包空间（第10次）
	--奖励
	tFestivalMonthCardPackage_Reward[3006931]["Reward-N"] = {} 	--普通奖励
	tFestivalMonthCardPackage_Reward[3006931]["Reward-N"][1] = 3005884		-- 赤炼石马匹可选包（赠）
	tFestivalMonthCardPackage_Reward[3006931]["Reward-N"][2] = 3005887		-- 极品装备卷碎片（赠）
	tFestivalMonthCardPackage_Reward[3006931]["Num-N"] = {}		-- 物品个数
	tFestivalMonthCardPackage_Reward[3006931]["Num-N"][1] = 1
	tFestivalMonthCardPackage_Reward[3006931]["Num-N"][2] = 1
	tFestivalMonthCardPackage_Reward[3006931]["Reward-1"] = {} 	--第一次奖励
	tFestivalMonthCardPackage_Reward[3006931]["Reward-1"][1] = 202009		-- 1%神佑极品混元塔（赠）
	tFestivalMonthCardPackage_Reward[3006931]["Num-1"] = {}
	tFestivalMonthCardPackage_Reward[3006931]["Num-1"][1] = 1
	tFestivalMonthCardPackage_Reward[3006931]["Reward-10"] = {} --第10次奖励
	tFestivalMonthCardPackage_Reward[3006931]["Reward-10"][1] = 730003		-- +3赤炼石（赠）
	tFestivalMonthCardPackage_Reward[3006931]["Num-10"] = {}
	tFestivalMonthCardPackage_Reward[3006931]["Num-10"][1] = 1


	-- 至尊月卡礼包
	tFestivalMonthCardPackage_Reward[3006932] = {}
	tFestivalMonthCardPackage_Reward[3006932]["Stone"] = 1 		--是否为+3赤炼石
	tFestivalMonthCardPackage_Reward[3006932]["Space1"] = 2		--背包空间（普通）
	tFestivalMonthCardPackage_Reward[3006932]["Space2"] = 3		--背包空间（第一次）
	tFestivalMonthCardPackage_Reward[3006932]["Space3"] = 4		--背包空间（第一次且第10次）
	tFestivalMonthCardPackage_Reward[3006932]["Space4"] = 3		--背包空间（第10次）
	--奖励
	tFestivalMonthCardPackage_Reward[3006932]["Reward-N"] = {} 	--普通奖励
	tFestivalMonthCardPackage_Reward[3006932]["Reward-N"][1] = 3005884		-- 赤炼石马匹可选包（赠）
	tFestivalMonthCardPackage_Reward[3006932]["Reward-N"][2] = 3005887		-- 极品装备卷碎片（赠）
	tFestivalMonthCardPackage_Reward[3006932]["Num-N"] = {}		-- 物品个数
	tFestivalMonthCardPackage_Reward[3006932]["Num-N"][1] = 1
	tFestivalMonthCardPackage_Reward[3006932]["Num-N"][2] = 1
	tFestivalMonthCardPackage_Reward[3006932]["Reward-1"] = {} 	--第一次奖励
	tFestivalMonthCardPackage_Reward[3006932]["Reward-1"][1] = 3005889		-- 极品2D武器兑换卷（赠）
	tFestivalMonthCardPackage_Reward[3006932]["Num-1"] = {}
	tFestivalMonthCardPackage_Reward[3006932]["Num-1"][1] = 1
	tFestivalMonthCardPackage_Reward[3006932]["Reward-10"] = {} --第10次奖励
	tFestivalMonthCardPackage_Reward[3006932]["Reward-10"][1] = 730003		-- +3赤炼石（赠）
	tFestivalMonthCardPackage_Reward[3006932]["Num-10"] = {}
	tFestivalMonthCardPackage_Reward[3006932]["Num-10"][1] = 1

	-- 神魂特惠礼包
	tFestivalMonthCardPackage_Reward[3006933] = {}
	tFestivalMonthCardPackage_Reward[3006933]["Space1"] = 1		--背包空间（普通）
	tFestivalMonthCardPackage_Reward[3006933]["Space2"] = 2		--背包空间（第一次）
	tFestivalMonthCardPackage_Reward[3006933]["Space3"] = 4		--背包空间（第一次且第10次）
	tFestivalMonthCardPackage_Reward[3006933]["Space4"] = 3		--背包空间（第10次）
	--奖励
	tFestivalMonthCardPackage_Reward[3006933]["Reward-N"] = {} 	--普通奖励
	tFestivalMonthCardPackage_Reward[3006933]["Reward-N"][1] = 3005890		-- 神魂结晶（赠）
	tFestivalMonthCardPackage_Reward[3006933]["Num-N"] = {}
	tFestivalMonthCardPackage_Reward[3006933]["Num-N"][1] = 1
	tFestivalMonthCardPackage_Reward[3006933]["Reward-1"] = {} 	--第一次奖励
	tFestivalMonthCardPackage_Reward[3006933]["Reward-1"][1] = 3005895		-- 小固化石碎片（赠）
	tFestivalMonthCardPackage_Reward[3006933]["Num-1"] = {}
	tFestivalMonthCardPackage_Reward[3006933]["Num-1"][1] = 6
	tFestivalMonthCardPackage_Reward[3006933]["Reward-10"] = {} --第10次奖励
	tFestivalMonthCardPackage_Reward[3006933]["Reward-10"][1] = 3005893		-- 6阶神魂礼包（赠）
	tFestivalMonthCardPackage_Reward[3006933]["Reward-10"][2] = 3005894		-- 5级淬炼礼包（赠）
	tFestivalMonthCardPackage_Reward[3006933]["Num-10"] = {}
	tFestivalMonthCardPackage_Reward[3006933]["Num-10"][1] = 1
	tFestivalMonthCardPackage_Reward[3006933]["Num-10"][2] = 1
	
	
	-- 经验特惠礼包
	tFestivalMonthCardPackage_Reward[3006934] = {}
	tFestivalMonthCardPackage_Reward[3006934]["Space1"] = 2		--背包空间（普通）
	tFestivalMonthCardPackage_Reward[3006934]["Space2"] = 3		--背包空间（第一次）
	tFestivalMonthCardPackage_Reward[3006934]["Space3"] = 4		--背包空间（第一次且第10次）
	tFestivalMonthCardPackage_Reward[3006934]["Space4"] = 3		--背包空间（第10次）
	--奖励
	tFestivalMonthCardPackage_Reward[3006934]["Reward-N"] = {} 	--普通奖励
	tFestivalMonthCardPackage_Reward[3006934]["Reward-N"][1] = 723700		-- 聚神丹（赠）
	tFestivalMonthCardPackage_Reward[3006934]["Reward-N"][2] = 723017		-- 双倍经验药水（赠）
	tFestivalMonthCardPackage_Reward[3006934]["Num-N"] = {}
	tFestivalMonthCardPackage_Reward[3006934]["Num-N"][1] = 5
	tFestivalMonthCardPackage_Reward[3006934]["Num-N"][2] = 2	
	tFestivalMonthCardPackage_Reward[3006934]["Reward-1"] = {} 	--第一次奖励
	tFestivalMonthCardPackage_Reward[3006934]["Reward-1"][1] = 728596		-- 九转聚神丹碎片（赠）
	tFestivalMonthCardPackage_Reward[3006934]["Num-1"] = {}
	tFestivalMonthCardPackage_Reward[3006934]["Num-1"][1] = 1
	tFestivalMonthCardPackage_Reward[3006934]["Reward-10"] = {} --第10次奖励
	tFestivalMonthCardPackage_Reward[3006934]["Reward-10"][1] = 3002559		-- 经验保护药水（赠）
	tFestivalMonthCardPackage_Reward[3006934]["Num-10"] = {}
	tFestivalMonthCardPackage_Reward[3006934]["Num-10"][1] = 10


	-- 龙珠特惠礼包
	tFestivalMonthCardPackage_Reward[3006935] = {}
	tFestivalMonthCardPackage_Reward[3006935]["Space1"] = 1		--背包空间（普通）
	tFestivalMonthCardPackage_Reward[3006935]["Space2"] = 3		--背包空间（第一次）
	tFestivalMonthCardPackage_Reward[3006935]["Space3"] = 4		--背包空间（第一次且第10次）
	tFestivalMonthCardPackage_Reward[3006935]["Space4"] = 3		--背包空间（第10次）
	--奖励
	tFestivalMonthCardPackage_Reward[3006935]["Reward-N"] = {} 	--普通奖励
	tFestivalMonthCardPackage_Reward[3006935]["Reward-N"][1] = 3005896		-- 龙珠碎片（赠）
	tFestivalMonthCardPackage_Reward[3006935]["Num-N"] = {}
	tFestivalMonthCardPackage_Reward[3006935]["Num-N"][1] = 1
	tFestivalMonthCardPackage_Reward[3006935]["Reward-1"] = {} 	--第一次奖励
	tFestivalMonthCardPackage_Reward[3006935]["Reward-1"][1] = 723342		-- 造化天书（赠）
	tFestivalMonthCardPackage_Reward[3006935]["Num-1"] = {}
	tFestivalMonthCardPackage_Reward[3006935]["Num-1"][1] = 2
	tFestivalMonthCardPackage_Reward[3006935]["Reward-10"] = {} --第10次奖励
	tFestivalMonthCardPackage_Reward[3006935]["Reward-10"][1] = 3005896		-- 龙珠碎片（赠）
	tFestivalMonthCardPackage_Reward[3006935]["Num-10"] = {}
	tFestivalMonthCardPackage_Reward[3006935]["Num-10"][1] = 5


	-- 宝石特惠礼包
	tFestivalMonthCardPackage_Reward[3006936] = {}
	tFestivalMonthCardPackage_Reward[3006936]["Space1"] = 1		--背包空间（普通）
	tFestivalMonthCardPackage_Reward[3006936]["Space2"] = 2		--背包空间（第一次）
	tFestivalMonthCardPackage_Reward[3006936]["Space3"] = 3		--背包空间（第一次且第10次）
	tFestivalMonthCardPackage_Reward[3006936]["Space4"] = 2		--背包空间（第10次）
	--奖励
	tFestivalMonthCardPackage_Reward[3006936]["Reward-N"] = {} 	--普通奖励
	tFestivalMonthCardPackage_Reward[3006936]["Reward-N"][1] = 3006937		-- 宝石结晶（赠）
	tFestivalMonthCardPackage_Reward[3006936]["Num-N"] = {}
	tFestivalMonthCardPackage_Reward[3006936]["Num-N"][1] = 1
	tFestivalMonthCardPackage_Reward[3006936]["Reward-1"] = {} 	--第一次奖励
	tFestivalMonthCardPackage_Reward[3006936]["Reward-1"][1] = 723727		-- 清心符（赠）
	tFestivalMonthCardPackage_Reward[3006936]["Num-1"] = {}
	tFestivalMonthCardPackage_Reward[3006936]["Num-1"][1] = 10
	tFestivalMonthCardPackage_Reward[3006936]["Reward-10"] = {} --第10次奖励
	tFestivalMonthCardPackage_Reward[3006936]["Reward-10"][1] = 3006937		-- 超级经验球碎片（赠）
	tFestivalMonthCardPackage_Reward[3006936]["Num-10"] = {}
	tFestivalMonthCardPackage_Reward[3006936]["Num-10"][1] = 5

------------------------------------------------------------------------------------
--活动LOG数据
local tFestivalMonthCardPackage_Log = {}
	-- 月卡礼包
	tFestivalMonthCardPackage_Log["GetReward"] = "0,0,0,0,12000035,2,%d,1"
	-- 月卡礼包开启
	tFestivalMonthCardPackage_Log["CardPag_Open1"] = "0,0,%d,%d,"
	tFestivalMonthCardPackage_Log["CardPag_Open2"] = "12000035,2,%s[%s][%s][%s],%s[%s][%s][%s]"
	-- 宝石结晶
	tFestivalMonthCardPackage_Log["GemCrystal"] = "0,0,3006937,%d,12000035,2,%d,1"
	-- 背包信
	tFestivalMonthCardPackage_Log["Letter"] = "0,0,3006938,1,12000035,2,%d,%d"

local tFestivalMonthCardPackage_EmoneyBuy = {}
	-- [1] A1包 999 8852
	-- [2] A2包 999 8853
	-- [3] A3包 999 8854
	-- [3] B包 神魂礼包 999 8855
	-- [4] C包 经验礼包 999 8856
	-- [5] D包 龙珠礼包 999 8857
	-- [6] E包 宝石礼包 350 20001

	tFestivalMonthCardPackage_EmoneyBuy["EmoneyLog"] = {}
	tFestivalMonthCardPackage_EmoneyBuy["EmoneyLog"][3006930] = "999	8852	149	149	1	"
	tFestivalMonthCardPackage_EmoneyBuy["EmoneyLog"][3006931] = "999	8853	149	149	1	"
	tFestivalMonthCardPackage_EmoneyBuy["EmoneyLog"][3006932] = "999	8854	149	149	1	"
	tFestivalMonthCardPackage_EmoneyBuy["EmoneyLog"][3006933] = "999	8855	99	99	1	"
	tFestivalMonthCardPackage_EmoneyBuy["EmoneyLog"][3006934] = "999	8856	99	99	1	"
	tFestivalMonthCardPackage_EmoneyBuy["EmoneyLog"][3006935] = "999	8857	99	99	1	"
	tFestivalMonthCardPackage_EmoneyBuy["EmoneyLog"][3006936] = "350	20001	99	99	1	"


---------------------------------------NPC函数---------------------------------------------
--网页链接
function FestivalMonthCardPackage_WebLink()
	local sWebAddress = tFestivalMonthCardPackage_Data["WebAddress"]
	User_SendWebPage(sWebAddress)
end


-- 寻路函数
function FestivalMonthCardPackage_FindWay(nObject)
	local nPosX = tFestivalMonthCardPackage_Data[nObject]["PosX"]
	local nPosY = tFestivalMonthCardPackage_Data[nObject]["PosY"]
	local nMapId = tFestivalMonthCardPackage_Data[nObject]["MapId"]
	local nNpcId = tFestivalMonthCardPackage_Data[nObject]["NpcId"]
	
	Sys_GotoSomeWhere(nPosX,nPosY,nMapId,nNpcId)
end

---------------------------------------NPC函数---------------------------------------------
-----------------------------------【月卡包贩售商】---------------------------------------
-- 确认购买函数
function FestivalMonthCardPackage_BuySuccess(nNpcId,nItemId,nEMoney)
	local nEventData_1 = tFestivalMonthCardPackage_Stc[1][nItemId]["EventData"]
	local nTypeData_1 = tFestivalMonthCardPackage_Stc[1][nItemId]["TypeData"]
	local nEventData_3 = tFestivalMonthCardPackage_Stc[3][nItemId]["EventData"]
	local nTypeData_3 = tFestivalMonthCardPackage_Stc[3][nItemId]["TypeData"]
	local nComplete_3 = tFestivalMonthCardPackage_Stc[3]["Complete"]
	
	--天石判断
	local nUserEMoney = Get_UserEMoney()
	if nUserEMoney < nEMoney then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	
	local nSaveTime = tFestivalMonthCardPackage_Data["SaveTime"]
	
	-- 减天石
	if User_AddEMoney(-nEMoney) then
		-- 个体开启次数清零
		Task_SetStatistic(nEventData_3,nTypeData_3,nComplete_3,1)
		Task_SetStatistic(nEventData_1,nTypeData_1,0,1)
		Task_SetStcTimestamp(nEventData_3,nTypeData_3,0)
		Item_AddItem(nItemId,0,0,0,nSaveTime,1)
	end
	
	local sItemName = Get_ItemtypeName(nItemId)
	local sLogText = string.format(tFestivalMonthCardPackage_Log["GetReward"],nItemId)
	local sTalkText = string.format(tFestivalMonthCardPackage_Text[18710]["GetReward"],sItemName)
	User_EffectAdd(tFestivalMonthCardPackage_Data["EffectObj"],tFestivalMonthCardPackage_Data["Effect_3"])
	Sys_SaveEmoneyBuy(tFestivalMonthCardPackage_EmoneyBuy["EmoneyLog"][nItemId])
	Sys_SaveActionFestivalLog(sLogText)
	User_TalkChannel2005(sTalkText)
end


-- 购买礼包接入函数
function FestivalMonthCardPackage_BuyPackage(nNpcId,nItemId,nEMoney)
	local nEventData_3 = tFestivalMonthCardPackage_Stc[3][nItemId]["EventData"]
	local nTypeData_3 = tFestivalMonthCardPackage_Stc[3][nItemId]["TypeData"]
	local nComplete_3 = tFestivalMonthCardPackage_Stc[3]["Complete"]
	-- 判断是否已购买该礼包
	if Task_ChkStcValue(nEventData_3,nTypeData_3,">=",nComplete_3) then
		
		-- 15天后才能再购买
		local nDays = tFestivalMonthCardPackage_Data["DaysApart"]
		if not Task_StcInterval(nEventData_3,nTypeData_3,nDays,4) then
			LinkNpcGossipFunc_New(nNpcId,"2-9")
			return
		end
	end

	-- 是否存在该礼包
	if Item_ChkItem(nItemId) then
		LinkNpcGossipFunc_New(nNpcId,"2-9")
		return
	end

	--判断背包空间
	if not User_CheckLeftSpace(tFestivalMonthCardPackage_Data["ChkSpace1"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end

	--天石判断
	local nUserEMoney = Get_UserEMoney()
	if nUserEMoney < nEMoney then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	
	-- 二次确认
	local sItemName = Get_ItemtypeName(nItemId)
	tNpcGossip[nNpcId]["Text231"] = string.format(tFestivalMonthCardPackage_Text[18710]["Text231"],nEMoney,sItemName)
	tNpcGossip[nNpcId]["OptionFunc231"] = string.format("FestivalMonthCardPackage_BuySuccess</N>%d</N>%d</N>%d",nNpcId,nItemId,nEMoney)
	LinkNpcGossipFunc_New(nNpcId,"2-3")
end


---------------------------------------物品函数---------------------------------------------
-- 背包空间函数
function FestivalMonthCardPackage_Space(nItemId)
	local nSpaceNum = tFestivalMonthCardPackage_Reward[nItemId]["Space1"]
	local nEventData_1 = tFestivalMonthCardPackage_Stc[1][nItemId]["EventData"]
	local nTypeData_1 = tFestivalMonthCardPackage_Stc[1][nItemId]["TypeData"]
	local nOpen14_1 = tFestivalMonthCardPackage_Stc[1]["Open14"]
	local nEventData_2 = tFestivalMonthCardPackage_Stc[2][nItemId]["EventData"]
	local nTypeData_2 = tFestivalMonthCardPackage_Stc[2][nItemId]["TypeData"] 
	local nOpen9_2 = tFestivalMonthCardPackage_Stc[2]["Open9"]

	-- 是否第一次
	if Task_ChkStcValue(nEventData_1,nTypeData_1,"==",0) then
	
		-- 是否总第10次
		if not Task_ChkStcValue(nEventData_2,nTypeData_2,"==",nOpen9_2) then
			nSpaceNum = tFestivalMonthCardPackage_Reward[nItemId]["Space2"]
		else
			nSpaceNum = tFestivalMonthCardPackage_Reward[nItemId]["Space3"]
		end
		
	-- 是否总第10次
	elseif Task_ChkStcValue(nEventData_2,nTypeData_2,"==",nOpen9_2) then
		nSpaceNum = tFestivalMonthCardPackage_Reward[nItemId]["Space4"]
	end
	
	-- 是否第15次（减少一个）
	if Task_ChkStcValue(nEventData_1,nTypeData_1,">=",nOpen14_1) then
		nSpaceNum = nSpaceNum - 1
	end
	
	-- 返回最终值
	return nSpaceNum
end


-- 礼包开启函数
function FestivalMonthCardPackage_RewardMain(nItemId)
	local nEventData_1 = tFestivalMonthCardPackage_Stc[1][nItemId]["EventData"]
	local nTypeData_1 = tFestivalMonthCardPackage_Stc[1][nItemId]["TypeData"]
	local nAdd_1 = tFestivalMonthCardPackage_Stc[1]["Add"]
	local nOpen14_1 = tFestivalMonthCardPackage_Stc[1]["Open14"]
	local nComplete_1 = tFestivalMonthCardPackage_Stc[1]["Complete"]
	local nEventData_2 = tFestivalMonthCardPackage_Stc[2][nItemId]["EventData"]
	local nTypeData_2 = tFestivalMonthCardPackage_Stc[2][nItemId]["TypeData"]
	local nAdd_2 = tFestivalMonthCardPackage_Stc[2]["Add"]
	local nOpen10_2 = tFestivalMonthCardPackage_Stc[2]["Open10"]
	local sTalkText = tFestivalMonthCardPackage_Text["CardPag"]["OpenStart"]
	local sTalkMid = tFestivalMonthCardPackage_Text["CardPag"]["OpenMid"]
	local sLogText = tFestivalMonthCardPackage_Log["CardPag_Open1"]
	local tItemId = {}
	local tItemNum = {}
	local tTableNum = 0
	local nLogNum = 0
	
	-- 是否隔天
	if not Task_ChkStcValue(nEventData_1,nTypeData_1,"==",0) then
		if not Task_StcInterval(nEventData_1,nTypeData_1,1,4) then
			User_TalkChannel2005(tFestivalMonthCardPackage_Text["CardPag"]["OpenFail"])
			return
		end
	end
	
	-- 背包判断
	local nSpaceNum = FestivalMonthCardPackage_Space(nItemId)
	if nSpaceNum ~= 0 then
		if not User_CheckLeftSpace(nSpaceNum) then
			User_TalkChannel2005(tFestivalMonthCardPackage_Text["CardPag"]["FullBag"])
			return
		end
	end

	-- 判断是否是否为第15次
	if Task_ChkStcValue(nEventData_1,nTypeData_1,">=",nOpen14_1) then
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			sLogText = string.format(sLogText,nItemId,1)
			local sItemName = Get_ItemtypeName(nItemId)
			User_TalkChannel2005(string.format(tFestivalMonthCardPackage_Text["DelItem"],sItemName))
		end
	else
		sLogText = string.format(sLogText,0,0)
	end
	
	-- 置掩码
	Task_AddStatistic(nEventData_1,nTypeData_1,nAdd_1,1)
	Task_AddStatistic(nEventData_2,nTypeData_2,nAdd_2,1)
	Task_SetStcTimestamp(nEventData_1,nTypeData_1,0)
	
	-- 普通奖励
	for i = 1, #tFestivalMonthCardPackage_Reward[nItemId]["Reward-N"] do
		local nNewItemId = tFestivalMonthCardPackage_Reward[nItemId]["Reward-N"][i]
		local nNewItemNum = tFestivalMonthCardPackage_Reward[nItemId]["Num-N"][i]
		local sItemName = Get_ItemtypeName(nNewItemId)
		Item_AddItem(nNewItemId,0,nNewItemNum,3)
		nLogNum = nLogNum + 1
		tItemId[nLogNum] = nNewItemId
		tItemNum[nLogNum] = nNewItemNum
		local sLinkText = string.format(tFestivalMonthCardPackage_Text["CardPag"]["OpenReward"],nNewItemNum,sItemName)
		sTalkText = sTalkText..sLinkText
	end
	
	-- 提示第几次打开
	local nOpenTimes = Get_UserStatisticValue(nEventData_1,nTypeData_1)
	local sTalkMid = string.format(sTalkMid,nOpenTimes)
	sTalkText = sTalkText..sTalkMid

	-- 第一次奖励
	if Task_ChkStcValue(nEventData_1,nTypeData_1,"==",1) then
		
		-- 给奖励
		for i = 1, #tFestivalMonthCardPackage_Reward[nItemId]["Reward-1"] do
			local nNewItemId = tFestivalMonthCardPackage_Reward[nItemId]["Reward-1"][i]
			local nNewItemNum = tFestivalMonthCardPackage_Reward[nItemId]["Num-1"][i]
			local sItemName = Get_ItemtypeName(nNewItemId)

			-- 是否为神佑
			if tFestivalMonthCardPackage_Reward[nItemId]["ShenYou"] ~= nil then
				Item_AddItem(nNewItemId,0,nNewItemNum,3,0,0,0,0,1)
				sItemName = tFestivalMonthCardPackage_Text["CardPag"]["HeavenFan"]..sItemName
			else
				Item_AddItem(nNewItemId,0,nNewItemNum,3)
			end
			nLogNum = nLogNum + 1
			tItemId[nLogNum] = nNewItemId
			tItemNum[nLogNum] = nNewItemNum
			local sLinkText = string.format(tFestivalMonthCardPackage_Text["CardPag"]["OpenReward"],nNewItemNum,sItemName)
			local sTextAdd = tFestivalMonthCardPackage_Text["CardPag"]["OpenAdd"]
			sTalkText = sTalkText..sTextAdd..sLinkText	
		end
	end
	
	-- 第10次打开
	if Task_ChkStcValue(nEventData_2,nTypeData_2,"==",nOpen10_2) then
		-- 10次一轮重置
		Task_SetStatistic(nEventData_2,nTypeData_2,0,1)
		
		--给奖励
		for i = 1, #tFestivalMonthCardPackage_Reward[nItemId]["Reward-10"] do
			local nNewItemId = tFestivalMonthCardPackage_Reward[nItemId]["Reward-10"][i]
			local nNewItemNum = tFestivalMonthCardPackage_Reward[nItemId]["Num-10"][i]
			local sItemName = Get_ItemtypeName(nNewItemId)
			
			-- 是否为赤炼石
			if tFestivalMonthCardPackage_Reward[nItemId]["Stone"] ~= nil then
				sItemName = tFestivalMonthCardPackage_Text["CardPag"]["Stone"]..sItemName
			end
			
			--给第10次奖励
			Item_AddItem(nNewItemId,0,nNewItemNum,3)
			nLogNum = nLogNum + 1
			tItemId[nLogNum] = nNewItemId
			tItemNum[nLogNum] = nNewItemNum
			local sLinkText = string.format(tFestivalMonthCardPackage_Text["CardPag"]["OpenReward"],nNewItemNum,sItemName)
			
			-- 为第一次不再链接“此次额外获得”
			if not Task_ChkStcValue(nEventData_1,nTypeData_1,"==",1) then
				local sTextAdd = tFestivalMonthCardPackage_Text["CardPag"]["OpenAdd"]
				sTalkText = sTalkText..sTextAdd
			end
			sTalkText = sTalkText..sLinkText
		end
	end
	
	-- 15次后重置掩码
	if Task_ChkStcValue(nEventData_1,nTypeData_1,">=",nComplete_1) then
		Task_SetStatistic(nEventData_1,nTypeData_1,0,1)
		Task_SetStcTimestamp(nEventData_1,nTypeData_1,0)
	end
	
	-- 提示
	local sLinkLog = tFestivalMonthCardPackage_Log["CardPag_Open2"]
	local sLink_format = string.format(sLinkLog,tItemId[1],tItemId[2],tItemId[3],tItemId[4],tItemNum[1],tItemNum[2],tItemNum[3],tItemNum[4])
	local sLink_gsub = string.gsub(sLink_format,"%[nil%]","")
	local sLogText = sLogText..sLink_gsub
	User_EffectAdd(tFestivalMonthCardPackage_Data["EffectObj"],tFestivalMonthCardPackage_Data["Effect_1"])
	Sys_SaveActionFestivalLog(sLogText)
	User_TalkChannel2005(sTalkText..".")
end


-------------------------------------【宝石结晶】---------------------------------------
-- 二次确认函数
function FestivalMonthCardPackage_GemCrystal(nItemId,nNewItemNum,nGemNum)
	--判断背包空间
	if not User_CheckLeftSpace(tFestivalMonthCardPackage_Data["ChkSpace1"]) then
		LinkItemGossipFunc_New(nItemId,"1-2")
		return
	end
	
	local nNewItem = tFestivalMonthCardPackage_Data["GemCrystal"][nNewItemNum]
	local sItemName = Get_ItemtypeName(nNewItem)
	local sFunc = "FestivalMonthCardPackage_GemSuccess</N>%d</N>%d</N>%d</S>%s"
	tItem[3006937]["Text141"] = string.format(tFestivalMonthCardPackage_Text[3006937]["Text141"],nGemNum,sItemName)
	tItem[3006937]["OptionFunc18"] = string.format(sFunc,nItemId,nGemNum,nNewItem,sItemName)
	LinkItemGossipFunc_New(nItemId,"1-4")
end


-- 确认兑换
function FestivalMonthCardPackage_GemSuccess(nItemId,nGemNum,nNewItem,sItemName)
	
	-- 宝石结晶是否足够
	if not Item_ChkMulItem(nItemId,nItemId,nGemNum,1) then
		LinkItemGossipFunc_New(nItemId,"1-3")
		return
	
	elseif Item_DelMulItem(nItemId,nItemId,nGemNum,1) then
		Item_AddItem(nNewItem,0,0,3)
		local sLogText = string.format(tFestivalMonthCardPackage_Log["GemCrystal"],nGemNum,nNewItem)
		local sTalkText = string.format(tFestivalMonthCardPackage_Text[3006937]["GemCrystal"],nGemNum,sItemName)
		
		User_EffectAdd(tFestivalMonthCardPackage_Data["EffectObj"],tFestivalMonthCardPackage_Data["Effect_2"])
		Sys_SaveActionFestivalLog(sLogText)
		User_TalkChannel2005(sTalkText)
	end
end

-------------------------------------【背包信】---------------------------------------
function FestivalMonthCardPackage_Letter(nItemId)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalMonthCardPackage_Data["Festival_NowTime"]) then
		if Item_ChkItem(nItemId) and Item_DelAllItemByType(nItemId) then
			User_TalkChannel2005(tFestivalMonthCardPackage_Text["TimeEnd"])
		end
		return
	end
	
	local nAddType = 0
	local nAddValue = 0
	
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		--等级判断
		local nUserLev = Get_UserLevel()
		
		--给经验
		if nUserLev < tFestivalMonthCardPackage_Data["LevelTop"] then
			nAddType = tFestivalMonthCardPackage_Data["Type_Exp"]
			nAddValue = tFestivalMonthCardPackage_Data["Letter_Exp"]
			User_AddExpTime(nAddValue)
			
		--给修行值
		else
			nAddType = tFestivalMonthCardPackage_Data["Type_Cul"]
			nAddValue = tFestivalMonthCardPackage_Data["Letter_Cul"]
			User_AddCultivation(nAddValue)
		end
	end
	
	FestivalMonthCardPackage_FindWay(nItemId)
	local sLinkText = tFestivalMonthCardPackage_Text[nItemId][nAddValue]
	local sLogText = string.format(tFestivalMonthCardPackage_Log["Letter"],nAddType,nAddValue)
	local sTalkText = string.format(tFestivalMonthCardPackage_Text[nItemId]["Letter"],nAddValue,sLinkText)
	User_EffectAdd(tFestivalMonthCardPackage_Data["EffectObj"],tFestivalMonthCardPackage_Data["Effect_2"])
	Sys_SaveActionFestivalLog(sLogText)
	User_TalkChannel2005(sTalkText)
end

------------------------------------------203W公告函数-------------------------------------------
function FestivalMonthCardPackage_NoticeBegin()
	local nDynaGlobalData0 = Get_SysDynaGlobalData0(tFestivalMonthCardPackage_DynaGlobal[1])
	
	-- 已发布公告
	if nDynaGlobalData0 ~= 0 then
		return
	end
	
	-- 发布公告
	Sys_TalkBroadcast(tFestivalMonthCardPackage_Text["Notice"])
	Sys_SetSynaGlobalData0(tFestivalMonthCardPackage_DynaGlobal[1],1)
end

function FestivalMonthCardPackage_NoticeEnd()
	local nDynaGlobalData0 = Get_SysDynaGlobalData0(tFestivalMonthCardPackage_DynaGlobal[1])
	if nDynaGlobalData0 ~= 0 then
		Sys_SetSynaGlobalData0(tFestivalMonthCardPackage_DynaGlobal[1],0)
	end
end

------------------------------------------NPC配置-------------------------------------------
---------------------NPC头像
tNpcFace[3739] = 1

---------------------NPC对话
------------------------------------------
-- 【==月卡包贩售商==】
tNpcGossip[18710] = tNpcGossip[18710] or DefaultNpc:new{}
tNpcGossip[18710]["OptionHidden"] = 1

---【起始对白】
tNpcGossip[18710]["Text1-1"] = {111,112} 			-- 活动前
tNpcGossip[18710]["Text1-2"] = {121,122} 			-- 活动后
tNpcGossip[18710]["Text1-3"] = {131,132} 			-- 可购买优质月卡礼包
tNpcGossip[18710]["Text1-4"] = {141,142} 			-- 已买优质月卡礼包未开完包
tNpcGossip[18710]["Text1-5"] = {151} 				-- 可购买豪华月卡礼包
tNpcGossip[18710]["Text1-6"] = {161,162} 			-- 已买豪华月卡礼包未开完包
tNpcGossip[18710]["Text1-7"] = {171} 				-- 可购买至尊月卡礼包
tNpcGossip[18710]["Text1-8"] = {181,182} 			-- 已买至尊月卡礼包未开完包
tNpcGossip[18710]["Text1-9"] = {191} 				-- 继续购买至尊月卡礼包
tNpcGossip[18710]["Text111"] = tFestivalMonthCardPackage_Text[18710]["Text111"]
tNpcGossip[18710]["Text112"] = tFestivalMonthCardPackage_Text[18710]["Text112"]
tNpcGossip[18710]["Text121"] = tFestivalMonthCardPackage_Text[18710]["Text121"]
tNpcGossip[18710]["Text122"] = tFestivalMonthCardPackage_Text[18710]["Text122"]
tNpcGossip[18710]["Text131"] = tFestivalMonthCardPackage_Text[18710]["Text131"]
tNpcGossip[18710]["Text132"] = tFestivalMonthCardPackage_Text[18710]["Text132"]
tNpcGossip[18710]["Text141"] = tFestivalMonthCardPackage_Text[18710]["Text141"]
tNpcGossip[18710]["Text142"] = tFestivalMonthCardPackage_Text[18710]["Text142"]
tNpcGossip[18710]["Text151"] = tFestivalMonthCardPackage_Text[18710]["Text151"]
tNpcGossip[18710]["Text161"] = tFestivalMonthCardPackage_Text[18710]["Text161"]
tNpcGossip[18710]["Text162"] = tFestivalMonthCardPackage_Text[18710]["Text162"]
tNpcGossip[18710]["Text171"] = tFestivalMonthCardPackage_Text[18710]["Text171"]
tNpcGossip[18710]["Text181"] = tFestivalMonthCardPackage_Text[18710]["Text181"]
tNpcGossip[18710]["Text182"] = tFestivalMonthCardPackage_Text[18710]["Text182"]
tNpcGossip[18710]["Text191"] = tFestivalMonthCardPackage_Text[18710]["Text191"]
tNpcGossip[18710]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tFestivalMonthCardPackage_Data["Festival_BefTime"])
end
tNpcGossip[18710]["ChkFunc1-2"] = function ()
	return not Sys_ChkFullTime(tFestivalMonthCardPackage_Data["Festival_NowTime"])
end
tNpcGossip[18710]["ChkFunc1-3"] = function ()
	local nItemId = tFestivalMonthCardPackage_Data["Package1"]
	local nEventData_5 = tFestivalMonthCardPackage_Stc[3][nItemId]["EventData"]
	local nTypeData_5 = tFestivalMonthCardPackage_Stc[3][nItemId]["TypeData"]
	
	-- 是否购买过优质月卡礼包
	return Task_ChkStcValue(nEventData_5,nTypeData_5,"==",0)
end
tNpcGossip[18710]["ChkFunc1-4"] = function ()
	local nItemId = tFestivalMonthCardPackage_Data["Package1"]
	local nEventData_5 = tFestivalMonthCardPackage_Stc[3][nItemId]["EventData"]
	local nTypeData_5 = tFestivalMonthCardPackage_Stc[3][nItemId]["TypeData"]
	local nDays = tFestivalMonthCardPackage_Data["DaysApart"]
	
	-- 是否过15天（优质月卡礼包）
	if Task_StcInterval(nEventData_5,nTypeData_5,nDays,4) and not Item_ChkItem(nItemId) then
		return false
	else
		return true
	end
end
tNpcGossip[18710]["ChkFunc1-5"] = function ()
	local nItemId = tFestivalMonthCardPackage_Data["Package2"]
	local nEventData_5 = tFestivalMonthCardPackage_Stc[3][nItemId]["EventData"]
	local nTypeData_5 = tFestivalMonthCardPackage_Stc[3][nItemId]["TypeData"]
	
	-- 是否购买过豪华月卡礼包
	return Task_ChkStcValue(nEventData_5,nTypeData_5,"==",0)
end
tNpcGossip[18710]["ChkFunc1-6"] = function ()
	local nItemId = tFestivalMonthCardPackage_Data["Package2"]
	local nEventData_5 = tFestivalMonthCardPackage_Stc[3][nItemId]["EventData"]
	local nTypeData_5 = tFestivalMonthCardPackage_Stc[3][nItemId]["TypeData"]
	local nDays = tFestivalMonthCardPackage_Data["DaysApart"]

	-- 是否过15天（豪华月卡礼包）
	if Task_StcInterval(nEventData_5,nTypeData_5,nDays,4) and not Item_ChkItem(nItemId) then
		return false
	else
		return true
	end
end
tNpcGossip[18710]["ChkFunc1-7"] = function ()
	local nItemId = tFestivalMonthCardPackage_Data["Package3"]
	local nEventData_5 = tFestivalMonthCardPackage_Stc[3][nItemId]["EventData"]
	local nTypeData_5 = tFestivalMonthCardPackage_Stc[3][nItemId]["TypeData"]	
	
	-- 是否购买过至尊月卡礼包
	return Task_ChkStcValue(nEventData_5,nTypeData_5,"==",0)
end
tNpcGossip[18710]["ChkFunc1-8"] = function ()
	local nItemId = tFestivalMonthCardPackage_Data["Package3"]
	local nEventData_5 = tFestivalMonthCardPackage_Stc[3][nItemId]["EventData"]
	local nTypeData_5 = tFestivalMonthCardPackage_Stc[3][nItemId]["TypeData"]
	local nDays = tFestivalMonthCardPackage_Data["DaysApart"]

	-- 是否过15天（至尊月卡礼包）
	if Task_StcInterval(nEventData_5,nTypeData_5,nDays,4) and not Item_ChkItem(nItemId) then
		return false
	else
		return true
	end
end
--选项
tNpcGossip[18710]["tOption1-1"] = {111}
tNpcGossip[18710]["tOption1-2"] = {121}
tNpcGossip[18710]["tOption1-3"] = {131,132,180,133}
tNpcGossip[18710]["tOption1-4"] = {141,142,143,144,180,145}
tNpcGossip[18710]["tOption1-5"] = {151,152,180,153}
tNpcGossip[18710]["tOption1-6"] = {141,142,143,144,180,145}
tNpcGossip[18710]["tOption1-7"] = {171,172,180,173}
tNpcGossip[18710]["tOption1-8"] = {141,142,143,144,180,145}
tNpcGossip[18710]["tOption1-9"] = {171,172,180,173}
tNpcGossip[18710]["Option111"] = tFestivalMonthCardPackage_Text[18710]["Option111"]
tNpcGossip[18710]["Option121"] = tFestivalMonthCardPackage_Text[18710]["Option121"]
tNpcGossip[18710]["Option131"] = tFestivalMonthCardPackage_Text[18710]["Option131"]
tNpcGossip[18710]["Option132"] = tFestivalMonthCardPackage_Text[18710]["Option132"]
tNpcGossip[18710]["Option133"] = tFestivalMonthCardPackage_Text[18710]["Option133"]
tNpcGossip[18710]["Option141"] = tFestivalMonthCardPackage_Text[18710]["Option141"]
tNpcGossip[18710]["Option142"] = tFestivalMonthCardPackage_Text[18710]["Option142"]
tNpcGossip[18710]["Option143"] = tFestivalMonthCardPackage_Text[18710]["Option143"]
tNpcGossip[18710]["Option144"] = tFestivalMonthCardPackage_Text[18710]["Option144"]
tNpcGossip[18710]["Option145"] = tFestivalMonthCardPackage_Text[18710]["Option145"]
tNpcGossip[18710]["Option151"] = tFestivalMonthCardPackage_Text[18710]["Option151"]
tNpcGossip[18710]["Option152"] = tFestivalMonthCardPackage_Text[18710]["Option152"]
tNpcGossip[18710]["Option153"] = tFestivalMonthCardPackage_Text[18710]["Option153"]
tNpcGossip[18710]["Option171"] = tFestivalMonthCardPackage_Text[18710]["Option171"]
tNpcGossip[18710]["Option172"] = tFestivalMonthCardPackage_Text[18710]["Option172"]
tNpcGossip[18710]["Option173"] = tFestivalMonthCardPackage_Text[18710]["Option173"]
tNpcGossip[18710]["Option180"] = tFestivalMonthCardPackage_Text[18710]["Option180"]
tNpcGossip[18710]["OptionPoint131"] = "2-4"
tNpcGossip[18710]["OptionPoint132"] = "4"
tNpcGossip[18710]["OptionPoint141"] = "2-5"
tNpcGossip[18710]["OptionPoint142"] = "2-6"
tNpcGossip[18710]["OptionPoint143"] = "2-7"
tNpcGossip[18710]["OptionPoint144"] = "2-8"
tNpcGossip[18710]["OptionPoint151"] = "2-10"
tNpcGossip[18710]["OptionPoint152"] = "4"
tNpcGossip[18710]["OptionPoint171"] = "2-11"
tNpcGossip[18710]["OptionPoint172"] = "4"
tNpcGossip[18710]["OptionFunc180"] = "FestivalMonthCardPackage_WebLink"


-- 【可购买优质月卡礼包】
tNpcGossip[18710]["Text2-1"] = {211}				-- 背包空间不足
tNpcGossip[18710]["Text2-2"] = {221}				-- 天石数不足
tNpcGossip[18710]["Text2-3"] = {231}				-- 二次确认
tNpcGossip[18710]["Text2-4"] = {241,242,243,244,245,246,247,248}		-- 购买优质月卡礼包
tNpcGossip[18710]["Text2-5"] = {251,252,253,254,255,256,257,258}		-- 购买神魂特惠礼包
tNpcGossip[18710]["Text2-6"] = {261,262,263,264,265,266,267,268}		-- 购买经验特惠礼包
tNpcGossip[18710]["Text2-7"] = {271,272,273,274,275,276,277,278}		-- 购买龙珠特惠礼包	
tNpcGossip[18710]["Text2-8"] = {281,282,283,284,285,286,287,288}		-- 购买宝石特惠礼包
tNpcGossip[18710]["Text2-9"] = {291}									-- 已有特惠包
tNpcGossip[18710]["Text2-10"] = {2101,2102,2103,2104,2105,2106,2107,2108}	-- 购买豪华月卡礼包
tNpcGossip[18710]["Text2-11"] = {2111,2112,2113,2114,2115,2116,2117,2118}	-- 购买至尊月卡礼包
tNpcGossip[18710]["Text211"] = tFestivalMonthCardPackage_Text[18710]["Text211"]
tNpcGossip[18710]["Text221"] = tFestivalMonthCardPackage_Text[18710]["Text221"]
tNpcGossip[18710]["Text231"] = tFestivalMonthCardPackage_Text[18710]["Text231"]
tNpcGossip[18710]["Text241"] = tFestivalMonthCardPackage_Text[18710]["Text241"]
tNpcGossip[18710]["Text242"] = tFestivalMonthCardPackage_Text[18710]["Text242"]
tNpcGossip[18710]["Text243"] = tFestivalMonthCardPackage_Text[18710]["Text243"]
tNpcGossip[18710]["Text244"] = tFestivalMonthCardPackage_Text[18710]["Text244"]
tNpcGossip[18710]["Text245"] = tFestivalMonthCardPackage_Text[18710]["Text245"]
tNpcGossip[18710]["Text246"] = tFestivalMonthCardPackage_Text[18710]["Text246"]
tNpcGossip[18710]["Text247"] = tFestivalMonthCardPackage_Text[18710]["Text247"]
tNpcGossip[18710]["Text248"] = tFestivalMonthCardPackage_Text[18710]["Text248"]
tNpcGossip[18710]["Text251"] = tFestivalMonthCardPackage_Text[18710]["Text251"]
tNpcGossip[18710]["Text252"] = tFestivalMonthCardPackage_Text[18710]["Text252"]
tNpcGossip[18710]["Text253"] = tFestivalMonthCardPackage_Text[18710]["Text253"]
tNpcGossip[18710]["Text254"] = tFestivalMonthCardPackage_Text[18710]["Text254"]
tNpcGossip[18710]["Text255"] = tFestivalMonthCardPackage_Text[18710]["Text255"]
tNpcGossip[18710]["Text256"] = tFestivalMonthCardPackage_Text[18710]["Text256"]
tNpcGossip[18710]["Text257"] = tFestivalMonthCardPackage_Text[18710]["Text257"]
tNpcGossip[18710]["Text258"] = tFestivalMonthCardPackage_Text[18710]["Text258"]
tNpcGossip[18710]["Text261"] = tFestivalMonthCardPackage_Text[18710]["Text261"]
tNpcGossip[18710]["Text262"] = tFestivalMonthCardPackage_Text[18710]["Text262"]
tNpcGossip[18710]["Text263"] = tFestivalMonthCardPackage_Text[18710]["Text263"]
tNpcGossip[18710]["Text264"] = tFestivalMonthCardPackage_Text[18710]["Text264"]
tNpcGossip[18710]["Text265"] = tFestivalMonthCardPackage_Text[18710]["Text265"]
tNpcGossip[18710]["Text266"] = tFestivalMonthCardPackage_Text[18710]["Text266"]
tNpcGossip[18710]["Text267"] = tFestivalMonthCardPackage_Text[18710]["Text267"]
tNpcGossip[18710]["Text268"] = tFestivalMonthCardPackage_Text[18710]["Text268"]
tNpcGossip[18710]["Text271"] = tFestivalMonthCardPackage_Text[18710]["Text271"]
tNpcGossip[18710]["Text272"] = tFestivalMonthCardPackage_Text[18710]["Text272"]
tNpcGossip[18710]["Text273"] = tFestivalMonthCardPackage_Text[18710]["Text273"]
tNpcGossip[18710]["Text274"] = tFestivalMonthCardPackage_Text[18710]["Text274"]
tNpcGossip[18710]["Text275"] = tFestivalMonthCardPackage_Text[18710]["Text275"]
tNpcGossip[18710]["Text276"] = tFestivalMonthCardPackage_Text[18710]["Text276"]
tNpcGossip[18710]["Text277"] = tFestivalMonthCardPackage_Text[18710]["Text277"]
tNpcGossip[18710]["Text278"] = tFestivalMonthCardPackage_Text[18710]["Text278"]
tNpcGossip[18710]["Text281"] = tFestivalMonthCardPackage_Text[18710]["Text281"]
tNpcGossip[18710]["Text282"] = tFestivalMonthCardPackage_Text[18710]["Text282"]
tNpcGossip[18710]["Text283"] = tFestivalMonthCardPackage_Text[18710]["Text283"]
tNpcGossip[18710]["Text284"] = tFestivalMonthCardPackage_Text[18710]["Text284"]
tNpcGossip[18710]["Text285"] = tFestivalMonthCardPackage_Text[18710]["Text285"]
tNpcGossip[18710]["Text286"] = tFestivalMonthCardPackage_Text[18710]["Text286"]
tNpcGossip[18710]["Text287"] = tFestivalMonthCardPackage_Text[18710]["Text287"]
tNpcGossip[18710]["Text288"] = tFestivalMonthCardPackage_Text[18710]["Text288"]
tNpcGossip[18710]["Text291"] = tFestivalMonthCardPackage_Text[18710]["Text291"]
tNpcGossip[18710]["Text2101"] = tFestivalMonthCardPackage_Text[18710]["Text2101"]
tNpcGossip[18710]["Text2102"] = tFestivalMonthCardPackage_Text[18710]["Text2102"]
tNpcGossip[18710]["Text2103"] = tFestivalMonthCardPackage_Text[18710]["Text2103"]
tNpcGossip[18710]["Text2104"] = tFestivalMonthCardPackage_Text[18710]["Text2104"]
tNpcGossip[18710]["Text2105"] = tFestivalMonthCardPackage_Text[18710]["Text2105"]
tNpcGossip[18710]["Text2106"] = tFestivalMonthCardPackage_Text[18710]["Text2106"]
tNpcGossip[18710]["Text2107"] = tFestivalMonthCardPackage_Text[18710]["Text2107"]
tNpcGossip[18710]["Text2108"] = tFestivalMonthCardPackage_Text[18710]["Text2108"]
tNpcGossip[18710]["Text2111"] = tFestivalMonthCardPackage_Text[18710]["Text2111"]
tNpcGossip[18710]["Text2112"] = tFestivalMonthCardPackage_Text[18710]["Text2112"]
tNpcGossip[18710]["Text2113"] = tFestivalMonthCardPackage_Text[18710]["Text2113"]
tNpcGossip[18710]["Text2114"] = tFestivalMonthCardPackage_Text[18710]["Text2114"]
tNpcGossip[18710]["Text2115"] = tFestivalMonthCardPackage_Text[18710]["Text2115"]
tNpcGossip[18710]["Text2116"] = tFestivalMonthCardPackage_Text[18710]["Text2116"]
tNpcGossip[18710]["Text2117"] = tFestivalMonthCardPackage_Text[18710]["Text2117"]
tNpcGossip[18710]["Text2118"] = tFestivalMonthCardPackage_Text[18710]["Text2118"]
--选项
tNpcGossip[18710]["tOption2-1"] = {211}
tNpcGossip[18710]["tOption2-2"] = {211}
tNpcGossip[18710]["tOption2-3"] = {231,232}
tNpcGossip[18710]["tOption2-4"] = {241,242,243}
tNpcGossip[18710]["tOption2-5"] = {251,252,253}
tNpcGossip[18710]["tOption2-6"] = {261,262}
tNpcGossip[18710]["tOption2-7"] = {271,272,273}
tNpcGossip[18710]["tOption2-8"] = {281,282,283}
tNpcGossip[18710]["tOption2-9"] = {291}
tNpcGossip[18710]["tOption2-10"] = {2101,2102,2103}
tNpcGossip[18710]["tOption2-11"] = {2111,2112,2113}
tNpcGossip[18710]["Option211"] = tFestivalMonthCardPackage_Text[18710]["Option211"]
tNpcGossip[18710]["Option231"] = tFestivalMonthCardPackage_Text[18710]["Option231"]
tNpcGossip[18710]["Option232"] = tFestivalMonthCardPackage_Text[18710]["Option232"]
tNpcGossip[18710]["Option241"] = tFestivalMonthCardPackage_Text[18710]["Option241"]
tNpcGossip[18710]["Option242"] = tFestivalMonthCardPackage_Text[18710]["Option242"]
tNpcGossip[18710]["Option243"] = tFestivalMonthCardPackage_Text[18710]["Option243"]
tNpcGossip[18710]["Option251"] = tFestivalMonthCardPackage_Text[18710]["Option251"]
tNpcGossip[18710]["Option252"] = tFestivalMonthCardPackage_Text[18710]["Option252"]
tNpcGossip[18710]["Option253"] = tFestivalMonthCardPackage_Text[18710]["Option253"]
tNpcGossip[18710]["Option261"] = tFestivalMonthCardPackage_Text[18710]["Option261"]
tNpcGossip[18710]["Option262"] = tFestivalMonthCardPackage_Text[18710]["Option262"]
tNpcGossip[18710]["Option271"] = tFestivalMonthCardPackage_Text[18710]["Option271"]
tNpcGossip[18710]["Option272"] = tFestivalMonthCardPackage_Text[18710]["Option272"]
tNpcGossip[18710]["Option273"] = tFestivalMonthCardPackage_Text[18710]["Option273"]
tNpcGossip[18710]["Option281"] = tFestivalMonthCardPackage_Text[18710]["Option281"]
tNpcGossip[18710]["Option282"] = tFestivalMonthCardPackage_Text[18710]["Option282"]
tNpcGossip[18710]["Option283"] = tFestivalMonthCardPackage_Text[18710]["Option283"]
tNpcGossip[18710]["Option291"] = tFestivalMonthCardPackage_Text[18710]["Option291"]
tNpcGossip[18710]["Option2101"] = tFestivalMonthCardPackage_Text[18710]["Option2101"]
tNpcGossip[18710]["Option2102"] = tFestivalMonthCardPackage_Text[18710]["Option2102"]
tNpcGossip[18710]["Option2103"] = tFestivalMonthCardPackage_Text[18710]["Option2103"]
tNpcGossip[18710]["Option2111"] = tFestivalMonthCardPackage_Text[18710]["Option2111"]
tNpcGossip[18710]["Option2112"] = tFestivalMonthCardPackage_Text[18710]["Option2112"]
tNpcGossip[18710]["Option2113"] = tFestivalMonthCardPackage_Text[18710]["Option2113"]
tNpcGossip[18710]["OptionFunc231"] = ""
tNpcGossip[18710]["OptionFunc241"] = "FestivalMonthCardPackage_BuyPackage</N>18710</N>3006930</N>149"
tNpcGossip[18710]["OptionPoint242"] = "3-1"
tNpcGossip[18710]["OptionFunc251"] = "FestivalMonthCardPackage_BuyPackage</N>18710</N>3006933</N>99"
tNpcGossip[18710]["OptionPoint252"] = "3-4"
tNpcGossip[18710]["OptionFunc261"] = "FestivalMonthCardPackage_BuyPackage</N>18710</N>3006934</N>99"
tNpcGossip[18710]["OptionFunc271"] = "FestivalMonthCardPackage_BuyPackage</N>18710</N>3006935</N>99"
tNpcGossip[18710]["OptionPoint272"] = "3-5"
tNpcGossip[18710]["OptionFunc281"] = "FestivalMonthCardPackage_BuyPackage</N>18710</N>3006936</N>99"
tNpcGossip[18710]["OptionPoint282"] = "3-6"
tNpcGossip[18710]["OptionFunc2101"] = "FestivalMonthCardPackage_BuyPackage</N>18710</N>3006931</N>149"
tNpcGossip[18710]["OptionPoint2102"] = "3-2"
tNpcGossip[18710]["OptionFunc2111"] = "FestivalMonthCardPackage_BuyPackage</N>18710</N>3006932</N>149"
tNpcGossip[18710]["OptionPoint2112"] = "3-3"




-- 【查看礼包详情】
tNpcGossip[18710]["Text3-1"] = {311,312} 			-- 优质月卡礼包
tNpcGossip[18710]["Text3-2"] = {321,322,323} 		-- 豪华月卡礼包
tNpcGossip[18710]["Text3-3"] = {331,332,333,334} 	-- 至尊月卡礼包
tNpcGossip[18710]["Text3-4"] = {341,342,343} 		-- 神魂特惠礼包
tNpcGossip[18710]["Text3-5"] = {351} 				-- 龙珠特惠礼包
tNpcGossip[18710]["Text3-6"] = {361,362} 			-- 宝石特惠礼包
tNpcGossip[18710]["Text311"] = tFestivalMonthCardPackage_Text[18710]["Text311"]
tNpcGossip[18710]["Text312"] = tFestivalMonthCardPackage_Text[18710]["Text312"]
tNpcGossip[18710]["Text321"] = tFestivalMonthCardPackage_Text[18710]["Text321"]
tNpcGossip[18710]["Text322"] = tFestivalMonthCardPackage_Text[18710]["Text322"]
tNpcGossip[18710]["Text323"] = tFestivalMonthCardPackage_Text[18710]["Text323"]
tNpcGossip[18710]["Text331"] = tFestivalMonthCardPackage_Text[18710]["Text331"]
tNpcGossip[18710]["Text332"] = tFestivalMonthCardPackage_Text[18710]["Text332"]
tNpcGossip[18710]["Text333"] = tFestivalMonthCardPackage_Text[18710]["Text333"]
tNpcGossip[18710]["Text334"] = tFestivalMonthCardPackage_Text[18710]["Text334"]
tNpcGossip[18710]["Text341"] = tFestivalMonthCardPackage_Text[18710]["Text341"]
tNpcGossip[18710]["Text342"] = tFestivalMonthCardPackage_Text[18710]["Text342"]
tNpcGossip[18710]["Text343"] = tFestivalMonthCardPackage_Text[18710]["Text343"]
tNpcGossip[18710]["Text351"] = tFestivalMonthCardPackage_Text[18710]["Text351"]
tNpcGossip[18710]["Text361"] = tFestivalMonthCardPackage_Text[18710]["Text361"]
tNpcGossip[18710]["Text362"] = tFestivalMonthCardPackage_Text[18710]["Text362"]


--选项
tNpcGossip[18710]["tOption3-1"] = {311,312}
tNpcGossip[18710]["tOption3-2"] = {321,312}
tNpcGossip[18710]["tOption3-3"] = {331,312}
tNpcGossip[18710]["tOption3-4"] = {341,312}
tNpcGossip[18710]["tOption3-5"] = {351,312}
tNpcGossip[18710]["tOption3-6"] = {361,312}
tNpcGossip[18710]["Option311"] = tFestivalMonthCardPackage_Text[18710]["Option311"]
tNpcGossip[18710]["Option312"] = tFestivalMonthCardPackage_Text[18710]["Option312"]
tNpcGossip[18710]["Option321"] = tFestivalMonthCardPackage_Text[18710]["Option321"]
tNpcGossip[18710]["Option331"] = tFestivalMonthCardPackage_Text[18710]["Option331"]
tNpcGossip[18710]["Option341"] = tFestivalMonthCardPackage_Text[18710]["Option341"]
tNpcGossip[18710]["Option351"] = tFestivalMonthCardPackage_Text[18710]["Option351"]
tNpcGossip[18710]["Option361"] = tFestivalMonthCardPackage_Text[18710]["Option361"]
tNpcGossip[18710]["OptionPoint311"] = "2-4"
tNpcGossip[18710]["OptionPoint321"] = "2-10"
tNpcGossip[18710]["OptionPoint331"] = "2-11"
tNpcGossip[18710]["OptionPoint341"] = "2-5"
tNpcGossip[18710]["OptionPoint351"] = "2-7"
tNpcGossip[18710]["OptionPoint361"] = "2-8"


-- 【查看其他礼包】
tNpcGossip[18710]["Text4-1"] = {411,412,413}
tNpcGossip[18710]["Text411"] = tFestivalMonthCardPackage_Text[18710]["Text411"]
tNpcGossip[18710]["Text412"] = tFestivalMonthCardPackage_Text[18710]["Text412"]
tNpcGossip[18710]["Text413"] = tFestivalMonthCardPackage_Text[18710]["Text413"]
--选项
tNpcGossip[18710]["tOption4-1"] = {41,42,43,44,45,46,47,48}
tNpcGossip[18710]["Option41"] = tFestivalMonthCardPackage_Text[18710]["Option41"]
tNpcGossip[18710]["Option42"] = tFestivalMonthCardPackage_Text[18710]["Option42"]
tNpcGossip[18710]["Option43"] = tFestivalMonthCardPackage_Text[18710]["Option43"]
tNpcGossip[18710]["Option44"] = tFestivalMonthCardPackage_Text[18710]["Option44"]
tNpcGossip[18710]["Option45"] = tFestivalMonthCardPackage_Text[18710]["Option45"]
tNpcGossip[18710]["Option46"] = tFestivalMonthCardPackage_Text[18710]["Option46"]
tNpcGossip[18710]["Option47"] = tFestivalMonthCardPackage_Text[18710]["Option47"]
tNpcGossip[18710]["Option48"] = tFestivalMonthCardPackage_Text[18710]["Option48"]
tNpcGossip[18710]["OptionChkFunc41"] = function ()
	local nItemId = tFestivalMonthCardPackage_Data["Package1"]
	local nEventData_5 = tFestivalMonthCardPackage_Stc[3][nItemId]["EventData"]
	local nTypeData_5 = tFestivalMonthCardPackage_Stc[3][nItemId]["TypeData"]
	
	-- 是否购买过优质月卡礼包
	return Task_ChkStcValue(nEventData_5,nTypeData_5,"==",0)
end
tNpcGossip[18710]["OptionChkFunc42"] = function ()
	local nItemId = tFestivalMonthCardPackage_Data["Package2"]
	local nEventData_5 = tFestivalMonthCardPackage_Stc[3][nItemId]["EventData"]
	local nTypeData_5 = tFestivalMonthCardPackage_Stc[3][nItemId]["TypeData"]
	
	-- 是否购买过豪华月卡礼包
	return Task_ChkStcValue(nEventData_5,nTypeData_5,"==",0)
end
tNpcGossip[18710]["OptionPoint41"] = "5-1"
tNpcGossip[18710]["OptionPoint42"] = "5-2"
tNpcGossip[18710]["OptionPoint43"] = "5-3"
tNpcGossip[18710]["OptionPoint44"] = "5-4"
tNpcGossip[18710]["OptionPoint45"] = "5-5"
tNpcGossip[18710]["OptionPoint46"] = "5-6"
tNpcGossip[18710]["OptionPoint47"] = "1"


-- 【其他礼包说明】
tNpcGossip[18710]["Text5-1"] = {511,512,513,514,515,516,517,518}		-- 查看豪华月卡礼包
tNpcGossip[18710]["Text5-2"] = {521,522,523,524,525,526,527,528}		-- 查看至尊月卡礼包
tNpcGossip[18710]["Text5-3"] = {531,532,533,534,535,536,537,538}		-- 查看神魂特惠礼包
tNpcGossip[18710]["Text5-4"] = {541,542,543,544,545,546,547,548}		-- 查看经验特惠礼包
tNpcGossip[18710]["Text5-5"] = {551,552,553,554,555,556,557,558}		-- 查看龙珠特惠礼包
tNpcGossip[18710]["Text5-6"] = {561,562,563,564,565,566,567,568}		-- 查看宝石特惠礼包
tNpcGossip[18710]["Text511"] = tFestivalMonthCardPackage_Text[18710]["Text2101"]
tNpcGossip[18710]["Text512"] = tFestivalMonthCardPackage_Text[18710]["Text2102"]
tNpcGossip[18710]["Text513"] = tFestivalMonthCardPackage_Text[18710]["Text2103"]
tNpcGossip[18710]["Text514"] = tFestivalMonthCardPackage_Text[18710]["Text2104"]
tNpcGossip[18710]["Text515"] = tFestivalMonthCardPackage_Text[18710]["Text2105"]
tNpcGossip[18710]["Text516"] = tFestivalMonthCardPackage_Text[18710]["Text2106"]
tNpcGossip[18710]["Text517"] = tFestivalMonthCardPackage_Text[18710]["Text2107"]
tNpcGossip[18710]["Text518"] = tFestivalMonthCardPackage_Text[18710]["Text2108"]
tNpcGossip[18710]["Text521"] = tFestivalMonthCardPackage_Text[18710]["Text2111"]
tNpcGossip[18710]["Text522"] = tFestivalMonthCardPackage_Text[18710]["Text2112"]
tNpcGossip[18710]["Text523"] = tFestivalMonthCardPackage_Text[18710]["Text2113"]
tNpcGossip[18710]["Text524"] = tFestivalMonthCardPackage_Text[18710]["Text2114"]
tNpcGossip[18710]["Text525"] = tFestivalMonthCardPackage_Text[18710]["Text2115"]
tNpcGossip[18710]["Text526"] = tFestivalMonthCardPackage_Text[18710]["Text2116"]
tNpcGossip[18710]["Text527"] = tFestivalMonthCardPackage_Text[18710]["Text2117"]
tNpcGossip[18710]["Text528"] = tFestivalMonthCardPackage_Text[18710]["Text2118"]
tNpcGossip[18710]["Text531"] = tFestivalMonthCardPackage_Text[18710]["Text251"]
tNpcGossip[18710]["Text532"] = tFestivalMonthCardPackage_Text[18710]["Text252"]
tNpcGossip[18710]["Text533"] = tFestivalMonthCardPackage_Text[18710]["Text253"]
tNpcGossip[18710]["Text534"] = tFestivalMonthCardPackage_Text[18710]["Text254"]
tNpcGossip[18710]["Text535"] = tFestivalMonthCardPackage_Text[18710]["Text255"]
tNpcGossip[18710]["Text536"] = tFestivalMonthCardPackage_Text[18710]["Text256"]
tNpcGossip[18710]["Text537"] = tFestivalMonthCardPackage_Text[18710]["Text257"]
tNpcGossip[18710]["Text538"] = tFestivalMonthCardPackage_Text[18710]["Text258"]
tNpcGossip[18710]["Text541"] = tFestivalMonthCardPackage_Text[18710]["Text261"]
tNpcGossip[18710]["Text542"] = tFestivalMonthCardPackage_Text[18710]["Text262"]
tNpcGossip[18710]["Text543"] = tFestivalMonthCardPackage_Text[18710]["Text263"]
tNpcGossip[18710]["Text544"] = tFestivalMonthCardPackage_Text[18710]["Text264"]
tNpcGossip[18710]["Text545"] = tFestivalMonthCardPackage_Text[18710]["Text265"]
tNpcGossip[18710]["Text546"] = tFestivalMonthCardPackage_Text[18710]["Text266"]
tNpcGossip[18710]["Text547"] = tFestivalMonthCardPackage_Text[18710]["Text267"]
tNpcGossip[18710]["Text548"] = tFestivalMonthCardPackage_Text[18710]["Text268"]
tNpcGossip[18710]["Text551"] = tFestivalMonthCardPackage_Text[18710]["Text271"]
tNpcGossip[18710]["Text552"] = tFestivalMonthCardPackage_Text[18710]["Text272"]
tNpcGossip[18710]["Text553"] = tFestivalMonthCardPackage_Text[18710]["Text273"]
tNpcGossip[18710]["Text554"] = tFestivalMonthCardPackage_Text[18710]["Text274"]
tNpcGossip[18710]["Text555"] = tFestivalMonthCardPackage_Text[18710]["Text275"]
tNpcGossip[18710]["Text556"] = tFestivalMonthCardPackage_Text[18710]["Text276"]
tNpcGossip[18710]["Text557"] = tFestivalMonthCardPackage_Text[18710]["Text277"]
tNpcGossip[18710]["Text558"] = tFestivalMonthCardPackage_Text[18710]["Text278"]
tNpcGossip[18710]["Text561"] = tFestivalMonthCardPackage_Text[18710]["Text281"]
tNpcGossip[18710]["Text562"] = tFestivalMonthCardPackage_Text[18710]["Text282"]
tNpcGossip[18710]["Text563"] = tFestivalMonthCardPackage_Text[18710]["Text283"]
tNpcGossip[18710]["Text564"] = tFestivalMonthCardPackage_Text[18710]["Text284"]
tNpcGossip[18710]["Text565"] = tFestivalMonthCardPackage_Text[18710]["Text285"]
tNpcGossip[18710]["Text566"] = tFestivalMonthCardPackage_Text[18710]["Text286"]
tNpcGossip[18710]["Text567"] = tFestivalMonthCardPackage_Text[18710]["Text287"]
tNpcGossip[18710]["Text568"] = tFestivalMonthCardPackage_Text[18710]["Text288"]
--选项
tNpcGossip[18710]["tOption5-1"] = {51,52}
tNpcGossip[18710]["tOption5-2"] = {51,52}
tNpcGossip[18710]["tOption5-3"] = {51,52}
tNpcGossip[18710]["tOption5-4"] = {51,52}
tNpcGossip[18710]["tOption5-5"] = {51,52}
tNpcGossip[18710]["tOption5-6"] = {51,52}
tNpcGossip[18710]["Option51"] = tFestivalMonthCardPackage_Text[18710]["Option51"]
tNpcGossip[18710]["Option52"] = tFestivalMonthCardPackage_Text[18710]["Option52"]
tNpcGossip[18710]["OptionPoint51"] = "4"






---------------------------------------物品配置---------------------------------------------
-------------------------------------【月卡礼包】---------------------------------------
tItem[3006930] = tItem[3006930] or {}
tItem[3006931] = tItem[3006930] or {}
tItem[3006932] = tItem[3006930] or {}
tItem[3006933] = tItem[3006930] or {}
tItem[3006934] = tItem[3006930] or {}
tItem[3006935] = tItem[3006930] or {}
tItem[3006936] = tItem[3006930] or {}
tItem[3006930]["Function"] = function (nItemId,sItemName)
	FestivalMonthCardPackage_RewardMain(nItemId)
end



-------------------------------------【宝石结晶】---------------------------------------
tItem[3006937] = tItem[3006937] or {}
tItem[3006937]["Text1-1"] = {111}		-- 初始对白
tItem[3006937]["Text1-2"] = {121}		-- 背包满
tItem[3006937]["Text1-3"] = {131}		-- 数量不足
tItem[3006937]["Text1-4"] = {141}		-- 二次确认
tItem[3006937]["Text111"] = tFestivalMonthCardPackage_Text[3006937]["Text111"] 
tItem[3006937]["Text121"] = tFestivalMonthCardPackage_Text[3006937]["Text121"] 
tItem[3006937]["Text131"] = tFestivalMonthCardPackage_Text[3006937]["Text131"] 
tItem[3006937]["Text141"] = tFestivalMonthCardPackage_Text[3006937]["Text141"] 
-- 选项
tItem[3006937]["tOption1-1"] = {11,12,13,14,15,16}
tItem[3006937]["tOption1-2"] = {17}
tItem[3006937]["tOption1-3"] = {17}
tItem[3006937]["tOption1-4"] = {18}
tItem[3006937]["Option11"] = tFestivalMonthCardPackage_Text[3006937]["Option11"]
tItem[3006937]["Option12"] = tFestivalMonthCardPackage_Text[3006937]["Option12"]
tItem[3006937]["Option13"] = tFestivalMonthCardPackage_Text[3006937]["Option13"]
tItem[3006937]["Option14"] = tFestivalMonthCardPackage_Text[3006937]["Option14"]
tItem[3006937]["Option15"] = tFestivalMonthCardPackage_Text[3006937]["Option15"]
tItem[3006937]["Option16"] = tFestivalMonthCardPackage_Text[3006937]["Option16"]
tItem[3006937]["Option17"] = tFestivalMonthCardPackage_Text[3006937]["Option17"]
tItem[3006937]["Option18"] = tFestivalMonthCardPackage_Text[3006937]["Option18"]
tItem[3006937]["OptionFunc11"] = "FestivalMonthCardPackage_GemCrystal</N>3006937</N>1</N>1"
tItem[3006937]["OptionFunc12"] = "FestivalMonthCardPackage_GemCrystal</N>3006937</N>2</N>2"
tItem[3006937]["OptionFunc13"] = "FestivalMonthCardPackage_GemCrystal</N>3006937</N>3</N>2"
tItem[3006937]["OptionFunc14"] = "FestivalMonthCardPackage_GemCrystal</N>3006937</N>4</N>3"
tItem[3006937]["OptionFunc15"] = "FestivalMonthCardPackage_GemCrystal</N>3006937</N>5</N>3"
tItem[3006937]["OptionFunc16"] = "FestivalMonthCardPackage_GemCrystal</N>3006937</N>6</N>15"
tItem[3006937]["OptionFunc18"] = ""

-------------------------------------【背包信】---------------------------------------
tItem[3006938] = tItem[3006938] or {}
tItem[3006938]["Text1-1"] = {111,112}		-- 初始对白
tItem[3006938]["Text111"] = tFestivalMonthCardPackage_Text[3006938]["Text111"] 
tItem[3006938]["Text112"] = tFestivalMonthCardPackage_Text[3006938]["Text112"] 
-- 选项
tItem[3006938]["tOption1-1"] = {11}
tItem[3006938]["Option11"] = tFestivalMonthCardPackage_Text[3006938]["Option11"]
tItem[3006938]["OptionFunc11"] = "FestivalMonthCardPackage_Letter</N>3006938"


-------------------------------------【203W系统自检】---------------------------------------
tOntimerMin_M[01] = tOntimerMin_M[01] or {}
table.insert(tOntimerMin_M[01],FestivalMonthCardPackage_NoticeBegin)
tOntimerMin_M[02] = tOntimerMin_M[02] or {}
table.insert(tOntimerMin_M[02],FestivalMonthCardPackage_NoticeBegin)
tOntimerMin_M[03] = tOntimerMin_M[03] or {}
table.insert(tOntimerMin_M[03],FestivalMonthCardPackage_NoticeBegin)
-- 4分-6分清掩码
tOntimerMin_M[04] = tOntimerMin_M[04] or {}
table.insert(tOntimerMin_M[04],FestivalMonthCardPackage_NoticeEnd)
tOntimerMin_M[05] = tOntimerMin_M[05] or {}
table.insert(tOntimerMin_M[05],FestivalMonthCardPackage_NoticeEnd)
tOntimerMin_M[06] = tOntimerMin_M[06] or {}
table.insert(tOntimerMin_M[06],FestivalMonthCardPackage_NoticeEnd)