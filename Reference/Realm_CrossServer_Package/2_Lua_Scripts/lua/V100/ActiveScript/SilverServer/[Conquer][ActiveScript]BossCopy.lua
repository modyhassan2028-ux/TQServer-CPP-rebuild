------------------------------------------------------------------------------------
--Name:			170827[英文征服][活动脚本]金币服相关内容制作个人boss部分
--Purpose:		金币服相关内容制作个人boss部分
--Creator:		陈琳
--Created:		2017/08/27
------------------------------------------------------------------------------------
-- lua.ini
-- 40657

-- logid
-- 12000851

-- 掩码说明
-- stc(165,57) 背包信
-- stc(165,58) 记录玩家每天挑战魔头的情况
-- stc(165,59) 记录玩家每天扫荡情况
-- stc(167,08) 记录玩家选择的魔头
-- stc(167,42) 记录玩家首通情况
-- stc(171,02) 记录每天每个怪物掉落情况

-- cq_dyna_global_data
-- 51755
-- data0 1为金币服
-- data1 3为开服第1日 2为开服第2日 1为开服第3日

-- npc
-- 22084 【魔头挑战】秘境传送大使
-- 22085 【魔头挑战】奖励宝箱
-- 22096 秘境守护黑龙

-- itemtype
-- 3305059 秘境30分钟经验礼盒
-- 3305060 秘境40分钟经验礼盒
-- 3305061 秘境50分钟经验礼盒
-- 3305062 秘境60分钟经验礼盒
-- 3305063 秘境70分钟经验礼盒
-- 3305064 秘境80分钟经验礼盒
-- 3305065 秘境90分钟经验礼盒
-- 3305066 秘境100分钟经验礼盒
-- 3305067 秘境110分钟经验礼盒
-- 3305068 秘境120分钟经验礼盒
-- 3305069 秘境130分钟经验礼盒
-- 3305070 秘境200分钟经验礼盒
-- 3305076 魔头挑战邀请函

-- 前缀
-- BossCopy_

--------------------------------------数据部分-------------------------------------------
local tBossCopy_Data = {}
	-- 等级
	tBossCopy_Data["Level"] = 50
	
	-- 副本
	tBossCopy_Data["Instance"] = 129
	
	-- 翻倍银两
	tBossCopy_Data["NeedMoney"] = 500000
	
	-- 新服开服奖励等级
	tBossCopy_Data["AwardLevel"] = 11
	
	-- log
	tBossCopy_Data["DelLog"] = "0,0,%d,0,12000851,2,0,0"
	
	-- 职业
	tBossCopy_Data["Pro"] = {}
	-- 勇士（10-15）
	tBossCopy_Data["Pro"][1] = {10,15}
	-- 战士（20-25）
	tBossCopy_Data["Pro"][2] = {20,25}
	-- 射手（40-45）
	tBossCopy_Data["Pro"][3] = {40,45}
	-- 忍者（50-55）
	tBossCopy_Data["Pro"][4] = {50,55}
	-- 武僧（60-65）
	tBossCopy_Data["Pro"][5] = {60,65}
	-- 海盗（70-75）
	tBossCopy_Data["Pro"][6] = {70,75}
	-- 拳师（80-85）
	tBossCopy_Data["Pro"][7] = {80,85}
	-- 道士（100-145） 水道（132-135） 火道（142-145）
	tBossCopy_Data["Pro"][8] = {{100,145},{132,135},{142,145}}
	-- 铁扇门
	tBossCopy_Data["Pro"][9] = {160,165}
	
	-- 坐标
	tBossCopy_Data["Location"] = {}
	tBossCopy_Data["Location"]["Instance"] = {}
	tBossCopy_Data["Location"]["Instance"]["PosX"] = 45
	tBossCopy_Data["Location"]["Instance"]["PosY"] = 44
	
	tBossCopy_Data["Location"]["Box"] = {}
	tBossCopy_Data["Location"]["Box"]["PosX"] = 42
	tBossCopy_Data["Location"]["Box"]["PosY"] = 40
	
	tBossCopy_Data["Location"]["Back"] = {}
	tBossCopy_Data["Location"]["Back"]["PosX"] = 464
	tBossCopy_Data["Location"]["Back"]["PosY"] = 378
	tBossCopy_Data["Location"]["Back"]["MapId"] = 1002
	
	-- nTask0
	tBossCopy_Data["Task0"] = {}
	tBossCopy_Data["Task0"][1] = 94136181
	tBossCopy_Data["Task0"][2] = 94136168
	
	-- NpcFace
	tBossCopy_Data["NpcFace"] = {}
	tBossCopy_Data["NpcFace"][1] = 57667
	tBossCopy_Data["NpcFace"][2] = 49980
	
	-- cq_generator
	tBossCopy_Data["GenId"] = 22636
	
	-- MonsterId                    50   60   70   80   90  100  110  115  120  125  130  135  40
	tBossCopy_Data["MonsterId"] = {3366,3367,3368,3369,3370,3371,3372,3373,3374,3375,3376,3377,3378}
	
	-- 等级索引               1  2  3  4  5   6   7   8   9  10  11  12  13
	tBossCopy_Data["Boss"] = {50,60,70,80,90,100,110,115,120,125,130,135,140}
	
	-- 等级临界                 1  2  3  4  5   6   7   8   9  10  11  12  13
	tBossCopy_Data["Crisis"] = {59,69,79,89,99,109,114,119,124,129,134,139,141}
	
	-- 扫荡背包空间            1 2 3 4 5 6 7 8 9 10 11 12 13
	tBossCopy_Data["Space"] = {0,0,0,1,3,4,5,6,7,8,9,10,11}
	
	-- Stc掩码
	tBossCopy_Data["Stc"] = {}
	-- stc(165,58) 记录玩家每天挑战魔头的情况
	tBossCopy_Data["Stc"]["Daily"] = {}
	tBossCopy_Data["Stc"]["Daily"]["EventType"] = 165
	tBossCopy_Data["Stc"]["Daily"]["DataType"] = 58
	-- stc(165,59) 记录玩家每天扫荡情况
	tBossCopy_Data["Stc"]["Clear"] = {}
	tBossCopy_Data["Stc"]["Clear"]["EventType"] = 165
	tBossCopy_Data["Stc"]["Clear"]["DataType"] = 59
	tBossCopy_Data["Stc"]["Clear"]["Complete"] = 1
	-- stc(167,08) 记录玩家选择的魔头
	tBossCopy_Data["Stc"]["Monster"] = {}
	tBossCopy_Data["Stc"]["Monster"]["EventType"] = 167
	tBossCopy_Data["Stc"]["Monster"]["DataType"] = 08
	-- stc(167,42) 记录玩家首通情况
	tBossCopy_Data["Stc"]["First"] = {}
	tBossCopy_Data["Stc"]["First"]["EventType"] = 167
	tBossCopy_Data["Stc"]["First"]["DataType"] = 42
	tBossCopy_Data["Stc"]["First"]["Complete"] = 1
	-- stc(171,02) 记录每天每个怪物掉落情况
	tBossCopy_Data["Stc"]["Drop"] = {}
	tBossCopy_Data["Stc"]["Drop"]["EventType"] = 171
	tBossCopy_Data["Stc"]["Drop"]["DataType"] = 02
	
	-- 光效
	tBossCopy_Data["Effect"] = {}
	tBossCopy_Data["Effect"]["OpenPack"] = "zf2-e128"
	
	-- 动态码
	tBossCopy_Data["GlobalId"] = {}
	tBossCopy_Data["GlobalId"]["Silver"] = 51755
	
	-- itemtype
	tBossCopy_Data["Itemtype"] = {}
	-- 首通
	tBossCopy_Data["Itemtype"]["First"] = {}
	-- 精品50级衣服
	-- 勇士    战士    弓手    忍者    武僧    海盗    小龙    道士    铁扇
	-- 130048  131058  133038  135038  136048  139048  138048  134038  101048
	tBossCopy_Data["Itemtype"]["First"][1] = {130048,131058,133038,135038,136048,139048,138048,134038,101048}
	-- 精品70级武器
	-- 勇士    战士    弓手    忍者    武僧    海盗    小龙    道士    铁扇
	-- 410138  561138  613128  601138  610138  611138  617138  421138  626138
	tBossCopy_Data["Itemtype"]["First"][3] = {410138,561138,613128,601138,610138,611138,617138,421138,626138}
	-- 精品90级衣服
	-- 勇士    战士    弓手    忍者    武僧    海盗    小龙    道士    铁扇
	-- 130078  131078  133068  135078  136078  139078  138078  134078  101078
	tBossCopy_Data["Itemtype"]["First"][5] = {130078,131078,133068,135078,136078,139078,138078,134078,101078}

-- 二进制
local tBossCopy_Binary = {}
	for i = 1,13 do
		tBossCopy_Binary[i] = 2^(i-1)
	end
	
local tBossCopy_Pack = {}
	
	-- 3305059 秘境30分钟经验礼盒
	tBossCopy_Pack[3305059] = {}
	tBossCopy_Pack[3305059]["RewardExpTime"] = {}
	tBossCopy_Pack[3305059]["RewardExpTime"]["Value"] = 30
	tBossCopy_Pack[3305059]["DeleteItem"] = {}
	tBossCopy_Pack[3305059]["DeleteItem"][1] = {}
	tBossCopy_Pack[3305059]["DeleteItem"][1]["Id"] = 3305059
	tBossCopy_Pack[3305059]["DeleteItem"][1]["ItemNum"] = 1
	tBossCopy_Pack[3305059]["LogId"] = 12000851
	tBossCopy_Pack[3305059]["RewardEffect"] = {}
	tBossCopy_Pack[3305059]["RewardEffect"]["Effect"] = tBossCopy_Data["Effect"]["OpenPack"]
	
	-- 3305060 秘境40分钟经验礼盒
	tBossCopy_Pack[3305060] = {}
	tBossCopy_Pack[3305060]["RewardExpTime"] = {}
	tBossCopy_Pack[3305060]["RewardExpTime"]["Value"] = 40
	tBossCopy_Pack[3305060]["DeleteItem"] = {}
	tBossCopy_Pack[3305060]["DeleteItem"][1] = {}
	tBossCopy_Pack[3305060]["DeleteItem"][1]["Id"] = 3305060
	tBossCopy_Pack[3305060]["DeleteItem"][1]["ItemNum"] = 1
	tBossCopy_Pack[3305060]["LogId"] = 12000851
	tBossCopy_Pack[3305060]["RewardEffect"] = {}
	tBossCopy_Pack[3305060]["RewardEffect"]["Effect"] = tBossCopy_Data["Effect"]["OpenPack"]
	
	-- 3305061 秘境50分钟经验礼盒
	tBossCopy_Pack[3305061] = {}
	tBossCopy_Pack[3305061]["RewardExpTime"] = {}
	tBossCopy_Pack[3305061]["RewardExpTime"]["Value"] = 50
	tBossCopy_Pack[3305061]["DeleteItem"] = {}
	tBossCopy_Pack[3305061]["DeleteItem"][1] = {}
	tBossCopy_Pack[3305061]["DeleteItem"][1]["Id"] = 3305061
	tBossCopy_Pack[3305061]["DeleteItem"][1]["ItemNum"] = 1
	tBossCopy_Pack[3305061]["LogId"] = 12000851
	tBossCopy_Pack[3305061]["RewardEffect"] = {}
	tBossCopy_Pack[3305061]["RewardEffect"]["Effect"] = tBossCopy_Data["Effect"]["OpenPack"]
	
	-- 3305062 秘境60分钟经验礼盒
	tBossCopy_Pack[3305062] = {}
	tBossCopy_Pack[3305062]["RewardExpTime"] = {}
	tBossCopy_Pack[3305062]["RewardExpTime"]["Value"] = 60
	tBossCopy_Pack[3305062]["DeleteItem"] = {}
	tBossCopy_Pack[3305062]["DeleteItem"][1] = {}
	tBossCopy_Pack[3305062]["DeleteItem"][1]["Id"] = 3305062
	tBossCopy_Pack[3305062]["DeleteItem"][1]["ItemNum"] = 1
	tBossCopy_Pack[3305062]["LogId"] = 12000851
	tBossCopy_Pack[3305062]["RewardEffect"] = {}
	tBossCopy_Pack[3305062]["RewardEffect"]["Effect"] = tBossCopy_Data["Effect"]["OpenPack"]
	
	-- 3305063 秘境70分钟经验礼盒
	tBossCopy_Pack[3305063] = {}
	tBossCopy_Pack[3305063]["RewardExpTime"] = {}
	tBossCopy_Pack[3305063]["RewardExpTime"]["Value"] = 70
	tBossCopy_Pack[3305063]["DeleteItem"] = {}
	tBossCopy_Pack[3305063]["DeleteItem"][1] = {}
	tBossCopy_Pack[3305063]["DeleteItem"][1]["Id"] = 3305063
	tBossCopy_Pack[3305063]["DeleteItem"][1]["ItemNum"] = 1
	tBossCopy_Pack[3305063]["LogId"] = 12000851
	tBossCopy_Pack[3305063]["RewardEffect"] = {}
	tBossCopy_Pack[3305063]["RewardEffect"]["Effect"] = tBossCopy_Data["Effect"]["OpenPack"]
	
	-- 3305064 秘境80分钟经验礼盒
	tBossCopy_Pack[3305064] = {}
	tBossCopy_Pack[3305064]["RewardExpTime"] = {}
	tBossCopy_Pack[3305064]["RewardExpTime"]["Value"] = 80
	tBossCopy_Pack[3305064]["DeleteItem"] = {}
	tBossCopy_Pack[3305064]["DeleteItem"][1] = {}
	tBossCopy_Pack[3305064]["DeleteItem"][1]["Id"] = 3305064
	tBossCopy_Pack[3305064]["DeleteItem"][1]["ItemNum"] = 1
	tBossCopy_Pack[3305064]["LogId"] = 12000851
	tBossCopy_Pack[3305064]["RewardEffect"] = {}
	tBossCopy_Pack[3305064]["RewardEffect"]["Effect"] = tBossCopy_Data["Effect"]["OpenPack"]
	
	-- 3305065 秘境90分钟经验礼盒
	tBossCopy_Pack[3305065] = {}
	tBossCopy_Pack[3305065]["RewardExpTime"] = {}
	tBossCopy_Pack[3305065]["RewardExpTime"]["Value"] = 90
	tBossCopy_Pack[3305065]["DeleteItem"] = {}
	tBossCopy_Pack[3305065]["DeleteItem"][1] = {}
	tBossCopy_Pack[3305065]["DeleteItem"][1]["Id"] = 3305065
	tBossCopy_Pack[3305065]["DeleteItem"][1]["ItemNum"] = 1
	tBossCopy_Pack[3305065]["LogId"] = 12000851
	tBossCopy_Pack[3305065]["RewardEffect"] = {}
	tBossCopy_Pack[3305065]["RewardEffect"]["Effect"] = tBossCopy_Data["Effect"]["OpenPack"]
	
	-- 3305066 秘境100分钟经验礼盒
	tBossCopy_Pack[3305066] = {}
	tBossCopy_Pack[3305066]["RewardExpTime"] = {}
	tBossCopy_Pack[3305066]["RewardExpTime"]["Value"] = 100
	tBossCopy_Pack[3305066]["DeleteItem"] = {}
	tBossCopy_Pack[3305066]["DeleteItem"][1] = {}
	tBossCopy_Pack[3305066]["DeleteItem"][1]["Id"] = 3305066
	tBossCopy_Pack[3305066]["DeleteItem"][1]["ItemNum"] = 1
	tBossCopy_Pack[3305066]["LogId"] = 12000851
	tBossCopy_Pack[3305066]["RewardEffect"] = {}
	tBossCopy_Pack[3305066]["RewardEffect"]["Effect"] = tBossCopy_Data["Effect"]["OpenPack"]
	
	-- 3305067 秘境110分钟经验礼盒
	tBossCopy_Pack[3305067] = {}
	tBossCopy_Pack[3305067]["RewardExpTime"] = {}
	tBossCopy_Pack[3305067]["RewardExpTime"]["Value"] = 110
	tBossCopy_Pack[3305067]["DeleteItem"] = {}
	tBossCopy_Pack[3305067]["DeleteItem"][1] = {}
	tBossCopy_Pack[3305067]["DeleteItem"][1]["Id"] = 3305067
	tBossCopy_Pack[3305067]["DeleteItem"][1]["ItemNum"] = 1
	tBossCopy_Pack[3305067]["LogId"] = 12000851
	tBossCopy_Pack[3305067]["RewardEffect"] = {}
	tBossCopy_Pack[3305067]["RewardEffect"]["Effect"] = tBossCopy_Data["Effect"]["OpenPack"]
	
	-- 3305068 秘境120分钟经验礼盒
	tBossCopy_Pack[3305068] = {}
	tBossCopy_Pack[3305068]["RewardExpTime"] = {}
	tBossCopy_Pack[3305068]["RewardExpTime"]["Value"] = 120
	tBossCopy_Pack[3305068]["DeleteItem"] = {}
	tBossCopy_Pack[3305068]["DeleteItem"][1] = {}
	tBossCopy_Pack[3305068]["DeleteItem"][1]["Id"] = 3305068
	tBossCopy_Pack[3305068]["DeleteItem"][1]["ItemNum"] = 1
	tBossCopy_Pack[3305068]["LogId"] = 12000851
	tBossCopy_Pack[3305068]["RewardEffect"] = {}
	tBossCopy_Pack[3305068]["RewardEffect"]["Effect"] = tBossCopy_Data["Effect"]["OpenPack"]
	
	-- 3305069 秘境130分钟经验礼盒
	tBossCopy_Pack[3305069] = {}
	tBossCopy_Pack[3305069]["RewardExpTime"] = {}
	tBossCopy_Pack[3305069]["RewardExpTime"]["Value"] = 130
	tBossCopy_Pack[3305069]["DeleteItem"] = {}
	tBossCopy_Pack[3305069]["DeleteItem"][1] = {}
	tBossCopy_Pack[3305069]["DeleteItem"][1]["Id"] = 3305069
	tBossCopy_Pack[3305069]["DeleteItem"][1]["ItemNum"] = 1
	tBossCopy_Pack[3305069]["LogId"] = 12000851
	tBossCopy_Pack[3305069]["RewardEffect"] = {}
	tBossCopy_Pack[3305069]["RewardEffect"]["Effect"] = tBossCopy_Data["Effect"]["OpenPack"]
	
	-- 3305070 秘境200分钟经验礼盒
	tBossCopy_Pack[3305070] = {}
	tBossCopy_Pack[3305070]["RewardExpTime"] = {}
	tBossCopy_Pack[3305070]["RewardExpTime"]["Value"] = 200
	tBossCopy_Pack[3305070]["DeleteItem"] = {}
	tBossCopy_Pack[3305070]["DeleteItem"][1] = {}
	tBossCopy_Pack[3305070]["DeleteItem"][1]["Id"] = 3305070
	tBossCopy_Pack[3305070]["DeleteItem"][1]["ItemNum"] = 1
	tBossCopy_Pack[3305070]["LogId"] = 12000851
	tBossCopy_Pack[3305070]["RewardEffect"] = {}
	tBossCopy_Pack[3305070]["RewardEffect"]["Effect"] = tBossCopy_Data["Effect"]["OpenPack"]
	
	-- 免费强炼丹小礼包	3003124	monopoly	0
	tBossCopy_Pack[3305115] = {}
	tBossCopy_Pack[3305115]["RewardItem"] = {}
	tBossCopy_Pack[3305115]["RewardItem"][1] = {}
	tBossCopy_Pack[3305115]["RewardItem"][1]["Id"] = 3003124
	tBossCopy_Pack[3305115]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305115]["DeleteItem"] = {}
	tBossCopy_Pack[3305115]["DeleteItem"][1] = {}
	tBossCopy_Pack[3305115]["DeleteItem"][1]["Id"] = 3305115
	tBossCopy_Pack[3305115]["DeleteItem"][1]["ItemNum"] = 1
	tBossCopy_Pack[3305115]["LogId"] = 12000851
	tBossCopy_Pack[3305115]["RewardEffect"] = {}
	tBossCopy_Pack[3305115]["RewardEffect"]["Effect"] = tBossCopy_Data["Effect"]["OpenPack"]
	
	-- 通神丹小礼包	3003125	monopoly	0
	tBossCopy_Pack[3305116] = {}
	tBossCopy_Pack[3305116]["RewardItem"] = {}
	tBossCopy_Pack[3305116]["RewardItem"][1] = {}
	tBossCopy_Pack[3305116]["RewardItem"][1]["Id"] = 3003125
	tBossCopy_Pack[3305116]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305116]["DeleteItem"] = {}
	tBossCopy_Pack[3305116]["DeleteItem"][1] = {}
	tBossCopy_Pack[3305116]["DeleteItem"][1]["Id"] = 3305116
	tBossCopy_Pack[3305116]["DeleteItem"][1]["ItemNum"] = 1
	tBossCopy_Pack[3305116]["LogId"] = 12000851
	tBossCopy_Pack[3305116]["RewardEffect"] = {}
	tBossCopy_Pack[3305116]["RewardEffect"]["Effect"] = tBossCopy_Data["Effect"]["OpenPack"]
	
	-- 究极通神丹小礼包	3003126	monopoly	0
	tBossCopy_Pack[3305117] = {}
	tBossCopy_Pack[3305117]["RewardItem"] = {}
	tBossCopy_Pack[3305117]["RewardItem"][1] = {}
	tBossCopy_Pack[3305117]["RewardItem"][1]["Id"] = 3003126
	tBossCopy_Pack[3305117]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305117]["DeleteItem"] = {}
	tBossCopy_Pack[3305117]["DeleteItem"][1] = {}
	tBossCopy_Pack[3305117]["DeleteItem"][1]["Id"] = 3305117
	tBossCopy_Pack[3305117]["DeleteItem"][1]["ItemNum"] = 1
	tBossCopy_Pack[3305117]["LogId"] = 12000851
	tBossCopy_Pack[3305117]["RewardEffect"] = {}
	tBossCopy_Pack[3305117]["RewardEffect"]["Effect"] = tBossCopy_Data["Effect"]["OpenPack"]
	
	-- 经验球小礼包
	tBossCopy_Pack[3306659] = {}
	tBossCopy_Pack[3306659]["RewardItem"] = {}
	tBossCopy_Pack[3306659]["RewardItem"][1] = {}
	tBossCopy_Pack[3306659]["RewardItem"][1]["Id"] = 723700
	tBossCopy_Pack[3306659]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3306659]["DeleteItem"] = {}
	tBossCopy_Pack[3306659]["DeleteItem"][1] = {}
	tBossCopy_Pack[3306659]["DeleteItem"][1]["Id"] = 3306659
	tBossCopy_Pack[3306659]["DeleteItem"][1]["ItemNum"] = 1
	tBossCopy_Pack[3306659]["LogId"] = 12000851
	tBossCopy_Pack[3306659]["RewardEffect"] = {}
	tBossCopy_Pack[3306659]["RewardEffect"]["Effect"] = tBossCopy_Data["Effect"]["OpenPack"]
	
	-- 50级 精品装备
	tBossCopy_Pack[3305091] = {}
	-- 勇士（10-15）
	tBossCopy_Pack[3305091][1] = {}
	tBossCopy_Pack[3305091][1]["LogId"] = 12000851
	tBossCopy_Pack[3305091][1]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305091][1][1] = {}
	tBossCopy_Pack[3305091][1][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305091][1][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305091][1][1]["RewardItem"] = {}
	tBossCopy_Pack[3305091][1][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305091][1][1]["RewardItem"][1]["Id"] = 410098
	tBossCopy_Pack[3305091][1][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305091][1][2] = {}
	tBossCopy_Pack[3305091][1][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305091][1][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305091][1][2]["RewardItem"] = {}
	tBossCopy_Pack[3305091][1][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305091][1][2]["RewardItem"][1]["Id"] = 150098
	tBossCopy_Pack[3305091][1][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 战士（20-25）
	tBossCopy_Pack[3305091][2] = {}
	tBossCopy_Pack[3305091][2]["LogId"] = 12000851
	tBossCopy_Pack[3305091][2]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305091][2][1] = {}
	tBossCopy_Pack[3305091][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305091][2][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305091][2][1]["RewardItem"] = {}
	tBossCopy_Pack[3305091][2][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305091][2][1]["RewardItem"][1]["Id"] = 624098
	tBossCopy_Pack[3305091][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305091][2][2] = {}
	tBossCopy_Pack[3305091][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305091][2][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305091][2][2]["RewardItem"] = {}
	tBossCopy_Pack[3305091][2][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305091][2][2]["RewardItem"][1]["Id"] = 150098
	tBossCopy_Pack[3305091][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 射手（40-45）
	tBossCopy_Pack[3305091][3] = {}
	tBossCopy_Pack[3305091][3]["LogId"] = 12000851
	tBossCopy_Pack[3305091][3]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305091][3][1] = {}
	tBossCopy_Pack[3305091][3][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305091][3][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305091][3][1]["RewardItem"] = {}
	tBossCopy_Pack[3305091][3][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305091][3][1]["RewardItem"][1]["Id"] = 613088
	tBossCopy_Pack[3305091][3][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305091][3][2] = {}
	tBossCopy_Pack[3305091][3][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305091][3][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305091][3][2]["RewardItem"] = {}
	tBossCopy_Pack[3305091][3][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305091][3][2]["RewardItem"][1]["Id"] = 150098
	tBossCopy_Pack[3305091][3][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 忍者（50-55）
	tBossCopy_Pack[3305091][4] = {}
	tBossCopy_Pack[3305091][4]["LogId"] = 12000851
	tBossCopy_Pack[3305091][4]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305091][4][1] = {}
	tBossCopy_Pack[3305091][4][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305091][4][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305091][4][1]["RewardItem"] = {}
	tBossCopy_Pack[3305091][4][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305091][4][1]["RewardItem"][1]["Id"] = 601098
	tBossCopy_Pack[3305091][4][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305091][4][2] = {}
	tBossCopy_Pack[3305091][4][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305091][4][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305091][4][2]["RewardItem"] = {}
	tBossCopy_Pack[3305091][4][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305091][4][2]["RewardItem"][1]["Id"] = 150098
	tBossCopy_Pack[3305091][4][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 武僧（60-65）
	tBossCopy_Pack[3305091][5] = {}
	tBossCopy_Pack[3305091][5]["LogId"] = 12000851
	tBossCopy_Pack[3305091][5]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305091][5][1] = {}
	tBossCopy_Pack[3305091][5][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305091][5][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305091][5][1]["RewardItem"] = {}
	tBossCopy_Pack[3305091][5][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305091][5][1]["RewardItem"][1]["Id"] = 610098
	tBossCopy_Pack[3305091][5][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305091][5][2] = {}
	tBossCopy_Pack[3305091][5][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305091][5][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305091][5][2]["RewardItem"] = {}
	tBossCopy_Pack[3305091][5][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305091][5][2]["RewardItem"][1]["Id"] = 150098
	tBossCopy_Pack[3305091][5][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 海盗（70-75）
	tBossCopy_Pack[3305091][6] = {}
	tBossCopy_Pack[3305091][6]["LogId"] = 12000851
	tBossCopy_Pack[3305091][6]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305091][6][1] = {}
	tBossCopy_Pack[3305091][6][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305091][6][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305091][6][1]["RewardItem"] = {}
	tBossCopy_Pack[3305091][6][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305091][6][1]["RewardItem"][1]["Id"] = 611098
	tBossCopy_Pack[3305091][6][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305091][6][2] = {}
	tBossCopy_Pack[3305091][6][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305091][6][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305091][6][2]["RewardItem"] = {}
	tBossCopy_Pack[3305091][6][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305091][6][2]["RewardItem"][1]["Id"] = 150098
	tBossCopy_Pack[3305091][6][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 拳师（80-85）
	tBossCopy_Pack[3305091][7] = {}
	tBossCopy_Pack[3305091][7]["LogId"] = 12000851
	tBossCopy_Pack[3305091][7]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305091][7][1] = {}
	tBossCopy_Pack[3305091][7][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305091][7][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305091][7][1]["RewardItem"] = {}
	tBossCopy_Pack[3305091][7][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305091][7][1]["RewardItem"][1]["Id"] = 617098
	tBossCopy_Pack[3305091][7][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305091][7][2] = {}
	tBossCopy_Pack[3305091][7][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305091][7][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305091][7][2]["RewardItem"] = {}
	tBossCopy_Pack[3305091][7][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305091][7][2]["RewardItem"][1]["Id"] = 150098
	tBossCopy_Pack[3305091][7][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 道士（100-145） -- 水道（132-135） -- 火道（142-145）
	tBossCopy_Pack[3305091][8] = {}
	tBossCopy_Pack[3305091][8]["LogId"] = 12000851
	tBossCopy_Pack[3305091][8]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305091][8][1] = {}
	tBossCopy_Pack[3305091][8][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305091][8][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305091][8][1]["RewardItem"] = {}
	tBossCopy_Pack[3305091][8][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305091][8][1]["RewardItem"][1]["Id"] = 421108
	tBossCopy_Pack[3305091][8][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305091][8][2] = {}
	tBossCopy_Pack[3305091][8][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305091][8][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305091][8][2]["RewardItem"] = {}
	tBossCopy_Pack[3305091][8][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305091][8][2]["RewardItem"][1]["Id"] = 150098
	tBossCopy_Pack[3305091][8][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 铁扇门
	tBossCopy_Pack[3305091][9] = {}
	tBossCopy_Pack[3305091][9]["LogId"] = 12000851
	tBossCopy_Pack[3305091][9]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305091][9][1] = {}
	tBossCopy_Pack[3305091][9][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305091][9][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305091][9][1]["RewardItem"] = {}
	tBossCopy_Pack[3305091][9][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305091][9][1]["RewardItem"][1]["Id"] = 626098
	tBossCopy_Pack[3305091][9][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305091][9][2] = {}
	tBossCopy_Pack[3305091][9][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305091][9][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305091][9][2]["RewardItem"] = {}
	tBossCopy_Pack[3305091][9][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305091][9][2]["RewardItem"][1]["Id"] = 150098
	tBossCopy_Pack[3305091][9][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
	-- 50级 极品装备
	tBossCopy_Pack[3305092] = {}
	-- 勇士（10-15）
	tBossCopy_Pack[3305092][1] = {}
	tBossCopy_Pack[3305092][1]["LogId"] = 12000851
	tBossCopy_Pack[3305092][1]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305092][1][1] = {}
	tBossCopy_Pack[3305092][1][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305092][1][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305092][1][1]["RewardItem"] = {}
	tBossCopy_Pack[3305092][1][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305092][1][1]["RewardItem"][1]["Id"] = 410099
	tBossCopy_Pack[3305092][1][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305092][1][2] = {}
	tBossCopy_Pack[3305092][1][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305092][1][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305092][1][2]["RewardItem"] = {}
	tBossCopy_Pack[3305092][1][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305092][1][2]["RewardItem"][1]["Id"] = 150099
	tBossCopy_Pack[3305092][1][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 战士（20-25）
	tBossCopy_Pack[3305092][2] = {}
	tBossCopy_Pack[3305092][2]["LogId"] = 12000851
	tBossCopy_Pack[3305092][2]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305092][2][1] = {}
	tBossCopy_Pack[3305092][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305092][2][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305092][2][1]["RewardItem"] = {}
	tBossCopy_Pack[3305092][2][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305092][2][1]["RewardItem"][1]["Id"] = 624099
	tBossCopy_Pack[3305092][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305092][2][2] = {}
	tBossCopy_Pack[3305092][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305092][2][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305092][2][2]["RewardItem"] = {}
	tBossCopy_Pack[3305092][2][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305092][2][2]["RewardItem"][1]["Id"] = 150099
	tBossCopy_Pack[3305092][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 射手（40-45）
	tBossCopy_Pack[3305092][3] = {}
	tBossCopy_Pack[3305092][3]["LogId"] = 12000851
	tBossCopy_Pack[3305092][3]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305092][3][1] = {}
	tBossCopy_Pack[3305092][3][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305092][3][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305092][3][1]["RewardItem"] = {}
	tBossCopy_Pack[3305092][3][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305092][3][1]["RewardItem"][1]["Id"] = 613089
	tBossCopy_Pack[3305092][3][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305092][3][2] = {}
	tBossCopy_Pack[3305092][3][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305092][3][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305092][3][2]["RewardItem"] = {}
	tBossCopy_Pack[3305092][3][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305092][3][2]["RewardItem"][1]["Id"] = 150099
	tBossCopy_Pack[3305092][3][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 忍者（50-55）
	tBossCopy_Pack[3305092][4] = {}
	tBossCopy_Pack[3305092][4]["LogId"] = 12000851
	tBossCopy_Pack[3305092][4]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305092][4][1] = {}
	tBossCopy_Pack[3305092][4][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305092][4][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305092][4][1]["RewardItem"] = {}
	tBossCopy_Pack[3305092][4][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305092][4][1]["RewardItem"][1]["Id"] = 601099
	tBossCopy_Pack[3305092][4][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305092][4][2] = {}
	tBossCopy_Pack[3305092][4][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305092][4][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305092][4][2]["RewardItem"] = {}
	tBossCopy_Pack[3305092][4][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305092][4][2]["RewardItem"][1]["Id"] = 150099
	tBossCopy_Pack[3305092][4][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 武僧（60-65）
	tBossCopy_Pack[3305092][5] = {}
	tBossCopy_Pack[3305092][5]["LogId"] = 12000851
	tBossCopy_Pack[3305092][5]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305092][5][1] = {}
	tBossCopy_Pack[3305092][5][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305092][5][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305092][5][1]["RewardItem"] = {}
	tBossCopy_Pack[3305092][5][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305092][5][1]["RewardItem"][1]["Id"] = 610099
	tBossCopy_Pack[3305092][5][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305092][5][2] = {}
	tBossCopy_Pack[3305092][5][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305092][5][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305092][5][2]["RewardItem"] = {}
	tBossCopy_Pack[3305092][5][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305092][5][2]["RewardItem"][1]["Id"] = 150099
	tBossCopy_Pack[3305092][5][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 海盗（70-75）
	tBossCopy_Pack[3305092][6] = {}
	tBossCopy_Pack[3305092][6]["LogId"] = 12000851
	tBossCopy_Pack[3305092][6]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305092][6][1] = {}
	tBossCopy_Pack[3305092][6][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305092][6][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305092][6][1]["RewardItem"] = {}
	tBossCopy_Pack[3305092][6][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305092][6][1]["RewardItem"][1]["Id"] = 611099
	tBossCopy_Pack[3305092][6][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305092][6][2] = {}
	tBossCopy_Pack[3305092][6][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305092][6][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305092][6][2]["RewardItem"] = {}
	tBossCopy_Pack[3305092][6][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305092][6][2]["RewardItem"][1]["Id"] = 150099
	tBossCopy_Pack[3305092][6][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 拳师（80-85）
	tBossCopy_Pack[3305092][7] = {}
	tBossCopy_Pack[3305092][7]["LogId"] = 12000851
	tBossCopy_Pack[3305092][7]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305092][7][1] = {}
	tBossCopy_Pack[3305092][7][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305092][7][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305092][7][1]["RewardItem"] = {}
	tBossCopy_Pack[3305092][7][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305092][7][1]["RewardItem"][1]["Id"] = 617099
	tBossCopy_Pack[3305092][7][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305092][7][2] = {}
	tBossCopy_Pack[3305092][7][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305092][7][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305092][7][2]["RewardItem"] = {}
	tBossCopy_Pack[3305092][7][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305092][7][2]["RewardItem"][1]["Id"] = 150099
	tBossCopy_Pack[3305092][7][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 道士（100-145） -- 水道（132-135） -- 火道（142-145）
	tBossCopy_Pack[3305092][8] = {}
	tBossCopy_Pack[3305092][8]["LogId"] = 12000851
	tBossCopy_Pack[3305092][8]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305092][8][1] = {}
	tBossCopy_Pack[3305092][8][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305092][8][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305092][8][1]["RewardItem"] = {}
	tBossCopy_Pack[3305092][8][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305092][8][1]["RewardItem"][1]["Id"] = 421109
	tBossCopy_Pack[3305092][8][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305092][8][2] = {}
	tBossCopy_Pack[3305092][8][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305092][8][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305092][8][2]["RewardItem"] = {}
	tBossCopy_Pack[3305092][8][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305092][8][2]["RewardItem"][1]["Id"] = 150099
	tBossCopy_Pack[3305092][8][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 铁扇门
	tBossCopy_Pack[3305092][9] = {}
	tBossCopy_Pack[3305092][9]["LogId"] = 12000851
	tBossCopy_Pack[3305092][9]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305092][9][1] = {}
	tBossCopy_Pack[3305092][9][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305092][9][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305092][9][1]["RewardItem"] = {}
	tBossCopy_Pack[3305092][9][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305092][9][1]["RewardItem"][1]["Id"] = 626099
	tBossCopy_Pack[3305092][9][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305092][9][2] = {}
	tBossCopy_Pack[3305092][9][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305092][9][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305092][9][2]["RewardItem"] = {}
	tBossCopy_Pack[3305092][9][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305092][9][2]["RewardItem"][1]["Id"] = 150099
	tBossCopy_Pack[3305092][9][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
	-- 60级 精品装备
	tBossCopy_Pack[3305093] = {}
	-- 勇士（10-15）
	tBossCopy_Pack[3305093][1] = {}
	tBossCopy_Pack[3305093][1]["LogId"] = 12000851
	tBossCopy_Pack[3305093][1]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305093][1][1] = {}
	tBossCopy_Pack[3305093][1][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305093][1][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305093][1][1]["RewardItem"] = {}
	tBossCopy_Pack[3305093][1][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305093][1][1]["RewardItem"][1]["Id"] = 130058
	tBossCopy_Pack[3305093][1][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305093][1][2] = {}
	tBossCopy_Pack[3305093][1][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305093][1][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305093][1][2]["RewardItem"] = {}
	tBossCopy_Pack[3305093][1][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305093][1][2]["RewardItem"][1]["Id"] = 120098
	tBossCopy_Pack[3305093][1][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 战士（20-25）
	tBossCopy_Pack[3305093][2] = {}
	tBossCopy_Pack[3305093][2]["LogId"] = 12000851
	tBossCopy_Pack[3305093][2]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305093][2][1] = {}
	tBossCopy_Pack[3305093][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305093][2][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305093][2][1]["RewardItem"] = {}
	tBossCopy_Pack[3305093][2][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305093][2][1]["RewardItem"][1]["Id"] = 131058
	tBossCopy_Pack[3305093][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305093][2][2] = {}
	tBossCopy_Pack[3305093][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305093][2][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305093][2][2]["RewardItem"] = {}
	tBossCopy_Pack[3305093][2][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305093][2][2]["RewardItem"][1]["Id"] = 120098
	tBossCopy_Pack[3305093][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 射手（40-45）
	tBossCopy_Pack[3305093][3] = {}
	tBossCopy_Pack[3305093][3]["LogId"] = 12000851
	tBossCopy_Pack[3305093][3]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305093][3][1] = {}
	tBossCopy_Pack[3305093][3][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305093][3][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305093][3][1]["RewardItem"] = {}
	tBossCopy_Pack[3305093][3][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305093][3][1]["RewardItem"][1]["Id"] = 133038
	tBossCopy_Pack[3305093][3][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305093][3][2] = {}
	tBossCopy_Pack[3305093][3][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305093][3][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305093][3][2]["RewardItem"] = {}
	tBossCopy_Pack[3305093][3][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305093][3][2]["RewardItem"][1]["Id"] = 120098
	tBossCopy_Pack[3305093][3][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 忍者（50-55）
	tBossCopy_Pack[3305093][4] = {}
	tBossCopy_Pack[3305093][4]["LogId"] = 12000851
	tBossCopy_Pack[3305093][4]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305093][4][1] = {}
	tBossCopy_Pack[3305093][4][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305093][4][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305093][4][1]["RewardItem"] = {}
	tBossCopy_Pack[3305093][4][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305093][4][1]["RewardItem"][1]["Id"] = 135058
	tBossCopy_Pack[3305093][4][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305093][4][2] = {}
	tBossCopy_Pack[3305093][4][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305093][4][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305093][4][2]["RewardItem"] = {}
	tBossCopy_Pack[3305093][4][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305093][4][2]["RewardItem"][1]["Id"] = 120098
	tBossCopy_Pack[3305093][4][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 武僧（60-65）
	tBossCopy_Pack[3305093][5] = {}
	tBossCopy_Pack[3305093][5]["LogId"] = 12000851
	tBossCopy_Pack[3305093][5]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305093][5][1] = {}
	tBossCopy_Pack[3305093][5][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305093][5][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305093][5][1]["RewardItem"] = {}
	tBossCopy_Pack[3305093][5][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305093][5][1]["RewardItem"][1]["Id"] = 136058
	tBossCopy_Pack[3305093][5][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305093][5][2] = {}
	tBossCopy_Pack[3305093][5][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305093][5][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305093][5][2]["RewardItem"] = {}
	tBossCopy_Pack[3305093][5][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305093][5][2]["RewardItem"][1]["Id"] = 120098
	tBossCopy_Pack[3305093][5][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 海盗（70-75）
	tBossCopy_Pack[3305093][6] = {}
	tBossCopy_Pack[3305093][6]["LogId"] = 12000851
	tBossCopy_Pack[3305093][6]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305093][6][1] = {}
	tBossCopy_Pack[3305093][6][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305093][6][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305093][6][1]["RewardItem"] = {}
	tBossCopy_Pack[3305093][6][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305093][6][1]["RewardItem"][1]["Id"] = 139058
	tBossCopy_Pack[3305093][6][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305093][6][2] = {}
	tBossCopy_Pack[3305093][6][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305093][6][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305093][6][2]["RewardItem"] = {}
	tBossCopy_Pack[3305093][6][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305093][6][2]["RewardItem"][1]["Id"] = 120098
	tBossCopy_Pack[3305093][6][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 拳师（80-85）
	tBossCopy_Pack[3305093][7] = {}
	tBossCopy_Pack[3305093][7]["LogId"] = 12000851
	tBossCopy_Pack[3305093][7]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305093][7][1] = {}
	tBossCopy_Pack[3305093][7][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305093][7][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305093][7][1]["RewardItem"] = {}
	tBossCopy_Pack[3305093][7][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305093][7][1]["RewardItem"][1]["Id"] = 138058
	tBossCopy_Pack[3305093][7][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305093][7][2] = {}
	tBossCopy_Pack[3305093][7][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305093][7][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305093][7][2]["RewardItem"] = {}
	tBossCopy_Pack[3305093][7][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305093][7][2]["RewardItem"][1]["Id"] = 120098
	tBossCopy_Pack[3305093][7][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 道士（100-145） -- 水道（132-135） -- 火道（142-145）
	tBossCopy_Pack[3305093][8] = {}
	tBossCopy_Pack[3305093][8]["LogId"] = 12000851
	tBossCopy_Pack[3305093][8]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305093][8][1] = {}
	tBossCopy_Pack[3305093][8][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305093][8][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305093][8][1]["RewardItem"] = {}
	tBossCopy_Pack[3305093][8][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305093][8][1]["RewardItem"][1]["Id"] = 134058
	tBossCopy_Pack[3305093][8][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305093][8][2] = {}
	tBossCopy_Pack[3305093][8][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305093][8][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305093][8][2]["RewardItem"] = {}
	tBossCopy_Pack[3305093][8][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305093][8][2]["RewardItem"][1]["Id"] = 120098
	tBossCopy_Pack[3305093][8][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 铁扇门
	tBossCopy_Pack[3305093][9] = {}
	tBossCopy_Pack[3305093][9]["LogId"] = 12000851
	tBossCopy_Pack[3305093][9]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305093][9][1] = {}
	tBossCopy_Pack[3305093][9][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305093][9][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305093][9][1]["RewardItem"] = {}
	tBossCopy_Pack[3305093][9][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305093][9][1]["RewardItem"][1]["Id"] = 101058
	tBossCopy_Pack[3305093][9][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305093][9][2] = {}
	tBossCopy_Pack[3305093][9][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305093][9][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305093][9][2]["RewardItem"] = {}
	tBossCopy_Pack[3305093][9][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305093][9][2]["RewardItem"][1]["Id"] = 120098
	tBossCopy_Pack[3305093][9][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
	-- 60级 极品装备
	tBossCopy_Pack[3305094] = {}
	-- 勇士（10-15）
	tBossCopy_Pack[3305094][1] = {}
	tBossCopy_Pack[3305094][1]["LogId"] = 12000851
	tBossCopy_Pack[3305094][1]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305094][1][1] = {}
	tBossCopy_Pack[3305094][1][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305094][1][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305094][1][1]["RewardItem"] = {}
	tBossCopy_Pack[3305094][1][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305094][1][1]["RewardItem"][1]["Id"] = 130059
	tBossCopy_Pack[3305094][1][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305094][1][2] = {}
	tBossCopy_Pack[3305094][1][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305094][1][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305094][1][2]["RewardItem"] = {}
	tBossCopy_Pack[3305094][1][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305094][1][2]["RewardItem"][1]["Id"] = 120099
	tBossCopy_Pack[3305094][1][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 战士（20-25）
	tBossCopy_Pack[3305094][2] = {}
	tBossCopy_Pack[3305094][2]["LogId"] = 12000851
	tBossCopy_Pack[3305094][2]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305094][2][1] = {}
	tBossCopy_Pack[3305094][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305094][2][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305094][2][1]["RewardItem"] = {}
	tBossCopy_Pack[3305094][2][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305094][2][1]["RewardItem"][1]["Id"] = 131059
	tBossCopy_Pack[3305094][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305094][2][2] = {}
	tBossCopy_Pack[3305094][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305094][2][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305094][2][2]["RewardItem"] = {}
	tBossCopy_Pack[3305094][2][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305094][2][2]["RewardItem"][1]["Id"] = 120099
	tBossCopy_Pack[3305094][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 射手（40-45）
	tBossCopy_Pack[3305094][3] = {}
	tBossCopy_Pack[3305094][3]["LogId"] = 12000851
	tBossCopy_Pack[3305094][3]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305094][3][1] = {}
	tBossCopy_Pack[3305094][3][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305094][3][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305094][3][1]["RewardItem"] = {}
	tBossCopy_Pack[3305094][3][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305094][3][1]["RewardItem"][1]["Id"] = 133039
	tBossCopy_Pack[3305094][3][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305094][3][2] = {}
	tBossCopy_Pack[3305094][3][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305094][3][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305094][3][2]["RewardItem"] = {}
	tBossCopy_Pack[3305094][3][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305094][3][2]["RewardItem"][1]["Id"] = 120099
	tBossCopy_Pack[3305094][3][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 忍者（50-55）
	tBossCopy_Pack[3305094][4] = {}
	tBossCopy_Pack[3305094][4]["LogId"] = 12000851
	tBossCopy_Pack[3305094][4]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305094][4][1] = {}
	tBossCopy_Pack[3305094][4][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305094][4][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305094][4][1]["RewardItem"] = {}
	tBossCopy_Pack[3305094][4][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305094][4][1]["RewardItem"][1]["Id"] = 135059
	tBossCopy_Pack[3305094][4][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305094][4][2] = {}
	tBossCopy_Pack[3305094][4][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305094][4][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305094][4][2]["RewardItem"] = {}
	tBossCopy_Pack[3305094][4][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305094][4][2]["RewardItem"][1]["Id"] = 120099
	tBossCopy_Pack[3305094][4][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 武僧（60-65）
	tBossCopy_Pack[3305094][5] = {}
	tBossCopy_Pack[3305094][5]["LogId"] = 12000851
	tBossCopy_Pack[3305094][5]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305094][5][1] = {}
	tBossCopy_Pack[3305094][5][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305094][5][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305094][5][1]["RewardItem"] = {}
	tBossCopy_Pack[3305094][5][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305094][5][1]["RewardItem"][1]["Id"] = 136059
	tBossCopy_Pack[3305094][5][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305094][5][2] = {}
	tBossCopy_Pack[3305094][5][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305094][5][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305094][5][2]["RewardItem"] = {}
	tBossCopy_Pack[3305094][5][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305094][5][2]["RewardItem"][1]["Id"] = 120099
	tBossCopy_Pack[3305094][5][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 海盗（70-75）
	tBossCopy_Pack[3305094][6] = {}
	tBossCopy_Pack[3305094][6]["LogId"] = 12000851
	tBossCopy_Pack[3305094][6]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305094][6][1] = {}
	tBossCopy_Pack[3305094][6][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305094][6][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305094][6][1]["RewardItem"] = {}
	tBossCopy_Pack[3305094][6][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305094][6][1]["RewardItem"][1]["Id"] = 139059
	tBossCopy_Pack[3305094][6][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305094][6][2] = {}
	tBossCopy_Pack[3305094][6][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305094][6][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305094][6][2]["RewardItem"] = {}
	tBossCopy_Pack[3305094][6][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305094][6][2]["RewardItem"][1]["Id"] = 120099
	tBossCopy_Pack[3305094][6][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 拳师（80-85）
	tBossCopy_Pack[3305094][7] = {}
	tBossCopy_Pack[3305094][7]["LogId"] = 12000851
	tBossCopy_Pack[3305094][7]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305094][7][1] = {}
	tBossCopy_Pack[3305094][7][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305094][7][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305094][7][1]["RewardItem"] = {}
	tBossCopy_Pack[3305094][7][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305094][7][1]["RewardItem"][1]["Id"] = 138059
	tBossCopy_Pack[3305094][7][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305094][7][2] = {}
	tBossCopy_Pack[3305094][7][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305094][7][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305094][7][2]["RewardItem"] = {}
	tBossCopy_Pack[3305094][7][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305094][7][2]["RewardItem"][1]["Id"] = 120099
	tBossCopy_Pack[3305094][7][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 道士（100-145） -- 水道（132-135） -- 火道（142-145）
	tBossCopy_Pack[3305094][8] = {}
	tBossCopy_Pack[3305094][8]["LogId"] = 12000851
	tBossCopy_Pack[3305094][8]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305094][8][1] = {}
	tBossCopy_Pack[3305094][8][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305094][8][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305094][8][1]["RewardItem"] = {}
	tBossCopy_Pack[3305094][8][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305094][8][1]["RewardItem"][1]["Id"] = 134059
	tBossCopy_Pack[3305094][8][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305094][8][2] = {}
	tBossCopy_Pack[3305094][8][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305094][8][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305094][8][2]["RewardItem"] = {}
	tBossCopy_Pack[3305094][8][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305094][8][2]["RewardItem"][1]["Id"] = 120099
	tBossCopy_Pack[3305094][8][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 铁扇门
	tBossCopy_Pack[3305094][9] = {}
	tBossCopy_Pack[3305094][9]["LogId"] = 12000851
	tBossCopy_Pack[3305094][9]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305094][9][1] = {}
	tBossCopy_Pack[3305094][9][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305094][9][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305094][9][1]["RewardItem"] = {}
	tBossCopy_Pack[3305094][9][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305094][9][1]["RewardItem"][1]["Id"] = 101059
	tBossCopy_Pack[3305094][9][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305094][9][2] = {}
	tBossCopy_Pack[3305094][9][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305094][9][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305094][9][2]["RewardItem"] = {}
	tBossCopy_Pack[3305094][9][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305094][9][2]["RewardItem"][1]["Id"] = 120099
	tBossCopy_Pack[3305094][9][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
	-- 70级 精品装备
	tBossCopy_Pack[3305095] = {}
	-- 勇士（10-15）
	tBossCopy_Pack[3305095][1] = {}
	tBossCopy_Pack[3305095][1]["LogId"] = 12000851
	tBossCopy_Pack[3305095][1]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305095][1][1] = {}
	tBossCopy_Pack[3305095][1][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305095][1][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305095][1][1]["RewardItem"] = {}
	tBossCopy_Pack[3305095][1][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305095][1][1]["RewardItem"][1]["Id"] = 118068
	tBossCopy_Pack[3305095][1][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305095][1][2] = {}
	tBossCopy_Pack[3305095][1][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305095][1][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305095][1][2]["RewardItem"] = {}
	tBossCopy_Pack[3305095][1][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305095][1][2]["RewardItem"][1]["Id"] = 160138
	tBossCopy_Pack[3305095][1][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 战士（20-25）
	tBossCopy_Pack[3305095][2] = {}
	tBossCopy_Pack[3305095][2]["LogId"] = 12000851
	tBossCopy_Pack[3305095][2]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305095][2][1] = {}
	tBossCopy_Pack[3305095][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305095][2][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305095][2][1]["RewardItem"] = {}
	tBossCopy_Pack[3305095][2][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305095][2][1]["RewardItem"][1]["Id"] = 111068
	tBossCopy_Pack[3305095][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305095][2][2] = {}
	tBossCopy_Pack[3305095][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305095][2][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305095][2][2]["RewardItem"] = {}
	tBossCopy_Pack[3305095][2][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305095][2][2]["RewardItem"][1]["Id"] = 160138
	tBossCopy_Pack[3305095][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 射手（40-45）
	tBossCopy_Pack[3305095][3] = {}
	tBossCopy_Pack[3305095][3]["LogId"] = 12000851
	tBossCopy_Pack[3305095][3]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305095][3][1] = {}
	tBossCopy_Pack[3305095][3][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305095][3][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305095][3][1]["RewardItem"] = {}
	tBossCopy_Pack[3305095][3][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305095][3][1]["RewardItem"][1]["Id"] = 113038
	tBossCopy_Pack[3305095][3][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305095][3][2] = {}
	tBossCopy_Pack[3305095][3][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305095][3][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305095][3][2]["RewardItem"] = {}
	tBossCopy_Pack[3305095][3][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305095][3][2]["RewardItem"][1]["Id"] = 160138
	tBossCopy_Pack[3305095][3][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 忍者（50-55）
	tBossCopy_Pack[3305095][4] = {}
	tBossCopy_Pack[3305095][4]["LogId"] = 12000851
	tBossCopy_Pack[3305095][4]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305095][4][1] = {}
	tBossCopy_Pack[3305095][4][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305095][4][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305095][4][1]["RewardItem"] = {}
	tBossCopy_Pack[3305095][4][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305095][4][1]["RewardItem"][1]["Id"] = 123068
	tBossCopy_Pack[3305095][4][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305095][4][2] = {}
	tBossCopy_Pack[3305095][4][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305095][4][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305095][4][2]["RewardItem"] = {}
	tBossCopy_Pack[3305095][4][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305095][4][2]["RewardItem"][1]["Id"] = 160138
	tBossCopy_Pack[3305095][4][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 武僧（60-65）
	tBossCopy_Pack[3305095][5] = {}
	tBossCopy_Pack[3305095][5]["LogId"] = 12000851
	tBossCopy_Pack[3305095][5]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305095][5][1] = {}
	tBossCopy_Pack[3305095][5][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305095][5][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305095][5][1]["RewardItem"] = {}
	tBossCopy_Pack[3305095][5][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305095][5][1]["RewardItem"][1]["Id"] = 143068
	tBossCopy_Pack[3305095][5][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305095][5][2] = {}
	tBossCopy_Pack[3305095][5][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305095][5][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305095][5][2]["RewardItem"] = {}
	tBossCopy_Pack[3305095][5][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305095][5][2]["RewardItem"][1]["Id"] = 160138
	tBossCopy_Pack[3305095][5][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 海盗（70-75）
	tBossCopy_Pack[3305095][6] = {}
	tBossCopy_Pack[3305095][6]["LogId"] = 12000851
	tBossCopy_Pack[3305095][6]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305095][6][1] = {}
	tBossCopy_Pack[3305095][6][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305095][6][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305095][6][1]["RewardItem"] = {}
	tBossCopy_Pack[3305095][6][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305095][6][1]["RewardItem"][1]["Id"] = 144068
	tBossCopy_Pack[3305095][6][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305095][6][2] = {}
	tBossCopy_Pack[3305095][6][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305095][6][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305095][6][2]["RewardItem"] = {}
	tBossCopy_Pack[3305095][6][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305095][6][2]["RewardItem"][1]["Id"] = 160138
	tBossCopy_Pack[3305095][6][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 拳师（80-85）
	tBossCopy_Pack[3305095][7] = {}
	tBossCopy_Pack[3305095][7]["LogId"] = 12000851
	tBossCopy_Pack[3305095][7]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305095][7][1] = {}
	tBossCopy_Pack[3305095][7][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305095][7][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305095][7][1]["RewardItem"] = {}
	tBossCopy_Pack[3305095][7][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305095][7][1]["RewardItem"][1]["Id"] = 148068
	tBossCopy_Pack[3305095][7][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305095][7][2] = {}
	tBossCopy_Pack[3305095][7][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305095][7][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305095][7][2]["RewardItem"] = {}
	tBossCopy_Pack[3305095][7][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305095][7][2]["RewardItem"][1]["Id"] = 160138
	tBossCopy_Pack[3305095][7][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 道士（100-145） -- 水道（132-135） -- 火道（142-145）
	tBossCopy_Pack[3305095][8] = {}
	tBossCopy_Pack[3305095][8]["LogId"] = 12000851
	tBossCopy_Pack[3305095][8]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305095][8][1] = {}
	tBossCopy_Pack[3305095][8][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305095][8][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305095][8][1]["RewardItem"] = {}
	tBossCopy_Pack[3305095][8][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305095][8][1]["RewardItem"][1]["Id"] = 114068
	tBossCopy_Pack[3305095][8][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305095][8][2] = {}
	tBossCopy_Pack[3305095][8][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305095][8][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305095][8][2]["RewardItem"] = {}
	tBossCopy_Pack[3305095][8][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305095][8][2]["RewardItem"][1]["Id"] = 160138
	tBossCopy_Pack[3305095][8][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 铁扇门
	tBossCopy_Pack[3305095][9] = {}
	tBossCopy_Pack[3305095][9]["LogId"] = 12000851
	tBossCopy_Pack[3305095][9]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305095][9][1] = {}
	tBossCopy_Pack[3305095][9][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305095][9][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305095][9][1]["RewardItem"] = {}
	tBossCopy_Pack[3305095][9][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305095][9][1]["RewardItem"][1]["Id"] = 170068
	tBossCopy_Pack[3305095][9][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305095][9][2] = {}
	tBossCopy_Pack[3305095][9][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305095][9][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305095][9][2]["RewardItem"] = {}
	tBossCopy_Pack[3305095][9][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305095][9][2]["RewardItem"][1]["Id"] = 160138
	tBossCopy_Pack[3305095][9][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
	-- 70级 极品装备
	tBossCopy_Pack[3305096] = {}
	-- 勇士（10-15）
	tBossCopy_Pack[3305096][1] = {}
	tBossCopy_Pack[3305096][1]["LogId"] = 12000851
	tBossCopy_Pack[3305096][1]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305096][1][1] = {}
	tBossCopy_Pack[3305096][1][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305096][1][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305096][1][1]["RewardItem"] = {}
	tBossCopy_Pack[3305096][1][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305096][1][1]["RewardItem"][1]["Id"] = 118069
	tBossCopy_Pack[3305096][1][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305096][1][2] = {}
	tBossCopy_Pack[3305096][1][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305096][1][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305096][1][2]["RewardItem"] = {}
	tBossCopy_Pack[3305096][1][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305096][1][2]["RewardItem"][1]["Id"] = 160139
	tBossCopy_Pack[3305096][1][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 战士（20-25）
	tBossCopy_Pack[3305096][2] = {}
	tBossCopy_Pack[3305096][2]["LogId"] = 12000851
	tBossCopy_Pack[3305096][2]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305096][2][1] = {}
	tBossCopy_Pack[3305096][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305096][2][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305096][2][1]["RewardItem"] = {}
	tBossCopy_Pack[3305096][2][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305096][2][1]["RewardItem"][1]["Id"] = 111069
	tBossCopy_Pack[3305096][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305096][2][2] = {}
	tBossCopy_Pack[3305096][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305096][2][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305096][2][2]["RewardItem"] = {}
	tBossCopy_Pack[3305096][2][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305096][2][2]["RewardItem"][1]["Id"] = 160139
	tBossCopy_Pack[3305096][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 射手（40-45）
	tBossCopy_Pack[3305096][3] = {}
	tBossCopy_Pack[3305096][3]["LogId"] = 12000851
	tBossCopy_Pack[3305096][3]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305096][3][1] = {}
	tBossCopy_Pack[3305096][3][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305096][3][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305096][3][1]["RewardItem"] = {}
	tBossCopy_Pack[3305096][3][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305096][3][1]["RewardItem"][1]["Id"] = 113039
	tBossCopy_Pack[3305096][3][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305096][3][2] = {}
	tBossCopy_Pack[3305096][3][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305096][3][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305096][3][2]["RewardItem"] = {}
	tBossCopy_Pack[3305096][3][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305096][3][2]["RewardItem"][1]["Id"] = 160139
	tBossCopy_Pack[3305096][3][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 忍者（50-55）
	tBossCopy_Pack[3305096][4] = {}
	tBossCopy_Pack[3305096][4]["LogId"] = 12000851
	tBossCopy_Pack[3305096][4]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305096][4][1] = {}
	tBossCopy_Pack[3305096][4][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305096][4][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305096][4][1]["RewardItem"] = {}
	tBossCopy_Pack[3305096][4][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305096][4][1]["RewardItem"][1]["Id"] = 123069
	tBossCopy_Pack[3305096][4][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305096][4][2] = {}
	tBossCopy_Pack[3305096][4][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305096][4][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305096][4][2]["RewardItem"] = {}
	tBossCopy_Pack[3305096][4][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305096][4][2]["RewardItem"][1]["Id"] = 160139
	tBossCopy_Pack[3305096][4][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 武僧（60-65）
	tBossCopy_Pack[3305096][5] = {}
	tBossCopy_Pack[3305096][5]["LogId"] = 12000851
	tBossCopy_Pack[3305096][5]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305096][5][1] = {}
	tBossCopy_Pack[3305096][5][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305096][5][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305096][5][1]["RewardItem"] = {}
	tBossCopy_Pack[3305096][5][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305096][5][1]["RewardItem"][1]["Id"] = 143069
	tBossCopy_Pack[3305096][5][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305096][5][2] = {}
	tBossCopy_Pack[3305096][5][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305096][5][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305096][5][2]["RewardItem"] = {}
	tBossCopy_Pack[3305096][5][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305096][5][2]["RewardItem"][1]["Id"] = 160139
	tBossCopy_Pack[3305096][5][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 海盗（70-75）
	tBossCopy_Pack[3305096][6] = {}
	tBossCopy_Pack[3305096][6]["LogId"] = 12000851
	tBossCopy_Pack[3305096][6]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305096][6][1] = {}
	tBossCopy_Pack[3305096][6][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305096][6][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305096][6][1]["RewardItem"] = {}
	tBossCopy_Pack[3305096][6][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305096][6][1]["RewardItem"][1]["Id"] = 144069
	tBossCopy_Pack[3305096][6][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305096][6][2] = {}
	tBossCopy_Pack[3305096][6][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305096][6][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305096][6][2]["RewardItem"] = {}
	tBossCopy_Pack[3305096][6][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305096][6][2]["RewardItem"][1]["Id"] = 160139
	tBossCopy_Pack[3305096][6][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 拳师（80-85）
	tBossCopy_Pack[3305096][7] = {}
	tBossCopy_Pack[3305096][7]["LogId"] = 12000851
	tBossCopy_Pack[3305096][7]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305096][7][1] = {}
	tBossCopy_Pack[3305096][7][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305096][7][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305096][7][1]["RewardItem"] = {}
	tBossCopy_Pack[3305096][7][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305096][7][1]["RewardItem"][1]["Id"] = 148069
	tBossCopy_Pack[3305096][7][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305096][7][2] = {}
	tBossCopy_Pack[3305096][7][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305096][7][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305096][7][2]["RewardItem"] = {}
	tBossCopy_Pack[3305096][7][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305096][7][2]["RewardItem"][1]["Id"] = 160139
	tBossCopy_Pack[3305096][7][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 道士（100-145） -- 水道（132-135） -- 火道（142-145）
	tBossCopy_Pack[3305096][8] = {}
	tBossCopy_Pack[3305096][8]["LogId"] = 12000851
	tBossCopy_Pack[3305096][8]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305096][8][1] = {}
	tBossCopy_Pack[3305096][8][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305096][8][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305096][8][1]["RewardItem"] = {}
	tBossCopy_Pack[3305096][8][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305096][8][1]["RewardItem"][1]["Id"] = 114069
	tBossCopy_Pack[3305096][8][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305096][8][2] = {}
	tBossCopy_Pack[3305096][8][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305096][8][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305096][8][2]["RewardItem"] = {}
	tBossCopy_Pack[3305096][8][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305096][8][2]["RewardItem"][1]["Id"] = 160139
	tBossCopy_Pack[3305096][8][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 铁扇门
	tBossCopy_Pack[3305096][9] = {}
	tBossCopy_Pack[3305096][9]["LogId"] = 12000851
	tBossCopy_Pack[3305096][9]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305096][9][1] = {}
	tBossCopy_Pack[3305096][9][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305096][9][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305096][9][1]["RewardItem"] = {}
	tBossCopy_Pack[3305096][9][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305096][9][1]["RewardItem"][1]["Id"] = 170069
	tBossCopy_Pack[3305096][9][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305096][9][2] = {}
	tBossCopy_Pack[3305096][9][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305096][9][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305096][9][2]["RewardItem"] = {}
	tBossCopy_Pack[3305096][9][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305096][9][2]["RewardItem"][1]["Id"] = 160139
	tBossCopy_Pack[3305096][9][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
	-- 80级 精品装备
	tBossCopy_Pack[3305097] = {}
	-- 勇士（10-15）
	tBossCopy_Pack[3305097][1] = {}
	tBossCopy_Pack[3305097][1]["LogId"] = 12000851
	tBossCopy_Pack[3305097][1]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305097][1][1] = {}
	tBossCopy_Pack[3305097][1][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305097][1][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305097][1][1]["RewardItem"] = {}
	tBossCopy_Pack[3305097][1][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305097][1][1]["RewardItem"][1]["Id"] = 410158
	tBossCopy_Pack[3305097][1][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305097][1][2] = {}
	tBossCopy_Pack[3305097][1][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305097][1][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305097][1][2]["RewardItem"] = {}
	tBossCopy_Pack[3305097][1][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305097][1][2]["RewardItem"][1]["Id"] = 150158
	tBossCopy_Pack[3305097][1][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 战士（20-25）
	tBossCopy_Pack[3305097][2] = {}
	tBossCopy_Pack[3305097][2]["LogId"] = 12000851
	tBossCopy_Pack[3305097][2]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305097][2][1] = {}
	tBossCopy_Pack[3305097][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305097][2][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305097][2][1]["RewardItem"] = {}
	tBossCopy_Pack[3305097][2][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305097][2][1]["RewardItem"][1]["Id"] = 624158
	tBossCopy_Pack[3305097][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305097][2][2] = {}
	tBossCopy_Pack[3305097][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305097][2][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305097][2][2]["RewardItem"] = {}
	tBossCopy_Pack[3305097][2][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305097][2][2]["RewardItem"][1]["Id"] = 150158
	tBossCopy_Pack[3305097][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 射手（40-45）
	tBossCopy_Pack[3305097][3] = {}
	tBossCopy_Pack[3305097][3]["LogId"] = 12000851
	tBossCopy_Pack[3305097][3]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305097][3][1] = {}
	tBossCopy_Pack[3305097][3][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305097][3][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305097][3][1]["RewardItem"] = {}
	tBossCopy_Pack[3305097][3][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305097][3][1]["RewardItem"][1]["Id"] = 613148
	tBossCopy_Pack[3305097][3][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305097][3][2] = {}
	tBossCopy_Pack[3305097][3][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305097][3][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305097][3][2]["RewardItem"] = {}
	tBossCopy_Pack[3305097][3][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305097][3][2]["RewardItem"][1]["Id"] = 150158
	tBossCopy_Pack[3305097][3][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 忍者（50-55）
	tBossCopy_Pack[3305097][4] = {}
	tBossCopy_Pack[3305097][4]["LogId"] = 12000851
	tBossCopy_Pack[3305097][4]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305097][4][1] = {}
	tBossCopy_Pack[3305097][4][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305097][4][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305097][4][1]["RewardItem"] = {}
	tBossCopy_Pack[3305097][4][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305097][4][1]["RewardItem"][1]["Id"] = 601158
	tBossCopy_Pack[3305097][4][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305097][4][2] = {}
	tBossCopy_Pack[3305097][4][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305097][4][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305097][4][2]["RewardItem"] = {}
	tBossCopy_Pack[3305097][4][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305097][4][2]["RewardItem"][1]["Id"] = 150158
	tBossCopy_Pack[3305097][4][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 武僧（60-65）
	tBossCopy_Pack[3305097][5] = {}
	tBossCopy_Pack[3305097][5]["LogId"] = 12000851
	tBossCopy_Pack[3305097][5]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305097][5][1] = {}
	tBossCopy_Pack[3305097][5][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305097][5][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305097][5][1]["RewardItem"] = {}
	tBossCopy_Pack[3305097][5][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305097][5][1]["RewardItem"][1]["Id"] = 610158
	tBossCopy_Pack[3305097][5][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305097][5][2] = {}
	tBossCopy_Pack[3305097][5][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305097][5][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305097][5][2]["RewardItem"] = {}
	tBossCopy_Pack[3305097][5][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305097][5][2]["RewardItem"][1]["Id"] = 150158
	tBossCopy_Pack[3305097][5][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 海盗（70-75）
	tBossCopy_Pack[3305097][6] = {}
	tBossCopy_Pack[3305097][6]["LogId"] = 12000851
	tBossCopy_Pack[3305097][6]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305097][6][1] = {}
	tBossCopy_Pack[3305097][6][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305097][6][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305097][6][1]["RewardItem"] = {}
	tBossCopy_Pack[3305097][6][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305097][6][1]["RewardItem"][1]["Id"] = 611158
	tBossCopy_Pack[3305097][6][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305097][6][2] = {}
	tBossCopy_Pack[3305097][6][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305097][6][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305097][6][2]["RewardItem"] = {}
	tBossCopy_Pack[3305097][6][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305097][6][2]["RewardItem"][1]["Id"] = 150158
	tBossCopy_Pack[3305097][6][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 拳师（80-85）
	tBossCopy_Pack[3305097][7] = {}
	tBossCopy_Pack[3305097][7]["LogId"] = 12000851
	tBossCopy_Pack[3305097][7]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305097][7][1] = {}
	tBossCopy_Pack[3305097][7][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305097][7][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305097][7][1]["RewardItem"] = {}
	tBossCopy_Pack[3305097][7][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305097][7][1]["RewardItem"][1]["Id"] = 617158
	tBossCopy_Pack[3305097][7][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305097][7][2] = {}
	tBossCopy_Pack[3305097][7][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305097][7][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305097][7][2]["RewardItem"] = {}
	tBossCopy_Pack[3305097][7][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305097][7][2]["RewardItem"][1]["Id"] = 150158
	tBossCopy_Pack[3305097][7][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 道士（100-145） -- 水道（132-135） -- 火道（142-145）
	tBossCopy_Pack[3305097][8] = {}
	tBossCopy_Pack[3305097][8]["LogId"] = 12000851
	tBossCopy_Pack[3305097][8]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305097][8][1] = {}
	tBossCopy_Pack[3305097][8][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305097][8][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305097][8][1]["RewardItem"] = {}
	tBossCopy_Pack[3305097][8][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305097][8][1]["RewardItem"][1]["Id"] = 421158
	tBossCopy_Pack[3305097][8][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305097][8][2] = {}
	tBossCopy_Pack[3305097][8][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305097][8][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305097][8][2]["RewardItem"] = {}
	tBossCopy_Pack[3305097][8][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305097][8][2]["RewardItem"][1]["Id"] = 150158
	tBossCopy_Pack[3305097][8][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 铁扇门
	tBossCopy_Pack[3305097][9] = {}
	tBossCopy_Pack[3305097][9]["LogId"] = 12000851
	tBossCopy_Pack[3305097][9]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305097][9][1] = {}
	tBossCopy_Pack[3305097][9][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305097][9][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305097][9][1]["RewardItem"] = {}
	tBossCopy_Pack[3305097][9][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305097][9][1]["RewardItem"][1]["Id"] = 626158
	tBossCopy_Pack[3305097][9][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305097][9][2] = {}
	tBossCopy_Pack[3305097][9][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305097][9][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305097][9][2]["RewardItem"] = {}
	tBossCopy_Pack[3305097][9][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305097][9][2]["RewardItem"][1]["Id"] = 150158
	tBossCopy_Pack[3305097][9][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
	-- 80级 极品装备
	tBossCopy_Pack[3305098] = {}
	-- 勇士（10-15）
	tBossCopy_Pack[3305098][1] = {}
	tBossCopy_Pack[3305098][1]["LogId"] = 12000851
	tBossCopy_Pack[3305098][1]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305098][1][1] = {}
	tBossCopy_Pack[3305098][1][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305098][1][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305098][1][1]["RewardItem"] = {}
	tBossCopy_Pack[3305098][1][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305098][1][1]["RewardItem"][1]["Id"] = 410159
	tBossCopy_Pack[3305098][1][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305098][1][2] = {}
	tBossCopy_Pack[3305098][1][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305098][1][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305098][1][2]["RewardItem"] = {}
	tBossCopy_Pack[3305098][1][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305098][1][2]["RewardItem"][1]["Id"] = 150159
	tBossCopy_Pack[3305098][1][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 战士（20-25）
	tBossCopy_Pack[3305098][2] = {}
	tBossCopy_Pack[3305098][2]["LogId"] = 12000851
	tBossCopy_Pack[3305098][2]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305098][2][1] = {}
	tBossCopy_Pack[3305098][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305098][2][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305098][2][1]["RewardItem"] = {}
	tBossCopy_Pack[3305098][2][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305098][2][1]["RewardItem"][1]["Id"] = 624159
	tBossCopy_Pack[3305098][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305098][2][2] = {}
	tBossCopy_Pack[3305098][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305098][2][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305098][2][2]["RewardItem"] = {}
	tBossCopy_Pack[3305098][2][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305098][2][2]["RewardItem"][1]["Id"] = 150159
	tBossCopy_Pack[3305098][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 射手（40-45）
	tBossCopy_Pack[3305098][3] = {}
	tBossCopy_Pack[3305098][3]["LogId"] = 12000851
	tBossCopy_Pack[3305098][3]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305098][3][1] = {}
	tBossCopy_Pack[3305098][3][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305098][3][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305098][3][1]["RewardItem"] = {}
	tBossCopy_Pack[3305098][3][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305098][3][1]["RewardItem"][1]["Id"] = 613149
	tBossCopy_Pack[3305098][3][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305098][3][2] = {}
	tBossCopy_Pack[3305098][3][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305098][3][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305098][3][2]["RewardItem"] = {}
	tBossCopy_Pack[3305098][3][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305098][3][2]["RewardItem"][1]["Id"] = 150159
	tBossCopy_Pack[3305098][3][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 忍者（50-55）
	tBossCopy_Pack[3305098][4] = {}
	tBossCopy_Pack[3305098][4]["LogId"] = 12000851
	tBossCopy_Pack[3305098][4]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305098][4][1] = {}
	tBossCopy_Pack[3305098][4][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305098][4][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305098][4][1]["RewardItem"] = {}
	tBossCopy_Pack[3305098][4][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305098][4][1]["RewardItem"][1]["Id"] = 601159
	tBossCopy_Pack[3305098][4][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305098][4][2] = {}
	tBossCopy_Pack[3305098][4][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305098][4][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305098][4][2]["RewardItem"] = {}
	tBossCopy_Pack[3305098][4][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305098][4][2]["RewardItem"][1]["Id"] = 150159
	tBossCopy_Pack[3305098][4][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 武僧（60-65）
	tBossCopy_Pack[3305098][5] = {}
	tBossCopy_Pack[3305098][5]["LogId"] = 12000851
	tBossCopy_Pack[3305098][5]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305098][5][1] = {}
	tBossCopy_Pack[3305098][5][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305098][5][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305098][5][1]["RewardItem"] = {}
	tBossCopy_Pack[3305098][5][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305098][5][1]["RewardItem"][1]["Id"] = 610159
	tBossCopy_Pack[3305098][5][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305098][5][2] = {}
	tBossCopy_Pack[3305098][5][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305098][5][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305098][5][2]["RewardItem"] = {}
	tBossCopy_Pack[3305098][5][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305098][5][2]["RewardItem"][1]["Id"] = 150159
	tBossCopy_Pack[3305098][5][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 海盗（70-75）
	tBossCopy_Pack[3305098][6] = {}
	tBossCopy_Pack[3305098][6]["LogId"] = 12000851
	tBossCopy_Pack[3305098][6]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305098][6][1] = {}
	tBossCopy_Pack[3305098][6][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305098][6][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305098][6][1]["RewardItem"] = {}
	tBossCopy_Pack[3305098][6][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305098][6][1]["RewardItem"][1]["Id"] = 611159
	tBossCopy_Pack[3305098][6][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305098][6][2] = {}
	tBossCopy_Pack[3305098][6][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305098][6][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305098][6][2]["RewardItem"] = {}
	tBossCopy_Pack[3305098][6][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305098][6][2]["RewardItem"][1]["Id"] = 150159
	tBossCopy_Pack[3305098][6][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 拳师（80-85）
	tBossCopy_Pack[3305098][7] = {}
	tBossCopy_Pack[3305098][7]["LogId"] = 12000851
	tBossCopy_Pack[3305098][7]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305098][7][1] = {}
	tBossCopy_Pack[3305098][7][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305098][7][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305098][7][1]["RewardItem"] = {}
	tBossCopy_Pack[3305098][7][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305098][7][1]["RewardItem"][1]["Id"] = 617159
	tBossCopy_Pack[3305098][7][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305098][7][2] = {}
	tBossCopy_Pack[3305098][7][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305098][7][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305098][7][2]["RewardItem"] = {}
	tBossCopy_Pack[3305098][7][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305098][7][2]["RewardItem"][1]["Id"] = 150159
	tBossCopy_Pack[3305098][7][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 道士（100-145） -- 水道（132-135） -- 火道（142-145）
	tBossCopy_Pack[3305098][8] = {}
	tBossCopy_Pack[3305098][8]["LogId"] = 12000851
	tBossCopy_Pack[3305098][8]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305098][8][1] = {}
	tBossCopy_Pack[3305098][8][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305098][8][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305098][8][1]["RewardItem"] = {}
	tBossCopy_Pack[3305098][8][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305098][8][1]["RewardItem"][1]["Id"] = 421159
	tBossCopy_Pack[3305098][8][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305098][8][2] = {}
	tBossCopy_Pack[3305098][8][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305098][8][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305098][8][2]["RewardItem"] = {}
	tBossCopy_Pack[3305098][8][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305098][8][2]["RewardItem"][1]["Id"] = 150159
	tBossCopy_Pack[3305098][8][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 铁扇门
	tBossCopy_Pack[3305098][9] = {}
	tBossCopy_Pack[3305098][9]["LogId"] = 12000851
	tBossCopy_Pack[3305098][9]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305098][9][1] = {}
	tBossCopy_Pack[3305098][9][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305098][9][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305098][9][1]["RewardItem"] = {}
	tBossCopy_Pack[3305098][9][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305098][9][1]["RewardItem"][1]["Id"] = 626159
	tBossCopy_Pack[3305098][9][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305098][9][2] = {}
	tBossCopy_Pack[3305098][9][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305098][9][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305098][9][2]["RewardItem"] = {}
	tBossCopy_Pack[3305098][9][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305098][9][2]["RewardItem"][1]["Id"] = 150159
	tBossCopy_Pack[3305098][9][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
	-- 90级 精品装备
	tBossCopy_Pack[3305099] = {}
	-- 勇士（10-15）
	tBossCopy_Pack[3305099][1] = {}
	tBossCopy_Pack[3305099][1]["LogId"] = 12000851
	tBossCopy_Pack[3305099][1]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305099][1][1] = {}
	tBossCopy_Pack[3305099][1][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305099][1][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305099][1][1]["RewardItem"] = {}
	tBossCopy_Pack[3305099][1][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305099][1][1]["RewardItem"][1]["Id"] = 130078
	tBossCopy_Pack[3305099][1][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305099][1][2] = {}
	tBossCopy_Pack[3305099][1][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305099][1][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305099][1][2]["RewardItem"] = {}
	tBossCopy_Pack[3305099][1][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305099][1][2]["RewardItem"][1]["Id"] = 120158
	tBossCopy_Pack[3305099][1][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 战士（20-25）
	tBossCopy_Pack[3305099][2] = {}
	tBossCopy_Pack[3305099][2]["LogId"] = 12000851
	tBossCopy_Pack[3305099][2]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305099][2][1] = {}
	tBossCopy_Pack[3305099][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305099][2][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305099][2][1]["RewardItem"] = {}
	tBossCopy_Pack[3305099][2][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305099][2][1]["RewardItem"][1]["Id"] = 131078
	tBossCopy_Pack[3305099][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305099][2][2] = {}
	tBossCopy_Pack[3305099][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305099][2][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305099][2][2]["RewardItem"] = {}
	tBossCopy_Pack[3305099][2][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305099][2][2]["RewardItem"][1]["Id"] = 120158
	tBossCopy_Pack[3305099][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 射手（40-45）
	tBossCopy_Pack[3305099][3] = {}
	tBossCopy_Pack[3305099][3]["LogId"] = 12000851
	tBossCopy_Pack[3305099][3]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305099][3][1] = {}
	tBossCopy_Pack[3305099][3][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305099][3][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305099][3][1]["RewardItem"] = {}
	tBossCopy_Pack[3305099][3][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305099][3][1]["RewardItem"][1]["Id"] = 133068
	tBossCopy_Pack[3305099][3][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305099][3][2] = {}
	tBossCopy_Pack[3305099][3][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305099][3][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305099][3][2]["RewardItem"] = {}
	tBossCopy_Pack[3305099][3][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305099][3][2]["RewardItem"][1]["Id"] = 120158
	tBossCopy_Pack[3305099][3][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 忍者（50-55）
	tBossCopy_Pack[3305099][4] = {}
	tBossCopy_Pack[3305099][4]["LogId"] = 12000851
	tBossCopy_Pack[3305099][4]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305099][4][1] = {}
	tBossCopy_Pack[3305099][4][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305099][4][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305099][4][1]["RewardItem"] = {}
	tBossCopy_Pack[3305099][4][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305099][4][1]["RewardItem"][1]["Id"] = 135078
	tBossCopy_Pack[3305099][4][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305099][4][2] = {}
	tBossCopy_Pack[3305099][4][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305099][4][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305099][4][2]["RewardItem"] = {}
	tBossCopy_Pack[3305099][4][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305099][4][2]["RewardItem"][1]["Id"] = 120158
	tBossCopy_Pack[3305099][4][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 武僧（60-65）
	tBossCopy_Pack[3305099][5] = {}
	tBossCopy_Pack[3305099][5]["LogId"] = 12000851
	tBossCopy_Pack[3305099][5]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305099][5][1] = {}
	tBossCopy_Pack[3305099][5][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305099][5][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305099][5][1]["RewardItem"] = {}
	tBossCopy_Pack[3305099][5][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305099][5][1]["RewardItem"][1]["Id"] = 136078
	tBossCopy_Pack[3305099][5][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305099][5][2] = {}
	tBossCopy_Pack[3305099][5][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305099][5][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305099][5][2]["RewardItem"] = {}
	tBossCopy_Pack[3305099][5][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305099][5][2]["RewardItem"][1]["Id"] = 120158
	tBossCopy_Pack[3305099][5][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 海盗（70-75）
	tBossCopy_Pack[3305099][6] = {}
	tBossCopy_Pack[3305099][6]["LogId"] = 12000851
	tBossCopy_Pack[3305099][6]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305099][6][1] = {}
	tBossCopy_Pack[3305099][6][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305099][6][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305099][6][1]["RewardItem"] = {}
	tBossCopy_Pack[3305099][6][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305099][6][1]["RewardItem"][1]["Id"] = 139078
	tBossCopy_Pack[3305099][6][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305099][6][2] = {}
	tBossCopy_Pack[3305099][6][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305099][6][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305099][6][2]["RewardItem"] = {}
	tBossCopy_Pack[3305099][6][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305099][6][2]["RewardItem"][1]["Id"] = 120158
	tBossCopy_Pack[3305099][6][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 拳师（80-85）
	tBossCopy_Pack[3305099][7] = {}
	tBossCopy_Pack[3305099][7]["LogId"] = 12000851
	tBossCopy_Pack[3305099][7]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305099][7][1] = {}
	tBossCopy_Pack[3305099][7][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305099][7][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305099][7][1]["RewardItem"] = {}
	tBossCopy_Pack[3305099][7][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305099][7][1]["RewardItem"][1]["Id"] = 138078
	tBossCopy_Pack[3305099][7][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305099][7][2] = {}
	tBossCopy_Pack[3305099][7][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305099][7][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305099][7][2]["RewardItem"] = {}
	tBossCopy_Pack[3305099][7][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305099][7][2]["RewardItem"][1]["Id"] = 120158
	tBossCopy_Pack[3305099][7][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 道士（100-145） -- 水道（132-135） -- 火道（142-145）
	tBossCopy_Pack[3305099][8] = {}
	tBossCopy_Pack[3305099][8]["LogId"] = 12000851
	tBossCopy_Pack[3305099][8]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305099][8][1] = {}
	tBossCopy_Pack[3305099][8][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305099][8][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305099][8][1]["RewardItem"] = {}
	tBossCopy_Pack[3305099][8][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305099][8][1]["RewardItem"][1]["Id"] = 134078
	tBossCopy_Pack[3305099][8][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305099][8][2] = {}
	tBossCopy_Pack[3305099][8][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305099][8][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305099][8][2]["RewardItem"] = {}
	tBossCopy_Pack[3305099][8][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305099][8][2]["RewardItem"][1]["Id"] = 120158
	tBossCopy_Pack[3305099][8][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 铁扇门
	tBossCopy_Pack[3305099][9] = {}
	tBossCopy_Pack[3305099][9]["LogId"] = 12000851
	tBossCopy_Pack[3305099][9]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305099][9][1] = {}
	tBossCopy_Pack[3305099][9][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305099][9][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305099][9][1]["RewardItem"] = {}
	tBossCopy_Pack[3305099][9][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305099][9][1]["RewardItem"][1]["Id"] = 101078
	tBossCopy_Pack[3305099][9][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305099][9][2] = {}
	tBossCopy_Pack[3305099][9][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305099][9][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305099][9][2]["RewardItem"] = {}
	tBossCopy_Pack[3305099][9][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305099][9][2]["RewardItem"][1]["Id"] = 120158
	tBossCopy_Pack[3305099][9][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
	-- 90级 极品装备
	tBossCopy_Pack[3305100] = {}
	-- 勇士（10-15）
	tBossCopy_Pack[3305100][1] = {}
	tBossCopy_Pack[3305100][1]["LogId"] = 12000851
	tBossCopy_Pack[3305100][1]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305100][1][1] = {}
	tBossCopy_Pack[3305100][1][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305100][1][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305100][1][1]["RewardItem"] = {}
	tBossCopy_Pack[3305100][1][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305100][1][1]["RewardItem"][1]["Id"] = 130079
	tBossCopy_Pack[3305100][1][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305100][1][2] = {}
	tBossCopy_Pack[3305100][1][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305100][1][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305100][1][2]["RewardItem"] = {}
	tBossCopy_Pack[3305100][1][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305100][1][2]["RewardItem"][1]["Id"] = 120159
	tBossCopy_Pack[3305100][1][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 战士（20-25）
	tBossCopy_Pack[3305100][2] = {}
	tBossCopy_Pack[3305100][2]["LogId"] = 12000851
	tBossCopy_Pack[3305100][2]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305100][2][1] = {}
	tBossCopy_Pack[3305100][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305100][2][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305100][2][1]["RewardItem"] = {}
	tBossCopy_Pack[3305100][2][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305100][2][1]["RewardItem"][1]["Id"] = 131079
	tBossCopy_Pack[3305100][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305100][2][2] = {}
	tBossCopy_Pack[3305100][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305100][2][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305100][2][2]["RewardItem"] = {}
	tBossCopy_Pack[3305100][2][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305100][2][2]["RewardItem"][1]["Id"] = 120159
	tBossCopy_Pack[3305100][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 射手（40-45）
	tBossCopy_Pack[3305100][3] = {}
	tBossCopy_Pack[3305100][3]["LogId"] = 12000851
	tBossCopy_Pack[3305100][3]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305100][3][1] = {}
	tBossCopy_Pack[3305100][3][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305100][3][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305100][3][1]["RewardItem"] = {}
	tBossCopy_Pack[3305100][3][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305100][3][1]["RewardItem"][1]["Id"] = 133069
	tBossCopy_Pack[3305100][3][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305100][3][2] = {}
	tBossCopy_Pack[3305100][3][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305100][3][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305100][3][2]["RewardItem"] = {}
	tBossCopy_Pack[3305100][3][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305100][3][2]["RewardItem"][1]["Id"] = 120159
	tBossCopy_Pack[3305100][3][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 忍者（50-55）
	tBossCopy_Pack[3305100][4] = {}
	tBossCopy_Pack[3305100][4]["LogId"] = 12000851
	tBossCopy_Pack[3305100][4]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305100][4][1] = {}
	tBossCopy_Pack[3305100][4][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305100][4][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305100][4][1]["RewardItem"] = {}
	tBossCopy_Pack[3305100][4][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305100][4][1]["RewardItem"][1]["Id"] = 135079
	tBossCopy_Pack[3305100][4][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305100][4][2] = {}
	tBossCopy_Pack[3305100][4][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305100][4][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305100][4][2]["RewardItem"] = {}
	tBossCopy_Pack[3305100][4][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305100][4][2]["RewardItem"][1]["Id"] = 120159
	tBossCopy_Pack[3305100][4][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 武僧（60-65）
	tBossCopy_Pack[3305100][5] = {}
	tBossCopy_Pack[3305100][5]["LogId"] = 12000851
	tBossCopy_Pack[3305100][5]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305100][5][1] = {}
	tBossCopy_Pack[3305100][5][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305100][5][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305100][5][1]["RewardItem"] = {}
	tBossCopy_Pack[3305100][5][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305100][5][1]["RewardItem"][1]["Id"] = 136079
	tBossCopy_Pack[3305100][5][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305100][5][2] = {}
	tBossCopy_Pack[3305100][5][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305100][5][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305100][5][2]["RewardItem"] = {}
	tBossCopy_Pack[3305100][5][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305100][5][2]["RewardItem"][1]["Id"] = 120159
	tBossCopy_Pack[3305100][5][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 海盗（70-75）
	tBossCopy_Pack[3305100][6] = {}
	tBossCopy_Pack[3305100][6]["LogId"] = 12000851
	tBossCopy_Pack[3305100][6]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305100][6][1] = {}
	tBossCopy_Pack[3305100][6][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305100][6][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305100][6][1]["RewardItem"] = {}
	tBossCopy_Pack[3305100][6][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305100][6][1]["RewardItem"][1]["Id"] = 139079
	tBossCopy_Pack[3305100][6][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305100][6][2] = {}
	tBossCopy_Pack[3305100][6][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305100][6][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305100][6][2]["RewardItem"] = {}
	tBossCopy_Pack[3305100][6][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305100][6][2]["RewardItem"][1]["Id"] = 120159
	tBossCopy_Pack[3305100][6][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 拳师（80-85）
	tBossCopy_Pack[3305100][7] = {}
	tBossCopy_Pack[3305100][7]["LogId"] = 12000851
	tBossCopy_Pack[3305100][7]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305100][7][1] = {}
	tBossCopy_Pack[3305100][7][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305100][7][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305100][7][1]["RewardItem"] = {}
	tBossCopy_Pack[3305100][7][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305100][7][1]["RewardItem"][1]["Id"] = 138079
	tBossCopy_Pack[3305100][7][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305100][7][2] = {}
	tBossCopy_Pack[3305100][7][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305100][7][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305100][7][2]["RewardItem"] = {}
	tBossCopy_Pack[3305100][7][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305100][7][2]["RewardItem"][1]["Id"] = 120159
	tBossCopy_Pack[3305100][7][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 道士（100-145） -- 水道（132-135） -- 火道（142-145）
	tBossCopy_Pack[3305100][8] = {}
	tBossCopy_Pack[3305100][8]["LogId"] = 12000851
	tBossCopy_Pack[3305100][8]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305100][8][1] = {}
	tBossCopy_Pack[3305100][8][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305100][8][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305100][8][1]["RewardItem"] = {}
	tBossCopy_Pack[3305100][8][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305100][8][1]["RewardItem"][1]["Id"] = 134079
	tBossCopy_Pack[3305100][8][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305100][8][2] = {}
	tBossCopy_Pack[3305100][8][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305100][8][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305100][8][2]["RewardItem"] = {}
	tBossCopy_Pack[3305100][8][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305100][8][2]["RewardItem"][1]["Id"] = 120159
	tBossCopy_Pack[3305100][8][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 铁扇门
	tBossCopy_Pack[3305100][9] = {}
	tBossCopy_Pack[3305100][9]["LogId"] = 12000851
	tBossCopy_Pack[3305100][9]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305100][9][1] = {}
	tBossCopy_Pack[3305100][9][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305100][9][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305100][9][1]["RewardItem"] = {}
	tBossCopy_Pack[3305100][9][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305100][9][1]["RewardItem"][1]["Id"] = 101078
	tBossCopy_Pack[3305100][9][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305100][9][2] = {}
	tBossCopy_Pack[3305100][9][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305100][9][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305100][9][2]["RewardItem"] = {}
	tBossCopy_Pack[3305100][9][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305100][9][2]["RewardItem"][1]["Id"] = 120159
	tBossCopy_Pack[3305100][9][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
	-- 100级 精品装备
	tBossCopy_Pack[3305101] = {}
	-- 勇士（10-15）
	tBossCopy_Pack[3305101][1] = {}
	tBossCopy_Pack[3305101][1]["LogId"] = 12000851
	tBossCopy_Pack[3305101][1]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305101][1][1] = {}
	tBossCopy_Pack[3305101][1][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305101][1][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305101][1][1]["RewardItem"] = {}
	tBossCopy_Pack[3305101][1][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305101][1][1]["RewardItem"][1]["Id"] = 118088
	tBossCopy_Pack[3305101][1][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305101][1][2] = {}
	tBossCopy_Pack[3305101][1][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305101][1][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305101][1][2]["RewardItem"] = {}
	tBossCopy_Pack[3305101][1][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305101][1][2]["RewardItem"][1]["Id"] = 160198
	tBossCopy_Pack[3305101][1][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 战士（20-25）
	tBossCopy_Pack[3305101][2] = {}
	tBossCopy_Pack[3305101][2]["LogId"] = 12000851
	tBossCopy_Pack[3305101][2]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305101][2][1] = {}
	tBossCopy_Pack[3305101][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305101][2][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305101][2][1]["RewardItem"] = {}
	tBossCopy_Pack[3305101][2][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305101][2][1]["RewardItem"][1]["Id"] = 111088
	tBossCopy_Pack[3305101][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305101][2][2] = {}
	tBossCopy_Pack[3305101][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305101][2][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305101][2][2]["RewardItem"] = {}
	tBossCopy_Pack[3305101][2][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305101][2][2]["RewardItem"][1]["Id"] = 160198
	tBossCopy_Pack[3305101][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 射手（40-45）
	tBossCopy_Pack[3305101][3] = {}
	tBossCopy_Pack[3305101][3]["LogId"] = 12000851
	tBossCopy_Pack[3305101][3]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305101][3][1] = {}
	tBossCopy_Pack[3305101][3][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305101][3][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305101][3][1]["RewardItem"] = {}
	tBossCopy_Pack[3305101][3][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305101][3][1]["RewardItem"][1]["Id"] = 113068
	tBossCopy_Pack[3305101][3][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305101][3][2] = {}
	tBossCopy_Pack[3305101][3][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305101][3][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305101][3][2]["RewardItem"] = {}
	tBossCopy_Pack[3305101][3][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305101][3][2]["RewardItem"][1]["Id"] = 160198
	tBossCopy_Pack[3305101][3][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 忍者（50-55）
	tBossCopy_Pack[3305101][4] = {}
	tBossCopy_Pack[3305101][4]["LogId"] = 12000851
	tBossCopy_Pack[3305101][4]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305101][4][1] = {}
	tBossCopy_Pack[3305101][4][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305101][4][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305101][4][1]["RewardItem"] = {}
	tBossCopy_Pack[3305101][4][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305101][4][1]["RewardItem"][1]["Id"] = 123088
	tBossCopy_Pack[3305101][4][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305101][4][2] = {}
	tBossCopy_Pack[3305101][4][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305101][4][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305101][4][2]["RewardItem"] = {}
	tBossCopy_Pack[3305101][4][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305101][4][2]["RewardItem"][1]["Id"] = 160198
	tBossCopy_Pack[3305101][4][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 武僧（60-65）
	tBossCopy_Pack[3305101][5] = {}
	tBossCopy_Pack[3305101][5]["LogId"] = 12000851
	tBossCopy_Pack[3305101][5]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305101][5][1] = {}
	tBossCopy_Pack[3305101][5][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305101][5][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305101][5][1]["RewardItem"] = {}
	tBossCopy_Pack[3305101][5][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305101][5][1]["RewardItem"][1]["Id"] = 143088
	tBossCopy_Pack[3305101][5][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305101][5][2] = {}
	tBossCopy_Pack[3305101][5][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305101][5][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305101][5][2]["RewardItem"] = {}
	tBossCopy_Pack[3305101][5][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305101][5][2]["RewardItem"][1]["Id"] = 160198
	tBossCopy_Pack[3305101][5][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 海盗（70-75）
	tBossCopy_Pack[3305101][6] = {}
	tBossCopy_Pack[3305101][6]["LogId"] = 12000851
	tBossCopy_Pack[3305101][6]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305101][6][1] = {}
	tBossCopy_Pack[3305101][6][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305101][6][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305101][6][1]["RewardItem"] = {}
	tBossCopy_Pack[3305101][6][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305101][6][1]["RewardItem"][1]["Id"] = 144088
	tBossCopy_Pack[3305101][6][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305101][6][2] = {}
	tBossCopy_Pack[3305101][6][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305101][6][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305101][6][2]["RewardItem"] = {}
	tBossCopy_Pack[3305101][6][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305101][6][2]["RewardItem"][1]["Id"] = 160198
	tBossCopy_Pack[3305101][6][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 拳师（80-85）
	tBossCopy_Pack[3305101][7] = {}
	tBossCopy_Pack[3305101][7]["LogId"] = 12000851
	tBossCopy_Pack[3305101][7]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305101][7][1] = {}
	tBossCopy_Pack[3305101][7][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305101][7][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305101][7][1]["RewardItem"] = {}
	tBossCopy_Pack[3305101][7][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305101][7][1]["RewardItem"][1]["Id"] = 148088
	tBossCopy_Pack[3305101][7][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305101][7][2] = {}
	tBossCopy_Pack[3305101][7][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305101][7][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305101][7][2]["RewardItem"] = {}
	tBossCopy_Pack[3305101][7][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305101][7][2]["RewardItem"][1]["Id"] = 160198
	tBossCopy_Pack[3305101][7][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 道士（100-145） -- 水道（132-135） -- 火道（142-145）
	tBossCopy_Pack[3305101][8] = {}
	tBossCopy_Pack[3305101][8]["LogId"] = 12000851
	tBossCopy_Pack[3305101][8]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305101][8][1] = {}
	tBossCopy_Pack[3305101][8][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305101][8][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305101][8][1]["RewardItem"] = {}
	tBossCopy_Pack[3305101][8][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305101][8][1]["RewardItem"][1]["Id"] = 114088
	tBossCopy_Pack[3305101][8][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305101][8][2] = {}
	tBossCopy_Pack[3305101][8][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305101][8][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305101][8][2]["RewardItem"] = {}
	tBossCopy_Pack[3305101][8][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305101][8][2]["RewardItem"][1]["Id"] = 160198
	tBossCopy_Pack[3305101][8][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 铁扇门
	tBossCopy_Pack[3305101][9] = {}
	tBossCopy_Pack[3305101][9]["LogId"] = 12000851
	tBossCopy_Pack[3305101][9]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305101][9][1] = {}
	tBossCopy_Pack[3305101][9][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305101][9][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305101][9][1]["RewardItem"] = {}
	tBossCopy_Pack[3305101][9][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305101][9][1]["RewardItem"][1]["Id"] = 170088
	tBossCopy_Pack[3305101][9][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305101][9][2] = {}
	tBossCopy_Pack[3305101][9][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305101][9][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305101][9][2]["RewardItem"] = {}
	tBossCopy_Pack[3305101][9][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305101][9][2]["RewardItem"][1]["Id"] = 160198
	tBossCopy_Pack[3305101][9][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
	-- 100级 极品装备
	tBossCopy_Pack[3305102] = {}
	-- 勇士（10-15）
	tBossCopy_Pack[3305102][1] = {}
	tBossCopy_Pack[3305102][1]["LogId"] = 12000851
	tBossCopy_Pack[3305102][1]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305102][1][1] = {}
	tBossCopy_Pack[3305102][1][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305102][1][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305102][1][1]["RewardItem"] = {}
	tBossCopy_Pack[3305102][1][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305102][1][1]["RewardItem"][1]["Id"] = 118089
	tBossCopy_Pack[3305102][1][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305102][1][2] = {}
	tBossCopy_Pack[3305102][1][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305102][1][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305102][1][2]["RewardItem"] = {}
	tBossCopy_Pack[3305102][1][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305102][1][2]["RewardItem"][1]["Id"] = 160199
	tBossCopy_Pack[3305102][1][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 战士（20-25）
	tBossCopy_Pack[3305102][2] = {}
	tBossCopy_Pack[3305102][2]["LogId"] = 12000851
	tBossCopy_Pack[3305102][2]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305102][2][1] = {}
	tBossCopy_Pack[3305102][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305102][2][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305102][2][1]["RewardItem"] = {}
	tBossCopy_Pack[3305102][2][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305102][2][1]["RewardItem"][1]["Id"] = 111089
	tBossCopy_Pack[3305102][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305102][2][2] = {}
	tBossCopy_Pack[3305102][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305102][2][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305102][2][2]["RewardItem"] = {}
	tBossCopy_Pack[3305102][2][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305102][2][2]["RewardItem"][1]["Id"] = 160199
	tBossCopy_Pack[3305102][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 射手（40-45）
	tBossCopy_Pack[3305102][3] = {}
	tBossCopy_Pack[3305102][3]["LogId"] = 12000851
	tBossCopy_Pack[3305102][3]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305102][3][1] = {}
	tBossCopy_Pack[3305102][3][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305102][3][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305102][3][1]["RewardItem"] = {}
	tBossCopy_Pack[3305102][3][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305102][3][1]["RewardItem"][1]["Id"] = 113069
	tBossCopy_Pack[3305102][3][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305102][3][2] = {}
	tBossCopy_Pack[3305102][3][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305102][3][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305102][3][2]["RewardItem"] = {}
	tBossCopy_Pack[3305102][3][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305102][3][2]["RewardItem"][1]["Id"] = 160199
	tBossCopy_Pack[3305102][3][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 忍者（50-55）
	tBossCopy_Pack[3305102][4] = {}
	tBossCopy_Pack[3305102][4]["LogId"] = 12000851
	tBossCopy_Pack[3305102][4]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305102][4][1] = {}
	tBossCopy_Pack[3305102][4][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305102][4][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305102][4][1]["RewardItem"] = {}
	tBossCopy_Pack[3305102][4][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305102][4][1]["RewardItem"][1]["Id"] = 123089
	tBossCopy_Pack[3305102][4][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305102][4][2] = {}
	tBossCopy_Pack[3305102][4][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305102][4][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305102][4][2]["RewardItem"] = {}
	tBossCopy_Pack[3305102][4][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305102][4][2]["RewardItem"][1]["Id"] = 160199
	tBossCopy_Pack[3305102][4][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 武僧（60-65）
	tBossCopy_Pack[3305102][5] = {}
	tBossCopy_Pack[3305102][5]["LogId"] = 12000851
	tBossCopy_Pack[3305102][5]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305102][5][1] = {}
	tBossCopy_Pack[3305102][5][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305102][5][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305102][5][1]["RewardItem"] = {}
	tBossCopy_Pack[3305102][5][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305102][5][1]["RewardItem"][1]["Id"] = 143089
	tBossCopy_Pack[3305102][5][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305102][5][2] = {}
	tBossCopy_Pack[3305102][5][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305102][5][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305102][5][2]["RewardItem"] = {}
	tBossCopy_Pack[3305102][5][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305102][5][2]["RewardItem"][1]["Id"] = 160199
	tBossCopy_Pack[3305102][5][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 海盗（70-75）
	tBossCopy_Pack[3305102][6] = {}
	tBossCopy_Pack[3305102][6]["LogId"] = 12000851
	tBossCopy_Pack[3305102][6]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305102][6][1] = {}
	tBossCopy_Pack[3305102][6][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305102][6][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305102][6][1]["RewardItem"] = {}
	tBossCopy_Pack[3305102][6][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305102][6][1]["RewardItem"][1]["Id"] = 144089
	tBossCopy_Pack[3305102][6][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305102][6][2] = {}
	tBossCopy_Pack[3305102][6][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305102][6][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305102][6][2]["RewardItem"] = {}
	tBossCopy_Pack[3305102][6][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305102][6][2]["RewardItem"][1]["Id"] = 160199
	tBossCopy_Pack[3305102][6][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 拳师（80-85）
	tBossCopy_Pack[3305102][7] = {}
	tBossCopy_Pack[3305102][7]["LogId"] = 12000851
	tBossCopy_Pack[3305102][7]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305102][7][1] = {}
	tBossCopy_Pack[3305102][7][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305102][7][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305102][7][1]["RewardItem"] = {}
	tBossCopy_Pack[3305102][7][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305102][7][1]["RewardItem"][1]["Id"] = 148089
	tBossCopy_Pack[3305102][7][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305102][7][2] = {}
	tBossCopy_Pack[3305102][7][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305102][7][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305102][7][2]["RewardItem"] = {}
	tBossCopy_Pack[3305102][7][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305102][7][2]["RewardItem"][1]["Id"] = 160199
	tBossCopy_Pack[3305102][7][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 道士（100-145） -- 水道（132-135） -- 火道（142-145）
	tBossCopy_Pack[3305102][8] = {}
	tBossCopy_Pack[3305102][8]["LogId"] = 12000851
	tBossCopy_Pack[3305102][8]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305102][8][1] = {}
	tBossCopy_Pack[3305102][8][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305102][8][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305102][8][1]["RewardItem"] = {}
	tBossCopy_Pack[3305102][8][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305102][8][1]["RewardItem"][1]["Id"] = 114089
	tBossCopy_Pack[3305102][8][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305102][8][2] = {}
	tBossCopy_Pack[3305102][8][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305102][8][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305102][8][2]["RewardItem"] = {}
	tBossCopy_Pack[3305102][8][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305102][8][2]["RewardItem"][1]["Id"] = 160199
	tBossCopy_Pack[3305102][8][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 铁扇门
	tBossCopy_Pack[3305102][9] = {}
	tBossCopy_Pack[3305102][9]["LogId"] = 12000851
	tBossCopy_Pack[3305102][9]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305102][9][1] = {}
	tBossCopy_Pack[3305102][9][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305102][9][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305102][9][1]["RewardItem"] = {}
	tBossCopy_Pack[3305102][9][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305102][9][1]["RewardItem"][1]["Id"] = 170089
	tBossCopy_Pack[3305102][9][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305102][9][2] = {}
	tBossCopy_Pack[3305102][9][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305102][9][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305102][9][2]["RewardItem"] = {}
	tBossCopy_Pack[3305102][9][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305102][9][2]["RewardItem"][1]["Id"] = 160199
	tBossCopy_Pack[3305102][9][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
	-- 110级 精品装备
	tBossCopy_Pack[3305103] = {}
	-- 勇士（10-15）
	tBossCopy_Pack[3305103][1] = {}
	tBossCopy_Pack[3305103][1]["LogId"] = 12000851
	tBossCopy_Pack[3305103][1]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305103][1][1] = {}
	tBossCopy_Pack[3305103][1][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305103][1][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305103][1][1]["RewardItem"] = {}
	tBossCopy_Pack[3305103][1][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305103][1][1]["RewardItem"][1]["Id"] = 410218
	tBossCopy_Pack[3305103][1][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305103][1][2] = {}
	tBossCopy_Pack[3305103][1][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305103][1][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305103][1][2]["RewardItem"] = {}
	tBossCopy_Pack[3305103][1][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305103][1][2]["RewardItem"][1]["Id"] = 150218
	tBossCopy_Pack[3305103][1][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 战士（20-25）
	tBossCopy_Pack[3305103][2] = {}
	tBossCopy_Pack[3305103][2]["LogId"] = 12000851
	tBossCopy_Pack[3305103][2]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305103][2][1] = {}
	tBossCopy_Pack[3305103][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305103][2][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305103][2][1]["RewardItem"] = {}
	tBossCopy_Pack[3305103][2][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305103][2][1]["RewardItem"][1]["Id"] = 480218
	tBossCopy_Pack[3305103][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305103][2][2] = {}
	tBossCopy_Pack[3305103][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305103][2][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305103][2][2]["RewardItem"] = {}
	tBossCopy_Pack[3305103][2][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305103][2][2]["RewardItem"][1]["Id"] = 150218
	tBossCopy_Pack[3305103][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 射手（40-45）
	tBossCopy_Pack[3305103][3] = {}
	tBossCopy_Pack[3305103][3]["LogId"] = 12000851
	tBossCopy_Pack[3305103][3]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305103][3][1] = {}
	tBossCopy_Pack[3305103][3][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305103][3][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305103][3][1]["RewardItem"] = {}
	tBossCopy_Pack[3305103][3][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305103][3][1]["RewardItem"][1]["Id"] = 613208
	tBossCopy_Pack[3305103][3][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305103][3][2] = {}
	tBossCopy_Pack[3305103][3][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305103][3][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305103][3][2]["RewardItem"] = {}
	tBossCopy_Pack[3305103][3][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305103][3][2]["RewardItem"][1]["Id"] = 150218
	tBossCopy_Pack[3305103][3][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 忍者（50-55）
	tBossCopy_Pack[3305103][4] = {}
	tBossCopy_Pack[3305103][4]["LogId"] = 12000851
	tBossCopy_Pack[3305103][4]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305103][4][1] = {}
	tBossCopy_Pack[3305103][4][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305103][4][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305103][4][1]["RewardItem"] = {}
	tBossCopy_Pack[3305103][4][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305103][4][1]["RewardItem"][1]["Id"] = 601218
	tBossCopy_Pack[3305103][4][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305103][4][2] = {}
	tBossCopy_Pack[3305103][4][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305103][4][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305103][4][2]["RewardItem"] = {}
	tBossCopy_Pack[3305103][4][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305103][4][2]["RewardItem"][1]["Id"] = 150218
	tBossCopy_Pack[3305103][4][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 武僧（60-65）
	tBossCopy_Pack[3305103][5] = {}
	tBossCopy_Pack[3305103][5]["LogId"] = 12000851
	tBossCopy_Pack[3305103][5]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305103][5][1] = {}
	tBossCopy_Pack[3305103][5][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305103][5][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305103][5][1]["RewardItem"] = {}
	tBossCopy_Pack[3305103][5][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305103][5][1]["RewardItem"][1]["Id"] = 610218
	tBossCopy_Pack[3305103][5][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305103][5][2] = {}
	tBossCopy_Pack[3305103][5][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305103][5][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305103][5][2]["RewardItem"] = {}
	tBossCopy_Pack[3305103][5][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305103][5][2]["RewardItem"][1]["Id"] = 150218
	tBossCopy_Pack[3305103][5][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 海盗（70-75）
	tBossCopy_Pack[3305103][6] = {}
	tBossCopy_Pack[3305103][6]["LogId"] = 12000851
	tBossCopy_Pack[3305103][6]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305103][6][1] = {}
	tBossCopy_Pack[3305103][6][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305103][6][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305103][6][1]["RewardItem"] = {}
	tBossCopy_Pack[3305103][6][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305103][6][1]["RewardItem"][1]["Id"] = 611218
	tBossCopy_Pack[3305103][6][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305103][6][2] = {}
	tBossCopy_Pack[3305103][6][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305103][6][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305103][6][2]["RewardItem"] = {}
	tBossCopy_Pack[3305103][6][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305103][6][2]["RewardItem"][1]["Id"] = 150218
	tBossCopy_Pack[3305103][6][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 拳师（80-85）
	tBossCopy_Pack[3305103][7] = {}
	tBossCopy_Pack[3305103][7]["LogId"] = 12000851
	tBossCopy_Pack[3305103][7]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305103][7][1] = {}
	tBossCopy_Pack[3305103][7][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305103][7][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305103][7][1]["RewardItem"] = {}
	tBossCopy_Pack[3305103][7][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305103][7][1]["RewardItem"][1]["Id"] = 617218
	tBossCopy_Pack[3305103][7][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305103][7][2] = {}
	tBossCopy_Pack[3305103][7][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305103][7][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305103][7][2]["RewardItem"] = {}
	tBossCopy_Pack[3305103][7][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305103][7][2]["RewardItem"][1]["Id"] = 150218
	tBossCopy_Pack[3305103][7][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 道士（100-145） -- 水道（132-135） -- 火道（142-145）
	tBossCopy_Pack[3305103][8] = {}
	tBossCopy_Pack[3305103][8]["LogId"] = 12000851
	tBossCopy_Pack[3305103][8]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305103][8][1] = {}
	tBossCopy_Pack[3305103][8][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305103][8][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305103][8][1]["RewardItem"] = {}
	tBossCopy_Pack[3305103][8][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305103][8][1]["RewardItem"][1]["Id"] = 421218
	tBossCopy_Pack[3305103][8][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305103][8][2] = {}
	tBossCopy_Pack[3305103][8][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305103][8][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305103][8][2]["RewardItem"] = {}
	tBossCopy_Pack[3305103][8][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305103][8][2]["RewardItem"][1]["Id"] = 150218
	tBossCopy_Pack[3305103][8][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 铁扇门
	tBossCopy_Pack[3305103][9] = {}
	tBossCopy_Pack[3305103][9]["LogId"] = 12000851
	tBossCopy_Pack[3305103][9]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305103][9][1] = {}
	tBossCopy_Pack[3305103][9][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305103][9][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305103][9][1]["RewardItem"] = {}
	tBossCopy_Pack[3305103][9][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305103][9][1]["RewardItem"][1]["Id"] = 626218
	tBossCopy_Pack[3305103][9][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305103][9][2] = {}
	tBossCopy_Pack[3305103][9][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305103][9][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305103][9][2]["RewardItem"] = {}
	tBossCopy_Pack[3305103][9][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305103][9][2]["RewardItem"][1]["Id"] = 150218
	tBossCopy_Pack[3305103][9][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
	-- 110级 极品装备
	tBossCopy_Pack[3305104] = {}
	-- 勇士（10-15）
	tBossCopy_Pack[3305104][1] = {}
	tBossCopy_Pack[3305104][1]["LogId"] = 12000851
	tBossCopy_Pack[3305104][1]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305104][1][1] = {}
	tBossCopy_Pack[3305104][1][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305104][1][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305104][1][1]["RewardItem"] = {}
	tBossCopy_Pack[3305104][1][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305104][1][1]["RewardItem"][1]["Id"] = 410219
	tBossCopy_Pack[3305104][1][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305104][1][2] = {}
	tBossCopy_Pack[3305104][1][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305104][1][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305104][1][2]["RewardItem"] = {}
	tBossCopy_Pack[3305104][1][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305104][1][2]["RewardItem"][1]["Id"] = 150219
	tBossCopy_Pack[3305104][1][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 战士（20-25）
	tBossCopy_Pack[3305104][2] = {}
	tBossCopy_Pack[3305104][2]["LogId"] = 12000851
	tBossCopy_Pack[3305104][2]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305104][2][1] = {}
	tBossCopy_Pack[3305104][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305104][2][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305104][2][1]["RewardItem"] = {}
	tBossCopy_Pack[3305104][2][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305104][2][1]["RewardItem"][1]["Id"] = 490219
	tBossCopy_Pack[3305104][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305104][2][2] = {}
	tBossCopy_Pack[3305104][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305104][2][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305104][2][2]["RewardItem"] = {}
	tBossCopy_Pack[3305104][2][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305104][2][2]["RewardItem"][1]["Id"] = 150219
	tBossCopy_Pack[3305104][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 射手（40-45）
	tBossCopy_Pack[3305104][3] = {}
	tBossCopy_Pack[3305104][3]["LogId"] = 12000851
	tBossCopy_Pack[3305104][3]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305104][3][1] = {}
	tBossCopy_Pack[3305104][3][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305104][3][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305104][3][1]["RewardItem"] = {}
	tBossCopy_Pack[3305104][3][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305104][3][1]["RewardItem"][1]["Id"] = 613209
	tBossCopy_Pack[3305104][3][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305104][3][2] = {}
	tBossCopy_Pack[3305104][3][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305104][3][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305104][3][2]["RewardItem"] = {}
	tBossCopy_Pack[3305104][3][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305104][3][2]["RewardItem"][1]["Id"] = 150219
	tBossCopy_Pack[3305104][3][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 忍者（50-55）
	tBossCopy_Pack[3305104][4] = {}
	tBossCopy_Pack[3305104][4]["LogId"] = 12000851
	tBossCopy_Pack[3305104][4]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305104][4][1] = {}
	tBossCopy_Pack[3305104][4][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305104][4][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305104][4][1]["RewardItem"] = {}
	tBossCopy_Pack[3305104][4][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305104][4][1]["RewardItem"][1]["Id"] = 601219
	tBossCopy_Pack[3305104][4][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305104][4][2] = {}
	tBossCopy_Pack[3305104][4][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305104][4][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305104][4][2]["RewardItem"] = {}
	tBossCopy_Pack[3305104][4][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305104][4][2]["RewardItem"][1]["Id"] = 150219
	tBossCopy_Pack[3305104][4][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 武僧（60-65）
	tBossCopy_Pack[3305104][5] = {}
	tBossCopy_Pack[3305104][5]["LogId"] = 12000851
	tBossCopy_Pack[3305104][5]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305104][5][1] = {}
	tBossCopy_Pack[3305104][5][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305104][5][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305104][5][1]["RewardItem"] = {}
	tBossCopy_Pack[3305104][5][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305104][5][1]["RewardItem"][1]["Id"] = 610219
	tBossCopy_Pack[3305104][5][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305104][5][2] = {}
	tBossCopy_Pack[3305104][5][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305104][5][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305104][5][2]["RewardItem"] = {}
	tBossCopy_Pack[3305104][5][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305104][5][2]["RewardItem"][1]["Id"] = 150219
	tBossCopy_Pack[3305104][5][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 海盗（70-75）
	tBossCopy_Pack[3305104][6] = {}
	tBossCopy_Pack[3305104][6]["LogId"] = 12000851
	tBossCopy_Pack[3305104][6]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305104][6][1] = {}
	tBossCopy_Pack[3305104][6][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305104][6][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305104][6][1]["RewardItem"] = {}
	tBossCopy_Pack[3305104][6][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305104][6][1]["RewardItem"][1]["Id"] = 611219
	tBossCopy_Pack[3305104][6][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305104][6][2] = {}
	tBossCopy_Pack[3305104][6][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305104][6][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305104][6][2]["RewardItem"] = {}
	tBossCopy_Pack[3305104][6][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305104][6][2]["RewardItem"][1]["Id"] = 150219
	tBossCopy_Pack[3305104][6][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 拳师（80-85）
	tBossCopy_Pack[3305104][7] = {}
	tBossCopy_Pack[3305104][7]["LogId"] = 12000851
	tBossCopy_Pack[3305104][7]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305104][7][1] = {}
	tBossCopy_Pack[3305104][7][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305104][7][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305104][7][1]["RewardItem"] = {}
	tBossCopy_Pack[3305104][7][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305104][7][1]["RewardItem"][1]["Id"] = 617219
	tBossCopy_Pack[3305104][7][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305104][7][2] = {}
	tBossCopy_Pack[3305104][7][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305104][7][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305104][7][2]["RewardItem"] = {}
	tBossCopy_Pack[3305104][7][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305104][7][2]["RewardItem"][1]["Id"] = 150219
	tBossCopy_Pack[3305104][7][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 道士（100-145） -- 水道（132-135） -- 火道（142-145）
	tBossCopy_Pack[3305104][8] = {}
	tBossCopy_Pack[3305104][8]["LogId"] = 12000851
	tBossCopy_Pack[3305104][8]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305104][8][1] = {}
	tBossCopy_Pack[3305104][8][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305104][8][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305104][8][1]["RewardItem"] = {}
	tBossCopy_Pack[3305104][8][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305104][8][1]["RewardItem"][1]["Id"] = 421219
	tBossCopy_Pack[3305104][8][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305104][8][2] = {}
	tBossCopy_Pack[3305104][8][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305104][8][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305104][8][2]["RewardItem"] = {}
	tBossCopy_Pack[3305104][8][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305104][8][2]["RewardItem"][1]["Id"] = 150219
	tBossCopy_Pack[3305104][8][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 铁扇门
	tBossCopy_Pack[3305104][9] = {}
	tBossCopy_Pack[3305104][9]["LogId"] = 12000851
	tBossCopy_Pack[3305104][9]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305104][9][1] = {}
	tBossCopy_Pack[3305104][9][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305104][9][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305104][9][1]["RewardItem"] = {}
	tBossCopy_Pack[3305104][9][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305104][9][1]["RewardItem"][1]["Id"] = 626219
	tBossCopy_Pack[3305104][9][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305104][9][2] = {}
	tBossCopy_Pack[3305104][9][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305104][9][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305104][9][2]["RewardItem"] = {}
	tBossCopy_Pack[3305104][9][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305104][9][2]["RewardItem"][1]["Id"] = 150219
	tBossCopy_Pack[3305104][9][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
	-- 115级 精品装备
	tBossCopy_Pack[3305105] = {}
	-- 勇士（10-15）
	tBossCopy_Pack[3305105][1] = {}
	tBossCopy_Pack[3305105][1]["LogId"] = 12000851
	tBossCopy_Pack[3305105][1]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305105][1][1] = {}
	tBossCopy_Pack[3305105][1][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305105][1][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305105][1][1]["RewardItem"] = {}
	tBossCopy_Pack[3305105][1][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305105][1][1]["RewardItem"][1]["Id"] = 130098
	tBossCopy_Pack[3305105][1][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305105][1][2] = {}
	tBossCopy_Pack[3305105][1][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305105][1][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305105][1][2]["RewardItem"] = {}
	tBossCopy_Pack[3305105][1][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305105][1][2]["RewardItem"][1]["Id"] = 120218
	tBossCopy_Pack[3305105][1][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 战士（20-25）
	tBossCopy_Pack[3305105][2] = {}
	tBossCopy_Pack[3305105][2]["LogId"] = 12000851
	tBossCopy_Pack[3305105][2]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305105][2][1] = {}
	tBossCopy_Pack[3305105][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305105][2][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305105][2][1]["RewardItem"] = {}
	tBossCopy_Pack[3305105][2][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305105][2][1]["RewardItem"][1]["Id"] = 131098
	tBossCopy_Pack[3305105][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305105][2][2] = {}
	tBossCopy_Pack[3305105][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305105][2][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305105][2][2]["RewardItem"] = {}
	tBossCopy_Pack[3305105][2][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305105][2][2]["RewardItem"][1]["Id"] = 120218
	tBossCopy_Pack[3305105][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 射手（40-45）
	tBossCopy_Pack[3305105][3] = {}
	tBossCopy_Pack[3305105][3]["LogId"] = 12000851
	tBossCopy_Pack[3305105][3]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305105][3][1] = {}
	tBossCopy_Pack[3305105][3][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305105][3][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305105][3][1]["RewardItem"] = {}
	tBossCopy_Pack[3305105][3][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305105][3][1]["RewardItem"][1]["Id"] = 133098
	tBossCopy_Pack[3305105][3][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305105][3][2] = {}
	tBossCopy_Pack[3305105][3][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305105][3][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305105][3][2]["RewardItem"] = {}
	tBossCopy_Pack[3305105][3][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305105][3][2]["RewardItem"][1]["Id"] = 120218
	tBossCopy_Pack[3305105][3][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 忍者（50-55）
	tBossCopy_Pack[3305105][4] = {}
	tBossCopy_Pack[3305105][4]["LogId"] = 12000851
	tBossCopy_Pack[3305105][4]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305105][4][1] = {}
	tBossCopy_Pack[3305105][4][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305105][4][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305105][4][1]["RewardItem"] = {}
	tBossCopy_Pack[3305105][4][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305105][4][1]["RewardItem"][1]["Id"] = 135098
	tBossCopy_Pack[3305105][4][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305105][4][2] = {}
	tBossCopy_Pack[3305105][4][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305105][4][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305105][4][2]["RewardItem"] = {}
	tBossCopy_Pack[3305105][4][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305105][4][2]["RewardItem"][1]["Id"] = 120218
	tBossCopy_Pack[3305105][4][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 武僧（60-65）
	tBossCopy_Pack[3305105][5] = {}
	tBossCopy_Pack[3305105][5]["LogId"] = 12000851
	tBossCopy_Pack[3305105][5]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305105][5][1] = {}
	tBossCopy_Pack[3305105][5][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305105][5][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305105][5][1]["RewardItem"] = {}
	tBossCopy_Pack[3305105][5][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305105][5][1]["RewardItem"][1]["Id"] = 136098
	tBossCopy_Pack[3305105][5][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305105][5][2] = {}
	tBossCopy_Pack[3305105][5][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305105][5][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305105][5][2]["RewardItem"] = {}
	tBossCopy_Pack[3305105][5][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305105][5][2]["RewardItem"][1]["Id"] = 120218
	tBossCopy_Pack[3305105][5][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 海盗（70-75）
	tBossCopy_Pack[3305105][6] = {}
	tBossCopy_Pack[3305105][6]["LogId"] = 12000851
	tBossCopy_Pack[3305105][6]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305105][6][1] = {}
	tBossCopy_Pack[3305105][6][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305105][6][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305105][6][1]["RewardItem"] = {}
	tBossCopy_Pack[3305105][6][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305105][6][1]["RewardItem"][1]["Id"] = 139098
	tBossCopy_Pack[3305105][6][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305105][6][2] = {}
	tBossCopy_Pack[3305105][6][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305105][6][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305105][6][2]["RewardItem"] = {}
	tBossCopy_Pack[3305105][6][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305105][6][2]["RewardItem"][1]["Id"] = 120218
	tBossCopy_Pack[3305105][6][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 拳师（80-85）
	tBossCopy_Pack[3305105][7] = {}
	tBossCopy_Pack[3305105][7]["LogId"] = 12000851
	tBossCopy_Pack[3305105][7]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305105][7][1] = {}
	tBossCopy_Pack[3305105][7][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305105][7][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305105][7][1]["RewardItem"] = {}
	tBossCopy_Pack[3305105][7][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305105][7][1]["RewardItem"][1]["Id"] = 138098
	tBossCopy_Pack[3305105][7][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305105][7][2] = {}
	tBossCopy_Pack[3305105][7][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305105][7][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305105][7][2]["RewardItem"] = {}
	tBossCopy_Pack[3305105][7][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305105][7][2]["RewardItem"][1]["Id"] = 120218
	tBossCopy_Pack[3305105][7][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 道士（100-145） -- 水道（132-135） -- 火道（142-145）
	tBossCopy_Pack[3305105][8] = {}
	tBossCopy_Pack[3305105][8]["LogId"] = 12000851
	tBossCopy_Pack[3305105][8]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305105][8][1] = {}
	tBossCopy_Pack[3305105][8][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305105][8][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305105][8][1]["RewardItem"] = {}
	tBossCopy_Pack[3305105][8][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305105][8][1]["RewardItem"][1]["Id"] = 134098
	tBossCopy_Pack[3305105][8][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305105][8][2] = {}
	tBossCopy_Pack[3305105][8][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305105][8][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305105][8][2]["RewardItem"] = {}
	tBossCopy_Pack[3305105][8][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305105][8][2]["RewardItem"][1]["Id"] = 120218
	tBossCopy_Pack[3305105][8][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 铁扇门
	tBossCopy_Pack[3305105][9] = {}
	tBossCopy_Pack[3305105][9]["LogId"] = 12000851
	tBossCopy_Pack[3305105][9]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305105][9][1] = {}
	tBossCopy_Pack[3305105][9][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305105][9][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305105][9][1]["RewardItem"] = {}
	tBossCopy_Pack[3305105][9][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305105][9][1]["RewardItem"][1]["Id"] = 101098
	tBossCopy_Pack[3305105][9][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305105][9][2] = {}
	tBossCopy_Pack[3305105][9][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305105][9][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305105][9][2]["RewardItem"] = {}
	tBossCopy_Pack[3305105][9][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305105][9][2]["RewardItem"][1]["Id"] = 120218
	tBossCopy_Pack[3305105][9][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
	-- 115级 极品装备
	tBossCopy_Pack[3305106] = {}
	-- 勇士（10-15）
	tBossCopy_Pack[3305106][1] = {}
	tBossCopy_Pack[3305106][1]["LogId"] = 12000851
	tBossCopy_Pack[3305106][1]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305106][1][1] = {}
	tBossCopy_Pack[3305106][1][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305106][1][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305106][1][1]["RewardItem"] = {}
	tBossCopy_Pack[3305106][1][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305106][1][1]["RewardItem"][1]["Id"] = 130099
	tBossCopy_Pack[3305106][1][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305106][1][2] = {}
	tBossCopy_Pack[3305106][1][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305106][1][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305106][1][2]["RewardItem"] = {}
	tBossCopy_Pack[3305106][1][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305106][1][2]["RewardItem"][1]["Id"] = 120219
	tBossCopy_Pack[3305106][1][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 战士（20-25）
	tBossCopy_Pack[3305106][2] = {}
	tBossCopy_Pack[3305106][2]["LogId"] = 12000851
	tBossCopy_Pack[3305106][2]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305106][2][1] = {}
	tBossCopy_Pack[3305106][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305106][2][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305106][2][1]["RewardItem"] = {}
	tBossCopy_Pack[3305106][2][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305106][2][1]["RewardItem"][1]["Id"] = 131099
	tBossCopy_Pack[3305106][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305106][2][2] = {}
	tBossCopy_Pack[3305106][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305106][2][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305106][2][2]["RewardItem"] = {}
	tBossCopy_Pack[3305106][2][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305106][2][2]["RewardItem"][1]["Id"] = 120219
	tBossCopy_Pack[3305106][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 射手（40-45）
	tBossCopy_Pack[3305106][3] = {}
	tBossCopy_Pack[3305106][3]["LogId"] = 12000851
	tBossCopy_Pack[3305106][3]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305106][3][1] = {}
	tBossCopy_Pack[3305106][3][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305106][3][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305106][3][1]["RewardItem"] = {}
	tBossCopy_Pack[3305106][3][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305106][3][1]["RewardItem"][1]["Id"] = 133099
	tBossCopy_Pack[3305106][3][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305106][3][2] = {}
	tBossCopy_Pack[3305106][3][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305106][3][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305106][3][2]["RewardItem"] = {}
	tBossCopy_Pack[3305106][3][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305106][3][2]["RewardItem"][1]["Id"] = 120219
	tBossCopy_Pack[3305106][3][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 忍者（50-55）
	tBossCopy_Pack[3305106][4] = {}
	tBossCopy_Pack[3305106][4]["LogId"] = 12000851
	tBossCopy_Pack[3305106][4]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305106][4][1] = {}
	tBossCopy_Pack[3305106][4][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305106][4][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305106][4][1]["RewardItem"] = {}
	tBossCopy_Pack[3305106][4][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305106][4][1]["RewardItem"][1]["Id"] = 135099
	tBossCopy_Pack[3305106][4][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305106][4][2] = {}
	tBossCopy_Pack[3305106][4][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305106][4][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305106][4][2]["RewardItem"] = {}
	tBossCopy_Pack[3305106][4][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305106][4][2]["RewardItem"][1]["Id"] = 120219
	tBossCopy_Pack[3305106][4][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 武僧（60-65）
	tBossCopy_Pack[3305106][5] = {}
	tBossCopy_Pack[3305106][5]["LogId"] = 12000851
	tBossCopy_Pack[3305106][5]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305106][5][1] = {}
	tBossCopy_Pack[3305106][5][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305106][5][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305106][5][1]["RewardItem"] = {}
	tBossCopy_Pack[3305106][5][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305106][5][1]["RewardItem"][1]["Id"] = 136099
	tBossCopy_Pack[3305106][5][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305106][5][2] = {}
	tBossCopy_Pack[3305106][5][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305106][5][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305106][5][2]["RewardItem"] = {}
	tBossCopy_Pack[3305106][5][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305106][5][2]["RewardItem"][1]["Id"] = 120219
	tBossCopy_Pack[3305106][5][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 海盗（70-75）
	tBossCopy_Pack[3305106][6] = {}
	tBossCopy_Pack[3305106][6]["LogId"] = 12000851
	tBossCopy_Pack[3305106][6]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305106][6][1] = {}
	tBossCopy_Pack[3305106][6][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305106][6][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305106][6][1]["RewardItem"] = {}
	tBossCopy_Pack[3305106][6][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305106][6][1]["RewardItem"][1]["Id"] = 139099
	tBossCopy_Pack[3305106][6][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305106][6][2] = {}
	tBossCopy_Pack[3305106][6][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305106][6][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305106][6][2]["RewardItem"] = {}
	tBossCopy_Pack[3305106][6][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305106][6][2]["RewardItem"][1]["Id"] = 120219
	tBossCopy_Pack[3305106][6][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 拳师（80-85）
	tBossCopy_Pack[3305106][7] = {}
	tBossCopy_Pack[3305106][7]["LogId"] = 12000851
	tBossCopy_Pack[3305106][7]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305106][7][1] = {}
	tBossCopy_Pack[3305106][7][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305106][7][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305106][7][1]["RewardItem"] = {}
	tBossCopy_Pack[3305106][7][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305106][7][1]["RewardItem"][1]["Id"] = 138099
	tBossCopy_Pack[3305106][7][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305106][7][2] = {}
	tBossCopy_Pack[3305106][7][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305106][7][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305106][7][2]["RewardItem"] = {}
	tBossCopy_Pack[3305106][7][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305106][7][2]["RewardItem"][1]["Id"] = 120219
	tBossCopy_Pack[3305106][7][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 道士（100-145） -- 水道（132-135） -- 火道（142-145）
	tBossCopy_Pack[3305106][8] = {}
	tBossCopy_Pack[3305106][8]["LogId"] = 12000851
	tBossCopy_Pack[3305106][8]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305106][8][1] = {}
	tBossCopy_Pack[3305106][8][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305106][8][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305106][8][1]["RewardItem"] = {}
	tBossCopy_Pack[3305106][8][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305106][8][1]["RewardItem"][1]["Id"] = 134099
	tBossCopy_Pack[3305106][8][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305106][8][2] = {}
	tBossCopy_Pack[3305106][8][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305106][8][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305106][8][2]["RewardItem"] = {}
	tBossCopy_Pack[3305106][8][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305106][8][2]["RewardItem"][1]["Id"] = 120219
	tBossCopy_Pack[3305106][8][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 铁扇门
	tBossCopy_Pack[3305106][9] = {}
	tBossCopy_Pack[3305106][9]["LogId"] = 12000851
	tBossCopy_Pack[3305106][9]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305106][9][1] = {}
	tBossCopy_Pack[3305106][9][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305106][9][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305106][9][1]["RewardItem"] = {}
	tBossCopy_Pack[3305106][9][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305106][9][1]["RewardItem"][1]["Id"] = 101099
	tBossCopy_Pack[3305106][9][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305106][9][2] = {}
	tBossCopy_Pack[3305106][9][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305106][9][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305106][9][2]["RewardItem"] = {}
	tBossCopy_Pack[3305106][9][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305106][9][2]["RewardItem"][1]["Id"] = 120219
	tBossCopy_Pack[3305106][9][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
	-- 120级 精品装备
	tBossCopy_Pack[3305107] = {}
	-- 勇士（10-15）
	tBossCopy_Pack[3305107][1] = {}
	tBossCopy_Pack[3305107][1]["LogId"] = 12000851
	tBossCopy_Pack[3305107][1]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305107][1][1] = {}
	tBossCopy_Pack[3305107][1][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305107][1][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305107][1][1]["RewardItem"] = {}
	tBossCopy_Pack[3305107][1][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305107][1][1]["RewardItem"][1]["Id"] = 118108
	tBossCopy_Pack[3305107][1][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305107][1][2] = {}
	tBossCopy_Pack[3305107][1][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305107][1][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305107][1][2]["RewardItem"] = {}
	tBossCopy_Pack[3305107][1][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305107][1][2]["RewardItem"][1]["Id"] = 160228
	tBossCopy_Pack[3305107][1][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 战士（20-25）
	tBossCopy_Pack[3305107][2] = {}
	tBossCopy_Pack[3305107][2]["LogId"] = 12000851
	tBossCopy_Pack[3305107][2]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305107][2][1] = {}
	tBossCopy_Pack[3305107][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305107][2][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305107][2][1]["RewardItem"] = {}
	tBossCopy_Pack[3305107][2][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305107][2][1]["RewardItem"][1]["Id"] = 111108
	tBossCopy_Pack[3305107][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305107][2][2] = {}
	tBossCopy_Pack[3305107][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305107][2][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305107][2][2]["RewardItem"] = {}
	tBossCopy_Pack[3305107][2][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305107][2][2]["RewardItem"][1]["Id"] = 160228
	tBossCopy_Pack[3305107][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 射手（40-45）
	tBossCopy_Pack[3305107][3] = {}
	tBossCopy_Pack[3305107][3]["LogId"] = 12000851
	tBossCopy_Pack[3305107][3]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305107][3][1] = {}
	tBossCopy_Pack[3305107][3][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305107][3][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305107][3][1]["RewardItem"] = {}
	tBossCopy_Pack[3305107][3][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305107][3][1]["RewardItem"][1]["Id"] = 113108
	tBossCopy_Pack[3305107][3][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305107][3][2] = {}
	tBossCopy_Pack[3305107][3][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305107][3][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305107][3][2]["RewardItem"] = {}
	tBossCopy_Pack[3305107][3][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305107][3][2]["RewardItem"][1]["Id"] = 160228
	tBossCopy_Pack[3305107][3][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 忍者（50-55）
	tBossCopy_Pack[3305107][4] = {}
	tBossCopy_Pack[3305107][4]["LogId"] = 12000851
	tBossCopy_Pack[3305107][4]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305107][4][1] = {}
	tBossCopy_Pack[3305107][4][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305107][4][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305107][4][1]["RewardItem"] = {}
	tBossCopy_Pack[3305107][4][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305107][4][1]["RewardItem"][1]["Id"] = 112108
	tBossCopy_Pack[3305107][4][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305107][4][2] = {}
	tBossCopy_Pack[3305107][4][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305107][4][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305107][4][2]["RewardItem"] = {}
	tBossCopy_Pack[3305107][4][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305107][4][2]["RewardItem"][1]["Id"] = 160228
	tBossCopy_Pack[3305107][4][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 武僧（60-65）
	tBossCopy_Pack[3305107][5] = {}
	tBossCopy_Pack[3305107][5]["LogId"] = 12000851
	tBossCopy_Pack[3305107][5]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305107][5][1] = {}
	tBossCopy_Pack[3305107][5][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305107][5][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305107][5][1]["RewardItem"] = {}
	tBossCopy_Pack[3305107][5][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305107][5][1]["RewardItem"][1]["Id"] = 143108
	tBossCopy_Pack[3305107][5][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305107][5][2] = {}
	tBossCopy_Pack[3305107][5][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305107][5][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305107][5][2]["RewardItem"] = {}
	tBossCopy_Pack[3305107][5][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305107][5][2]["RewardItem"][1]["Id"] = 160228
	tBossCopy_Pack[3305107][5][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 海盗（70-75）
	tBossCopy_Pack[3305107][6] = {}
	tBossCopy_Pack[3305107][6]["LogId"] = 12000851
	tBossCopy_Pack[3305107][6]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305107][6][1] = {}
	tBossCopy_Pack[3305107][6][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305107][6][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305107][6][1]["RewardItem"] = {}
	tBossCopy_Pack[3305107][6][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305107][6][1]["RewardItem"][1]["Id"] = 144108
	tBossCopy_Pack[3305107][6][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305107][6][2] = {}
	tBossCopy_Pack[3305107][6][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305107][6][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305107][6][2]["RewardItem"] = {}
	tBossCopy_Pack[3305107][6][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305107][6][2]["RewardItem"][1]["Id"] = 160228
	tBossCopy_Pack[3305107][6][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 拳师（80-85）
	tBossCopy_Pack[3305107][7] = {}
	tBossCopy_Pack[3305107][7]["LogId"] = 12000851
	tBossCopy_Pack[3305107][7]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305107][7][1] = {}
	tBossCopy_Pack[3305107][7][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305107][7][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305107][7][1]["RewardItem"] = {}
	tBossCopy_Pack[3305107][7][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305107][7][1]["RewardItem"][1]["Id"] = 148108
	tBossCopy_Pack[3305107][7][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305107][7][2] = {}
	tBossCopy_Pack[3305107][7][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305107][7][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305107][7][2]["RewardItem"] = {}
	tBossCopy_Pack[3305107][7][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305107][7][2]["RewardItem"][1]["Id"] = 160228
	tBossCopy_Pack[3305107][7][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 道士（100-145） -- 水道（132-135） -- 火道（142-145）
	tBossCopy_Pack[3305107][8] = {}
	tBossCopy_Pack[3305107][8]["LogId"] = 12000851
	tBossCopy_Pack[3305107][8]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305107][8][1] = {}
	tBossCopy_Pack[3305107][8][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305107][8][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305107][8][1]["RewardItem"] = {}
	tBossCopy_Pack[3305107][8][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305107][8][1]["RewardItem"][1]["Id"] = 114108
	tBossCopy_Pack[3305107][8][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305107][8][2] = {}
	tBossCopy_Pack[3305107][8][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305107][8][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305107][8][2]["RewardItem"] = {}
	tBossCopy_Pack[3305107][8][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305107][8][2]["RewardItem"][1]["Id"] = 160228
	tBossCopy_Pack[3305107][8][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 铁扇门
	tBossCopy_Pack[3305107][9] = {}
	tBossCopy_Pack[3305107][9]["LogId"] = 12000851
	tBossCopy_Pack[3305107][9]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305107][9][1] = {}
	tBossCopy_Pack[3305107][9][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305107][9][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305107][9][1]["RewardItem"] = {}
	tBossCopy_Pack[3305107][9][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305107][9][1]["RewardItem"][1]["Id"] = 170108
	tBossCopy_Pack[3305107][9][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305107][9][2] = {}
	tBossCopy_Pack[3305107][9][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305107][9][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305107][9][2]["RewardItem"] = {}
	tBossCopy_Pack[3305107][9][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305107][9][2]["RewardItem"][1]["Id"] = 160228
	tBossCopy_Pack[3305107][9][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
	-- 120级 极品装备
	tBossCopy_Pack[3305108] = {}
	-- 勇士（10-15）
	tBossCopy_Pack[3305108][1] = {}
	tBossCopy_Pack[3305108][1]["LogId"] = 12000851
	tBossCopy_Pack[3305108][1]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305108][1][1] = {}
	tBossCopy_Pack[3305108][1][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305108][1][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305108][1][1]["RewardItem"] = {}
	tBossCopy_Pack[3305108][1][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305108][1][1]["RewardItem"][1]["Id"] = 118109
	tBossCopy_Pack[3305108][1][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305108][1][2] = {}
	tBossCopy_Pack[3305108][1][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305108][1][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305108][1][2]["RewardItem"] = {}
	tBossCopy_Pack[3305108][1][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305108][1][2]["RewardItem"][1]["Id"] = 160229
	tBossCopy_Pack[3305108][1][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 战士（20-25）
	tBossCopy_Pack[3305108][2] = {}
	tBossCopy_Pack[3305108][2]["LogId"] = 12000851
	tBossCopy_Pack[3305108][2]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305108][2][1] = {}
	tBossCopy_Pack[3305108][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305108][2][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305108][2][1]["RewardItem"] = {}
	tBossCopy_Pack[3305108][2][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305108][2][1]["RewardItem"][1]["Id"] = 111109
	tBossCopy_Pack[3305108][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305108][2][2] = {}
	tBossCopy_Pack[3305108][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305108][2][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305108][2][2]["RewardItem"] = {}
	tBossCopy_Pack[3305108][2][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305108][2][2]["RewardItem"][1]["Id"] = 160229
	tBossCopy_Pack[3305108][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 射手（40-45）
	tBossCopy_Pack[3305108][3] = {}
	tBossCopy_Pack[3305108][3]["LogId"] = 12000851
	tBossCopy_Pack[3305108][3]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305108][3][1] = {}
	tBossCopy_Pack[3305108][3][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305108][3][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305108][3][1]["RewardItem"] = {}
	tBossCopy_Pack[3305108][3][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305108][3][1]["RewardItem"][1]["Id"] = 113109
	tBossCopy_Pack[3305108][3][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305108][3][2] = {}
	tBossCopy_Pack[3305108][3][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305108][3][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305108][3][2]["RewardItem"] = {}
	tBossCopy_Pack[3305108][3][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305108][3][2]["RewardItem"][1]["Id"] = 160229
	tBossCopy_Pack[3305108][3][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 忍者（50-55）
	tBossCopy_Pack[3305108][4] = {}
	tBossCopy_Pack[3305108][4]["LogId"] = 12000851
	tBossCopy_Pack[3305108][4]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305108][4][1] = {}
	tBossCopy_Pack[3305108][4][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305108][4][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305108][4][1]["RewardItem"] = {}
	tBossCopy_Pack[3305108][4][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305108][4][1]["RewardItem"][1]["Id"] = 112109
	tBossCopy_Pack[3305108][4][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305108][4][2] = {}
	tBossCopy_Pack[3305108][4][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305108][4][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305108][4][2]["RewardItem"] = {}
	tBossCopy_Pack[3305108][4][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305108][4][2]["RewardItem"][1]["Id"] = 160229
	tBossCopy_Pack[3305108][4][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 武僧（60-65）
	tBossCopy_Pack[3305108][5] = {}
	tBossCopy_Pack[3305108][5]["LogId"] = 12000851
	tBossCopy_Pack[3305108][5]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305108][5][1] = {}
	tBossCopy_Pack[3305108][5][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305108][5][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305108][5][1]["RewardItem"] = {}
	tBossCopy_Pack[3305108][5][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305108][5][1]["RewardItem"][1]["Id"] = 143109
	tBossCopy_Pack[3305108][5][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305108][5][2] = {}
	tBossCopy_Pack[3305108][5][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305108][5][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305108][5][2]["RewardItem"] = {}
	tBossCopy_Pack[3305108][5][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305108][5][2]["RewardItem"][1]["Id"] = 160229
	tBossCopy_Pack[3305108][5][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 海盗（70-75）
	tBossCopy_Pack[3305108][6] = {}
	tBossCopy_Pack[3305108][6]["LogId"] = 12000851
	tBossCopy_Pack[3305108][6]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305108][6][1] = {}
	tBossCopy_Pack[3305108][6][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305108][6][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305108][6][1]["RewardItem"] = {}
	tBossCopy_Pack[3305108][6][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305108][6][1]["RewardItem"][1]["Id"] = 144109
	tBossCopy_Pack[3305108][6][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305108][6][2] = {}
	tBossCopy_Pack[3305108][6][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305108][6][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305108][6][2]["RewardItem"] = {}
	tBossCopy_Pack[3305108][6][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305108][6][2]["RewardItem"][1]["Id"] = 160229
	tBossCopy_Pack[3305108][6][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 拳师（80-85）
	tBossCopy_Pack[3305108][7] = {}
	tBossCopy_Pack[3305108][7]["LogId"] = 12000851
	tBossCopy_Pack[3305108][7]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305108][7][1] = {}
	tBossCopy_Pack[3305108][7][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305108][7][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305108][7][1]["RewardItem"] = {}
	tBossCopy_Pack[3305108][7][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305108][7][1]["RewardItem"][1]["Id"] = 148109
	tBossCopy_Pack[3305108][7][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305108][7][2] = {}
	tBossCopy_Pack[3305108][7][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305108][7][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305108][7][2]["RewardItem"] = {}
	tBossCopy_Pack[3305108][7][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305108][7][2]["RewardItem"][1]["Id"] = 160229
	tBossCopy_Pack[3305108][7][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 道士（100-145） -- 水道（132-135） -- 火道（142-145）
	tBossCopy_Pack[3305108][8] = {}
	tBossCopy_Pack[3305108][8]["LogId"] = 12000851
	tBossCopy_Pack[3305108][8]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305108][8][1] = {}
	tBossCopy_Pack[3305108][8][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305108][8][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305108][8][1]["RewardItem"] = {}
	tBossCopy_Pack[3305108][8][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305108][8][1]["RewardItem"][1]["Id"] = 114109
	tBossCopy_Pack[3305108][8][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305108][8][2] = {}
	tBossCopy_Pack[3305108][8][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305108][8][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305108][8][2]["RewardItem"] = {}
	tBossCopy_Pack[3305108][8][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305108][8][2]["RewardItem"][1]["Id"] = 160229
	tBossCopy_Pack[3305108][8][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 铁扇门
	tBossCopy_Pack[3305108][9] = {}
	tBossCopy_Pack[3305108][9]["LogId"] = 12000851
	tBossCopy_Pack[3305108][9]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305108][9][1] = {}
	tBossCopy_Pack[3305108][9][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305108][9][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305108][9][1]["RewardItem"] = {}
	tBossCopy_Pack[3305108][9][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305108][9][1]["RewardItem"][1]["Id"] = 170109
	tBossCopy_Pack[3305108][9][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305108][9][2] = {}
	tBossCopy_Pack[3305108][9][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305108][9][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305108][9][2]["RewardItem"] = {}
	tBossCopy_Pack[3305108][9][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305108][9][2]["RewardItem"][1]["Id"] = 160229
	tBossCopy_Pack[3305108][9][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
	-- 125级 精品装备
	tBossCopy_Pack[3305109] = {}
	-- 勇士（10-15）
	tBossCopy_Pack[3305109][1] = {}
	tBossCopy_Pack[3305109][1]["LogId"] = 12000851
	tBossCopy_Pack[3305109][1]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305109][1][1] = {}
	tBossCopy_Pack[3305109][1][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305109][1][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305109][1][1]["RewardItem"] = {}
	tBossCopy_Pack[3305109][1][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305109][1][1]["RewardItem"][1]["Id"] = 410288
	tBossCopy_Pack[3305109][1][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305109][1][2] = {}
	tBossCopy_Pack[3305109][1][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305109][1][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305109][1][2]["RewardItem"] = {}
	tBossCopy_Pack[3305109][1][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305109][1][2]["RewardItem"][1]["Id"] = 120238
	tBossCopy_Pack[3305109][1][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 战士（20-25）
	tBossCopy_Pack[3305109][2] = {}
	tBossCopy_Pack[3305109][2]["LogId"] = 12000851
	tBossCopy_Pack[3305109][2]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305109][2][1] = {}
	tBossCopy_Pack[3305109][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305109][2][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305109][2][1]["RewardItem"] = {}
	tBossCopy_Pack[3305109][2][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305109][2][1]["RewardItem"][1]["Id"] = 480288
	tBossCopy_Pack[3305109][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305109][2][2] = {}
	tBossCopy_Pack[3305109][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305109][2][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305109][2][2]["RewardItem"] = {}
	tBossCopy_Pack[3305109][2][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305109][2][2]["RewardItem"][1]["Id"] = 120238
	tBossCopy_Pack[3305109][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 射手（40-45）
	tBossCopy_Pack[3305109][3] = {}
	tBossCopy_Pack[3305109][3]["LogId"] = 12000851
	tBossCopy_Pack[3305109][3]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305109][3][1] = {}
	tBossCopy_Pack[3305109][3][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305109][3][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305109][3][1]["RewardItem"] = {}
	tBossCopy_Pack[3305109][3][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305109][3][1]["RewardItem"][1]["Id"] = 613278
	tBossCopy_Pack[3305109][3][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305109][3][2] = {}
	tBossCopy_Pack[3305109][3][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305109][3][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305109][3][2]["RewardItem"] = {}
	tBossCopy_Pack[3305109][3][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305109][3][2]["RewardItem"][1]["Id"] = 120238
	tBossCopy_Pack[3305109][3][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 忍者（50-55）
	tBossCopy_Pack[3305109][4] = {}
	tBossCopy_Pack[3305109][4]["LogId"] = 12000851
	tBossCopy_Pack[3305109][4]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305109][4][1] = {}
	tBossCopy_Pack[3305109][4][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305109][4][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305109][4][1]["RewardItem"] = {}
	tBossCopy_Pack[3305109][4][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305109][4][1]["RewardItem"][1]["Id"] = 601288
	tBossCopy_Pack[3305109][4][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305109][4][2] = {}
	tBossCopy_Pack[3305109][4][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305109][4][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305109][4][2]["RewardItem"] = {}
	tBossCopy_Pack[3305109][4][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305109][4][2]["RewardItem"][1]["Id"] = 120238
	tBossCopy_Pack[3305109][4][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 武僧（60-65）
	tBossCopy_Pack[3305109][5] = {}
	tBossCopy_Pack[3305109][5]["LogId"] = 12000851
	tBossCopy_Pack[3305109][5]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305109][5][1] = {}
	tBossCopy_Pack[3305109][5][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305109][5][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305109][5][1]["RewardItem"] = {}
	tBossCopy_Pack[3305109][5][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305109][5][1]["RewardItem"][1]["Id"] = 610288
	tBossCopy_Pack[3305109][5][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305109][5][2] = {}
	tBossCopy_Pack[3305109][5][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305109][5][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305109][5][2]["RewardItem"] = {}
	tBossCopy_Pack[3305109][5][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305109][5][2]["RewardItem"][1]["Id"] = 120238
	tBossCopy_Pack[3305109][5][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 海盗（70-75）
	tBossCopy_Pack[3305109][6] = {}
	tBossCopy_Pack[3305109][6]["LogId"] = 12000851
	tBossCopy_Pack[3305109][6]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305109][6][1] = {}
	tBossCopy_Pack[3305109][6][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305109][6][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305109][6][1]["RewardItem"] = {}
	tBossCopy_Pack[3305109][6][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305109][6][1]["RewardItem"][1]["Id"] = 611288
	tBossCopy_Pack[3305109][6][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305109][6][2] = {}
	tBossCopy_Pack[3305109][6][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305109][6][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305109][6][2]["RewardItem"] = {}
	tBossCopy_Pack[3305109][6][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305109][6][2]["RewardItem"][1]["Id"] = 120238
	tBossCopy_Pack[3305109][6][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 拳师（80-85）
	tBossCopy_Pack[3305109][7] = {}
	tBossCopy_Pack[3305109][7]["LogId"] = 12000851
	tBossCopy_Pack[3305109][7]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305109][7][1] = {}
	tBossCopy_Pack[3305109][7][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305109][7][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305109][7][1]["RewardItem"] = {}
	tBossCopy_Pack[3305109][7][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305109][7][1]["RewardItem"][1]["Id"] = 617288
	tBossCopy_Pack[3305109][7][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305109][7][2] = {}
	tBossCopy_Pack[3305109][7][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305109][7][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305109][7][2]["RewardItem"] = {}
	tBossCopy_Pack[3305109][7][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305109][7][2]["RewardItem"][1]["Id"] = 120238
	tBossCopy_Pack[3305109][7][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 道士（100-145） -- 水道（132-135） -- 火道（142-145）
	tBossCopy_Pack[3305109][8] = {}
	tBossCopy_Pack[3305109][8]["LogId"] = 12000851
	tBossCopy_Pack[3305109][8]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305109][8][1] = {}
	tBossCopy_Pack[3305109][8][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305109][8][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305109][8][1]["RewardItem"] = {}
	tBossCopy_Pack[3305109][8][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305109][8][1]["RewardItem"][1]["Id"] = 421288
	tBossCopy_Pack[3305109][8][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305109][8][2] = {}
	tBossCopy_Pack[3305109][8][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305109][8][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305109][8][2]["RewardItem"] = {}
	tBossCopy_Pack[3305109][8][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305109][8][2]["RewardItem"][1]["Id"] = 120238
	tBossCopy_Pack[3305109][8][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 铁扇门
	tBossCopy_Pack[3305109][9] = {}
	tBossCopy_Pack[3305109][9]["LogId"] = 12000851
	tBossCopy_Pack[3305109][9]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305109][9][1] = {}
	tBossCopy_Pack[3305109][9][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305109][9][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305109][9][1]["RewardItem"] = {}
	tBossCopy_Pack[3305109][9][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305109][9][1]["RewardItem"][1]["Id"] = 626288
	tBossCopy_Pack[3305109][9][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305109][9][2] = {}
	tBossCopy_Pack[3305109][9][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305109][9][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305109][9][2]["RewardItem"] = {}
	tBossCopy_Pack[3305109][9][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305109][9][2]["RewardItem"][1]["Id"] = 120238
	tBossCopy_Pack[3305109][9][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
	-- 125级 极品装备
	tBossCopy_Pack[3305110] = {}
	-- 勇士（10-15）
	tBossCopy_Pack[3305110][1] = {}
	tBossCopy_Pack[3305110][1]["LogId"] = 12000851
	tBossCopy_Pack[3305110][1]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305110][1][1] = {}
	tBossCopy_Pack[3305110][1][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305110][1][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305110][1][1]["RewardItem"] = {}
	tBossCopy_Pack[3305110][1][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305110][1][1]["RewardItem"][1]["Id"] = 410289
	tBossCopy_Pack[3305110][1][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305110][1][2] = {}
	tBossCopy_Pack[3305110][1][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305110][1][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305110][1][2]["RewardItem"] = {}
	tBossCopy_Pack[3305110][1][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305110][1][2]["RewardItem"][1]["Id"] = 120239
	tBossCopy_Pack[3305110][1][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 战士（20-25）
	tBossCopy_Pack[3305110][2] = {}
	tBossCopy_Pack[3305110][2]["LogId"] = 12000851
	tBossCopy_Pack[3305110][2]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305110][2][1] = {}
	tBossCopy_Pack[3305110][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305110][2][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305110][2][1]["RewardItem"] = {}
	tBossCopy_Pack[3305110][2][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305110][2][1]["RewardItem"][1]["Id"] = 480289
	tBossCopy_Pack[3305110][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305110][2][2] = {}
	tBossCopy_Pack[3305110][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305110][2][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305110][2][2]["RewardItem"] = {}
	tBossCopy_Pack[3305110][2][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305110][2][2]["RewardItem"][1]["Id"] = 120239
	tBossCopy_Pack[3305110][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 射手（40-45）
	tBossCopy_Pack[3305110][3] = {}
	tBossCopy_Pack[3305110][3]["LogId"] = 12000851
	tBossCopy_Pack[3305110][3]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305110][3][1] = {}
	tBossCopy_Pack[3305110][3][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305110][3][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305110][3][1]["RewardItem"] = {}
	tBossCopy_Pack[3305110][3][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305110][3][1]["RewardItem"][1]["Id"] = 613279
	tBossCopy_Pack[3305110][3][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305110][3][2] = {}
	tBossCopy_Pack[3305110][3][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305110][3][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305110][3][2]["RewardItem"] = {}
	tBossCopy_Pack[3305110][3][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305110][3][2]["RewardItem"][1]["Id"] = 120239
	tBossCopy_Pack[3305110][3][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 忍者（50-55）
	tBossCopy_Pack[3305110][4] = {}
	tBossCopy_Pack[3305110][4]["LogId"] = 12000851
	tBossCopy_Pack[3305110][4]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305110][4][1] = {}
	tBossCopy_Pack[3305110][4][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305110][4][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305110][4][1]["RewardItem"] = {}
	tBossCopy_Pack[3305110][4][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305110][4][1]["RewardItem"][1]["Id"] = 601289
	tBossCopy_Pack[3305110][4][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305110][4][2] = {}
	tBossCopy_Pack[3305110][4][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305110][4][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305110][4][2]["RewardItem"] = {}
	tBossCopy_Pack[3305110][4][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305110][4][2]["RewardItem"][1]["Id"] = 120239
	tBossCopy_Pack[3305110][4][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 武僧（60-65）
	tBossCopy_Pack[3305110][5] = {}
	tBossCopy_Pack[3305110][5]["LogId"] = 12000851
	tBossCopy_Pack[3305110][5]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305110][5][1] = {}
	tBossCopy_Pack[3305110][5][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305110][5][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305110][5][1]["RewardItem"] = {}
	tBossCopy_Pack[3305110][5][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305110][5][1]["RewardItem"][1]["Id"] = 610289
	tBossCopy_Pack[3305110][5][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305110][5][2] = {}
	tBossCopy_Pack[3305110][5][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305110][5][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305110][5][2]["RewardItem"] = {}
	tBossCopy_Pack[3305110][5][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305110][5][2]["RewardItem"][1]["Id"] = 120239
	tBossCopy_Pack[3305110][5][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 海盗（70-75）
	tBossCopy_Pack[3305110][6] = {}
	tBossCopy_Pack[3305110][6]["LogId"] = 12000851
	tBossCopy_Pack[3305110][6]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305110][6][1] = {}
	tBossCopy_Pack[3305110][6][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305110][6][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305110][6][1]["RewardItem"] = {}
	tBossCopy_Pack[3305110][6][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305110][6][1]["RewardItem"][1]["Id"] = 611289
	tBossCopy_Pack[3305110][6][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305110][6][2] = {}
	tBossCopy_Pack[3305110][6][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305110][6][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305110][6][2]["RewardItem"] = {}
	tBossCopy_Pack[3305110][6][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305110][6][2]["RewardItem"][1]["Id"] = 120239
	tBossCopy_Pack[3305110][6][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 拳师（80-85）
	tBossCopy_Pack[3305110][7] = {}
	tBossCopy_Pack[3305110][7]["LogId"] = 12000851
	tBossCopy_Pack[3305110][7]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305110][7][1] = {}
	tBossCopy_Pack[3305110][7][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305110][7][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305110][7][1]["RewardItem"] = {}
	tBossCopy_Pack[3305110][7][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305110][7][1]["RewardItem"][1]["Id"] = 617289
	tBossCopy_Pack[3305110][7][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305110][7][2] = {}
	tBossCopy_Pack[3305110][7][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305110][7][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305110][7][2]["RewardItem"] = {}
	tBossCopy_Pack[3305110][7][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305110][7][2]["RewardItem"][1]["Id"] = 120239
	tBossCopy_Pack[3305110][7][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 道士（100-145） -- 水道（132-135） -- 火道（142-145）
	tBossCopy_Pack[3305110][8] = {}
	tBossCopy_Pack[3305110][8]["LogId"] = 12000851
	tBossCopy_Pack[3305110][8]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305110][8][1] = {}
	tBossCopy_Pack[3305110][8][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305110][8][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305110][8][1]["RewardItem"] = {}
	tBossCopy_Pack[3305110][8][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305110][8][1]["RewardItem"][1]["Id"] = 421289
	tBossCopy_Pack[3305110][8][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305110][8][2] = {}
	tBossCopy_Pack[3305110][8][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305110][8][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305110][8][2]["RewardItem"] = {}
	tBossCopy_Pack[3305110][8][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305110][8][2]["RewardItem"][1]["Id"] = 120239
	tBossCopy_Pack[3305110][8][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 铁扇门
	tBossCopy_Pack[3305110][9] = {}
	tBossCopy_Pack[3305110][9]["LogId"] = 12000851
	tBossCopy_Pack[3305110][9]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305110][9][1] = {}
	tBossCopy_Pack[3305110][9][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305110][9][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305110][9][1]["RewardItem"] = {}
	tBossCopy_Pack[3305110][9][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305110][9][1]["RewardItem"][1]["Id"] = 626289
	tBossCopy_Pack[3305110][9][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305110][9][2] = {}
	tBossCopy_Pack[3305110][9][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305110][9][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305110][9][2]["RewardItem"] = {}
	tBossCopy_Pack[3305110][9][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305110][9][2]["RewardItem"][1]["Id"] = 120239
	tBossCopy_Pack[3305110][9][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
	-- 130级 精品装备
	tBossCopy_Pack[3305111] = {}
	-- 勇士（10-15）
	tBossCopy_Pack[3305111][1] = {}
	tBossCopy_Pack[3305111][1]["LogId"] = 12000851
	tBossCopy_Pack[3305111][1]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305111][1][1] = {}
	tBossCopy_Pack[3305111][1][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305111][1][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305111][1][1]["RewardItem"] = {}
	tBossCopy_Pack[3305111][1][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305111][1][1]["RewardItem"][1]["Id"] = 130188
	tBossCopy_Pack[3305111][1][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305111][1][2] = {}
	tBossCopy_Pack[3305111][1][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305111][1][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305111][1][2]["RewardItem"] = {}
	tBossCopy_Pack[3305111][1][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305111][1][2]["RewardItem"][1]["Id"] = 120248
	tBossCopy_Pack[3305111][1][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 战士（20-25）
	tBossCopy_Pack[3305111][2] = {}
	tBossCopy_Pack[3305111][2]["LogId"] = 12000851
	tBossCopy_Pack[3305111][2]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305111][2][1] = {}
	tBossCopy_Pack[3305111][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305111][2][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305111][2][1]["RewardItem"] = {}
	tBossCopy_Pack[3305111][2][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305111][2][1]["RewardItem"][1]["Id"] = 131188
	tBossCopy_Pack[3305111][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305111][2][2] = {}
	tBossCopy_Pack[3305111][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305111][2][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305111][2][2]["RewardItem"] = {}
	tBossCopy_Pack[3305111][2][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305111][2][2]["RewardItem"][1]["Id"] = 120248
	tBossCopy_Pack[3305111][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 射手（40-45）
	tBossCopy_Pack[3305111][3] = {}
	tBossCopy_Pack[3305111][3]["LogId"] = 12000851
	tBossCopy_Pack[3305111][3]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305111][3][1] = {}
	tBossCopy_Pack[3305111][3][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305111][3][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305111][3][1]["RewardItem"] = {}
	tBossCopy_Pack[3305111][3][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305111][3][1]["RewardItem"][1]["Id"] = 133208
	tBossCopy_Pack[3305111][3][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305111][3][2] = {}
	tBossCopy_Pack[3305111][3][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305111][3][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305111][3][2]["RewardItem"] = {}
	tBossCopy_Pack[3305111][3][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305111][3][2]["RewardItem"][1]["Id"] = 120248
	tBossCopy_Pack[3305111][3][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 忍者（50-55）
	tBossCopy_Pack[3305111][4] = {}
	tBossCopy_Pack[3305111][4]["LogId"] = 12000851
	tBossCopy_Pack[3305111][4]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305111][4][1] = {}
	tBossCopy_Pack[3305111][4][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305111][4][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305111][4][1]["RewardItem"] = {}
	tBossCopy_Pack[3305111][4][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305111][4][1]["RewardItem"][1]["Id"] = 135208
	tBossCopy_Pack[3305111][4][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305111][4][2] = {}
	tBossCopy_Pack[3305111][4][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305111][4][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305111][4][2]["RewardItem"] = {}
	tBossCopy_Pack[3305111][4][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305111][4][2]["RewardItem"][1]["Id"] = 120248
	tBossCopy_Pack[3305111][4][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 武僧（60-65）
	tBossCopy_Pack[3305111][5] = {}
	tBossCopy_Pack[3305111][5]["LogId"] = 12000851
	tBossCopy_Pack[3305111][5]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305111][5][1] = {}
	tBossCopy_Pack[3305111][5][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305111][5][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305111][5][1]["RewardItem"] = {}
	tBossCopy_Pack[3305111][5][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305111][5][1]["RewardItem"][1]["Id"] = 136208
	tBossCopy_Pack[3305111][5][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305111][5][2] = {}
	tBossCopy_Pack[3305111][5][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305111][5][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305111][5][2]["RewardItem"] = {}
	tBossCopy_Pack[3305111][5][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305111][5][2]["RewardItem"][1]["Id"] = 120248
	tBossCopy_Pack[3305111][5][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 海盗（70-75）
	tBossCopy_Pack[3305111][6] = {}
	tBossCopy_Pack[3305111][6]["LogId"] = 12000851
	tBossCopy_Pack[3305111][6]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305111][6][1] = {}
	tBossCopy_Pack[3305111][6][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305111][6][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305111][6][1]["RewardItem"] = {}
	tBossCopy_Pack[3305111][6][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305111][6][1]["RewardItem"][1]["Id"] = 139208
	tBossCopy_Pack[3305111][6][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305111][6][2] = {}
	tBossCopy_Pack[3305111][6][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305111][6][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305111][6][2]["RewardItem"] = {}
	tBossCopy_Pack[3305111][6][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305111][6][2]["RewardItem"][1]["Id"] = 120248
	tBossCopy_Pack[3305111][6][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 拳师（80-85）
	tBossCopy_Pack[3305111][7] = {}
	tBossCopy_Pack[3305111][7]["LogId"] = 12000851
	tBossCopy_Pack[3305111][7]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305111][7][1] = {}
	tBossCopy_Pack[3305111][7][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305111][7][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305111][7][1]["RewardItem"] = {}
	tBossCopy_Pack[3305111][7][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305111][7][1]["RewardItem"][1]["Id"] = 138208
	tBossCopy_Pack[3305111][7][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305111][7][2] = {}
	tBossCopy_Pack[3305111][7][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305111][7][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305111][7][2]["RewardItem"] = {}
	tBossCopy_Pack[3305111][7][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305111][7][2]["RewardItem"][1]["Id"] = 120248
	tBossCopy_Pack[3305111][7][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 道士（100-145） -- 水道（132-135） -- 火道（142-145）
	tBossCopy_Pack[3305111][8] = {}
	tBossCopy_Pack[3305111][8]["LogId"] = 12000851
	tBossCopy_Pack[3305111][8]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305111][8][1] = {}
	tBossCopy_Pack[3305111][8][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305111][8][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305111][8][1]["RewardItem"] = {}
	tBossCopy_Pack[3305111][8][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305111][8][1]["RewardItem"][1]["Id"] = 134208
	tBossCopy_Pack[3305111][8][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305111][8][2] = {}
	tBossCopy_Pack[3305111][8][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305111][8][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305111][8][2]["RewardItem"] = {}
	tBossCopy_Pack[3305111][8][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305111][8][2]["RewardItem"][1]["Id"] = 120248
	tBossCopy_Pack[3305111][8][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 铁扇门
	tBossCopy_Pack[3305111][9] = {}
	tBossCopy_Pack[3305111][9]["LogId"] = 12000851
	tBossCopy_Pack[3305111][9]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305111][9][1] = {}
	tBossCopy_Pack[3305111][9][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305111][9][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305111][9][1]["RewardItem"] = {}
	tBossCopy_Pack[3305111][9][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305111][9][1]["RewardItem"][1]["Id"] = 101208
	tBossCopy_Pack[3305111][9][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305111][9][2] = {}
	tBossCopy_Pack[3305111][9][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305111][9][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305111][9][2]["RewardItem"] = {}
	tBossCopy_Pack[3305111][9][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305111][9][2]["RewardItem"][1]["Id"] = 120248
	tBossCopy_Pack[3305111][9][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
	-- 130级 极品装备
	tBossCopy_Pack[3305112] = {}
	-- 勇士（10-15）
	tBossCopy_Pack[3305112][1] = {}
	tBossCopy_Pack[3305112][1]["LogId"] = 12000851
	tBossCopy_Pack[3305112][1]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305112][1][1] = {}
	tBossCopy_Pack[3305112][1][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305112][1][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305112][1][1]["RewardItem"] = {}
	tBossCopy_Pack[3305112][1][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305112][1][1]["RewardItem"][1]["Id"] = 130189
	tBossCopy_Pack[3305112][1][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305112][1][2] = {}
	tBossCopy_Pack[3305112][1][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305112][1][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305112][1][2]["RewardItem"] = {}
	tBossCopy_Pack[3305112][1][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305112][1][2]["RewardItem"][1]["Id"] = 120249
	tBossCopy_Pack[3305112][1][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 战士（20-25）
	tBossCopy_Pack[3305112][2] = {}
	tBossCopy_Pack[3305112][2]["LogId"] = 12000851
	tBossCopy_Pack[3305112][2]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305112][2][1] = {}
	tBossCopy_Pack[3305112][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305112][2][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305112][2][1]["RewardItem"] = {}
	tBossCopy_Pack[3305112][2][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305112][2][1]["RewardItem"][1]["Id"] = 131189
	tBossCopy_Pack[3305112][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305112][2][2] = {}
	tBossCopy_Pack[3305112][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305112][2][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305112][2][2]["RewardItem"] = {}
	tBossCopy_Pack[3305112][2][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305112][2][2]["RewardItem"][1]["Id"] = 120249
	tBossCopy_Pack[3305112][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 射手（40-45）
	tBossCopy_Pack[3305112][3] = {}
	tBossCopy_Pack[3305112][3]["LogId"] = 12000851
	tBossCopy_Pack[3305112][3]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305112][3][1] = {}
	tBossCopy_Pack[3305112][3][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305112][3][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305112][3][1]["RewardItem"] = {}
	tBossCopy_Pack[3305112][3][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305112][3][1]["RewardItem"][1]["Id"] = 133209
	tBossCopy_Pack[3305112][3][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305112][3][2] = {}
	tBossCopy_Pack[3305112][3][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305112][3][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305112][3][2]["RewardItem"] = {}
	tBossCopy_Pack[3305112][3][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305112][3][2]["RewardItem"][1]["Id"] = 120249
	tBossCopy_Pack[3305112][3][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 忍者（50-55）
	tBossCopy_Pack[3305112][4] = {}
	tBossCopy_Pack[3305112][4]["LogId"] = 12000851
	tBossCopy_Pack[3305112][4]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305112][4][1] = {}
	tBossCopy_Pack[3305112][4][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305112][4][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305112][4][1]["RewardItem"] = {}
	tBossCopy_Pack[3305112][4][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305112][4][1]["RewardItem"][1]["Id"] = 135209
	tBossCopy_Pack[3305112][4][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305112][4][2] = {}
	tBossCopy_Pack[3305112][4][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305112][4][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305112][4][2]["RewardItem"] = {}
	tBossCopy_Pack[3305112][4][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305112][4][2]["RewardItem"][1]["Id"] = 120249
	tBossCopy_Pack[3305112][4][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 武僧（60-65）
	tBossCopy_Pack[3305112][5] = {}
	tBossCopy_Pack[3305112][5]["LogId"] = 12000851
	tBossCopy_Pack[3305112][5]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305112][5][1] = {}
	tBossCopy_Pack[3305112][5][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305112][5][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305112][5][1]["RewardItem"] = {}
	tBossCopy_Pack[3305112][5][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305112][5][1]["RewardItem"][1]["Id"] = 136209
	tBossCopy_Pack[3305112][5][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305112][5][2] = {}
	tBossCopy_Pack[3305112][5][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305112][5][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305112][5][2]["RewardItem"] = {}
	tBossCopy_Pack[3305112][5][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305112][5][2]["RewardItem"][1]["Id"] = 120249
	tBossCopy_Pack[3305112][5][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 海盗（70-75）
	tBossCopy_Pack[3305112][6] = {}
	tBossCopy_Pack[3305112][6]["LogId"] = 12000851
	tBossCopy_Pack[3305112][6]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305112][6][1] = {}
	tBossCopy_Pack[3305112][6][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305112][6][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305112][6][1]["RewardItem"] = {}
	tBossCopy_Pack[3305112][6][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305112][6][1]["RewardItem"][1]["Id"] = 139209
	tBossCopy_Pack[3305112][6][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305112][6][2] = {}
	tBossCopy_Pack[3305112][6][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305112][6][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305112][6][2]["RewardItem"] = {}
	tBossCopy_Pack[3305112][6][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305112][6][2]["RewardItem"][1]["Id"] = 120249
	tBossCopy_Pack[3305112][6][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 拳师（80-85）
	tBossCopy_Pack[3305112][7] = {}
	tBossCopy_Pack[3305112][7]["LogId"] = 12000851
	tBossCopy_Pack[3305112][7]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305112][7][1] = {}
	tBossCopy_Pack[3305112][7][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305112][7][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305112][7][1]["RewardItem"] = {}
	tBossCopy_Pack[3305112][7][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305112][7][1]["RewardItem"][1]["Id"] = 138209
	tBossCopy_Pack[3305112][7][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305112][7][2] = {}
	tBossCopy_Pack[3305112][7][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305112][7][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305112][7][2]["RewardItem"] = {}
	tBossCopy_Pack[3305112][7][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305112][7][2]["RewardItem"][1]["Id"] = 120249
	tBossCopy_Pack[3305112][7][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 道士（100-145） -- 水道（132-135） -- 火道（142-145）
	tBossCopy_Pack[3305112][8] = {}
	tBossCopy_Pack[3305112][8]["LogId"] = 12000851
	tBossCopy_Pack[3305112][8]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305112][8][1] = {}
	tBossCopy_Pack[3305112][8][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305112][8][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305112][8][1]["RewardItem"] = {}
	tBossCopy_Pack[3305112][8][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305112][8][1]["RewardItem"][1]["Id"] = 134209
	tBossCopy_Pack[3305112][8][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305112][8][2] = {}
	tBossCopy_Pack[3305112][8][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305112][8][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305112][8][2]["RewardItem"] = {}
	tBossCopy_Pack[3305112][8][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305112][8][2]["RewardItem"][1]["Id"] = 120249
	tBossCopy_Pack[3305112][8][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 铁扇门
	tBossCopy_Pack[3305112][9] = {}
	tBossCopy_Pack[3305112][9]["LogId"] = 12000851
	tBossCopy_Pack[3305112][9]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305112][9][1] = {}
	tBossCopy_Pack[3305112][9][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305112][9][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305112][9][1]["RewardItem"] = {}
	tBossCopy_Pack[3305112][9][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305112][9][1]["RewardItem"][1]["Id"] = 101209
	tBossCopy_Pack[3305112][9][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305112][9][2] = {}
	tBossCopy_Pack[3305112][9][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305112][9][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305112][9][2]["RewardItem"] = {}
	tBossCopy_Pack[3305112][9][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305112][9][2]["RewardItem"][1]["Id"] = 120249
	tBossCopy_Pack[3305112][9][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
	-- 135级 精品装备
	tBossCopy_Pack[3305113] = {}
	-- 勇士（10-15）
	tBossCopy_Pack[3305113][1] = {}
	tBossCopy_Pack[3305113][1]["LogId"] = 12000851
	tBossCopy_Pack[3305113][1]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305113][1][1] = {}
	tBossCopy_Pack[3305113][1][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305113][1][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305113][1][1]["RewardItem"] = {}
	tBossCopy_Pack[3305113][1][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305113][1][1]["RewardItem"][1]["Id"] = 118258
	tBossCopy_Pack[3305113][1][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305113][1][2] = {}
	tBossCopy_Pack[3305113][1][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305113][1][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305113][1][2]["RewardItem"] = {}
	tBossCopy_Pack[3305113][1][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305113][1][2]["RewardItem"][1]["Id"] = 160248
	tBossCopy_Pack[3305113][1][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 战士（20-25）
	tBossCopy_Pack[3305113][2] = {}
	tBossCopy_Pack[3305113][2]["LogId"] = 12000851
	tBossCopy_Pack[3305113][2]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305113][2][1] = {}
	tBossCopy_Pack[3305113][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305113][2][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305113][2][1]["RewardItem"] = {}
	tBossCopy_Pack[3305113][2][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305113][2][1]["RewardItem"][1]["Id"] = 111258
	tBossCopy_Pack[3305113][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305113][2][2] = {}
	tBossCopy_Pack[3305113][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305113][2][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305113][2][2]["RewardItem"] = {}
	tBossCopy_Pack[3305113][2][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305113][2][2]["RewardItem"][1]["Id"] = 160248
	tBossCopy_Pack[3305113][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 射手（40-45）
	tBossCopy_Pack[3305113][3] = {}
	tBossCopy_Pack[3305113][3]["LogId"] = 12000851
	tBossCopy_Pack[3305113][3]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305113][3][1] = {}
	tBossCopy_Pack[3305113][3][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305113][3][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305113][3][1]["RewardItem"] = {}
	tBossCopy_Pack[3305113][3][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305113][3][1]["RewardItem"][1]["Id"] = 113258
	tBossCopy_Pack[3305113][3][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305113][3][2] = {}
	tBossCopy_Pack[3305113][3][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305113][3][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305113][3][2]["RewardItem"] = {}
	tBossCopy_Pack[3305113][3][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305113][3][2]["RewardItem"][1]["Id"] = 160248
	tBossCopy_Pack[3305113][3][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 忍者（50-55）
	tBossCopy_Pack[3305113][4] = {}
	tBossCopy_Pack[3305113][4]["LogId"] = 12000851
	tBossCopy_Pack[3305113][4]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305113][4][1] = {}
	tBossCopy_Pack[3305113][4][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305113][4][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305113][4][1]["RewardItem"] = {}
	tBossCopy_Pack[3305113][4][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305113][4][1]["RewardItem"][1]["Id"] = 112258
	tBossCopy_Pack[3305113][4][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305113][4][2] = {}
	tBossCopy_Pack[3305113][4][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305113][4][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305113][4][2]["RewardItem"] = {}
	tBossCopy_Pack[3305113][4][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305113][4][2]["RewardItem"][1]["Id"] = 160248
	tBossCopy_Pack[3305113][4][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 武僧（60-65）
	tBossCopy_Pack[3305113][5] = {}
	tBossCopy_Pack[3305113][5]["LogId"] = 12000851
	tBossCopy_Pack[3305113][5]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305113][5][1] = {}
	tBossCopy_Pack[3305113][5][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305113][5][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305113][5][1]["RewardItem"] = {}
	tBossCopy_Pack[3305113][5][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305113][5][1]["RewardItem"][1]["Id"] = 143258
	tBossCopy_Pack[3305113][5][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305113][5][2] = {}
	tBossCopy_Pack[3305113][5][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305113][5][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305113][5][2]["RewardItem"] = {}
	tBossCopy_Pack[3305113][5][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305113][5][2]["RewardItem"][1]["Id"] = 160248
	tBossCopy_Pack[3305113][5][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 海盗（70-75）
	tBossCopy_Pack[3305113][6] = {}
	tBossCopy_Pack[3305113][6]["LogId"] = 12000851
	tBossCopy_Pack[3305113][6]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305113][6][1] = {}
	tBossCopy_Pack[3305113][6][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305113][6][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305113][6][1]["RewardItem"] = {}
	tBossCopy_Pack[3305113][6][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305113][6][1]["RewardItem"][1]["Id"] = 144258
	tBossCopy_Pack[3305113][6][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305113][6][2] = {}
	tBossCopy_Pack[3305113][6][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305113][6][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305113][6][2]["RewardItem"] = {}
	tBossCopy_Pack[3305113][6][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305113][6][2]["RewardItem"][1]["Id"] = 160248
	tBossCopy_Pack[3305113][6][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 拳师（80-85）
	tBossCopy_Pack[3305113][7] = {}
	tBossCopy_Pack[3305113][7]["LogId"] = 12000851
	tBossCopy_Pack[3305113][7]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305113][7][1] = {}
	tBossCopy_Pack[3305113][7][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305113][7][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305113][7][1]["RewardItem"] = {}
	tBossCopy_Pack[3305113][7][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305113][7][1]["RewardItem"][1]["Id"] = 148258
	tBossCopy_Pack[3305113][7][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305113][7][2] = {}
	tBossCopy_Pack[3305113][7][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305113][7][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305113][7][2]["RewardItem"] = {}
	tBossCopy_Pack[3305113][7][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305113][7][2]["RewardItem"][1]["Id"] = 160248
	tBossCopy_Pack[3305113][7][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 道士（100-145） -- 水道（132-135） -- 火道（142-145）
	tBossCopy_Pack[3305113][8] = {}
	tBossCopy_Pack[3305113][8]["LogId"] = 12000851
	tBossCopy_Pack[3305113][8]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305113][8][1] = {}
	tBossCopy_Pack[3305113][8][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305113][8][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305113][8][1]["RewardItem"] = {}
	tBossCopy_Pack[3305113][8][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305113][8][1]["RewardItem"][1]["Id"] = 114258
	tBossCopy_Pack[3305113][8][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305113][8][2] = {}
	tBossCopy_Pack[3305113][8][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305113][8][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305113][8][2]["RewardItem"] = {}
	tBossCopy_Pack[3305113][8][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305113][8][2]["RewardItem"][1]["Id"] = 160248
	tBossCopy_Pack[3305113][8][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 铁扇门
	tBossCopy_Pack[3305113][9] = {}
	tBossCopy_Pack[3305113][9]["LogId"] = 12000851
	tBossCopy_Pack[3305113][9]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305113][9][1] = {}
	tBossCopy_Pack[3305113][9][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305113][9][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305113][9][1]["RewardItem"] = {}
	tBossCopy_Pack[3305113][9][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305113][9][1]["RewardItem"][1]["Id"] = 170258
	tBossCopy_Pack[3305113][9][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305113][9][2] = {}
	tBossCopy_Pack[3305113][9][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305113][9][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305113][9][2]["RewardItem"] = {}
	tBossCopy_Pack[3305113][9][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305113][9][2]["RewardItem"][1]["Id"] = 160248
	tBossCopy_Pack[3305113][9][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
	-- 135级 极品装备
	tBossCopy_Pack[3305114] = {}
	-- 勇士（10-15）
	tBossCopy_Pack[3305114][1] = {}
	tBossCopy_Pack[3305114][1]["LogId"] = 12000851
	tBossCopy_Pack[3305114][1]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305114][1][1] = {}
	tBossCopy_Pack[3305114][1][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305114][1][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305114][1][1]["RewardItem"] = {}
	tBossCopy_Pack[3305114][1][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305114][1][1]["RewardItem"][1]["Id"] = 118259
	tBossCopy_Pack[3305114][1][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305114][1][2] = {}
	tBossCopy_Pack[3305114][1][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305114][1][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305114][1][2]["RewardItem"] = {}
	tBossCopy_Pack[3305114][1][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305114][1][2]["RewardItem"][1]["Id"] = 160249
	tBossCopy_Pack[3305114][1][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 战士（20-25）
	tBossCopy_Pack[3305114][2] = {}
	tBossCopy_Pack[3305114][2]["LogId"] = 12000851
	tBossCopy_Pack[3305114][2]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305114][2][1] = {}
	tBossCopy_Pack[3305114][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305114][2][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305114][2][1]["RewardItem"] = {}
	tBossCopy_Pack[3305114][2][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305114][2][1]["RewardItem"][1]["Id"] = 111259
	tBossCopy_Pack[3305114][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305114][2][2] = {}
	tBossCopy_Pack[3305114][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305114][2][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305114][2][2]["RewardItem"] = {}
	tBossCopy_Pack[3305114][2][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305114][2][2]["RewardItem"][1]["Id"] = 160249
	tBossCopy_Pack[3305114][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 射手（40-45）
	tBossCopy_Pack[3305114][3] = {}
	tBossCopy_Pack[3305114][3]["LogId"] = 12000851
	tBossCopy_Pack[3305114][3]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305114][3][1] = {}
	tBossCopy_Pack[3305114][3][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305114][3][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305114][3][1]["RewardItem"] = {}
	tBossCopy_Pack[3305114][3][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305114][3][1]["RewardItem"][1]["Id"] = 113259
	tBossCopy_Pack[3305114][3][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305114][3][2] = {}
	tBossCopy_Pack[3305114][3][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305114][3][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305114][3][2]["RewardItem"] = {}
	tBossCopy_Pack[3305114][3][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305114][3][2]["RewardItem"][1]["Id"] = 160249
	tBossCopy_Pack[3305114][3][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 忍者（50-55）
	tBossCopy_Pack[3305114][4] = {}
	tBossCopy_Pack[3305114][4]["LogId"] = 12000851
	tBossCopy_Pack[3305114][4]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305114][4][1] = {}
	tBossCopy_Pack[3305114][4][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305114][4][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305114][4][1]["RewardItem"] = {}
	tBossCopy_Pack[3305114][4][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305114][4][1]["RewardItem"][1]["Id"] = 112259
	tBossCopy_Pack[3305114][4][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305114][4][2] = {}
	tBossCopy_Pack[3305114][4][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305114][4][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305114][4][2]["RewardItem"] = {}
	tBossCopy_Pack[3305114][4][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305114][4][2]["RewardItem"][1]["Id"] = 160249
	tBossCopy_Pack[3305114][4][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 武僧（60-65）
	tBossCopy_Pack[3305114][5] = {}
	tBossCopy_Pack[3305114][5]["LogId"] = 12000851
	tBossCopy_Pack[3305114][5]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305114][5][1] = {}
	tBossCopy_Pack[3305114][5][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305114][5][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305114][5][1]["RewardItem"] = {}
	tBossCopy_Pack[3305114][5][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305114][5][1]["RewardItem"][1]["Id"] = 143259
	tBossCopy_Pack[3305114][5][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305114][5][2] = {}
	tBossCopy_Pack[3305114][5][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305114][5][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305114][5][2]["RewardItem"] = {}
	tBossCopy_Pack[3305114][5][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305114][5][2]["RewardItem"][1]["Id"] = 160249
	tBossCopy_Pack[3305114][5][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 海盗（70-75）
	tBossCopy_Pack[3305114][6] = {}
	tBossCopy_Pack[3305114][6]["LogId"] = 12000851
	tBossCopy_Pack[3305114][6]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305114][6][1] = {}
	tBossCopy_Pack[3305114][6][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305114][6][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305114][6][1]["RewardItem"] = {}
	tBossCopy_Pack[3305114][6][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305114][6][1]["RewardItem"][1]["Id"] = 144259
	tBossCopy_Pack[3305114][6][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305114][6][2] = {}
	tBossCopy_Pack[3305114][6][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305114][6][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305114][6][2]["RewardItem"] = {}
	tBossCopy_Pack[3305114][6][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305114][6][2]["RewardItem"][1]["Id"] = 160249
	tBossCopy_Pack[3305114][6][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 拳师（80-85）
	tBossCopy_Pack[3305114][7] = {}
	tBossCopy_Pack[3305114][7]["LogId"] = 12000851
	tBossCopy_Pack[3305114][7]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305114][7][1] = {}
	tBossCopy_Pack[3305114][7][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305114][7][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305114][7][1]["RewardItem"] = {}
	tBossCopy_Pack[3305114][7][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305114][7][1]["RewardItem"][1]["Id"] = 148259
	tBossCopy_Pack[3305114][7][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305114][7][2] = {}
	tBossCopy_Pack[3305114][7][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305114][7][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305114][7][2]["RewardItem"] = {}
	tBossCopy_Pack[3305114][7][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305114][7][2]["RewardItem"][1]["Id"] = 160249
	tBossCopy_Pack[3305114][7][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 道士（100-145） -- 水道（132-135） -- 火道（142-145）
	tBossCopy_Pack[3305114][8] = {}
	tBossCopy_Pack[3305114][8]["LogId"] = 12000851
	tBossCopy_Pack[3305114][8]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305114][8][1] = {}
	tBossCopy_Pack[3305114][8][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305114][8][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305114][8][1]["RewardItem"] = {}
	tBossCopy_Pack[3305114][8][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305114][8][1]["RewardItem"][1]["Id"] = 114259
	tBossCopy_Pack[3305114][8][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305114][8][2] = {}
	tBossCopy_Pack[3305114][8][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305114][8][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305114][8][2]["RewardItem"] = {}
	tBossCopy_Pack[3305114][8][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305114][8][2]["RewardItem"][1]["Id"] = 160249
	tBossCopy_Pack[3305114][8][2]["RewardItem"][1]["Attr"] = "0 1 3"
	-- 铁扇门
	tBossCopy_Pack[3305114][9] = {}
	tBossCopy_Pack[3305114][9]["LogId"] = 12000851
	tBossCopy_Pack[3305114][9]["ItemChanceSum"] = 10000
	tBossCopy_Pack[3305114][9][1] = {}
	tBossCopy_Pack[3305114][9][1]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305114][9][1]["ItemChance"] = 5000
	tBossCopy_Pack[3305114][9][1]["RewardItem"] = {}
	tBossCopy_Pack[3305114][9][1]["RewardItem"][1] = {}
	tBossCopy_Pack[3305114][9][1]["RewardItem"][1]["Id"] = 170259
	tBossCopy_Pack[3305114][9][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Pack[3305114][9][2] = {}
	tBossCopy_Pack[3305114][9][2]["RandomItemChanceType"] = 2
	tBossCopy_Pack[3305114][9][2]["ItemChance"] = 5000
	tBossCopy_Pack[3305114][9][2]["RewardItem"] = {}
	tBossCopy_Pack[3305114][9][2]["RewardItem"][1] = {}
	tBossCopy_Pack[3305114][9][2]["RewardItem"][1]["Id"] = 160249
	tBossCopy_Pack[3305114][9][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
-- 怪物掉落
local tBossCopy_MonsterDrop = {}
	-- 50级
	tBossCopy_MonsterDrop[1] = {}
	tBossCopy_MonsterDrop[1]["ItemChanceSum"] = 10000
	-- 流星卷碎片（10合1）	25.00%	3305073
	tBossCopy_MonsterDrop[1][1] = {}
	tBossCopy_MonsterDrop[1][1]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[1][1]["ItemChance"] = 2500
	tBossCopy_MonsterDrop[1][1]["Item_1"] = 3305073
	-- 龙珠碎片（20合1）	10.00%	3305071
	tBossCopy_MonsterDrop[1][2] = {}
	tBossCopy_MonsterDrop[1][2]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[1][2]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[1][2]["Item_1"] = 3305071
	-- 极品宝石碎片（15合1，不能合成玄元）	10.00%	新制作
	tBossCopy_MonsterDrop[1][3] = {}
	tBossCopy_MonsterDrop[1][3]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[1][3]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[1][3]["Item_1"] = 3305072
	-- 50点修行书	5.00%	3006536
	tBossCopy_MonsterDrop[1][4] = {}
	tBossCopy_MonsterDrop[1][4]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[1][4]["ItemChance"] = 500
	tBossCopy_MonsterDrop[1][4]["Item_1"] = 3006536
	-- 强效护心丹	10.00%	3002030
	tBossCopy_MonsterDrop[1][5] = {}
	tBossCopy_MonsterDrop[1][5]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[1][5]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[1][5]["Item_1"] = 3002030
	-- 强炼丹	30.00%	3305115
	tBossCopy_MonsterDrop[1][6] = {}
	tBossCopy_MonsterDrop[1][6]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[1][6]["ItemChance"] = 3000
	tBossCopy_MonsterDrop[1][6]["Item_1"] = 3305115
	-- 秘制免费修炼丹	0.00%	3002926
	tBossCopy_MonsterDrop[1][7] = {}
	tBossCopy_MonsterDrop[1][7]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[1][7]["ItemChance"] = 0
	tBossCopy_MonsterDrop[1][7]["Item_1"] = 3002926
	-- 通神丹	0.00%	3305116
	tBossCopy_MonsterDrop[1][8] = {}
	tBossCopy_MonsterDrop[1][8]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[1][8]["ItemChance"] = 0
	tBossCopy_MonsterDrop[1][8]["Item_1"] = 3305116
	-- 究极通神丹	0.00%	3305117
	tBossCopy_MonsterDrop[1][9] = {}
	tBossCopy_MonsterDrop[1][9]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[1][9]["ItemChance"] = 0
	tBossCopy_MonsterDrop[1][9]["Item_1"] = 3305117
	-- 随机本职业精品装备	3.00%
	tBossCopy_MonsterDrop[1][10] = {}
	tBossCopy_MonsterDrop[1][10]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[1][10]["ItemChance"] = 300
	tBossCopy_MonsterDrop[1][10]["Item_1"] = 3305091
	-- 随机本职业极品装备	2.00%
	tBossCopy_MonsterDrop[1][11] = {}
	tBossCopy_MonsterDrop[1][11]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[1][11]["ItemChance"] = 200
	tBossCopy_MonsterDrop[1][11]["Item_1"] = 3305092
	-- 聚神丹（赠）	5.00%	3306659
	tBossCopy_MonsterDrop[1][12] = {}
	tBossCopy_MonsterDrop[1][12]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[1][12]["ItemChance"] = 500
	tBossCopy_MonsterDrop[1][12]["Item_1"] = 3306659
	-- 气力值	0.00%	729478
	tBossCopy_MonsterDrop[1][13] = {}
	tBossCopy_MonsterDrop[1][13]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[1][13]["ItemChance"] = 0
	tBossCopy_MonsterDrop[1][13]["Item_1"] = 729478
	-- 百炼天机果
	tBossCopy_MonsterDrop[1][14] = {}
	tBossCopy_MonsterDrop[1][14]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[1][14]["ItemChance"] = 0
	tBossCopy_MonsterDrop[1][14]["Item_1"] = 3001044
	
	-- 60级
	tBossCopy_MonsterDrop[2] = {}
	tBossCopy_MonsterDrop[2]["ItemChanceSum"] = 10000
	-- 流星卷碎片（10合1）	15.00%	3305073
	tBossCopy_MonsterDrop[2][1] = {}
	tBossCopy_MonsterDrop[2][1]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[2][1]["ItemChance"] = 1500
	tBossCopy_MonsterDrop[2][1]["Item_1"] = 3305073
	-- 龙珠碎片（20合1）	10.00%	3305071
	tBossCopy_MonsterDrop[2][2] = {}
	tBossCopy_MonsterDrop[2][2]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[2][2]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[2][2]["Item_1"] = 3305071
	-- 极品宝石碎片（15合1，不能合成玄元）	10.00%	新制作
	tBossCopy_MonsterDrop[2][3] = {}
	tBossCopy_MonsterDrop[2][3]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[2][3]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[2][3]["Item_1"] = 3305072
	-- 50点修行书	5.00%	3006536
	tBossCopy_MonsterDrop[2][4] = {}
	tBossCopy_MonsterDrop[2][4]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[2][4]["ItemChance"] = 500
	tBossCopy_MonsterDrop[2][4]["Item_1"] = 3006536
	-- 强效护心丹	15.00%	3002030
	tBossCopy_MonsterDrop[2][5] = {}
	tBossCopy_MonsterDrop[2][5]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[2][5]["ItemChance"] = 1500
	tBossCopy_MonsterDrop[2][5]["Item_1"] = 3002030
	-- 强炼丹	35.00%	3305115
	tBossCopy_MonsterDrop[2][6] = {}
	tBossCopy_MonsterDrop[2][6]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[2][6]["ItemChance"] = 3500
	tBossCopy_MonsterDrop[2][6]["Item_1"] = 3305115
	-- 秘制免费修炼丹	0.00%	3002926
	tBossCopy_MonsterDrop[2][7] = {}
	tBossCopy_MonsterDrop[2][7]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[2][7]["ItemChance"] = 0
	tBossCopy_MonsterDrop[2][7]["Item_1"] = 3002926
	-- 通神丹	0.00%	3305116
	tBossCopy_MonsterDrop[2][8] = {}
	tBossCopy_MonsterDrop[2][8]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[2][8]["ItemChance"] = 0
	tBossCopy_MonsterDrop[2][8]["Item_1"] = 3305116
	-- 究极通神丹	0.00%	3305117
	tBossCopy_MonsterDrop[2][9] = {}
	tBossCopy_MonsterDrop[2][9]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[2][9]["ItemChance"] = 0
	tBossCopy_MonsterDrop[2][9]["Item_1"] = 3305117
	-- 随机本职业精品装备	3.00%
	tBossCopy_MonsterDrop[2][10] = {}
	tBossCopy_MonsterDrop[2][10]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[2][10]["ItemChance"] = 300
	tBossCopy_MonsterDrop[2][10]["Item_1"] = 3305093
	-- 随机本职业极品装备	2.00%
	tBossCopy_MonsterDrop[2][11] = {}
	tBossCopy_MonsterDrop[2][11]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[2][11]["ItemChance"] = 200
	tBossCopy_MonsterDrop[2][11]["Item_1"] = 3305094
	-- 聚神丹（赠）	5.00%	3306659
	tBossCopy_MonsterDrop[2][12] = {}
	tBossCopy_MonsterDrop[2][12]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[2][12]["ItemChance"] = 500
	tBossCopy_MonsterDrop[2][12]["Item_1"] = 3306659
	-- 气力值	0.00%	729478
	tBossCopy_MonsterDrop[2][13] = {}
	tBossCopy_MonsterDrop[2][13]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[2][13]["ItemChance"] = 0
	tBossCopy_MonsterDrop[2][13]["Item_1"] = 729478
	-- 百炼天机果
	tBossCopy_MonsterDrop[2][14] = {}
	tBossCopy_MonsterDrop[2][14]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[2][14]["ItemChance"] = 0
	tBossCopy_MonsterDrop[2][14]["Item_1"] = 3001044
	
	-- 70级
	tBossCopy_MonsterDrop[3] = {}
	tBossCopy_MonsterDrop[3]["ItemChanceSum"] = 10000
	-- 流星卷碎片（10合1）	10.00%	3305073
	tBossCopy_MonsterDrop[3][1] = {}
	tBossCopy_MonsterDrop[3][1]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[3][1]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[3][1]["Item_1"] = 3305073
	-- 龙珠碎片（20合1）	5.00%	3305071
	tBossCopy_MonsterDrop[3][2] = {}
	tBossCopy_MonsterDrop[3][2]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[3][2]["ItemChance"] = 500
	tBossCopy_MonsterDrop[3][2]["Item_1"] = 3305071
	-- 极品宝石碎片（15合1，不能合成玄元）	10.00%	新制作
	tBossCopy_MonsterDrop[3][3] = {}
	tBossCopy_MonsterDrop[3][3]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[3][3]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[3][3]["Item_1"] = 3305072
	-- 50点修行书	15.00%	3006536
	tBossCopy_MonsterDrop[3][4] = {}
	tBossCopy_MonsterDrop[3][4]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[3][4]["ItemChance"] = 1500
	tBossCopy_MonsterDrop[3][4]["Item_1"] = 3006536
	-- 强效护心丹	15.00%	3002030
	tBossCopy_MonsterDrop[3][5] = {}
	tBossCopy_MonsterDrop[3][5]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[3][5]["ItemChance"] = 1500
	tBossCopy_MonsterDrop[3][5]["Item_1"] = 3002030
	-- 强炼丹	35.00%	3305115
	tBossCopy_MonsterDrop[3][6] = {}
	tBossCopy_MonsterDrop[3][6]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[3][6]["ItemChance"] = 3500
	tBossCopy_MonsterDrop[3][6]["Item_1"] = 3305115
	-- 秘制免费修炼丹	0.00%	3002926
	tBossCopy_MonsterDrop[3][7] = {}
	tBossCopy_MonsterDrop[3][7]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[3][7]["ItemChance"] = 0
	tBossCopy_MonsterDrop[3][7]["Item_1"] = 3002926
	-- 通神丹	0.00%	3305116
	tBossCopy_MonsterDrop[3][8] = {}
	tBossCopy_MonsterDrop[3][8]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[3][8]["ItemChance"] = 0
	tBossCopy_MonsterDrop[3][8]["Item_1"] = 3305116
	-- 究极通神丹	0.00%	3305117
	tBossCopy_MonsterDrop[3][9] = {}
	tBossCopy_MonsterDrop[3][9]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[3][9]["ItemChance"] = 0
	tBossCopy_MonsterDrop[3][9]["Item_1"] = 3305117
	-- 随机本职业精品装备	3.00%
	tBossCopy_MonsterDrop[3][10] = {}
	tBossCopy_MonsterDrop[3][10]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[3][10]["ItemChance"] = 300
	tBossCopy_MonsterDrop[3][10]["Item_1"] = 3305095
	-- 随机本职业极品装备	2.00%
	tBossCopy_MonsterDrop[3][11] = {}
	tBossCopy_MonsterDrop[3][11]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[3][11]["ItemChance"] = 200
	tBossCopy_MonsterDrop[3][11]["Item_1"] = 3305096
	-- 聚神丹（赠）	5.00%	3306659
	tBossCopy_MonsterDrop[3][12] = {}
	tBossCopy_MonsterDrop[3][12]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[3][12]["ItemChance"] = 500
	tBossCopy_MonsterDrop[3][12]["Item_1"] = 3306659
	-- 气力值	0.00%	729478
	tBossCopy_MonsterDrop[3][13] = {}
	tBossCopy_MonsterDrop[3][13]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[3][13]["ItemChance"] = 0
	tBossCopy_MonsterDrop[3][13]["Item_1"] = 729478
	-- 百炼天机果
	tBossCopy_MonsterDrop[3][14] = {}
	tBossCopy_MonsterDrop[3][14]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[3][14]["ItemChance"] = 0
	tBossCopy_MonsterDrop[3][14]["Item_1"] = 3001044
	
	-- 80级
	tBossCopy_MonsterDrop[4] = {}
	tBossCopy_MonsterDrop[4]["ItemChanceSum"] = 10000
	-- 流星卷碎片（10合1）	8.00%	3305073
	tBossCopy_MonsterDrop[4][1] = {}
	tBossCopy_MonsterDrop[4][1]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[4][1]["ItemChance"] = 800
	tBossCopy_MonsterDrop[4][1]["Item_1"] = 3305073
	-- 龙珠碎片（20合1）	7.00%	3305071
	tBossCopy_MonsterDrop[4][2] = {}
	tBossCopy_MonsterDrop[4][2]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[4][2]["ItemChance"] = 700
	tBossCopy_MonsterDrop[4][2]["Item_1"] = 3305071
	-- 极品宝石碎片（15合1，不能合成玄元）	10.00%	新制作
	tBossCopy_MonsterDrop[4][3] = {}
	tBossCopy_MonsterDrop[4][3]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[4][3]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[4][3]["Item_1"] = 3305072
	-- 50点修行书	10.00%	3006536
	tBossCopy_MonsterDrop[4][4] = {}
	tBossCopy_MonsterDrop[4][4]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[4][4]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[4][4]["Item_1"] = 3006536
	-- 强效护心丹	20.00%	3002030
	tBossCopy_MonsterDrop[4][5] = {}
	tBossCopy_MonsterDrop[4][5]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[4][5]["ItemChance"] = 2000
	tBossCopy_MonsterDrop[4][5]["Item_1"] = 3002030
	-- 强炼丹	35.00%	3305115
	tBossCopy_MonsterDrop[4][6] = {}
	tBossCopy_MonsterDrop[4][6]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[4][6]["ItemChance"] = 3500
	tBossCopy_MonsterDrop[4][6]["Item_1"] = 3305115
	-- 秘制免费修炼丹	0.00%	3002926
	tBossCopy_MonsterDrop[4][7] = {}
	tBossCopy_MonsterDrop[4][7]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[4][7]["ItemChance"] = 0
	tBossCopy_MonsterDrop[4][7]["Item_1"] = 3002926
	-- 通神丹	0.00%	3305116
	tBossCopy_MonsterDrop[4][8] = {}
	tBossCopy_MonsterDrop[4][8]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[4][8]["ItemChance"] = 0
	tBossCopy_MonsterDrop[4][8]["Item_1"] = 3305116
	-- 究极通神丹	0.00%	3305117
	tBossCopy_MonsterDrop[4][9] = {}
	tBossCopy_MonsterDrop[4][9]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[4][9]["ItemChance"] = 0
	tBossCopy_MonsterDrop[4][9]["Item_1"] = 3305117
	-- 随机本职业精品装备	3.00%
	tBossCopy_MonsterDrop[4][10] = {}
	tBossCopy_MonsterDrop[4][10]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[4][10]["ItemChance"] = 300
	tBossCopy_MonsterDrop[4][10]["Item_1"] = 3305097
	-- 随机本职业极品装备	2.00%
	tBossCopy_MonsterDrop[4][11] = {}
	tBossCopy_MonsterDrop[4][11]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[4][11]["ItemChance"] = 200
	tBossCopy_MonsterDrop[4][11]["Item_1"] = 3305098
	-- 聚神丹（赠）	5.00%	3306659
	tBossCopy_MonsterDrop[4][12] = {}
	tBossCopy_MonsterDrop[4][12]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[4][12]["ItemChance"] = 500
	tBossCopy_MonsterDrop[4][12]["Item_1"] = 3306659
	-- 气力值	0.00%	729478
	tBossCopy_MonsterDrop[4][13] = {}
	tBossCopy_MonsterDrop[4][13]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[4][13]["ItemChance"] = 0
	tBossCopy_MonsterDrop[4][13]["Item_1"] = 729478
	-- 百炼天机果
	tBossCopy_MonsterDrop[4][14] = {}
	tBossCopy_MonsterDrop[4][14]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[4][14]["ItemChance"] = 0
	tBossCopy_MonsterDrop[4][14]["Item_1"] = 3001044
	
	-- 90级
	tBossCopy_MonsterDrop[5] = {}
	tBossCopy_MonsterDrop[5]["ItemChanceSum"] = 10000
	-- 流星卷碎片（10合1）	10.00%	3305073
	tBossCopy_MonsterDrop[5][1] = {}
	tBossCopy_MonsterDrop[5][1]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[5][1]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[5][1]["Item_1"] = 3305073
	-- 龙珠碎片（20合1）	5.00%	3305071
	tBossCopy_MonsterDrop[5][2] = {}
	tBossCopy_MonsterDrop[5][2]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[5][2]["ItemChance"] = 500
	tBossCopy_MonsterDrop[5][2]["Item_1"] = 3305071
	-- 极品宝石碎片（15合1，不能合成玄元）	10.00%	新制作
	tBossCopy_MonsterDrop[5][3] = {}
	tBossCopy_MonsterDrop[5][3]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[5][3]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[5][3]["Item_1"] = 3305072
	-- 50点修行书	10.00%	3006536
	tBossCopy_MonsterDrop[5][4] = {}
	tBossCopy_MonsterDrop[5][4]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[5][4]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[5][4]["Item_1"] = 3006536
	-- 强效护心丹	20.00%	3002030
	tBossCopy_MonsterDrop[5][5] = {}
	tBossCopy_MonsterDrop[5][5]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[5][5]["ItemChance"] = 2000
	tBossCopy_MonsterDrop[5][5]["Item_1"] = 3002030
	-- 强炼丹	35.00%	3305115
	tBossCopy_MonsterDrop[5][6] = {}
	tBossCopy_MonsterDrop[5][6]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[5][6]["ItemChance"] = 3500
	tBossCopy_MonsterDrop[5][6]["Item_1"] = 3305115
	-- 秘制免费修炼丹	0.00%	3002926
	tBossCopy_MonsterDrop[5][7] = {}
	tBossCopy_MonsterDrop[5][7]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[5][7]["ItemChance"] = 0
	tBossCopy_MonsterDrop[5][7]["Item_1"] = 3002926
	-- 通神丹	0.00%	3305116
	tBossCopy_MonsterDrop[5][8] = {}
	tBossCopy_MonsterDrop[5][8]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[5][8]["ItemChance"] = 0
	tBossCopy_MonsterDrop[5][8]["Item_1"] = 3305116
	-- 究极通神丹	0.00%	3305117
	tBossCopy_MonsterDrop[5][9] = {}
	tBossCopy_MonsterDrop[5][9]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[5][9]["ItemChance"] = 0
	tBossCopy_MonsterDrop[5][9]["Item_1"] = 3305117
	-- 随机本职业精品装备	4.00%
	tBossCopy_MonsterDrop[5][10] = {}
	tBossCopy_MonsterDrop[5][10]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[5][10]["ItemChance"] = 400
	tBossCopy_MonsterDrop[5][10]["Item_1"] = 3305099
	-- 随机本职业极品装备	1.00%
	tBossCopy_MonsterDrop[5][11] = {}
	tBossCopy_MonsterDrop[5][11]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[5][11]["ItemChance"] = 100
	tBossCopy_MonsterDrop[5][11]["Item_1"] = 3305100
	-- 聚神丹（赠）	5.00%	3306659
	tBossCopy_MonsterDrop[5][12] = {}
	tBossCopy_MonsterDrop[5][12]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[5][12]["ItemChance"] = 500
	tBossCopy_MonsterDrop[5][12]["Item_1"] = 3306659
	-- 气力值	0.00%	729478
	tBossCopy_MonsterDrop[5][13] = {}
	tBossCopy_MonsterDrop[5][13]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[5][13]["ItemChance"] = 0
	tBossCopy_MonsterDrop[5][13]["Item_1"] = 729478
	-- 百炼天机果
	tBossCopy_MonsterDrop[5][14] = {}
	tBossCopy_MonsterDrop[5][14]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[5][14]["ItemChance"] = 0
	tBossCopy_MonsterDrop[5][14]["Item_1"] = 3001044
	
	-- 100级
	tBossCopy_MonsterDrop[6] = {}
	tBossCopy_MonsterDrop[6]["ItemChanceSum"] = 10000
	-- 流星卷碎片（10合1）	8.00%	3305073
	tBossCopy_MonsterDrop[6][1] = {}
	tBossCopy_MonsterDrop[6][1]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[6][1]["ItemChance"] = 800
	tBossCopy_MonsterDrop[6][1]["Item_1"] = 3305073
	-- 龙珠碎片（20合1）	7.00%	3305071
	tBossCopy_MonsterDrop[6][2] = {}
	tBossCopy_MonsterDrop[6][2]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[6][2]["ItemChance"] = 700
	tBossCopy_MonsterDrop[6][2]["Item_1"] = 3305071
	-- 极品宝石碎片（15合1，不能合成玄元）	10.00%	新制作
	tBossCopy_MonsterDrop[6][3] = {}
	tBossCopy_MonsterDrop[6][3]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[6][3]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[6][3]["Item_1"] = 3305072
	-- 50点修行书	10.00%	3006536
	tBossCopy_MonsterDrop[6][4] = {}
	tBossCopy_MonsterDrop[6][4]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[6][4]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[6][4]["Item_1"] = 3006536
	-- 强效护心丹	20.00%	3002030
	tBossCopy_MonsterDrop[6][5] = {}
	tBossCopy_MonsterDrop[6][5]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[6][5]["ItemChance"] = 2000
	tBossCopy_MonsterDrop[6][5]["Item_1"] = 3002030
	-- 强炼丹	35.00%	3305115
	tBossCopy_MonsterDrop[6][6] = {}
	tBossCopy_MonsterDrop[6][6]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[6][6]["ItemChance"] = 3500
	tBossCopy_MonsterDrop[6][6]["Item_1"] = 3305115
	-- 秘制免费修炼丹	0.00%	3002926
	tBossCopy_MonsterDrop[6][7] = {}
	tBossCopy_MonsterDrop[6][7]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[6][7]["ItemChance"] = 0
	tBossCopy_MonsterDrop[6][7]["Item_1"] = 3002926
	-- 通神丹	0.00%	3305116
	tBossCopy_MonsterDrop[6][8] = {}
	tBossCopy_MonsterDrop[6][8]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[6][8]["ItemChance"] = 0
	tBossCopy_MonsterDrop[6][8]["Item_1"] = 3305116
	-- 究极通神丹	0.00%	3305117
	tBossCopy_MonsterDrop[6][9] = {}
	tBossCopy_MonsterDrop[6][9]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[6][9]["ItemChance"] = 0
	tBossCopy_MonsterDrop[6][9]["Item_1"] = 3305117
	-- 随机本职业精品装备	4.50%
	tBossCopy_MonsterDrop[6][10] = {}
	tBossCopy_MonsterDrop[6][10]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[6][10]["ItemChance"] = 450
	tBossCopy_MonsterDrop[6][10]["Item_1"] = 3305101
	-- 随机本职业极品装备	0.50%
	tBossCopy_MonsterDrop[6][11] = {}
	tBossCopy_MonsterDrop[6][11]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[6][11]["ItemChance"] = 50
	tBossCopy_MonsterDrop[6][11]["Item_1"] = 3305102
	-- 聚神丹（赠）	5.00%	3306659
	tBossCopy_MonsterDrop[6][12] = {}
	tBossCopy_MonsterDrop[6][12]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[6][12]["ItemChance"] = 500
	tBossCopy_MonsterDrop[6][12]["Item_1"] = 3306659
	-- 气力值	0.00%	729478
	tBossCopy_MonsterDrop[6][13] = {}
	tBossCopy_MonsterDrop[6][13]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[6][13]["ItemChance"] = 0
	tBossCopy_MonsterDrop[6][13]["Item_1"] = 729478
	-- 百炼天机果
	tBossCopy_MonsterDrop[6][14] = {}
	tBossCopy_MonsterDrop[6][14]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[6][14]["ItemChance"] = 0
	tBossCopy_MonsterDrop[6][14]["Item_1"] = 3001044
	
	-- 110级
	tBossCopy_MonsterDrop[7] = {}
	tBossCopy_MonsterDrop[7]["ItemChanceSum"] = 10000
	-- 流星卷碎片（10合1）	8.00%	3305073
	tBossCopy_MonsterDrop[7][1] = {}
	tBossCopy_MonsterDrop[7][1]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[7][1]["ItemChance"] = 800
	tBossCopy_MonsterDrop[7][1]["Item_1"] = 3305073
	-- 龙珠碎片（20合1）	10.00%	3305071
	tBossCopy_MonsterDrop[7][2] = {}
	tBossCopy_MonsterDrop[7][2]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[7][2]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[7][2]["Item_1"] = 3305071
	-- 极品宝石碎片（15合1，不能合成玄元）	7.00%	新制作
	tBossCopy_MonsterDrop[7][3] = {}
	tBossCopy_MonsterDrop[7][3]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[7][3]["ItemChance"] = 700
	tBossCopy_MonsterDrop[7][3]["Item_1"] = 3305072
	-- 50点修行书	10.00%	3006536
	tBossCopy_MonsterDrop[7][4] = {}
	tBossCopy_MonsterDrop[7][4]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[7][4]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[7][4]["Item_1"] = 3006536
	-- 强效护心丹	20.00%	3002030
	tBossCopy_MonsterDrop[7][5] = {}
	tBossCopy_MonsterDrop[7][5]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[7][5]["ItemChance"] = 2000
	tBossCopy_MonsterDrop[7][5]["Item_1"] = 3002030
	-- 强炼丹	22.00%	3305115
	tBossCopy_MonsterDrop[7][6] = {}
	tBossCopy_MonsterDrop[7][6]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[7][6]["ItemChance"] = 2200
	tBossCopy_MonsterDrop[7][6]["Item_1"] = 3305115
	-- 秘制免费修炼丹	10.00%	3002926
	tBossCopy_MonsterDrop[7][7] = {}
	tBossCopy_MonsterDrop[7][7]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[7][7]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[7][7]["Item_1"] = 3002926
	-- 通神丹	5.00%	3305116
	tBossCopy_MonsterDrop[7][8] = {}
	tBossCopy_MonsterDrop[7][8]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[7][8]["ItemChance"] = 500
	tBossCopy_MonsterDrop[7][8]["Item_1"] = 3305116
	-- 究极通神丹	2.00%	3305117
	tBossCopy_MonsterDrop[7][9] = {}
	tBossCopy_MonsterDrop[7][9]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[7][9]["ItemChance"] = 200
	tBossCopy_MonsterDrop[7][9]["Item_1"] = 3305117
	-- 随机本职业精品装备	2.50%
	tBossCopy_MonsterDrop[7][10] = {}
	tBossCopy_MonsterDrop[7][10]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[7][10]["ItemChance"] = 250
	tBossCopy_MonsterDrop[7][10]["Item_1"] = 3305103
	-- 随机本职业极品装备	0.50%
	tBossCopy_MonsterDrop[7][11] = {}
	tBossCopy_MonsterDrop[7][11]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[7][11]["ItemChance"] = 50
	tBossCopy_MonsterDrop[7][11]["Item_1"] = 3305104
	-- 聚神丹（赠）	3.00%	3306659
	tBossCopy_MonsterDrop[7][12] = {}
	tBossCopy_MonsterDrop[7][12]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[7][12]["ItemChance"] = 300
	tBossCopy_MonsterDrop[7][12]["Item_1"] = 3306659
	-- 气力值	0.00%	729478
	tBossCopy_MonsterDrop[7][13] = {}
	tBossCopy_MonsterDrop[7][13]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[7][13]["ItemChance"] = 0
	tBossCopy_MonsterDrop[7][13]["Item_1"] = 729478
	-- 百炼天机果
	tBossCopy_MonsterDrop[7][14] = {}
	tBossCopy_MonsterDrop[7][14]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[7][14]["ItemChance"] = 0
	tBossCopy_MonsterDrop[7][14]["Item_1"] = 3001044
	
	-- 115级
	tBossCopy_MonsterDrop[8] = {}
	tBossCopy_MonsterDrop[8]["ItemChanceSum"] = 10000
	-- 流星卷碎片（10合1）	8.00%	3305073
	tBossCopy_MonsterDrop[8][1] = {}
	tBossCopy_MonsterDrop[8][1]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[8][1]["ItemChance"] = 800
	tBossCopy_MonsterDrop[8][1]["Item_1"] = 3305073
	-- 龙珠碎片（20合1）	7.00%	3305071
	tBossCopy_MonsterDrop[8][2] = {}
	tBossCopy_MonsterDrop[8][2]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[8][2]["ItemChance"] = 700
	tBossCopy_MonsterDrop[8][2]["Item_1"] = 3305071
	-- 极品宝石碎片（15合1，不能合成玄元）	10.00%	新制作
	tBossCopy_MonsterDrop[8][3] = {}
	tBossCopy_MonsterDrop[8][3]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[8][3]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[8][3]["Item_1"] = 3305072
	-- 50点修行书	10.00%	3006536
	tBossCopy_MonsterDrop[8][4] = {}
	tBossCopy_MonsterDrop[8][4]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[8][4]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[8][4]["Item_1"] = 3006536
	-- 强效护心丹	12.00%	3002030
	tBossCopy_MonsterDrop[8][5] = {}
	tBossCopy_MonsterDrop[8][5]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[8][5]["ItemChance"] = 1200
	tBossCopy_MonsterDrop[8][5]["Item_1"] = 3002030
	-- 强炼丹	20.00%	3305115
	tBossCopy_MonsterDrop[8][6] = {}
	tBossCopy_MonsterDrop[8][6]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[8][6]["ItemChance"] = 2000
	tBossCopy_MonsterDrop[8][6]["Item_1"] = 3305115
	-- 秘制免费修炼丹	12.00%	3002926
	tBossCopy_MonsterDrop[8][7] = {}
	tBossCopy_MonsterDrop[8][7]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[8][7]["ItemChance"] = 1200
	tBossCopy_MonsterDrop[8][7]["Item_1"] = 3002926
	-- 通神丹	10.00%	3305116
	tBossCopy_MonsterDrop[8][8] = {}
	tBossCopy_MonsterDrop[8][8]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[8][8]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[8][8]["Item_1"] = 3305116
	-- 究极通神丹	5.00%	3305117
	tBossCopy_MonsterDrop[8][9] = {}
	tBossCopy_MonsterDrop[8][9]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[8][9]["ItemChance"] = 500
	tBossCopy_MonsterDrop[8][9]["Item_1"] = 3305117
	-- 随机本职业精品装备	2.50%
	tBossCopy_MonsterDrop[8][10] = {}
	tBossCopy_MonsterDrop[8][10]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[8][10]["ItemChance"] = 250
	tBossCopy_MonsterDrop[8][10]["Item_1"] = 3305105
	-- 随机本职业极品装备	0.50%
	tBossCopy_MonsterDrop[8][11] = {}
	tBossCopy_MonsterDrop[8][11]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[8][11]["ItemChance"] = 50
	tBossCopy_MonsterDrop[8][11]["Item_1"] = 3305106
	-- 聚神丹（赠）	3.00%	3306659
	tBossCopy_MonsterDrop[8][12] = {}
	tBossCopy_MonsterDrop[8][12]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[8][12]["ItemChance"] = 300
	tBossCopy_MonsterDrop[8][12]["Item_1"] = 3306659
	-- 气力值	0.00%	729478
	tBossCopy_MonsterDrop[8][13] = {}
	tBossCopy_MonsterDrop[8][13]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[8][13]["ItemChance"] = 0
	tBossCopy_MonsterDrop[8][13]["Item_1"] = 729478
	-- 百炼天机果
	tBossCopy_MonsterDrop[8][14] = {}
	tBossCopy_MonsterDrop[8][14]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[8][14]["ItemChance"] = 0
	tBossCopy_MonsterDrop[8][14]["Item_1"] = 3001044
	
	-- 120级
	tBossCopy_MonsterDrop[9] = {}
	tBossCopy_MonsterDrop[9]["ItemChanceSum"] = 10000
	-- 流星卷碎片（10合1）	8.00%	3305073
	tBossCopy_MonsterDrop[9][1] = {}
	tBossCopy_MonsterDrop[9][1]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[9][1]["ItemChance"] = 800
	tBossCopy_MonsterDrop[9][1]["Item_1"] = 3305073
	-- 龙珠碎片（20合1）	7.00%	3305071
	tBossCopy_MonsterDrop[9][2] = {}
	tBossCopy_MonsterDrop[9][2]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[9][2]["ItemChance"] = 700
	tBossCopy_MonsterDrop[9][2]["Item_1"] = 3305071
	-- 极品宝石碎片（15合1，不能合成玄元）	10%	新制作
	tBossCopy_MonsterDrop[9][3] = {}
	tBossCopy_MonsterDrop[9][3]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[9][3]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[9][3]["Item_1"] = 3305072
	-- 50点修行书	5.00%	3006536
	tBossCopy_MonsterDrop[9][4] = {}
	tBossCopy_MonsterDrop[9][4]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[9][4]["ItemChance"] = 500
	tBossCopy_MonsterDrop[9][4]["Item_1"] = 3006536
	-- 强效护心丹	20.00%	3002030
	tBossCopy_MonsterDrop[9][5] = {}
	tBossCopy_MonsterDrop[9][5]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[9][5]["ItemChance"] = 2000
	tBossCopy_MonsterDrop[9][5]["Item_1"] = 3002030
	-- 强炼丹	7.40%	3305115
	tBossCopy_MonsterDrop[9][6] = {}
	tBossCopy_MonsterDrop[9][6]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[9][6]["ItemChance"] = 740
	tBossCopy_MonsterDrop[9][6]["Item_1"] = 3305115
	-- 秘制免费修炼丹	10.00%	3002926
	tBossCopy_MonsterDrop[9][7] = {}
	tBossCopy_MonsterDrop[9][7]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[9][7]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[9][7]["Item_1"] = 3002926
	-- 通神丹	10.00%	3305116
	tBossCopy_MonsterDrop[9][8] = {}
	tBossCopy_MonsterDrop[9][8]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[9][8]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[9][8]["Item_1"] = 3305116
	-- 究极通神丹	5.00%	3305117
	tBossCopy_MonsterDrop[9][9] = {}
	tBossCopy_MonsterDrop[9][9]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[9][9]["ItemChance"] = 500
	tBossCopy_MonsterDrop[9][9]["Item_1"] = 3305117
	-- 随机本职业精品装备	2.50%
	tBossCopy_MonsterDrop[9][10] = {}
	tBossCopy_MonsterDrop[9][10]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[9][10]["ItemChance"] = 250
	tBossCopy_MonsterDrop[9][10]["Item_1"] = 3305107
	-- 随机本职业极品装备	0.10%
	tBossCopy_MonsterDrop[9][11] = {}
	tBossCopy_MonsterDrop[9][11]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[9][11]["ItemChance"] = 10
	tBossCopy_MonsterDrop[9][11]["Item_1"] = 3305108
	-- 聚神丹（赠）	5.00%	3306659
	tBossCopy_MonsterDrop[9][12] = {}
	tBossCopy_MonsterDrop[9][12]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[9][12]["ItemChance"] = 500
	tBossCopy_MonsterDrop[9][12]["Item_1"] = 3306659
	-- 气力值	10.00%	729478
	tBossCopy_MonsterDrop[9][13] = {}
	tBossCopy_MonsterDrop[9][13]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[9][13]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[9][13]["Item_1"] = 729478
	-- 百炼天机果
	tBossCopy_MonsterDrop[9][14] = {}
	tBossCopy_MonsterDrop[9][14]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[9][14]["ItemChance"] = 0
	tBossCopy_MonsterDrop[9][14]["Item_1"] = 3001044
	
	-- 125级
	tBossCopy_MonsterDrop[10] = {}
	tBossCopy_MonsterDrop[10]["ItemChanceSum"] = 10000
	-- 流星卷碎片（10合1）	8.00%	3305073
	tBossCopy_MonsterDrop[10][1] = {}
	tBossCopy_MonsterDrop[10][1]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[10][1]["ItemChance"] = 800
	tBossCopy_MonsterDrop[10][1]["Item_1"] = 3305073
	-- 龙珠碎片（20合1）	7.00%	3305071
	tBossCopy_MonsterDrop[10][2] = {}
	tBossCopy_MonsterDrop[10][2]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[10][2]["ItemChance"] = 700
	tBossCopy_MonsterDrop[10][2]["Item_1"] = 3305071
	-- 极品宝石碎片（15合1，不能合成玄元）	10%	新制作
	tBossCopy_MonsterDrop[10][3] = {}
	tBossCopy_MonsterDrop[10][3]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[10][3]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[10][3]["Item_1"] = 3305072
	-- 50点修行书	5.00%	3006536
	tBossCopy_MonsterDrop[10][4] = {}
	tBossCopy_MonsterDrop[10][4]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[10][4]["ItemChance"] = 500
	tBossCopy_MonsterDrop[10][4]["Item_1"] = 3006536
	-- 强效护心丹	20.00%	3002030
	tBossCopy_MonsterDrop[10][5] = {}
	tBossCopy_MonsterDrop[10][5]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[10][5]["ItemChance"] = 2000
	tBossCopy_MonsterDrop[10][5]["Item_1"] = 3002030
	-- 强炼丹	7.40%	3305115
	tBossCopy_MonsterDrop[10][6] = {}
	tBossCopy_MonsterDrop[10][6]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[10][6]["ItemChance"] = 740
	tBossCopy_MonsterDrop[10][6]["Item_1"] = 3305115
	-- 秘制免费修炼丹	10.00%	3002926
	tBossCopy_MonsterDrop[10][7] = {}
	tBossCopy_MonsterDrop[10][7]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[10][7]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[10][7]["Item_1"] = 3002926
	-- 通神丹	10.00%	3305116
	tBossCopy_MonsterDrop[10][8] = {}
	tBossCopy_MonsterDrop[10][8]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[10][8]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[10][8]["Item_1"] = 3305116
	-- 究极通神丹	5.00%	3305117
	tBossCopy_MonsterDrop[10][9] = {}
	tBossCopy_MonsterDrop[10][9]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[10][9]["ItemChance"] = 500
	tBossCopy_MonsterDrop[10][9]["Item_1"] = 3305117
	-- 随机本职业精品装备	2.50%
	tBossCopy_MonsterDrop[10][10] = {}
	tBossCopy_MonsterDrop[10][10]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[10][10]["ItemChance"] = 250
	tBossCopy_MonsterDrop[10][10]["Item_1"] = 3305109
	-- 随机本职业极品装备	0.10%
	tBossCopy_MonsterDrop[10][11] = {}
	tBossCopy_MonsterDrop[10][11]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[10][11]["ItemChance"] = 10
	tBossCopy_MonsterDrop[10][11]["Item_1"] = 3305110
	-- 聚神丹（赠）	5.00%	3306659
	tBossCopy_MonsterDrop[10][12] = {}
	tBossCopy_MonsterDrop[10][12]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[10][12]["ItemChance"] = 500
	tBossCopy_MonsterDrop[10][12]["Item_1"] = 3306659
	-- 气力值	10.00%	729478
	tBossCopy_MonsterDrop[10][13] = {}
	tBossCopy_MonsterDrop[10][13]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[10][13]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[10][13]["Item_1"] = 729478
	-- 百炼天机果
	tBossCopy_MonsterDrop[10][14] = {}
	tBossCopy_MonsterDrop[10][14]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[10][14]["ItemChance"] = 0
	tBossCopy_MonsterDrop[10][14]["Item_1"] = 3001044
	
	-- 130级
	tBossCopy_MonsterDrop[11] = {}
	tBossCopy_MonsterDrop[11]["ItemChanceSum"] = 10000
	-- 流星卷碎片（10合1）	8.00%	3305073
	tBossCopy_MonsterDrop[11][1] = {}
	tBossCopy_MonsterDrop[11][1]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[11][1]["ItemChance"] = 800
	tBossCopy_MonsterDrop[11][1]["Item_1"] = 3305073
	-- 龙珠碎片（20合1）	7.00%	3305071
	tBossCopy_MonsterDrop[11][2] = {}
	tBossCopy_MonsterDrop[11][2]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[11][2]["ItemChance"] = 700
	tBossCopy_MonsterDrop[11][2]["Item_1"] = 3305071
	-- 极品宝石碎片（15合1，不能合成玄元）	10%	新制作
	tBossCopy_MonsterDrop[11][3] = {}
	tBossCopy_MonsterDrop[11][3]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[11][3]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[11][3]["Item_1"] = 3305072
	-- 50点修行书	5.00%	3006536
	tBossCopy_MonsterDrop[11][4] = {}
	tBossCopy_MonsterDrop[11][4]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[11][4]["ItemChance"] = 500
	tBossCopy_MonsterDrop[11][4]["Item_1"] = 3006536
	-- 强效护心丹	20.00%	3002030
	tBossCopy_MonsterDrop[11][5] = {}
	tBossCopy_MonsterDrop[11][5]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[11][5]["ItemChance"] = 2000
	tBossCopy_MonsterDrop[11][5]["Item_1"] = 3002030
	-- 强炼丹	7.40%	3305115
	tBossCopy_MonsterDrop[11][6] = {}
	tBossCopy_MonsterDrop[11][6]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[11][6]["ItemChance"] = 740
	tBossCopy_MonsterDrop[11][6]["Item_1"] = 3305115
	-- 秘制免费修炼丹	10.00%	3002926
	tBossCopy_MonsterDrop[11][7] = {}
	tBossCopy_MonsterDrop[11][7]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[11][7]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[11][7]["Item_1"] = 3002926
	-- 通神丹	10.00%	3305116
	tBossCopy_MonsterDrop[11][8] = {}
	tBossCopy_MonsterDrop[11][8]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[11][8]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[11][8]["Item_1"] = 3305116
	-- 究极通神丹	5.00%	3305117
	tBossCopy_MonsterDrop[11][9] = {}
	tBossCopy_MonsterDrop[11][9]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[11][9]["ItemChance"] = 500
	tBossCopy_MonsterDrop[11][9]["Item_1"] = 3305117
	-- 随机本职业精品装备	2.00%
	tBossCopy_MonsterDrop[11][10] = {}
	tBossCopy_MonsterDrop[11][10]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[11][10]["ItemChance"] = 200
	tBossCopy_MonsterDrop[11][10]["Item_1"] = 3305111
	-- 随机本职业极品装备	0.10%
	tBossCopy_MonsterDrop[11][11] = {}
	tBossCopy_MonsterDrop[11][11]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[11][11]["ItemChance"] = 10
	tBossCopy_MonsterDrop[11][11]["Item_1"] = 3305112
	-- 聚神丹（赠）	5.00%	3306659
	tBossCopy_MonsterDrop[11][12] = {}
	tBossCopy_MonsterDrop[11][12]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[11][12]["ItemChance"] = 500
	tBossCopy_MonsterDrop[11][12]["Item_1"] = 3306659
	-- 气力值	10.00%	729478
	tBossCopy_MonsterDrop[11][13] = {}
	tBossCopy_MonsterDrop[11][13]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[11][13]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[11][13]["Item_1"] = 729478
	-- 百炼天机果	0.50%	3001044
	tBossCopy_MonsterDrop[11][14] = {}
	tBossCopy_MonsterDrop[11][14]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[11][14]["ItemChance"] = 50
	tBossCopy_MonsterDrop[11][14]["Item_1"] = 3001044
	
	-- 135级
	tBossCopy_MonsterDrop[12] = {}
	tBossCopy_MonsterDrop[12]["ItemChanceSum"] = 10000
	-- 流星卷碎片（10合1）	8.00%	3305073
	tBossCopy_MonsterDrop[12][1] = {}
	tBossCopy_MonsterDrop[12][1]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[12][1]["ItemChance"] = 800
	tBossCopy_MonsterDrop[12][1]["Item_1"] = 3305073
	-- 龙珠碎片（20合1）	7.00%	3305071
	tBossCopy_MonsterDrop[12][2] = {}
	tBossCopy_MonsterDrop[12][2]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[12][2]["ItemChance"] = 700
	tBossCopy_MonsterDrop[12][2]["Item_1"] = 3305071
	-- 极品宝石碎片（15合1，不能合成玄元）	10%	新制作
	tBossCopy_MonsterDrop[12][3] = {}
	tBossCopy_MonsterDrop[12][3]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[12][3]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[12][3]["Item_1"] = 3305072
	-- 50点修行书	5.00%	3006536
	tBossCopy_MonsterDrop[12][4] = {}
	tBossCopy_MonsterDrop[12][4]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[12][4]["ItemChance"] = 500
	tBossCopy_MonsterDrop[12][4]["Item_1"] = 3006536
	-- 强效护心丹	20.00%	3002030
	tBossCopy_MonsterDrop[12][5] = {}
	tBossCopy_MonsterDrop[12][5]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[12][5]["ItemChance"] = 2000
	tBossCopy_MonsterDrop[12][5]["Item_1"] = 3002030
	-- 强炼丹	7.40%	3305115
	tBossCopy_MonsterDrop[12][6] = {}
	tBossCopy_MonsterDrop[12][6]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[12][6]["ItemChance"] = 740
	tBossCopy_MonsterDrop[12][6]["Item_1"] = 3305115
	-- 秘制免费修炼丹	10.00%	3002926
	tBossCopy_MonsterDrop[12][7] = {}
	tBossCopy_MonsterDrop[12][7]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[12][7]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[12][7]["Item_1"] = 3002926
	-- 通神丹	10.00%	3305116
	tBossCopy_MonsterDrop[12][8] = {}
	tBossCopy_MonsterDrop[12][8]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[12][8]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[12][8]["Item_1"] = 3305116
	-- 究极通神丹	5.00%	3305117
	tBossCopy_MonsterDrop[12][9] = {}
	tBossCopy_MonsterDrop[12][9]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[12][9]["ItemChance"] = 500
	tBossCopy_MonsterDrop[12][9]["Item_1"] = 3305117
	-- 随机本职业精品装备	2.00%
	tBossCopy_MonsterDrop[12][10] = {}
	tBossCopy_MonsterDrop[12][10]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[12][10]["ItemChance"] = 200
	tBossCopy_MonsterDrop[12][10]["Item_1"] = 3305113
	-- 随机本职业极品装备	0.10%
	tBossCopy_MonsterDrop[12][11] = {}
	tBossCopy_MonsterDrop[12][11]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[12][11]["ItemChance"] = 10
	tBossCopy_MonsterDrop[12][11]["Item_1"] = 3305114
	-- 聚神丹（赠）	5.00%	3306659
	tBossCopy_MonsterDrop[12][12] = {}
	tBossCopy_MonsterDrop[12][12]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[12][12]["ItemChance"] = 500
	tBossCopy_MonsterDrop[12][12]["Item_1"] = 3306659
	-- 气力值	10.00%	729478
	tBossCopy_MonsterDrop[12][13] = {}
	tBossCopy_MonsterDrop[12][13]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[12][13]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[12][13]["Item_1"] = 729478
	-- 百炼天机果	0.50%	3001044
	tBossCopy_MonsterDrop[12][14] = {}
	tBossCopy_MonsterDrop[12][14]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[12][14]["ItemChance"] = 50
	tBossCopy_MonsterDrop[12][14]["Item_1"] = 3001044
	
	-- 140级
	tBossCopy_MonsterDrop[13] = {}
	tBossCopy_MonsterDrop[13]["ItemChanceSum"] = 10000
	-- 流星卷碎片（10合1）	8.00%	3305073
	tBossCopy_MonsterDrop[13][1] = {}
	tBossCopy_MonsterDrop[13][1]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[13][1]["ItemChance"] = 800
	tBossCopy_MonsterDrop[13][1]["Item_1"] = 3305073
	-- 龙珠碎片（20合1）	7.00%	3305071
	tBossCopy_MonsterDrop[13][2] = {}
	tBossCopy_MonsterDrop[13][2]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[13][2]["ItemChance"] = 700
	tBossCopy_MonsterDrop[13][2]["Item_1"] = 3305071
	-- 极品宝石碎片（15合1，不能合成玄元）	10%	新制作
	tBossCopy_MonsterDrop[13][3] = {}
	tBossCopy_MonsterDrop[13][3]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[13][3]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[13][3]["Item_1"] = 3305072
	-- 50点修行书	5.00%	3006536
	tBossCopy_MonsterDrop[13][4] = {}
	tBossCopy_MonsterDrop[13][4]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[13][4]["ItemChance"] = 500
	tBossCopy_MonsterDrop[13][4]["Item_1"] = 3006536
	-- 强效护心丹	20.00%	3002030
	tBossCopy_MonsterDrop[13][5] = {}
	tBossCopy_MonsterDrop[13][5]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[13][5]["ItemChance"] = 2000
	tBossCopy_MonsterDrop[13][5]["Item_1"] = 3002030
	-- 强炼丹	7.50%	3305115
	tBossCopy_MonsterDrop[13][6] = {}
	tBossCopy_MonsterDrop[13][6]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[13][6]["ItemChance"] = 750
	tBossCopy_MonsterDrop[13][6]["Item_1"] = 3305115
	-- 秘制免费修炼丹	10.00%	3002926
	tBossCopy_MonsterDrop[13][7] = {}
	tBossCopy_MonsterDrop[13][7]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[13][7]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[13][7]["Item_1"] = 3002926
	-- 通神丹	10.00%	3305116
	tBossCopy_MonsterDrop[13][8] = {}
	tBossCopy_MonsterDrop[13][8]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[13][8]["ItemChance"] = 1000
	tBossCopy_MonsterDrop[13][8]["Item_1"] = 3305116
	-- 究极通神丹	5.00%	3305117
	tBossCopy_MonsterDrop[13][9] = {}
	tBossCopy_MonsterDrop[13][9]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[13][9]["ItemChance"] = 500
	tBossCopy_MonsterDrop[13][9]["Item_1"] = 3305117
	-- 随机本职业精品装备	0.00%
	tBossCopy_MonsterDrop[13][10] = {}
	tBossCopy_MonsterDrop[13][10]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[13][10]["ItemChance"] = 0
	tBossCopy_MonsterDrop[13][10]["Item_1"] = 0
	-- 随机本职业极品装备	0.00%
	tBossCopy_MonsterDrop[13][11] = {}
	tBossCopy_MonsterDrop[13][11]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[13][11]["ItemChance"] = 0
	tBossCopy_MonsterDrop[13][11]["Item_1"] = 0
	-- 聚神丹（赠）	5.00%	3306659
	tBossCopy_MonsterDrop[13][12] = {}
	tBossCopy_MonsterDrop[13][12]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[13][12]["ItemChance"] = 500
	tBossCopy_MonsterDrop[13][12]["Item_1"] = 3306659
	-- 气力值	12.00%	729478
	tBossCopy_MonsterDrop[13][13] = {}
	tBossCopy_MonsterDrop[13][13]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[13][13]["ItemChance"] = 1200
	tBossCopy_MonsterDrop[13][13]["Item_1"] = 729478
	-- 百炼天机果	0.50%	3001044
	tBossCopy_MonsterDrop[13][14] = {}
	tBossCopy_MonsterDrop[13][14]["RandomItemChanceType"] = 2
	tBossCopy_MonsterDrop[13][14]["ItemChance"] = 50
	tBossCopy_MonsterDrop[13][14]["Item_1"] = 3001044
	
local tBossCopy_Reward = {}
	-- 首通
	tBossCopy_Reward["First"] = {}
	-- 精品50级衣服
	tBossCopy_Reward["First"][1] = {}
	for i,v in pairs(tBossCopy_Data["Itemtype"]["First"][1]) do
	tBossCopy_Reward["First"][1][i] = {}
	tBossCopy_Reward["First"][1][i]["RewardItem"] = {}
	tBossCopy_Reward["First"][1][i]["RewardItem"][1] = {}
	tBossCopy_Reward["First"][1][i]["RewardItem"][1]["Id"] = v
	tBossCopy_Reward["First"][1][i]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Reward["First"][1][i]["LogId"] = 12000851
	end
	
	-- 精品60级戒指 150118	152108(道士)
	tBossCopy_Reward["First"][2] = {}
	for i = 1,9 do
	tBossCopy_Reward["First"][2][i] = {}
	tBossCopy_Reward["First"][2][i]["RewardItem"] = {}
	tBossCopy_Reward["First"][2][i]["RewardItem"][1] = {}
	tBossCopy_Reward["First"][2][i]["RewardItem"][1]["Id"] = 150118
	tBossCopy_Reward["First"][2][i]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Reward["First"][2][i]["LogId"] = 12000851
	end
	-- 道士
	tBossCopy_Reward["First"][2][8] = {}
	tBossCopy_Reward["First"][2][8]["RewardItem"] = {}
	tBossCopy_Reward["First"][2][8]["RewardItem"][1] = {}
	tBossCopy_Reward["First"][2][8]["RewardItem"][1]["Id"] = 152108
	tBossCopy_Reward["First"][2][8]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Reward["First"][2][8]["LogId"] = 12000851
	
	-- 精品70级武器
	tBossCopy_Reward["First"][3] = {}
	for i,v in pairs(tBossCopy_Data["Itemtype"]["First"][3]) do
	tBossCopy_Reward["First"][3][i] = {}
	tBossCopy_Reward["First"][3][i]["RewardItem"] = {}
	tBossCopy_Reward["First"][3][i]["RewardItem"][1] = {}
	tBossCopy_Reward["First"][3][i]["RewardItem"][1]["Id"] = v
	tBossCopy_Reward["First"][3][i]["RewardItem"][1]["Attr"] = "0 2 3"
	tBossCopy_Reward["First"][3][i]["LogId"] = 12000851
	end
	-- 海盗
	tBossCopy_Reward["First"][3][6] = {}
	tBossCopy_Reward["First"][3][6]["RewardItem"] = {}
	tBossCopy_Reward["First"][3][6]["RewardItem"][1] = {}
	tBossCopy_Reward["First"][3][6]["RewardItem"][1]["Id"] = 611138
	tBossCopy_Reward["First"][3][6]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Reward["First"][3][6]["RewardItem"][2] = {}
	tBossCopy_Reward["First"][3][6]["RewardItem"][2]["Id"] = 612138
	tBossCopy_Reward["First"][3][6]["RewardItem"][2]["Attr"] = "0 1 3"
	tBossCopy_Reward["First"][3][6]["LogId"] = 12000851
	-- 道士
	tBossCopy_Reward["First"][3][8] = {}
	tBossCopy_Reward["First"][3][8]["RewardItem"] = {}
	tBossCopy_Reward["First"][3][8]["RewardItem"][1] = {}
	tBossCopy_Reward["First"][3][8]["RewardItem"][1]["Id"] = 421138
	tBossCopy_Reward["First"][3][8]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Reward["First"][3][8]["RewardItem"][2] = {}
	tBossCopy_Reward["First"][3][8]["RewardItem"][2]["Id"] = 619138
	tBossCopy_Reward["First"][3][8]["RewardItem"][2]["Attr"] = "0 1 3"
	tBossCopy_Reward["First"][3][8]["LogId"] = 12000851
	
	-- 精品80级项链	120158
	tBossCopy_Reward["First"][4] = {}
	for i = 1,9 do
	tBossCopy_Reward["First"][4][i] = {}
	tBossCopy_Reward["First"][4][i]["RewardItem"] = {}
	tBossCopy_Reward["First"][4][i]["RewardItem"][1] = {}
	tBossCopy_Reward["First"][4][i]["RewardItem"][1]["Id"] = 120158
	tBossCopy_Reward["First"][4][i]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Reward["First"][4][i]["LogId"] = 12000851
	end
	
	-- 精品90级衣服
	tBossCopy_Reward["First"][5] = {}
	for i,v in pairs(tBossCopy_Data["Itemtype"]["First"][5]) do
	tBossCopy_Reward["First"][5][i] = {}
	tBossCopy_Reward["First"][5][i]["RewardItem"] = {}
	tBossCopy_Reward["First"][5][i]["RewardItem"][1] = {}
	tBossCopy_Reward["First"][5][i]["RewardItem"][1]["Id"] = v
	tBossCopy_Reward["First"][5][i]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Reward["First"][5][i]["LogId"] = 12000851
	end
	
	-- 塔 202009
	tBossCopy_Reward["First"][6] = {}
	for i = 1,9 do
	tBossCopy_Reward["First"][6][i] = {}
	tBossCopy_Reward["First"][6][i]["RewardItem"] = {}
	tBossCopy_Reward["First"][6][i]["RewardItem"][1] = {}
	tBossCopy_Reward["First"][6][i]["RewardItem"][1]["Id"] = 202009
	tBossCopy_Reward["First"][6][i]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Reward["First"][6][i]["LogId"] = 12000851
	end
	
	-- 扇 201009
	tBossCopy_Reward["First"][7] = {}
	for i = 1,9 do
	tBossCopy_Reward["First"][7][i] = {}
	tBossCopy_Reward["First"][7][i]["RewardItem"] = {}
	tBossCopy_Reward["First"][7][i]["RewardItem"][1] = {}
	tBossCopy_Reward["First"][7][i]["RewardItem"][1]["Id"] = 201009
	tBossCopy_Reward["First"][7][i]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Reward["First"][7][i]["LogId"] = 12000851
	end
	
	-- 翅膀 204009
	tBossCopy_Reward["First"][8] = {}
	for i = 1,9 do
	tBossCopy_Reward["First"][8][i] = {}
	tBossCopy_Reward["First"][8][i]["RewardItem"] = {}
	tBossCopy_Reward["First"][8][i]["RewardItem"][1] = {}
	tBossCopy_Reward["First"][8][i]["RewardItem"][1]["Id"] = 204009
	tBossCopy_Reward["First"][8][i]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Reward["First"][8][i]["LogId"] = 12000851
	end
	
	-- 龙珠赠
	for i = 9,13 do
	tBossCopy_Reward["First"][i] = {}
	for j = 1,9 do
	tBossCopy_Reward["First"][i][j] = {}
	tBossCopy_Reward["First"][i][j]["RewardItem"] = {}
	tBossCopy_Reward["First"][i][j]["RewardItem"][1] = {}
	tBossCopy_Reward["First"][i][j]["RewardItem"][1]["Id"] = 1088000
	tBossCopy_Reward["First"][i][j]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Reward["First"][i][j]["LogId"] = 12000851
	end
	end
	
	-- 基础奖励
	tBossCopy_Reward["Basic"] = {}
	-- 50 1 30分钟
	tBossCopy_Reward["Basic"][1] = {}
	tBossCopy_Reward["Basic"][1]["RewardItem"] = {}
	tBossCopy_Reward["Basic"][1]["RewardItem"][1] = {}
	tBossCopy_Reward["Basic"][1]["RewardItem"][1]["Id"] = 3305059
	tBossCopy_Reward["Basic"][1]["RewardItem"][1]["Attr"] = "0 1"
	tBossCopy_Reward["Basic"][1]["LogId"] = 12000851
	
	-- 60 2 40分钟	1个真气礼包	3006542 monopoly 9
	tBossCopy_Reward["Basic"][2] = {}
	tBossCopy_Reward["Basic"][2]["RewardItem"] = {}
	tBossCopy_Reward["Basic"][2]["RewardItem"][1] = {}
	tBossCopy_Reward["Basic"][2]["RewardItem"][1]["Id"] = 3305060
	tBossCopy_Reward["Basic"][2]["RewardItem"][1]["Attr"] = "0 1"
	tBossCopy_Reward["Basic"][2]["RewardItem"][2] = {}
	tBossCopy_Reward["Basic"][2]["RewardItem"][2]["Id"] = 3006542
	tBossCopy_Reward["Basic"][2]["RewardItem"][2]["Attr"] = "0 1"
	tBossCopy_Reward["Basic"][2]["LogId"] = 12000851
	
	-- 70 3	50分钟	2个真气礼包	50修行值
	tBossCopy_Reward["Basic"][3] = {}
	tBossCopy_Reward["Basic"][3]["RewardItem"] = {}
	tBossCopy_Reward["Basic"][3]["RewardItem"][1] = {}
	tBossCopy_Reward["Basic"][3]["RewardItem"][1]["Id"] = 3305061
	tBossCopy_Reward["Basic"][3]["RewardItem"][1]["Attr"] = "0 1"
	tBossCopy_Reward["Basic"][3]["RewardItem"][2] = {}
	tBossCopy_Reward["Basic"][3]["RewardItem"][2]["Id"] = 3006542
	tBossCopy_Reward["Basic"][3]["RewardItem"][2]["Attr"] = "0 2"
	tBossCopy_Reward["Basic"][3]["RewardCultivation"] = {}
	tBossCopy_Reward["Basic"][3]["RewardCultivation"]["Value"] = 50
	tBossCopy_Reward["Basic"][3]["LogId"] = 12000851
	
	-- 80 4	60分钟	3个真气礼包	100修行值
	tBossCopy_Reward["Basic"][4] = {}
	tBossCopy_Reward["Basic"][4]["RewardItem"] = {}
	tBossCopy_Reward["Basic"][4]["RewardItem"][1] = {}
	tBossCopy_Reward["Basic"][4]["RewardItem"][1]["Id"] = 3305062
	tBossCopy_Reward["Basic"][4]["RewardItem"][1]["Attr"] = "0 1"
	tBossCopy_Reward["Basic"][4]["RewardItem"][2] = {}
	tBossCopy_Reward["Basic"][4]["RewardItem"][2]["Id"] = 3006542
	tBossCopy_Reward["Basic"][4]["RewardItem"][2]["Attr"] = "0 3"
	tBossCopy_Reward["Basic"][4]["RewardCultivation"] = {}
	tBossCopy_Reward["Basic"][4]["RewardCultivation"]["Value"] = 100
	tBossCopy_Reward["Basic"][4]["LogId"] = 12000851
	
	-- 90 5	70分钟	4个真气礼包	200修行值
	tBossCopy_Reward["Basic"][5] = {}
	tBossCopy_Reward["Basic"][5]["RewardItem"] = {}
	tBossCopy_Reward["Basic"][5]["RewardItem"][1] = {}
	tBossCopy_Reward["Basic"][5]["RewardItem"][1]["Id"] = 3305063
	tBossCopy_Reward["Basic"][5]["RewardItem"][1]["Attr"] = "0 1"
	tBossCopy_Reward["Basic"][5]["RewardItem"][2] = {}
	tBossCopy_Reward["Basic"][5]["RewardItem"][2]["Id"] = 3006542
	tBossCopy_Reward["Basic"][5]["RewardItem"][2]["Attr"] = "0 4"
	tBossCopy_Reward["Basic"][5]["RewardCultivation"] = {}
	tBossCopy_Reward["Basic"][5]["RewardCultivation"]["Value"] = 200
	tBossCopy_Reward["Basic"][5]["LogId"] = 12000851
	
	-- 100 6	80分钟	5个真气礼包	300修行值	冷香草*20大还丹*20（打包）
	tBossCopy_Reward["Basic"][6] = {}
	tBossCopy_Reward["Basic"][6]["RewardItem"] = {}
	tBossCopy_Reward["Basic"][6]["RewardItem"][1] = {}
	tBossCopy_Reward["Basic"][6]["RewardItem"][1]["Id"] = 3305064
	tBossCopy_Reward["Basic"][6]["RewardItem"][1]["Attr"] = "0 1"
	tBossCopy_Reward["Basic"][6]["RewardItem"][2] = {}
	tBossCopy_Reward["Basic"][6]["RewardItem"][2]["Id"] = 3006542
	tBossCopy_Reward["Basic"][6]["RewardItem"][2]["Attr"] = "0 5"
	tBossCopy_Reward["Basic"][6]["RewardCultivation"] = {}
	tBossCopy_Reward["Basic"][6]["RewardCultivation"]["Value"] = 300
	tBossCopy_Reward["Basic"][6]["LogId"] = 12000851
	
	-- 110 7	90分钟	8个真气礼包	400修行值	冷香草*20大还丹*20（打包）
	tBossCopy_Reward["Basic"][7] = {}
	tBossCopy_Reward["Basic"][7]["RewardItem"] = {}
	tBossCopy_Reward["Basic"][7]["RewardItem"][1] = {}
	tBossCopy_Reward["Basic"][7]["RewardItem"][1]["Id"] = 3305065
	tBossCopy_Reward["Basic"][7]["RewardItem"][1]["Attr"] = "0 1"
	tBossCopy_Reward["Basic"][7]["RewardItem"][2] = {}
	tBossCopy_Reward["Basic"][7]["RewardItem"][2]["Id"] = 3006542
	tBossCopy_Reward["Basic"][7]["RewardItem"][2]["Attr"] = "0 8"
	tBossCopy_Reward["Basic"][7]["RewardCultivation"] = {}
	tBossCopy_Reward["Basic"][7]["RewardCultivation"]["Value"] = 400
	tBossCopy_Reward["Basic"][7]["LogId"] = 12000851
	
	-- 115 8	100分钟	10个真气礼包	500修行值	冷香草*20大还丹*20（打包）
	tBossCopy_Reward["Basic"][8] = {}
	tBossCopy_Reward["Basic"][8]["RewardItem"] = {}
	tBossCopy_Reward["Basic"][8]["RewardItem"][1] = {}
	tBossCopy_Reward["Basic"][8]["RewardItem"][1]["Id"] = 3305066
	tBossCopy_Reward["Basic"][8]["RewardItem"][1]["Attr"] = "0 1"
	tBossCopy_Reward["Basic"][8]["RewardItem"][2] = {}
	tBossCopy_Reward["Basic"][8]["RewardItem"][2]["Id"] = 3006542
	tBossCopy_Reward["Basic"][8]["RewardItem"][2]["Attr"] = "0 10"
	tBossCopy_Reward["Basic"][8]["RewardCultivation"] = {}
	tBossCopy_Reward["Basic"][8]["RewardCultivation"]["Value"] = 500
	tBossCopy_Reward["Basic"][8]["LogId"] = 12000851
	
	-- 120 9	110分钟	100气力值	600修行值	归元灵露*20回元金丹*20（打包）
	tBossCopy_Reward["Basic"][9] = {}
	tBossCopy_Reward["Basic"][9]["RewardItem"] = {}
	tBossCopy_Reward["Basic"][9]["RewardItem"][1] = {}
	tBossCopy_Reward["Basic"][9]["RewardItem"][1]["Id"] = 3305067
	tBossCopy_Reward["Basic"][9]["RewardItem"][1]["Attr"] = "0 1"
	tBossCopy_Reward["Basic"][9]["RewardCultivation"] = {}
	tBossCopy_Reward["Basic"][9]["RewardCultivation"]["Value"] = 600
	tBossCopy_Reward["Basic"][9]["RewardStrengthValue"] = {}
	tBossCopy_Reward["Basic"][9]["RewardStrengthValue"]["Value"] = 100
	tBossCopy_Reward["Basic"][9]["LogId"] = 12000851
	
	-- 125 10	120分钟	200气力值	700修行值	归元灵露*20回元金丹*20（打包）
	tBossCopy_Reward["Basic"][10] = {}
	tBossCopy_Reward["Basic"][10]["RewardItem"] = {}
	tBossCopy_Reward["Basic"][10]["RewardItem"][1] = {}
	tBossCopy_Reward["Basic"][10]["RewardItem"][1]["Id"] = 3305068
	tBossCopy_Reward["Basic"][10]["RewardItem"][1]["Attr"] = "0 1"
	tBossCopy_Reward["Basic"][10]["RewardCultivation"] = {}
	tBossCopy_Reward["Basic"][10]["RewardCultivation"]["Value"] = 700
	tBossCopy_Reward["Basic"][10]["RewardStrengthValue"] = {}
	tBossCopy_Reward["Basic"][10]["RewardStrengthValue"]["Value"] = 200
	tBossCopy_Reward["Basic"][10]["LogId"] = 12000851
	
	-- 130 11	130分钟	300气力值	800修行值	微光星陨石*5	归元灵露*20回元金丹*20（打包）
	tBossCopy_Reward["Basic"][11] = {}
	tBossCopy_Reward["Basic"][11]["RewardItem"] = {}
	tBossCopy_Reward["Basic"][11]["RewardItem"][1] = {}
	tBossCopy_Reward["Basic"][11]["RewardItem"][1]["Id"] = 3305069
	tBossCopy_Reward["Basic"][11]["RewardItem"][1]["Attr"] = "0 1"
	tBossCopy_Reward["Basic"][11]["RewardItem"][2] = {}
	tBossCopy_Reward["Basic"][11]["RewardItem"][2]["Id"] = 3009000
	tBossCopy_Reward["Basic"][11]["RewardItem"][2]["Attr"] = "0 5 0 2880 1"
	tBossCopy_Reward["Basic"][11]["RewardCultivation"] = {}
	tBossCopy_Reward["Basic"][11]["RewardCultivation"]["Value"] = 800
	tBossCopy_Reward["Basic"][11]["RewardStrengthValue"] = {}
	tBossCopy_Reward["Basic"][11]["RewardStrengthValue"]["Value"] = 300
	tBossCopy_Reward["Basic"][11]["LogId"] = 12000851
	
	-- 135 12	200分钟	400气力值	900修行值	明亮星陨石*1	七星断续膏*20三清回魂散*20（打包）
	tBossCopy_Reward["Basic"][12] = {}
	tBossCopy_Reward["Basic"][12]["RewardItem"] = {}
	tBossCopy_Reward["Basic"][12]["RewardItem"][1] = {}
	tBossCopy_Reward["Basic"][12]["RewardItem"][1]["Id"] = 3305070
	tBossCopy_Reward["Basic"][12]["RewardItem"][1]["Attr"] = "0 1"
	tBossCopy_Reward["Basic"][12]["RewardItem"][2] = {}
	tBossCopy_Reward["Basic"][12]["RewardItem"][2]["Id"] = 3009001
	tBossCopy_Reward["Basic"][12]["RewardItem"][2]["Attr"] = "0 1 0 2880 1"
	tBossCopy_Reward["Basic"][12]["RewardCultivation"] = {}
	tBossCopy_Reward["Basic"][12]["RewardCultivation"]["Value"] = 900
	tBossCopy_Reward["Basic"][12]["RewardStrengthValue"] = {}
	tBossCopy_Reward["Basic"][12]["RewardStrengthValue"]["Value"] = 400
	tBossCopy_Reward["Basic"][12]["LogId"] = 12000851
	
	-- 140 13	500气力值	1000修行值	明亮星陨石*2	七星断续膏*20三清回魂散*20（打包）
	tBossCopy_Reward["Basic"][13] = {}
	tBossCopy_Reward["Basic"][13]["RewardItem"] = {}
	tBossCopy_Reward["Basic"][13]["RewardItem"][1] = {}
	tBossCopy_Reward["Basic"][13]["RewardItem"][1]["Id"] = 3009001
	tBossCopy_Reward["Basic"][13]["RewardItem"][1]["Attr"] = "0 2 0 2880 1"
	tBossCopy_Reward["Basic"][13]["RewardCultivation"] = {}
	tBossCopy_Reward["Basic"][13]["RewardCultivation"]["Value"] = 1000
	tBossCopy_Reward["Basic"][13]["RewardStrengthValue"] = {}
	tBossCopy_Reward["Basic"][13]["RewardStrengthValue"]["Value"] = 500
	tBossCopy_Reward["Basic"][13]["LogId"] = 12000851
	
	-- 基础奖励 翻倍
	tBossCopy_Reward["Double"] = {}
	-- 50 1 30分钟
	tBossCopy_Reward["Double"][1] = {}
	tBossCopy_Reward["Double"][1]["RewardItem"] = {}
	tBossCopy_Reward["Double"][1]["RewardItem"][1] = {}
	tBossCopy_Reward["Double"][1]["RewardItem"][1]["Id"] = 3305059
	tBossCopy_Reward["Double"][1]["RewardItem"][1]["Attr"] = "0 2"
	tBossCopy_Reward["Double"][1]["LogId"] = 12000851
	
	-- 60 2 40分钟	1个真气礼包	3006542 monopoly 9
	tBossCopy_Reward["Double"][2] = {}
	tBossCopy_Reward["Double"][2]["RewardItem"] = {}
	tBossCopy_Reward["Double"][2]["RewardItem"][1] = {}
	tBossCopy_Reward["Double"][2]["RewardItem"][1]["Id"] = 3305060
	tBossCopy_Reward["Double"][2]["RewardItem"][1]["Attr"] = "0 2"
	tBossCopy_Reward["Double"][2]["RewardItem"][2] = {}
	tBossCopy_Reward["Double"][2]["RewardItem"][2]["Id"] = 3006542
	tBossCopy_Reward["Double"][2]["RewardItem"][2]["Attr"] = "0 2"
	tBossCopy_Reward["Double"][2]["LogId"] = 12000851
	
	-- 70 3	50分钟	2个真气礼包	50修行值
	tBossCopy_Reward["Double"][3] = {}
	tBossCopy_Reward["Double"][3]["RewardItem"] = {}
	tBossCopy_Reward["Double"][3]["RewardItem"][1] = {}
	tBossCopy_Reward["Double"][3]["RewardItem"][1]["Id"] = 3305061
	tBossCopy_Reward["Double"][3]["RewardItem"][1]["Attr"] = "0 2"
	tBossCopy_Reward["Double"][3]["RewardItem"][2] = {}
	tBossCopy_Reward["Double"][3]["RewardItem"][2]["Id"] = 3006542
	tBossCopy_Reward["Double"][3]["RewardItem"][2]["Attr"] = "0 4"
	tBossCopy_Reward["Double"][3]["RewardCultivation"] = {}
	tBossCopy_Reward["Double"][3]["RewardCultivation"]["Value"] = 100
	tBossCopy_Reward["Double"][3]["LogId"] = 12000851
	
	-- 80 4	60分钟	3个真气礼包	100修行值
	tBossCopy_Reward["Double"][4] = {}
	tBossCopy_Reward["Double"][4]["RewardItem"] = {}
	tBossCopy_Reward["Double"][4]["RewardItem"][1] = {}
	tBossCopy_Reward["Double"][4]["RewardItem"][1]["Id"] = 3305062
	tBossCopy_Reward["Double"][4]["RewardItem"][1]["Attr"] = "0 2"
	tBossCopy_Reward["Double"][4]["RewardItem"][2] = {}
	tBossCopy_Reward["Double"][4]["RewardItem"][2]["Id"] = 3006542
	tBossCopy_Reward["Double"][4]["RewardItem"][2]["Attr"] = "0 6"
	tBossCopy_Reward["Double"][4]["RewardCultivation"] = {}
	tBossCopy_Reward["Double"][4]["RewardCultivation"]["Value"] = 200
	tBossCopy_Reward["Double"][4]["LogId"] = 12000851
	
	-- 90 5	70分钟	4个真气礼包	200修行值
	tBossCopy_Reward["Double"][5] = {}
	tBossCopy_Reward["Double"][5]["RewardItem"] = {}
	tBossCopy_Reward["Double"][5]["RewardItem"][1] = {}
	tBossCopy_Reward["Double"][5]["RewardItem"][1]["Id"] = 3305063
	tBossCopy_Reward["Double"][5]["RewardItem"][1]["Attr"] = "0 2"
	tBossCopy_Reward["Double"][5]["RewardItem"][2] = {}
	tBossCopy_Reward["Double"][5]["RewardItem"][2]["Id"] = 3006542
	tBossCopy_Reward["Double"][5]["RewardItem"][2]["Attr"] = "0 8"
	tBossCopy_Reward["Double"][5]["RewardCultivation"] = {}
	tBossCopy_Reward["Double"][5]["RewardCultivation"]["Value"] = 400
	tBossCopy_Reward["Double"][5]["LogId"] = 12000851
	
	-- 100 6	80分钟	5个真气礼包	300修行值	冷香草*20大还丹*20（打包）
	tBossCopy_Reward["Double"][6] = {}
	tBossCopy_Reward["Double"][6]["RewardItem"] = {}
	tBossCopy_Reward["Double"][6]["RewardItem"][1] = {}
	tBossCopy_Reward["Double"][6]["RewardItem"][1]["Id"] = 3305064
	tBossCopy_Reward["Double"][6]["RewardItem"][1]["Attr"] = "0 2"
	tBossCopy_Reward["Double"][6]["RewardItem"][2] = {}
	tBossCopy_Reward["Double"][6]["RewardItem"][2]["Id"] = 3006542
	tBossCopy_Reward["Double"][6]["RewardItem"][2]["Attr"] = "0 10"
	tBossCopy_Reward["Double"][6]["RewardCultivation"] = {}
	tBossCopy_Reward["Double"][6]["RewardCultivation"]["Value"] = 600
	tBossCopy_Reward["Double"][6]["LogId"] = 12000851
	
	-- 110 7	90分钟	8个真气礼包	400修行值	冷香草*20大还丹*20（打包）
	tBossCopy_Reward["Double"][7] = {}
	tBossCopy_Reward["Double"][7]["RewardItem"] = {}
	tBossCopy_Reward["Double"][7]["RewardItem"][1] = {}
	tBossCopy_Reward["Double"][7]["RewardItem"][1]["Id"] = 3305065
	tBossCopy_Reward["Double"][7]["RewardItem"][1]["Attr"] = "0 2"
	tBossCopy_Reward["Double"][7]["RewardItem"][2] = {}
	tBossCopy_Reward["Double"][7]["RewardItem"][2]["Id"] = 3006542
	tBossCopy_Reward["Double"][7]["RewardItem"][2]["Attr"] = "0 16"
	tBossCopy_Reward["Double"][7]["RewardCultivation"] = {}
	tBossCopy_Reward["Double"][7]["RewardCultivation"]["Value"] = 800
	tBossCopy_Reward["Double"][7]["LogId"] = 12000851
	
	-- 115 8	100分钟	10个真气礼包	500修行值	冷香草*20大还丹*20（打包）
	tBossCopy_Reward["Double"][8] = {}
	tBossCopy_Reward["Double"][8]["RewardItem"] = {}
	tBossCopy_Reward["Double"][8]["RewardItem"][1] = {}
	tBossCopy_Reward["Double"][8]["RewardItem"][1]["Id"] = 3305066
	tBossCopy_Reward["Double"][8]["RewardItem"][1]["Attr"] = "0 2"
	tBossCopy_Reward["Double"][8]["RewardItem"][2] = {}
	tBossCopy_Reward["Double"][8]["RewardItem"][2]["Id"] = 3006542
	tBossCopy_Reward["Double"][8]["RewardItem"][2]["Attr"] = "0 20"
	tBossCopy_Reward["Double"][8]["RewardCultivation"] = {}
	tBossCopy_Reward["Double"][8]["RewardCultivation"]["Value"] = 1000
	tBossCopy_Reward["Double"][8]["LogId"] = 12000851
	
	-- 120 9	110分钟	100气力值	600修行值	归元灵露*20回元金丹*20（打包）
	tBossCopy_Reward["Double"][9] = {}
	tBossCopy_Reward["Double"][9]["RewardItem"] = {}
	tBossCopy_Reward["Double"][9]["RewardItem"][1] = {}
	tBossCopy_Reward["Double"][9]["RewardItem"][1]["Id"] = 3305067
	tBossCopy_Reward["Double"][9]["RewardItem"][1]["Attr"] = "0 2"
	tBossCopy_Reward["Double"][9]["RewardCultivation"] = {}
	tBossCopy_Reward["Double"][9]["RewardCultivation"]["Value"] = 1200
	tBossCopy_Reward["Double"][9]["RewardStrengthValue"] = {}
	tBossCopy_Reward["Double"][9]["RewardStrengthValue"]["Value"] = 200
	tBossCopy_Reward["Double"][9]["LogId"] = 12000851
	
	-- 125 10	120分钟	200气力值	700修行值	归元灵露*20回元金丹*20（打包）
	tBossCopy_Reward["Double"][10] = {}
	tBossCopy_Reward["Double"][10]["RewardItem"] = {}
	tBossCopy_Reward["Double"][10]["RewardItem"][1] = {}
	tBossCopy_Reward["Double"][10]["RewardItem"][1]["Id"] = 3305068
	tBossCopy_Reward["Double"][10]["RewardItem"][1]["Attr"] = "0 2"
	tBossCopy_Reward["Double"][10]["RewardCultivation"] = {}
	tBossCopy_Reward["Double"][10]["RewardCultivation"]["Value"] = 1400
	tBossCopy_Reward["Double"][10]["RewardStrengthValue"] = {}
	tBossCopy_Reward["Double"][10]["RewardStrengthValue"]["Value"] = 400
	tBossCopy_Reward["Double"][10]["LogId"] = 12000851
	
	-- 130 11	130分钟	300气力值	800修行值	微光星陨石*5	归元灵露*20回元金丹*20（打包）
	tBossCopy_Reward["Double"][11] = {}
	tBossCopy_Reward["Double"][11]["RewardItem"] = {}
	tBossCopy_Reward["Double"][11]["RewardItem"][1] = {}
	tBossCopy_Reward["Double"][11]["RewardItem"][1]["Id"] = 3305069
	tBossCopy_Reward["Double"][11]["RewardItem"][1]["Attr"] = "0 2"
	tBossCopy_Reward["Double"][11]["RewardItem"][2] = {}
	tBossCopy_Reward["Double"][11]["RewardItem"][2]["Id"] = 3009000
	tBossCopy_Reward["Double"][11]["RewardItem"][2]["Attr"] = "0 10 0 2880 1"
	tBossCopy_Reward["Double"][11]["RewardCultivation"] = {}
	tBossCopy_Reward["Double"][11]["RewardCultivation"]["Value"] = 1600
	tBossCopy_Reward["Double"][11]["RewardStrengthValue"] = {}
	tBossCopy_Reward["Double"][11]["RewardStrengthValue"]["Value"] = 600
	tBossCopy_Reward["Double"][11]["LogId"] = 12000851
	
	-- 135 12	200分钟	400气力值	900修行值	明亮星陨石*1	七星断续膏*20三清回魂散*20（打包）
	tBossCopy_Reward["Double"][12] = {}
	tBossCopy_Reward["Double"][12]["RewardItem"] = {}
	tBossCopy_Reward["Double"][12]["RewardItem"][1] = {}
	tBossCopy_Reward["Double"][12]["RewardItem"][1]["Id"] = 3305070
	tBossCopy_Reward["Double"][12]["RewardItem"][1]["Attr"] = "0 2"
	tBossCopy_Reward["Double"][12]["RewardItem"][2] = {}
	tBossCopy_Reward["Double"][12]["RewardItem"][2]["Id"] = 3009001
	tBossCopy_Reward["Double"][12]["RewardItem"][2]["Attr"] = "0 2 0 2880 1"
	tBossCopy_Reward["Double"][12]["RewardCultivation"] = {}
	tBossCopy_Reward["Double"][12]["RewardCultivation"]["Value"] = 1800
	tBossCopy_Reward["Double"][12]["RewardStrengthValue"] = {}
	tBossCopy_Reward["Double"][12]["RewardStrengthValue"]["Value"] = 800
	tBossCopy_Reward["Double"][12]["LogId"] = 12000851
	
	-- 140 13	500气力值	1000修行值	明亮星陨石*2	七星断续膏*20三清回魂散*20（打包）
	tBossCopy_Reward["Double"][13] = {}
	tBossCopy_Reward["Double"][13]["RewardItem"] = {}
	tBossCopy_Reward["Double"][13]["RewardItem"][1] = {}
	tBossCopy_Reward["Double"][13]["RewardItem"][1]["Id"] = 3009001
	tBossCopy_Reward["Double"][13]["RewardItem"][1]["Attr"] = "0 4 0 2880 1"
	tBossCopy_Reward["Double"][13]["RewardCultivation"] = {}
	tBossCopy_Reward["Double"][13]["RewardCultivation"]["Value"] = 2000
	tBossCopy_Reward["Double"][13]["RewardStrengthValue"] = {}
	tBossCopy_Reward["Double"][13]["RewardStrengthValue"]["Value"] = 1000
	tBossCopy_Reward["Double"][13]["LogId"] = 12000851
	
	-- 开服
	-- 3星外套
	tBossCopy_Reward["Special"] = {}
	tBossCopy_Reward["Special"][11] = {}
	tBossCopy_Reward["Special"][11]["LogId"] = 12000851
	tBossCopy_Reward["Special"][11]["ItemChanceSum"] = 10000
	tBossCopy_Reward["Special"][11][1] = {}
	tBossCopy_Reward["Special"][11][1]["RandomItemChanceType"] = 2
	tBossCopy_Reward["Special"][11][1]["ItemChance"] = 2500
	tBossCopy_Reward["Special"][11][1]["RewardItem"] = {}
	tBossCopy_Reward["Special"][11][1]["RewardItem"][1] = {}
	tBossCopy_Reward["Special"][11][1]["RewardItem"][1]["Id"] = 184355
	tBossCopy_Reward["Special"][11][1]["RewardItem"][1]["Attr"] = "0 1 3 0 0 0 0 1"
	tBossCopy_Reward["Special"][11][2] = {}
	tBossCopy_Reward["Special"][11][2]["RandomItemChanceType"] = 2
	tBossCopy_Reward["Special"][11][2]["ItemChance"] = 2500
	tBossCopy_Reward["Special"][11][2]["RewardItem"] = {}
	tBossCopy_Reward["Special"][11][2]["RewardItem"][1] = {}
	tBossCopy_Reward["Special"][11][2]["RewardItem"][1]["Id"] = 184345
	tBossCopy_Reward["Special"][11][2]["RewardItem"][1]["Attr"] = "0 1 3 0 0 0 0 1"
	tBossCopy_Reward["Special"][11][3] = {}
	tBossCopy_Reward["Special"][11][3]["RandomItemChanceType"] = 2
	tBossCopy_Reward["Special"][11][3]["ItemChance"] = 2500
	tBossCopy_Reward["Special"][11][3]["RewardItem"] = {}
	tBossCopy_Reward["Special"][11][3]["RewardItem"][1] = {}
	tBossCopy_Reward["Special"][11][3]["RewardItem"][1]["Id"] = 183385
	tBossCopy_Reward["Special"][11][3]["RewardItem"][1]["Attr"] = "0 1 3 0 0 0 0 1"
	tBossCopy_Reward["Special"][11][4] = {}
	tBossCopy_Reward["Special"][11][4]["RandomItemChanceType"] = 2
	tBossCopy_Reward["Special"][11][4]["ItemChance"] = 2500
	tBossCopy_Reward["Special"][11][4]["RewardItem"] = {}
	tBossCopy_Reward["Special"][11][4]["RewardItem"][1] = {}
	tBossCopy_Reward["Special"][11][4]["RewardItem"][1]["Id"] = 184385
	tBossCopy_Reward["Special"][11][4]["RewardItem"][1]["Attr"] = "0 1 3 0 0 0 0 1"
	
	-- 4星外套
	tBossCopy_Reward["Special"][12] = {}
	tBossCopy_Reward["Special"][12]["LogId"] = 12000851
	tBossCopy_Reward["Special"][12]["ItemChanceSum"] = 10000
	tBossCopy_Reward["Special"][12][1] = {}
	tBossCopy_Reward["Special"][12][1]["RandomItemChanceType"] = 2
	tBossCopy_Reward["Special"][12][1]["ItemChance"] = 3300
	tBossCopy_Reward["Special"][12][1]["RewardItem"] = {}
	tBossCopy_Reward["Special"][12][1]["RewardItem"][1] = {}
	tBossCopy_Reward["Special"][12][1]["RewardItem"][1]["Id"] = 193225
	tBossCopy_Reward["Special"][12][1]["RewardItem"][1]["Attr"] = "0 1 3 0 0 0 0 1"
	tBossCopy_Reward["Special"][12][2] = {}
	tBossCopy_Reward["Special"][12][2]["RandomItemChanceType"] = 2
	tBossCopy_Reward["Special"][12][2]["ItemChance"] = 3300
	tBossCopy_Reward["Special"][12][2]["RewardItem"] = {}
	tBossCopy_Reward["Special"][12][2]["RewardItem"][1] = {}
	tBossCopy_Reward["Special"][12][2]["RewardItem"][1]["Id"] = 192605
	tBossCopy_Reward["Special"][12][2]["RewardItem"][1]["Attr"] = "0 1 3 0 0 0 0 1"
	tBossCopy_Reward["Special"][12][3] = {}
	tBossCopy_Reward["Special"][12][3]["RandomItemChanceType"] = 2
	tBossCopy_Reward["Special"][12][3]["ItemChance"] = 3400
	tBossCopy_Reward["Special"][12][3]["RewardItem"] = {}
	tBossCopy_Reward["Special"][12][3]["RewardItem"][1] = {}
	tBossCopy_Reward["Special"][12][3]["RewardItem"][1]["Id"] = 188495
	tBossCopy_Reward["Special"][12][3]["RewardItem"][1]["Attr"] = "0 1 3 0 0 0 0 1"
	
	-- 5星外套
	tBossCopy_Reward["Special"][13] = {}
	tBossCopy_Reward["Special"][13]["LogId"] = 12000851
	tBossCopy_Reward["Special"][13]["ItemChanceSum"] = 10000
	tBossCopy_Reward["Special"][13][1] = {}
	tBossCopy_Reward["Special"][13][1]["RandomItemChanceType"] = 2
	tBossCopy_Reward["Special"][13][1]["ItemChance"] = 3334
	tBossCopy_Reward["Special"][13][1]["RewardItem"] = {}
	tBossCopy_Reward["Special"][13][1]["RewardItem"][1] = {}
	tBossCopy_Reward["Special"][13][1]["RewardItem"][1]["Id"] = 193565
	tBossCopy_Reward["Special"][13][1]["RewardItem"][1]["Attr"] = "0 1 3 0 0 0 0 1"
	tBossCopy_Reward["Special"][13][2] = {}
	tBossCopy_Reward["Special"][13][2]["RandomItemChanceType"] = 2
	tBossCopy_Reward["Special"][13][2]["ItemChance"] = 3333
	tBossCopy_Reward["Special"][13][2]["RewardItem"] = {}
	tBossCopy_Reward["Special"][13][2]["RewardItem"][1] = {}
	tBossCopy_Reward["Special"][13][2]["RewardItem"][1]["Id"] = 189065
	tBossCopy_Reward["Special"][13][2]["RewardItem"][1]["Attr"] = "0 1 3 0 0 0 0 1"
	tBossCopy_Reward["Special"][13][3] = {}
	tBossCopy_Reward["Special"][13][3]["RandomItemChanceType"] = 2
	tBossCopy_Reward["Special"][13][3]["ItemChance"] = 3333
	tBossCopy_Reward["Special"][13][3]["RewardItem"] = {}
	tBossCopy_Reward["Special"][13][3]["RewardItem"][1] = {}
	tBossCopy_Reward["Special"][13][3]["RewardItem"][1]["Id"] = 193445
	tBossCopy_Reward["Special"][13][3]["RewardItem"][1]["Attr"] = "0 1 3 0 0 0 0 1"
	
local tBossCopy_Fragment = {}
	-- 3305071 龙珠碎片
	tBossCopy_Fragment[3305071] = {}
	tBossCopy_Fragment[3305071]["RewardItem"] = {}
	tBossCopy_Fragment[3305071]["RewardItem"][1] = {}
	tBossCopy_Fragment[3305071]["RewardItem"][1]["Id"] = 1088000
	tBossCopy_Fragment[3305071]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Fragment[3305071]["DeleteItem"] = {}
	tBossCopy_Fragment[3305071]["DeleteItem"][1] = {}
	tBossCopy_Fragment[3305071]["DeleteItem"][1]["Id"] = 3305071
	tBossCopy_Fragment[3305071]["DeleteItem"][1]["ItemNum"] = 20
	tBossCopy_Fragment[3305071]["LogId"] = 12000851
	tBossCopy_Fragment[3305071]["RewardEffect"] = {}
	tBossCopy_Fragment[3305071]["RewardEffect"]["Effect"] = tBossCopy_Data["Effect"]["OpenPack"]
	
	-- 3305072 宝石精华
	tBossCopy_Fragment[3305072] = {}
	tBossCopy_Fragment[3305072][1] = {}
	tBossCopy_Fragment[3305072][1]["RewardItem"] = {}
	tBossCopy_Fragment[3305072][1]["RewardItem"][1] = {}
	tBossCopy_Fragment[3305072][1]["RewardItem"][1]["Id"] = 700073
	tBossCopy_Fragment[3305072][1]["RewardItem"][1]["Attr"] = "0 1 3"
	tBossCopy_Fragment[3305072][1]["DeleteItem"] = {}
	tBossCopy_Fragment[3305072][1]["DeleteItem"][1] = {}
	tBossCopy_Fragment[3305072][1]["DeleteItem"][1]["Id"] = 3305072
	tBossCopy_Fragment[3305072][1]["DeleteItem"][1]["ItemNum"] = 15
	tBossCopy_Fragment[3305072][1]["LogId"] = 12000851
	
	tBossCopy_Fragment[3305072][2] = {}
	tBossCopy_Fragment[3305072][2]["ItemChanceSum"] = 10000
	tBossCopy_Fragment[3305072][2]["LogId"] = 12000851
	
	tBossCopy_Fragment[3305072][2][1] = {}
	tBossCopy_Fragment[3305072][2][1]["RandomItemChanceType"] = 2
	tBossCopy_Fragment[3305072][2][1]["ItemChance"] = 500
	tBossCopy_Fragment[3305072][2][1]["RewardItem"] = {}
	tBossCopy_Fragment[3305072][2][1]["RewardItem"][1] = {}
	tBossCopy_Fragment[3305072][2][1]["RewardItem"][1]["Id"] = 700013 -- 优质龙恨宝石
	tBossCopy_Fragment[3305072][2][1]["RewardItem"][1]["Attr"] = "0 1 3"
	
	tBossCopy_Fragment[3305072][2][2] = {}
	tBossCopy_Fragment[3305072][2][2]["RandomItemChanceType"] = 2
	tBossCopy_Fragment[3305072][2][2]["ItemChance"] = 500
	tBossCopy_Fragment[3305072][2][2]["RewardItem"] = {}
	tBossCopy_Fragment[3305072][2][2]["RewardItem"][1] = {}
	tBossCopy_Fragment[3305072][2][2]["RewardItem"][1]["Id"] = 700003 -- 优质凤吟宝石
	tBossCopy_Fragment[3305072][2][2]["RewardItem"][1]["Attr"] = "0 1 3"
	
	tBossCopy_Fragment[3305072][2][3] = {}
	tBossCopy_Fragment[3305072][2][3]["RandomItemChanceType"] = 2
	tBossCopy_Fragment[3305072][2][3]["ItemChance"] = 2050
	tBossCopy_Fragment[3305072][2][3]["RewardItem"] = {}
	tBossCopy_Fragment[3305072][2][3]["RewardItem"][1] = {}
	tBossCopy_Fragment[3305072][2][3]["RewardItem"][1]["Id"] = 700023 -- 优质惊鸿宝石
	tBossCopy_Fragment[3305072][2][3]["RewardItem"][1]["Attr"] = "0 1 3"
	
	tBossCopy_Fragment[3305072][2][4] = {}
	tBossCopy_Fragment[3305072][2][4]["RandomItemChanceType"] = 2
	tBossCopy_Fragment[3305072][2][4]["ItemChance"] = 2050
	tBossCopy_Fragment[3305072][2][4]["RewardItem"] = {}
	tBossCopy_Fragment[3305072][2][4]["RewardItem"][1] = {}
	tBossCopy_Fragment[3305072][2][4]["RewardItem"][1]["Id"] = 700033 -- 优质青虹宝石
	tBossCopy_Fragment[3305072][2][4]["RewardItem"][1]["Attr"] = "0 1 3"
	
	tBossCopy_Fragment[3305072][2][5] = {}
	tBossCopy_Fragment[3305072][2][5]["RandomItemChanceType"] = 2
	tBossCopy_Fragment[3305072][2][5]["ItemChance"] = 2050
	tBossCopy_Fragment[3305072][2][5]["RewardItem"] = {}
	tBossCopy_Fragment[3305072][2][5]["RewardItem"][1] = {}
	tBossCopy_Fragment[3305072][2][5]["RewardItem"][1]["Id"] = 700053 -- 优质紫霞宝石
	tBossCopy_Fragment[3305072][2][5]["RewardItem"][1]["Attr"] = "0 1 3"
	
	tBossCopy_Fragment[3305072][2][6] = {}
	tBossCopy_Fragment[3305072][2][6]["RandomItemChanceType"] = 2
	tBossCopy_Fragment[3305072][2][6]["ItemChance"] = 2050
	tBossCopy_Fragment[3305072][2][6]["RewardItem"] = {}
	tBossCopy_Fragment[3305072][2][6]["RewardItem"][1] = {}
	tBossCopy_Fragment[3305072][2][6]["RewardItem"][1]["Id"] = 700063 -- 优质明月宝石
	tBossCopy_Fragment[3305072][2][6]["RewardItem"][1]["Attr"] = "0 1 3"
	
	tBossCopy_Fragment[3305072][2][7] = {}
	tBossCopy_Fragment[3305072][2][7]["RandomItemChanceType"] = 2
	tBossCopy_Fragment[3305072][2][7]["ItemChance"] = 400
	tBossCopy_Fragment[3305072][2][7]["RewardItem"] = {}
	tBossCopy_Fragment[3305072][2][7]["RewardItem"][1] = {}
	tBossCopy_Fragment[3305072][2][7]["RewardItem"][1]["Id"] = 700123 -- 优质天怒宝石
	tBossCopy_Fragment[3305072][2][7]["RewardItem"][1]["Attr"] = "0 1 3"
	
	tBossCopy_Fragment[3305072][2][8] = {}
	tBossCopy_Fragment[3305072][2][8]["RandomItemChanceType"] = 2
	tBossCopy_Fragment[3305072][2][8]["ItemChance"] = 400
	tBossCopy_Fragment[3305072][2][8]["RewardItem"] = {}
	tBossCopy_Fragment[3305072][2][8]["RewardItem"][1] = {}
	tBossCopy_Fragment[3305072][2][8]["RewardItem"][1]["Id"] = 700103 -- 优质地灵宝石
	tBossCopy_Fragment[3305072][2][8]["RewardItem"][1]["Attr"] = "0 1 3"
	
	-- 3305073 流星卷碎片
	tBossCopy_Fragment[3305073] = {}
	tBossCopy_Fragment[3305073]["RewardItem"] = {}
	tBossCopy_Fragment[3305073]["RewardItem"][1] = {}
	tBossCopy_Fragment[3305073]["RewardItem"][1]["Id"] = 3006277
	tBossCopy_Fragment[3305073]["RewardItem"][1]["Attr"] = "0 1"
	tBossCopy_Fragment[3305073]["DeleteItem"] = {}
	tBossCopy_Fragment[3305073]["DeleteItem"][1] = {}
	tBossCopy_Fragment[3305073]["DeleteItem"][1]["Id"] = 3305073
	tBossCopy_Fragment[3305073]["DeleteItem"][1]["ItemNum"] = 10
	tBossCopy_Fragment[3305073]["LogId"] = 12000851
	tBossCopy_Fragment[3305073]["RewardEffect"] = {}
	tBossCopy_Fragment[3305073]["RewardEffect"]["Effect"] = tBossCopy_Data["Effect"]["OpenPack"]
	
--------------------------------------物品逻辑-------------------------------------------
-- 判断职业索引
function BossCopy_JudgePro()
	local nPro = Get_UserProfession()
	local nIndex = 0
	for i,v in pairs(tBossCopy_Data["Pro"]) do
		if i ~= 8 then
			if nPro >= tBossCopy_Data["Pro"][i][1] and nPro <= tBossCopy_Data["Pro"][i][2] then
				nIndex = i
			end
		elseif (nPro >= tBossCopy_Data["Pro"][i][1][1] and nPro <= tBossCopy_Data["Pro"][i][1][2]) or (nPro >= tBossCopy_Data["Pro"][i][2][1] and nPro <= tBossCopy_Data["Pro"][i][2][2]) or (nPro >= tBossCopy_Data["Pro"][i][3][1] and nPro <= tBossCopy_Data["Pro"][i][3][2]) then
			nIndex = i
		end
	end
	
	return nIndex
end

-- 判断玩家等级
function BossCopy_JudgeLevel()
	local nNowUserId = Get_UserId()
	local nUserLev = Get_UserLevel(nNowUserId)
	local nCount = 0
	
	for i,v in pairs(tBossCopy_Data["Crisis"]) do
		if nUserLev < tBossCopy_Data["Crisis"][i] then
			nCount = i
			break
		end
	end
	
	return nCount
end

-- 3305072 宝石精华
function BossCopy_MeteorEssence(nItemId,nIndex)
	local nNum = tBossCopy_Fragment[nItemId][1]["DeleteItem"][1]["ItemNum"]
	if not Item_ChkMulItem(nItemId,nItemId,nNum) then
		Sys_MsgBox(tBossCopy_Text[nItemId]["NoGemsNum"])
		return
	end
	
	local nSpace = RewardTemplate_GetRewardSpace(tBossCopy_Fragment[nItemId][1])
	if not User_CheckLeftSpace(nSpace) then
		Sys_MsgBox(tBossCopy_Text[nItemId]["NoSpace"])
		return
	end
	
	if nIndex == 1 then
		RewardTemplate_UseItemAndMsg(tBossCopy_Fragment[nItemId][1])
	elseif nIndex == 2 then
		if Item_DelMulItem(nItemId,nItemId,nNum) then
			local sDelLog = string.format(tBossCopy_Data["DelLog"],nItemId)
			RewardTemplate_NewRandom(tBossCopy_Fragment[nItemId],2)
			User_EffectAdd("self",tBossCopy_Data["Effect"]["OpenPack"])
			Sys_SaveActionRewardLog(sDelLog)
		end
	end
end

--------------------------------------npc逻辑-------------------------------------------

-- 扫荡魔头
function BossCopy_Clear(nNpcId)
	-- stc(165,59) 记录玩家每天扫荡情况
	local nClearEventType = tBossCopy_Data["Stc"]["Clear"]["EventType"]
	local nClearDataType = tBossCopy_Data["Stc"]["Clear"]["DataType"]
	local nClearComplete = tBossCopy_Data["Stc"]["Clear"]["Complete"]
	-- 隔天
	Task_StcReset(nClearEventType,nClearDataType)
	if Task_ChkStcValue(nClearEventType,nClearDataType,">=",nClearComplete) then
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end
	
	LinkNpcGossipFunc_New(nNpcId,"2-4")
end

-- 确定扫荡
function BossCopy_ConfirmToClear(nNpcId)
	-- 【判断掩码】
	-- stc(165,59) 记录玩家每天扫荡情况
	local nClearEventType = tBossCopy_Data["Stc"]["Clear"]["EventType"]
	local nClearDataType = tBossCopy_Data["Stc"]["Clear"]["DataType"]
	local nClearComplete = tBossCopy_Data["Stc"]["Clear"]["Complete"]
	-- 隔天
	Task_StcReset(nClearEventType,nClearDataType)
	if Task_ChkStcValue(nClearEventType,nClearDataType,">=",nClearComplete) then
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end
	
	-- 【判断等级】
	local nCount = BossCopy_JudgeLevel()
	if nCount < 4 then
		return
	end
	
	-- 【判断背包】
	local nSpace = tBossCopy_Data["Space"][nCount]
	if not User_CheckLeftSpace(nSpace) then
		tNpcGossip[nNpcId]["Text331"] = string.format(tBossCopy_Text[nNpcId]["Text331"],nSpace)
		LinkNpcGossipFunc_New(nNpcId,"3-3")
		return
	end
	
	---------------------------------------- 给奖
	
	-- 打掩码
	-- stc(165,59) 记录玩家每天扫荡情况
	Task_SetStatistic(nClearEventType,nClearDataType,1,1)
	Task_SetStcTimestamp(nClearEventType,nClearDataType,0)
	for i = 1,nCount-3 do
		RewardTemplate_UseItemAndMsg(tBossCopy_Reward["Basic"][i])
	end
	User_EffectAdd("self",tBossCopy_Data["Effect"]["OpenPack"])
end

-- 【选项 挑战魔头（%d/3）】
function BossCopy_Challenge(nNpcId)
	-- 【判断等级】
	local nNowUserId = Get_UserId()
	local nUserLev = Get_UserLevel(nNowUserId)
	local nLevel = tBossCopy_Data["Level"]
	if nUserLev < nLevel then
		LinkNpcGossipFunc_New(nNpcId,"1-1")
		return
	end
		
	-- 【挑战情况】
	-- stc(165,58) 记录玩家每天挑战魔头的情况
	local nEventType = tBossCopy_Data["Stc"]["Daily"]["EventType"]
	local nDataType = tBossCopy_Data["Stc"]["Daily"]["DataType"]
	-- 隔天
	Task_StcReset(nEventType,nDataType)
	-- 判断
	local nUserValue = Get_UserStatisticValue(nEventType,nDataType)
	local nIndex = 0
	for i = 1,13 do
		if Sys_ParseNumbersContain(tBossCopy_Binary[i],nUserValue) then
			nIndex = nIndex + 1
		end
	end
	if nIndex >= 3 then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	LinkNpcGossipFunc_New(nNpcId,"2-2")
end

-- %d级魔头（%d/1）
function BossCopy_Choose(nNpcId,nIndex)
	-- 【判断等级】
	local nNowUserId = Get_UserId()
	local nUserLev = Get_UserLevel(nNowUserId)
	local nLevel = tBossCopy_Data["Level"]
	local nMonsterLevel = tBossCopy_Data["Boss"][nIndex]
	if nUserLev < nLevel then
		LinkNpcGossipFunc_New(nNpcId,"1-1")
		return
	end
	if nUserLev < nMonsterLevel then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	-- 【是否挑战】
	-- stc(165,58) 记录玩家每天挑战魔头的情况
	local nEventType = tBossCopy_Data["Stc"]["Daily"]["EventType"]
	local nDataType = tBossCopy_Data["Stc"]["Daily"]["DataType"]
	-- 隔天
	Task_StcReset(nEventType,nDataType)
	-- 判断
	local nUserValue = Get_UserStatisticValue(nEventType,nDataType)
	if Sys_ParseNumbersContain(tBossCopy_Binary[nIndex],nUserValue) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	tNpcGossip[nNpcId]["Text321"] = string.format(tBossCopy_Text[nNpcId]["Text321"],nMonsterLevel)
	tNpcGossip[nNpcId]["Text323"] = string.format(tBossCopy_Text[nNpcId]["Text323"],nMonsterLevel)
	tNpcGossip[nNpcId]["Text324"] = string.format(tBossCopy_Text[nNpcId]["Text324"],tBossCopy_Text["Monster"][nIndex]["Pass"])
	tNpcGossip[nNpcId]["Text325"] = string.format(tBossCopy_Text[nNpcId]["Text325"],tBossCopy_Text["Monster"][nIndex]["Drop"])
	tNpcGossip[nNpcId]["OptionFunc321"] = "BossCopy_ComfirmToChallenge</N>22084</N>" .. nIndex
	-- 【是否为开服前3日】
	local nGlobalId = tBossCopy_Data["GlobalId"]["Silver"]
	local nData = Get_SysDynaGlobalData1(nGlobalId)
	if nMonsterLevel >= tBossCopy_Data["Boss"][11] then
		if nData ~= 0 then
			tNpcGossip[nNpcId]["Text326"] = tBossCopy_Text["Monster"][nIndex]["Special"]
		else
			tNpcGossip[nNpcId]["Text326"] = ""
		end
	end
	LinkNpcGossipFunc_New(nNpcId,"3-2")
end

-- 确认挑战
function BossCopy_ComfirmToChallenge(nNpcId,nIndex)
	-- 【判断等级】
	local nNowUserId = Get_UserId()
	local nUserLev = Get_UserLevel(nNowUserId)
	local nLevel = tBossCopy_Data["Level"]
	local nMonsterLevel = tBossCopy_Data["Boss"][nIndex]
	if nUserLev < nLevel then
		LinkNpcGossipFunc_New(nNpcId,"1-1")
		return
	end
	if nUserLev < nMonsterLevel then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	-- 【是否挑战】
	-- stc(165,58) 记录玩家每天挑战魔头的情况
	local nEventType = tBossCopy_Data["Stc"]["Daily"]["EventType"]
	local nDataType = tBossCopy_Data["Stc"]["Daily"]["DataType"]
	-- 隔天
	Task_StcReset(nEventType,nDataType)
	-- 判断
	local nUserValue = Get_UserStatisticValue(nEventType,nDataType)
	if Sys_ParseNumbersContain(tBossCopy_Binary[nIndex],nUserValue) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	-- 【是否组队】
	if Get_UserTeamNumbers(nNowUserId) > 0 then
		User_TalkChannel2005(tBossCopy_Text["Msg"]["Team"])
		return
	end
	
	-- 【进入副本】
	-- stc(167,08) 记录玩家选择的魔头
	local nMonsterEventType = tBossCopy_Data["Stc"]["Monster"]["EventType"]
	local nMonsterDataType = tBossCopy_Data["Stc"]["Monster"]["DataType"]
	Task_SetStatistic(nMonsterEventType,nMonsterDataType,nIndex,1)
	User_EnterInstance(tBossCopy_Data["Instance"])
	User_TalkChannel2005(string.format(tBossCopy_Text["Msg"]["EnterInstance"],nMonsterLevel))
	BossCopy_Create(nNpcId)
end

-- 创建dynanpc 秘境守护黑龙
function BossCopy_Create(nNpcId)
	local nUserId = Get_UserId()
	local nMapId =  Get_UserMapId(nUserId)
	local sName = tBossCopy_Text["Npc"]["Name"][1]
	local nPosX = tBossCopy_Data["Location"]["Instance"]["PosX"]
	local nPosY = tBossCopy_Data["Location"]["Instance"]["PosY"]
	local nTask0 = tBossCopy_Data["Task0"][1]
	local nNpcFace = tBossCopy_Data["NpcFace"][1]
	Npc_CreateDynaNpc(sName,2,1,nNpcFace,0,nUserId,nMapId,nPosX,nPosY,0,0,0,nTask0)
end

-- 22096 秘境守护黑龙 主对白
function BossCopy_Guard(nNpcId)
	-- stc(167,08) 记录玩家选择的魔头
	local nEventType = tBossCopy_Data["Stc"]["Monster"]["EventType"]
	local nDataType = tBossCopy_Data["Stc"]["Monster"]["DataType"]
	local nValue = Get_UserStatisticValue(nEventType,nDataType)
	local nMonsterLevel = tBossCopy_Data["Boss"][nValue]
	tNpcGossip[nNpcId]["Text111"] = string.format(tBossCopy_Text[nNpcId]["Text111"],nMonsterLevel)
	tNpcGossip[nNpcId]["OptionFunc1"] = "BossCopy_StartToChallenge</N>22096</N>" .. nValue
	LinkNpcGossipFunc_New(nNpcId,"1-1")
end

-- 开始挑战
function BossCopy_StartToChallenge(nNpcId,nIndex)
	-- 删除动态npc
	local nUserId = Get_UserId()
	local nMapId =  Get_UserMapId(nUserId)
	local sNpcName = tBossCopy_Text["Npc"]["Name"][1]
	Npc_DelDynaNpc(nMapId,"name",sNpcName)
	
	-- 刷怪
	local nPosX = tBossCopy_Data["Location"]["Instance"]["PosX"]
	local nPosY = tBossCopy_Data["Location"]["Instance"]["PosY"]
	local nGenId = tBossCopy_Data["GenId"]
	local nMonsterId = tBossCopy_Data["MonsterId"][nIndex]
	Monster_AddMonster(nMapId,nPosX,nPosY,nGenId,nMonsterId)
end

-- 22085 【魔头挑战】奖励宝箱
function BossCopy_Box(nNpcId)
	-- 【判断是否领奖】
	-- stc(167,08) 记录玩家选择的魔头
	local nMonsterEventType = tBossCopy_Data["Stc"]["Monster"]["EventType"]
	local nMonsterDataType = tBossCopy_Data["Stc"]["Monster"]["DataType"]
	local nMonsterValue = Get_UserStatisticValue(nMonsterEventType,nMonsterDataType)
	-- stc(165,58) 记录玩家每天挑战魔头的情况
	local nDailyEventType = tBossCopy_Data["Stc"]["Daily"]["EventType"]
	local nDailyDataType = tBossCopy_Data["Stc"]["Daily"]["DataType"]
	Task_StcReset(nDailyEventType,nDailyDataType)
	local nDailyValue = Get_UserStatisticValue(nDailyEventType,nDailyDataType)
	if Sys_ParseNumbersContain(tBossCopy_Binary[nMonsterValue],nDailyValue) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	-- 通关奖励
	tNpcGossip[nNpcId]["Text113"] = string.format(tBossCopy_Text[nNpcId]["Text113"],tBossCopy_Data["Boss"][nMonsterValue])
	tNpcGossip[nNpcId]["Text114"] = string.format(tBossCopy_Text[nNpcId]["Text114"],tBossCopy_Text["Monster"][nMonsterValue]["Pass"])
	tNpcGossip[nNpcId]["Text1-1"] = {111,112,113,114}
	
	-- 惊喜奖励
	-- stc(167,42) 记录玩家首通情况
	local nFirstEventType = tBossCopy_Data["Stc"]["First"]["EventType"]
	local nFirstDataType = tBossCopy_Data["Stc"]["First"]["DataType"]
	local nFirstValue = Get_UserStatisticValue(nFirstEventType,nFirstDataType)
	if not Sys_ParseNumbersContain(tBossCopy_Binary[nMonsterValue],nFirstValue) then
		tNpcGossip[nNpcId]["Text115"] = tBossCopy_Text["Monster"][nMonsterValue]["First"]
		table.insert(tNpcGossip[nNpcId]["Text1-1"],115)
	end
	
	-- 特别奖励
	-- 是否为开服前3日
	local nGlobalId = tBossCopy_Data["GlobalId"]["Silver"]
	local nData = Get_SysDynaGlobalData1(nGlobalId)
	if nMonsterValue >= tBossCopy_Data["AwardLevel"] then
		if nData ~= 0 then
			tNpcGossip[nNpcId]["Text116"] = tBossCopy_Text["Monster"][nMonsterValue]["Special"]
			table.insert(tNpcGossip[nNpcId]["Text1-1"],116)
		end
	end
	
	table.insert(tNpcGossip[nNpcId]["Text1-1"],117)
	-- table.insert(tNpcGossip[nNpcId]["Text1-1"],118)
	-- tNpcGossip[nNpcId]["OptionFunc111"] = "BossCopy_Award</N>" .. nNpcId .. "</N>" .. 2
	tNpcGossip[nNpcId]["OptionFunc112"] = "BossCopy_Award</N>" .. nNpcId .. "</N>" .. 1
	LinkNpcGossipFunc_New(nNpcId,"1-1")
end

-- 领奖
function BossCopy_Award(nNpcId,nWay)
	-- 【判断是否领奖】
	-- stc(167,08) 记录玩家选择的魔头
	local nMonsterEventType = tBossCopy_Data["Stc"]["Monster"]["EventType"]
	local nMonsterDataType = tBossCopy_Data["Stc"]["Monster"]["DataType"]
	local nMonsterValue = Get_UserStatisticValue(nMonsterEventType,nMonsterDataType)
	-- stc(165,58) 记录玩家每天挑战魔头的情况
	local nDailyEventType = tBossCopy_Data["Stc"]["Daily"]["EventType"]
	local nDailyDataType = tBossCopy_Data["Stc"]["Daily"]["DataType"]
	Task_StcReset(nDailyEventType,nDailyDataType)
	local nDailyValue = Get_UserStatisticValue(nDailyEventType,nDailyDataType)
	if Sys_ParseNumbersContain(tBossCopy_Binary[nMonsterValue],nDailyValue) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	local tAward = tBossCopy_Reward["Basic"]
	local nNeedMoney = tBossCopy_Data["NeedMoney"]
	if nWay == 2 then
		-- 【判断银两】
		if not User_CanPutMoney2Bag(-nNeedMoney) then
			Sys_MsgBox(tBossCopy_Text["Msg"]["MoneyNotEnough"])
			return
		end
		
		tAward = tBossCopy_Reward["Double"]
	end
	
	-- 【判断背包】
	local nSpace = RewardTemplate_GetRewardSpace(tAward[nMonsterValue])
	
	-- stc(167,42) 记录玩家首通情况
	local nFirstEventType = tBossCopy_Data["Stc"]["First"]["EventType"]
	local nFirstDataType = tBossCopy_Data["Stc"]["First"]["DataType"]
	local nFirstValue = Get_UserStatisticValue(nFirstEventType,nFirstDataType)
	local nProIndex = BossCopy_JudgePro()
	if not Sys_ParseNumbersContain(tBossCopy_Binary[nMonsterValue],nFirstValue) then
		if nMonsterValue >= 9 then
			nSpace = nSpace + RewardTemplate_GetRewardSpace(tBossCopy_Reward["First"][nMonsterValue])
		else
			nSpace = nSpace + RewardTemplate_GetRewardSpace(tBossCopy_Reward["First"][nMonsterValue][nProIndex])
		end
	end
	
	-- 是否为开服前3日
	local nGlobalId = tBossCopy_Data["GlobalId"]["Silver"]
	local nData = Get_SysDynaGlobalData1(nGlobalId)
	if nMonsterValue >= tBossCopy_Data["AwardLevel"] then
		if nData ~= 0 then
			nSpace = nSpace + RewardTemplate_GetRandomSpace(tBossCopy_Reward["Special"],nMonsterValue)
		end
	end
	
	if not User_CheckLeftSpace(nSpace) then
		local sMsg = string.format(tBossCopy_Text["Msg"]["NoSpace"],nSpace)
		Sys_MsgBox(sMsg)
		return
	end
	
	---------------------------------------- 给奖
	if nWay == 2 then
		User_AddMoney(-nNeedMoney)
	end
	-- 打掩码
	-- stc(167,42) 记录玩家首通情况
	if not Sys_ParseNumbersContain(tBossCopy_Binary[nMonsterValue],nFirstValue) then
		Task_AddStatistic(nFirstEventType,nFirstDataType,tBossCopy_Binary[nMonsterValue],1)
		local tFirstReward = tBossCopy_Reward["First"][nMonsterValue][nProIndex]
		RewardTemplate_UseItemAndMsg(tFirstReward)
	end
	-- stc(165,58) 记录玩家每天挑战魔头的情况
	if not Sys_ParseNumbersContain(tBossCopy_Binary[nMonsterValue],nDailyValue) then
		Task_AddStatistic(nDailyEventType,nDailyDataType,tBossCopy_Binary[nMonsterValue],1)
		RewardTemplate_UseItemAndMsg(tAward[nMonsterValue])
	end
	-- 是否为开服前3日
	if nMonsterValue >= tBossCopy_Data["AwardLevel"] then
		if nData ~= 0 then
			RewardTemplate_NewRandom(tBossCopy_Reward["Special"],nMonsterValue)
		end
	end
	User_EffectAdd("self",tBossCopy_Data["Effect"]["OpenPack"])
	BossCopy_Leave()
end

-- 离开
function BossCopy_Leave()
	local nMapId = tBossCopy_Data["Location"]["Back"]["MapId"]
	local nBoundX = tBossCopy_Data["Location"]["Back"]["PosX"]
	local nBoundY = tBossCopy_Data["Location"]["Back"]["PosY"]
	User_UserRandBoundTrans(nMapId,nBoundX,nBoundY,5,5,1)
	User_TalkChannel2005(tBossCopy_Text["Msg"]["Leave"])
end
--------------------------------------陷阱逻辑-------------------------------------------
function tBossCopy_Trap()
	Sys_MsgBox(tBossCopy_Text["Msg"]["WannaLeave"],"BossCopy_Leave")
end
--------------------------------------怪物逻辑-------------------------------------------
function BossCopy_MonsterDeath()
	-- 怪物掉落
	-- stc(167,08) 记录玩家选择的魔头
	local nMonsterEventType = tBossCopy_Data["Stc"]["Monster"]["EventType"]
	local nMonsterDataType = tBossCopy_Data["Stc"]["Monster"]["DataType"]
	local nMonsterValue = Get_UserStatisticValue(nMonsterEventType,nMonsterDataType)
	-- stc(171,02) 记录每天每个怪物掉落情况
	local nDropEventType = tBossCopy_Data["Stc"]["Drop"]["EventType"]
	local nDropDataType = tBossCopy_Data["Stc"]["Drop"]["DataType"]
	Task_StcReset(nDropEventType,nDropDataType)
	local nDropValue = Get_UserStatisticValue(nDropEventType,nDropDataType)
	if not Sys_ParseNumbersContain(tBossCopy_Binary[nMonsterValue],nDropValue) then
		Task_AddStatistic(nDropEventType,nDropDataType,tBossCopy_Binary[nMonsterValue],1)
		for i = 1,8 do
			local nFlat,tAward = Probabil_RandomAward(tBossCopy_MonsterDrop,nMonsterValue)
			local nItemId = tAward[1]["tAward"][1]["Item_1"]
			Monster_SysDropItem(nItemId)
		end
	end
	
	-- 刷奖励宝箱
	local nUserId = Get_UserId()
	local nMapId =  Get_UserMapId(nUserId)
	local sName = tBossCopy_Text["Npc"]["Name"][2]
	local nPosX = tBossCopy_Data["Location"]["Box"]["PosX"]
	local nPosY = tBossCopy_Data["Location"]["Box"]["PosY"]
	local nTask0 = tBossCopy_Data["Task0"][2]
	local nNpcFace = tBossCopy_Data["NpcFace"][2]
	Npc_CreateDynaNpc(sName,2,1,nNpcFace,0,nUserId,nMapId,nPosX,nPosY,0,0,0,nTask0)
end
--------------------------------------时间自检-------------------------------------------
function BossCopy_Reset()
	local nGlobalId = tBossCopy_Data["GlobalId"]["Silver"]
	local nData0 = Get_SysDynaGlobalData0(nGlobalId)
	local nData1 = Get_SysDynaGlobalData1(nGlobalId)
	
	-- 判断是否是金币服
	if nData0 == 0 then
		return
	end
	
	-- 判断是否是开服前3日
	if nData1 <= 0 then
		return
	end
	
	-- 操作
	Sys_SetSynaGlobalData1(nGlobalId,nData1-1)
end
--------------------------------------npc配置-------------------------------------------
-- 22084 【魔头挑战】秘境传送大使
tNpcFace[4997] = 210
tNpcGossip[22084] = tNpcGossip[22084] or DefaultNpc:new{}
tNpcGossip[22084]["OptionHidden"] = 1
tNpcGossip[22084]["DialogueText"] = tBossCopy_Text[22084]

-- 等级不满足条件
tNpcGossip[22084]["Text1-1"] = {111,112,113,114,115}
tNpcGossip[22084]["tOption1-1"] = {1}
tNpcGossip[22084]["ChkFunc1-1"] = function()
	local nNowUserId = Get_UserId()
	local nUserLev = Get_UserLevel(nNowUserId)
	local nLevel = tBossCopy_Data["Level"]
	if nUserLev < nLevel then
		return true
	end
	return false
end

-- 等级满足条件
tNpcGossip[22084]["Text1-2"] = {111,112,113,114,115}
tNpcGossip[22084]["tOption1-2"] = {2,3}
tNpcGossip[22084]["ChkFunc1-2"] = function()
	local nNowUserId = Get_UserId()
	local nUserLev = Get_UserLevel(nNowUserId)
	local nLevel = tBossCopy_Data["Level"]
	if nUserLev >= nLevel then
		-- 【选项 挑战魔头（%d/3）】
		-- stc(165,58) 记录玩家每天挑战魔头的情况
		local nEventType = tBossCopy_Data["Stc"]["Daily"]["EventType"]
		local nDataType = tBossCopy_Data["Stc"]["Daily"]["DataType"]
		-- 隔天
		Task_StcReset(nEventType,nDataType)
		-- 判断
		local nUserValue = Get_UserStatisticValue(nEventType,nDataType)
		local nIndex = 0
		for i = 1,13 do
			if Sys_ParseNumbersContain(tBossCopy_Binary[i],nUserValue) then
				nIndex = nIndex + 1
			end
		end
		tNpcGossip[22084]["Option2"] = string.format(tBossCopy_Text[22084]["Option2"],nIndex)
		
		-- 【选项 扫荡魔头%s】
		-- stc(165,59) 记录玩家每天扫荡情况
		local nClearEventType = tBossCopy_Data["Stc"]["Clear"]["EventType"]
		local nClearDataType = tBossCopy_Data["Stc"]["Clear"]["DataType"]
		local nClearComplete = tBossCopy_Data["Stc"]["Clear"]["Complete"]
		-- 隔天
		Task_StcReset(nClearEventType,nClearDataType)
		-- 选项文字
		if Task_ChkStcValue(nClearEventType,nClearDataType,">=",nClearComplete) then
			tNpcGossip[22084]["Option3"] = string.format(tBossCopy_Text[22084]["Option3"],tBossCopy_Text["Msg"]["Option"])
		else
			tNpcGossip[22084]["Option3"] = string.format(tBossCopy_Text[22084]["Option3"],tBossCopy_Text["Msg"]["NotYet"])
		end
		-- 选项显示
		local nCount = BossCopy_JudgeLevel()
		if nCount >= 4 then
			tNpcGossip[22084]["tOption1-2"] = {2,3}
		else
			tNpcGossip[22084]["tOption1-2"] = {2}
		end
		
		return true
	end
	
	return false
end
tNpcGossip[22084]["OptionFunc2"] = "BossCopy_Challenge</N>22084"
tNpcGossip[22084]["OptionFunc3"] = "BossCopy_Clear</N>22084"

-- 接1，玩家今日已挑战了3次
tNpcGossip[22084]["Text2-1"] = {211}
tNpcGossip[22084]["tOption2-1"] = {211}

-- 接1，玩家今日未挑战过
tNpcGossip[22084]["Text2-2"] = {221}
tNpcGossip[22084]["tOption2-2"] = {221,222,223,224}
tNpcGossip[22084]["ChkFunc2-2"] = function()
	-- 【对白】
	-- stc(165,58) 记录玩家每天挑战魔头的情况
	local nEventType = tBossCopy_Data["Stc"]["Daily"]["EventType"]
	local nDataType = tBossCopy_Data["Stc"]["Daily"]["DataType"]
	-- 隔天
	Task_StcReset(nEventType,nDataType)
	-- 判断
	local nUserValue = Get_UserStatisticValue(nEventType,nDataType)
	local tBoss = {}
	local sStr = ""
	local sMonster = ""
	for i = 1,13 do
		if Sys_ParseNumbersContain(tBossCopy_Binary[i],nUserValue) then
			table.insert(tBoss,tBossCopy_Data["Boss"][i])
		end
	end
	-- 今日未挑战过
	if next(tBoss) == nil then
		tNpcGossip[22084]["Text221"] = string.format(tBossCopy_Text[22084]["Text221"],tBossCopy_Text["Msg"]["None"])
	elseif #tBoss == 1 then
		sStr = string.format(tBossCopy_Text["Msg"]["Monster"],tBoss[1])
		tNpcGossip[22084]["Text221"] = string.format(tBossCopy_Text[22084]["Text221"],sStr)
	else
		for i = 1,#tBoss-1 do
			sMonster = sMonster .. string.format(tBossCopy_Text["Msg"]["Monster"],tBoss[i]) .. tBossCopy_Text["Msg"]["Comma"]
		end
		sMonster = sMonster .. string.format(tBossCopy_Text["Msg"]["Monster"],tBoss[#tBoss])
		tNpcGossip[22084]["Text221"] = string.format(tBossCopy_Text[22084]["Text221"],sMonster)
	end
	
	-- 【选项】
	tNpcGossip[22084]["tOption2-2"] = {}
	local nNowUserId = Get_UserId()
	local nUserLev = Get_UserLevel(nNowUserId)
	local nLevel = tBossCopy_Data["Level"]
	if nUserLev < nLevel then
		return false
	end
	for i,v in pairs(tBossCopy_Data["Crisis"]) do
		if nUserLev < tBossCopy_Data["Crisis"][i] then
			local nCount = 1
			for j = i,1,-1 do
				if Sys_ParseNumbersContain(tBossCopy_Binary[j],nUserValue) then
					tNpcGossip[22084]["Option22" .. nCount] = string.format(tBossCopy_Text[22084]["Option22" .. nCount],tBossCopy_Data["Boss"][j],1)
				else
					tNpcGossip[22084]["Option22" .. nCount] = string.format(tBossCopy_Text[22084]["Option22" .. nCount],tBossCopy_Data["Boss"][j],0)
				end
				tNpcGossip[22084]["OptionFunc22" .. nCount] = "BossCopy_Choose</N>22084</N>" .. j
				table.insert(tNpcGossip[22084]["tOption2-2"],220+nCount)
				
				nCount = nCount + 1
				if nCount == 4 then
					break
				end
			end
			
			table.insert(tNpcGossip[22084]["tOption2-2"],224)
			break
		end
	end
	
	return true
end

-- 玩家已挑战过本级魔头
tNpcGossip[22084]["Text3-1"] = {311}
tNpcGossip[22084]["tOption3-1"] = {311}
tNpcGossip[22084]["OptionPoint311"] = "2-2"

-- 玩家未挑战过本级魔头
tNpcGossip[22084]["Text3-2"] = {321,322,323,324,325,326,327}
tNpcGossip[22084]["tOption3-2"] = {321,322}
tNpcGossip[22084]["OptionPoint322"] = "2-2"

-- 接2，玩家今日已扫荡过
tNpcGossip[22084]["Text2-3"] = {231}
tNpcGossip[22084]["tOption2-3"] = {231}

-- 接2，玩家今日未扫荡过
tNpcGossip[22084]["Text2-4"] = {241,242,243,2411,2412,2413,2414,2415,2416,2417,2418,2419,2420,2421,2422,244}
tNpcGossip[22084]["tOption2-4"] = {241,242}
tNpcGossip[22084]["ChkFunc2-4"] = function()
	local nCount = BossCopy_JudgeLevel()
	local nDialog = 11
	
	if nCount >= 4 then
		tNpcGossip[22084]["Text243"] = string.format(tBossCopy_Text[22084]["Text243"],tBossCopy_Data["Boss"][1],tBossCopy_Data["Boss"][nCount-3])
		for i = 1,nCount-3 do
			tNpcGossip[22084]["Text24" .. nDialog] = string.format(tBossCopy_Text["Msg"]["CleanUp"],tBossCopy_Data["Boss"][i],tBossCopy_Text["Monster"][i]["Pass"])
			nDialog = nDialog + 1
		end
		
		if nCount == 4 then
			tNpcGossip[22084]["Text243"] = tBossCopy_Text["Msg"]["JustOne"]
		end
		
		return true
	end
	
	return false
end
tNpcGossip[22084]["OptionFunc241"] = "BossCopy_ConfirmToClear</N>22084"

-- 接2-1，银两充足，背包空间不足
tNpcGossip[22084]["Text3-3"] = {331}
tNpcGossip[22084]["tOption3-3"] = {331}

-- 22096 秘境守护黑龙
tNpcFace[5766] = 32
tNpcGossip[22096] = tNpcGossip[22096] or DefaultNpc:new{}
tNpcGossip[22096]["OptionHidden"] = 1
tNpcGossip[22096]["DialogueText"] = tBossCopy_Text[22096]

tNpcGossip[22096]["Text1-1"] = {111}
tNpcGossip[22096]["tOption1-1"] = {1}

-- 22085 【魔头挑战】奖励宝箱
tNpcFace[4998] = 849
tNpcGossip[22085] = tNpcGossip[22085] or DefaultNpc:new{}
tNpcGossip[22085]["OptionHidden"] = 1
tNpcGossip[22085]["DialogueText"] = tBossCopy_Text[22085]

-- tNpcGossip[22085]["Text1-1"] = {111,112,113,114,115,116,117,118}
tNpcGossip[22085]["Text1-1"] = {111,112,113,114,115,116,117}
-- tNpcGossip[22085]["tOption1-1"] = {111,112}
tNpcGossip[22085]["tOption1-1"] = {112}

tNpcGossip[22085]["Text1-2"] = {121}
tNpcGossip[22085]["tOption1-2"] = {121}
tNpcGossip[22085]["OptionFunc121"] = "BossCopy_Leave"
--------------------------------------物品配置-------------------------------------------
-- 一般礼包
tItem[3305059] = tItem[3305059] or {}
tItem[3305060] = tItem[3305059] or {}
tItem[3305061] = tItem[3305059] or {}
tItem[3305062] = tItem[3305059] or {}
tItem[3305063] = tItem[3305059] or {}
tItem[3305064] = tItem[3305059] or {}
tItem[3305065] = tItem[3305059] or {}
tItem[3305066] = tItem[3305059] or {}
tItem[3305067] = tItem[3305059] or {}
tItem[3305068] = tItem[3305059] or {}
tItem[3305069] = tItem[3305059] or {}
tItem[3305070] = tItem[3305059] or {}

tItem[3305115] = tItem[3305059] or {}
tItem[3305116] = tItem[3305059] or {}
tItem[3305117] = tItem[3305059] or {}
tItem[3306659] = tItem[3305059] or {}

tItem[3305059]["Function"] = function(nItemId,sItemName)
	RewardTemplate_UseItemAndMsg(tBossCopy_Pack[nItemId])
end

-- 装备礼包
tItem[3305091] = tItem[3305091] or {}
tItem[3305092] = tItem[3305091] or {}
tItem[3305093] = tItem[3305091] or {}
tItem[3305094] = tItem[3305091] or {}
tItem[3305095] = tItem[3305091] or {}
tItem[3305096] = tItem[3305091] or {}
tItem[3305097] = tItem[3305091] or {}
tItem[3305098] = tItem[3305091] or {}
tItem[3305099] = tItem[3305091] or {}
tItem[3305100] = tItem[3305091] or {}
tItem[3305101] = tItem[3305091] or {}
tItem[3305102] = tItem[3305091] or {}
tItem[3305103] = tItem[3305091] or {}
tItem[3305104] = tItem[3305091] or {}
tItem[3305105] = tItem[3305091] or {}
tItem[3305106] = tItem[3305091] or {}
tItem[3305107] = tItem[3305091] or {}
tItem[3305108] = tItem[3305091] or {}
tItem[3305109] = tItem[3305091] or {}
tItem[3305110] = tItem[3305091] or {}
tItem[3305111] = tItem[3305091] or {}
tItem[3305112] = tItem[3305091] or {}
tItem[3305113] = tItem[3305091] or {}
tItem[3305114] = tItem[3305091] or {}
tItem[3305091]["Function"] = function(nItemId,sItemName)
	-- 判断职业索引
	local nProIndex = BossCopy_JudgePro()
	
	-- 给奖 打log 加光效
	local sDelLog = string.format(tBossCopy_Data["DelLog"],nItemId)
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		RewardTemplate_NewRandom(tBossCopy_Pack[nItemId],nProIndex)
		User_EffectAdd("self",tBossCopy_Data["Effect"]["OpenPack"])
		Sys_SaveActionRewardLog(sDelLog)
	end
end

-- 3305071 龙珠碎片
tItem[3305071] = tItem[3305071] or {}
tItem[3305071]["Function"] = function(nItemId,sItemName)
	local nAmount = tBossCopy_Fragment[nItemId]["DeleteItem"][1]["ItemNum"]
	if not Item_ChkMulItem(nItemId,nItemId,nAmount) then
		Sys_MsgBox(tBossCopy_Text[nItemId][1])
		return
	end
	
	local nSpace = RewardTemplate_GetRewardSpace(tBossCopy_Fragment[nItemId])
	if not User_CheckLeftSpace(nSpace) then
		User_TalkChannel2005(tBossCopy_Text[nItemId][2])
		return
	end
	
	RewardTemplate_UseItemAndMsg(tBossCopy_Fragment[nItemId])
end

-- 3305072 宝石精华
tItem[3305072] = tItem[3305072] or {}
tItem[3305072]["DialogueText"] = tBossCopy_Text[3305072]
tItem[3305072]["Text1-1"] = {111,112,113,114,115,116}
tItem[3305072]["tOption1-1"] = {111,112}
tItem[3305072]["OptionFunc111"] = "BossCopy_MeteorEssence</N>3305072</N>1"
tItem[3305072]["OptionFunc112"] = "BossCopy_MeteorEssence</N>3305072</N>2"

-- 3305073 流星卷碎片
tItem[3305073] = tItem[3305073] or {}
tItem[3305073]["Function"] = function(nItemId,sItemName)
	local nAmount = tBossCopy_Fragment[nItemId]["DeleteItem"][1]["ItemNum"]
	if not Item_ChkMulItem(nItemId,nItemId,nAmount) then
		Sys_MsgBox(tBossCopy_Text[nItemId][1])
		return
	end
	
	local nSpace = RewardTemplate_GetRewardSpace(tBossCopy_Fragment[nItemId])
	if not User_CheckLeftSpace(nSpace) then
		User_TalkChannel2005(tBossCopy_Text[nItemId][2])
		return
	end
	
	RewardTemplate_UseItemAndMsg(tBossCopy_Fragment[nItemId])
end

-- tItemFace[3305076] = 399

--------------------------------------陷阱模块-------------------------------------------
tTrap[1758]= tTrap[1758] or {}
tTrap[1758]["Function"] = function (nTrapId,nTrapType)
	tBossCopy_Trap()
end
--------------------------------------怪物模块-------------------------------------------
local tBossCopy_Monster = {}
	tBossCopy_Monster[1] = {}
	tBossCopy_Monster[1]["Function"] = BossCopy_MonsterDeath
	tBossCopy_Monster[1]["MonsterId"] = {3366,3367,3368,3369,3370,3371,3372,3373,3374,3375,3376,3377,3378}
tMonsterDrop_AreaLoad = tMonsterDrop_AreaLoad or {}
table.insert(tMonsterDrop_AreaLoad,tBossCopy_Monster[1])
--------------------------------------时间自检-------------------------------------------
local tBossCopy_Time = {}
	tBossCopy_Time[1] = {}
	tBossCopy_Time[1]["Type"] = 2
	tBossCopy_Time[1]["TimeType"] = 5
	tBossCopy_Time[1]["Time"] = "00 00"
	tBossCopy_Time[1]["Func"] = BossCopy_Reset
-- table.insert(tSystemTime_InitialData,tBossCopy_Time[1])

tOntimerMin_HM[0000] = tOntimerMin_HM[0000] or {}
table.insert(tOntimerMin_HM[0000],BossCopy_Reset)
