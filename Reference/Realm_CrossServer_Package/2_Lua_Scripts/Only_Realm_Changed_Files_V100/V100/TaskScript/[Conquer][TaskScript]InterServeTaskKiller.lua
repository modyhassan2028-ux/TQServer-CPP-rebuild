------------------------------------------------------------------------------------
--Name:		[征服][活动脚本]国战任务优化
--Purpose:	国战任务优化
--Creator: 	丁晨
--Created:	2015/07/26
------------------------------------------------------------------------------------

--InterServeTask

local tInterServeTask_Killer_Data ={}
	
	tInterServeTask_Killer_Data["KillMonster"] ={}
	--气力怪
	tInterServeTask_Killer_Data["KillMonster"][7854] = 1
	--修为怪
	tInterServeTask_Killer_Data["KillMonster"][7855] = 1
	--强炼怪
	tInterServeTask_Killer_Data["KillMonster"][7856] = 1
	--百炼怪
	tInterServeTask_Killer_Data["KillMonster"][7857] = 1
	--通神怪
	tInterServeTask_Killer_Data["KillMonster"][7858] = 1
	--青龙
	tInterServeTask_Killer_Data["KillMonster"][7859] = 1
	--国境士兵
	tInterServeTask_Killer_Data["KillMonster"][7896] = 1
	--杀人
	tInterServeTask_Killer_Data["Killer"] = 10
	
	--兑换规则
	--气力值
	tInterServeTask_Killer_Data["KillRule"] ={}
	
	tInterServeTask_Killer_Data["KillRule"][1] = 300
	
	tInterServeTask_Killer_Data["KillRule"][7854] = 300
	--修为值
	tInterServeTask_Killer_Data["KillRule"][7855] = 100
	--强炼丹
	tInterServeTask_Killer_Data["KillRule"][7856] = 100
	--经验值
	tInterServeTask_Killer_Data["KillRule"][7857] = 10
	--通神丹
	tInterServeTask_Killer_Data["KillRule"][7858] = 50
	--杀人
	tInterServeTask_Killer_Data["KillRule"][0] = 300
	tInterServeTask_Killer_Data["KillRule"][7896] = 300
	
	--青龙
	tInterServeTask_Killer_Data["KillRule"][7859] = 1
	--地图ID
	tInterServeTask_Killer_Data["MapId"] = 3935
	

--怪物积分限制
local tInterServeTask_Killer_MonsterLimit ={}
	tInterServeTask_Killer_MonsterLimit[1] = {}
	tInterServeTask_Killer_MonsterLimit[1]["Num"] = 50
	tInterServeTask_Killer_MonsterLimit[1]["Pre"] = 45
	
	tInterServeTask_Killer_MonsterLimit[2] = {}
	tInterServeTask_Killer_MonsterLimit[2]["Num"] = 100
	tInterServeTask_Killer_MonsterLimit[2]["Pre"] = 40
	
	tInterServeTask_Killer_MonsterLimit[3] = {}
	tInterServeTask_Killer_MonsterLimit[3]["Num"] = 200
	tInterServeTask_Killer_MonsterLimit[3]["Pre"] = 35
	
	tInterServeTask_Killer_MonsterLimit[4] = {}
	tInterServeTask_Killer_MonsterLimit[4]["Num"] = 500
	tInterServeTask_Killer_MonsterLimit[4]["Pre"] = 25

--全服排行
local tInterServeTask_Killer_Global ={}
	--每日
	tInterServeTask_Killer_Global[1] = 50936
	tInterServeTask_Killer_Global[2] = 50937
	--永久
	tInterServeTask_Killer_Global[3] = 50938
	tInterServeTask_Killer_Global[4] = 50939
	
local tInterServeTask_Killer_TaskGlobal = {}
	--个人掩码记录
	tInterServeTask_Killer_TaskGlobal[1] = 35009
	tInterServeTask_Killer_TaskGlobal[2] = 35010
	
local tInterServeTask_Killer_Task = {}
	--杀怪 
	tInterServeTask_Killer_Task[1] = 35007
	--杀BOSS
	tInterServeTask_Killer_Task[2] = 35008
	tInterServeTask_Killer_Task["LevLimit"] = 110
	tInterServeTask_Killer_Task["MinMetempsychosis"] = 1
	tInterServeTask_Killer_Task["IdLimit"] = 7853
	tInterServeTask_Killer_Task["BagFull"] = 1
	
	

local tInterServeTask_Killer_BossReward ={}
	--七阶神魂
	tInterServeTask_Killer_BossReward["SevenStage"]={}
	tInterServeTask_Killer_BossReward["SevenStage"][1]=  824020
	tInterServeTask_Killer_BossReward["SevenStage"][2]=  824019
	tInterServeTask_Killer_BossReward["SevenStage"][3]=  824018
	tInterServeTask_Killer_BossReward["SevenStage"][4]=  823062
	tInterServeTask_Killer_BossReward["SevenStage"][5]=  823061
	tInterServeTask_Killer_BossReward["SevenStage"][6]=  823060
	tInterServeTask_Killer_BossReward["SevenStage"][7]=  823059
	tInterServeTask_Killer_BossReward["SevenStage"][8]=  823058
	tInterServeTask_Killer_BossReward["SevenStage"][9]=  822072
	tInterServeTask_Killer_BossReward["SevenStage"][10]= 822071
	tInterServeTask_Killer_BossReward["SevenStage"][11]= 821034
	tInterServeTask_Killer_BossReward["SevenStage"][12]= 821033
	tInterServeTask_Killer_BossReward["SevenStage"][13]= 820076
	tInterServeTask_Killer_BossReward["SevenStage"][14]= 820075
	tInterServeTask_Killer_BossReward["SevenStage"][15]= 820074
	tInterServeTask_Killer_BossReward["SevenStage"][16]= 820073
	tInterServeTask_Killer_BossReward["SevenStage"][17]= 800917
	tInterServeTask_Killer_BossReward["SevenStage"][18]= 800811
	tInterServeTask_Killer_BossReward["SevenStage"][19]= 800810
	tInterServeTask_Killer_BossReward["SevenStage"][20]= 800725
	tInterServeTask_Killer_BossReward["SevenStage"][21]= 800618 
	tInterServeTask_Killer_BossReward["SevenStage"][22]= 800522
	tInterServeTask_Killer_BossReward["SevenStage"][23]= 800422
	tInterServeTask_Killer_BossReward["SevenStage"][24]= 800255
	tInterServeTask_Killer_BossReward["SevenStage"][25]= 800215
	tInterServeTask_Killer_BossReward["SevenStage"][26]= 800142
	tInterServeTask_Killer_BossReward["SevenStage"][27]= 800111
	tInterServeTask_Killer_BossReward["SevenStage"][28]= 800020
	tInterServeTask_Killer_BossReward["SevenStage"][29]= 801004
	tInterServeTask_Killer_BossReward["SevenStage"][30]= 801104
	
	--六阶神魂
	tInterServeTask_Killer_BossReward["SixStage"]={}
	tInterServeTask_Killer_BossReward["SixStage"][1]=  822053
	tInterServeTask_Killer_BossReward["SixStage"][2]=  822055
	tInterServeTask_Killer_BossReward["SixStage"][3]=  800000
	tInterServeTask_Killer_BossReward["SixStage"][4]=  800110
	tInterServeTask_Killer_BossReward["SixStage"][5]=  800017
	tInterServeTask_Killer_BossReward["SixStage"][6]=  800320
	tInterServeTask_Killer_BossReward["SixStage"][7]=  800513
	tInterServeTask_Killer_BossReward["SixStage"][8]=  800616
	tInterServeTask_Killer_BossReward["SixStage"][9]=  800722
	tInterServeTask_Killer_BossReward["SixStage"][10]= 823055
	tInterServeTask_Killer_BossReward["SixStage"][11]= 823056
	tInterServeTask_Killer_BossReward["SixStage"][12]= 820071
	tInterServeTask_Killer_BossReward["SixStage"][13]= 820072
	tInterServeTask_Killer_BossReward["SixStage"][14]= 800421
	tInterServeTask_Killer_BossReward["SixStage"][15]= 821031
	tInterServeTask_Killer_BossReward["SixStage"][16]= 821032
	tInterServeTask_Killer_BossReward["SixStage"][17]= 824017
	tInterServeTask_Killer_BossReward["SixStage"][18]= 823057
	tInterServeTask_Killer_BossReward["SixStage"][19]= 800804
	tInterServeTask_Killer_BossReward["SixStage"][20]= 800809
	tInterServeTask_Killer_BossReward["SixStage"][21]= 800254
	tInterServeTask_Killer_BossReward["SixStage"][22]= 800916
	tInterServeTask_Killer_BossReward["SixStage"][23]= 801003
	tInterServeTask_Killer_BossReward["SixStage"][24]= 801103
	
	--极品淬炼
	tInterServeTask_Killer_BossReward["Grade"]={}
	tInterServeTask_Killer_BossReward["Grade"][1]=  724404
	tInterServeTask_Killer_BossReward["Grade"][2]=  724409
	tInterServeTask_Killer_BossReward["Grade"][3]=  724414
	tInterServeTask_Killer_BossReward["Grade"][4]=  724419
	tInterServeTask_Killer_BossReward["Grade"][5]=  724424
	tInterServeTask_Killer_BossReward["Grade"][6]=  724429
	tInterServeTask_Killer_BossReward["Grade"][7]=  724434
	tInterServeTask_Killer_BossReward["Grade"][8]=  724439
	tInterServeTask_Killer_BossReward["Grade"][9]=  724444
	tInterServeTask_Killer_BossReward["Grade"][10]= 724453
	tInterServeTask_Killer_BossReward["Grade"][11]= 724458
	tInterServeTask_Killer_BossReward["Grade"][12]= 724463
	tInterServeTask_Killer_BossReward["Grade"][13]= 724472
	tInterServeTask_Killer_BossReward["Grade"][14]= 724477
	tInterServeTask_Killer_BossReward["Grade"][15]= 724482
	tInterServeTask_Killer_BossReward["Grade"][16]= 724487
	tInterServeTask_Killer_BossReward["Grade"][17]= 724492
	tInterServeTask_Killer_BossReward["Grade"][18]= 724497
	tInterServeTask_Killer_BossReward["Grade"][19]= 724352
	tInterServeTask_Killer_BossReward["Grade"][20]= 724357
	tInterServeTask_Killer_BossReward["Grade"][21]= 724362
	tInterServeTask_Killer_BossReward["Grade"][22]= 724367
	tInterServeTask_Killer_BossReward["Grade"][23]= 724372
	tInterServeTask_Killer_BossReward["Grade"][24]= 724377
	tInterServeTask_Killer_BossReward["Grade"][25]= 724384
	tInterServeTask_Killer_BossReward["Grade"][26]= 724389
	tInterServeTask_Killer_BossReward["Grade"][27]= 724394
	tInterServeTask_Killer_BossReward["Grade"][28]= 724519
	tInterServeTask_Killer_BossReward["Grade"][29]= 725196
	tInterServeTask_Killer_BossReward["Grade"][30]= 725201
	tInterServeTask_Killer_BossReward["Grade"][31]= 725206
	tInterServeTask_Killer_BossReward["Grade"][32]= 725211
	tInterServeTask_Killer_BossReward["Grade"][33]= 3006169
	
	--神品淬炼
	tInterServeTask_Killer_BossReward["Spirit"]={}
	tInterServeTask_Killer_BossReward["Spirit"][1]= 3004137
	tInterServeTask_Killer_BossReward["Spirit"][2]= 3004138
	tInterServeTask_Killer_BossReward["Spirit"][3]= 3004139
	tInterServeTask_Killer_BossReward["Spirit"][4]= 3004140
	tInterServeTask_Killer_BossReward["Spirit"][5]= 3004141
	tInterServeTask_Killer_BossReward["Spirit"][6]= 3004142
	tInterServeTask_Killer_BossReward["Spirit"][7]= 3004143
	tInterServeTask_Killer_BossReward["Spirit"][8]= 3004144
	tInterServeTask_Killer_BossReward["Spirit"][9]= 3004147
	tInterServeTask_Killer_BossReward["Spirit"][10]=3004148
	tInterServeTask_Killer_BossReward["Spirit"][11]=3004149
	tInterServeTask_Killer_BossReward["Spirit"][12]=3004150
	tInterServeTask_Killer_BossReward["Spirit"][13]=3004151
	tInterServeTask_Killer_BossReward["Spirit"][14]=3004152
	tInterServeTask_Killer_BossReward["Spirit"][15]=3004153
	tInterServeTask_Killer_BossReward["Spirit"][16]=3004156
	tInterServeTask_Killer_BossReward["Spirit"][17]=3004158
	tInterServeTask_Killer_BossReward["Spirit"][18]=3004159
	tInterServeTask_Killer_BossReward["Spirit"][19]=3004160
	tInterServeTask_Killer_BossReward["Spirit"][20]=3004161
	tInterServeTask_Killer_BossReward["Spirit"][21]=3004163
	tInterServeTask_Killer_BossReward["Spirit"][22]=3004164
	tInterServeTask_Killer_BossReward["Spirit"][23]=3004165
	tInterServeTask_Killer_BossReward["Spirit"][24]=3004166
	tInterServeTask_Killer_BossReward["Spirit"][25]=3004136
	tInterServeTask_Killer_BossReward["Spirit"][26]=3004146
	tInterServeTask_Killer_BossReward["Spirit"][27]=3004157
	tInterServeTask_Killer_BossReward["Spirit"][28]=3004155
	tInterServeTask_Killer_BossReward["Spirit"][29]=3004145
	tInterServeTask_Killer_BossReward["Spirit"][30]=3004154
	tInterServeTask_Killer_BossReward["Spirit"][31]=3004162
	tInterServeTask_Killer_BossReward["Spirit"][32]=3006170
	
	tInterServeTask_Killer_BossReward["Precent"] = {}
	--6阶神魂
	tInterServeTask_Killer_BossReward["Precent"][1] = {}
	tInterServeTask_Killer_BossReward["Precent"][1]["TName"] ="SixStage"
	tInterServeTask_Killer_BossReward["Precent"][1]["Pre"]= 20
	--7阶神魂
	tInterServeTask_Killer_BossReward["Precent"][2] = {}
	tInterServeTask_Killer_BossReward["Precent"][2]["TName"] ="SevenStage"
	tInterServeTask_Killer_BossReward["Precent"][2]["Pre"]= 30
	--极品
	tInterServeTask_Killer_BossReward["Precent"][3] = {}
	tInterServeTask_Killer_BossReward["Precent"][3]["TName"] ="Grade"
	tInterServeTask_Killer_BossReward["Precent"][3]["Pre"]= 20
	--神品
	tInterServeTask_Killer_BossReward["Precent"][4] = {}
	tInterServeTask_Killer_BossReward["Precent"][4]["TName"] ="Spirit"
	tInterServeTask_Killer_BossReward["Precent"][4]["Pre"]= 30
	--分钟
	tInterServeTask_Killer_BossReward["Time"] = 10080
	--限制
	tInterServeTask_Killer_BossReward["BagFull"] =2
	--三种外套礼包
	tInterServeTask_Killer_BossReward["Gift"] = 3007107
--查询stc                                         
local tInterServeTask_Killer_FinStc ={}           

	tInterServeTask_Killer_FinStc["EventType"] =136
	tInterServeTask_Killer_FinStc["DataType"] ={}
	--气力怪
	tInterServeTask_Killer_FinStc["DataType"][7854] = 74
	--修为怪
	tInterServeTask_Killer_FinStc["DataType"][7855] = 75
	--强炼怪
	tInterServeTask_Killer_FinStc["DataType"][7856] = 76
	--百炼怪
	tInterServeTask_Killer_FinStc["DataType"][7857] = 77
	--通神怪
	tInterServeTask_Killer_FinStc["DataType"][7858] = 78
	--青龙
	tInterServeTask_Killer_FinStc["DataType"][7859] = 79
	--杀人
	tInterServeTask_Killer_FinStc["DataType"][0] = 80
	
local tInterServeTask_Killer_Reward={}
	--气力值
	tInterServeTask_Killer_Reward[7854] ={}
    tInterServeTask_Killer_Reward[7854]["Func"] = User_AddStrengthValue
    tInterServeTask_Killer_Reward[7854]["Num"] = 100
	--修为值
	tInterServeTask_Killer_Reward[7855] ={}
    tInterServeTask_Killer_Reward[7855]["Func"] = User_AddCultivation
    tInterServeTask_Killer_Reward[7855]["Num"] = 100
	--强炼丹
	tInterServeTask_Killer_Reward[7856] ={}
    tInterServeTask_Killer_Reward[7856]["Func"] = Item_AddItem
    tInterServeTask_Killer_Reward[7856]["ItemId"] = 3003124
    tInterServeTask_Killer_Reward[7856]["Num"] = 5
	--百炼
	tInterServeTask_Killer_Reward[7857] ={}
    tInterServeTask_Killer_Reward[7857]["Func"] = Item_AddItem
    tInterServeTask_Killer_Reward[7857]["ItemId"] = 723700
    tInterServeTask_Killer_Reward[7857]["Num"] = 1
	
	--通神怪
	tInterServeTask_Killer_Reward[7858] ={}
    tInterServeTask_Killer_Reward[7858]["Func"] = Item_AddItem
    tInterServeTask_Killer_Reward[7858]["ItemId"] = 3003126
    tInterServeTask_Killer_Reward[7858]["Num"] = 1
	
	--青龙
	
	
	--杀人
	tInterServeTask_Killer_Reward[0] ={}
    tInterServeTask_Killer_Reward[0]["Func"] = Item_AddItem
    tInterServeTask_Killer_Reward[0]["ItemId"] = 730003
    tInterServeTask_Killer_Reward[0]["Num"] = 1
	
--击杀怪物LOG
local tInterServeTask_Killer_Log ={}
	--击杀怪物杀人
	tInterServeTask_Killer_Log["CrossoverLog"] = "0,0,0,0,12000166,3,%s,1"
	--击杀BOSS
	tInterServeTask_Killer_Log["CrossBossLog"] = "0,0,0,0,12000167,3,%s,1"
	--领取MJ奖励
	tInterServeTask_Killer_Log["CrossRewMjLog"] = "0,0,0,0,12000168,2,%s,%s"
	--领取BOSS奖励
	tInterServeTask_Killer_Log["CrossRewBossLog"] = "0,0,0,0,12000169,2,%s,%s"
	--第一次杀怪
	tInterServeTask_Killer_Log["CrossFirstKLog"] = "0,0,0,0,12000170,3,0,0"
	--第500积分
	tInterServeTask_Killer_Log["CrossLastKLog"] = "0,0,0,0,12000171,3,0,0"	
	--随机礼包log
	tInterServeTask_Killer_Log["CrossSjGift"] = "0,0,0,0,12000172,2,%s,1"	
--Kill Monster 
local tInterServeTask_Killer_MonsterReward ={}
	--999999999  天石赠
	tInterServeTask_Killer_MonsterReward[1]={}

	tInterServeTask_Killer_MonsterReward[1]["Func"]= User_AddEMoneyMono
	tInterServeTask_Killer_MonsterReward[1]["Param"]= "30"
	tInterServeTask_Killer_MonsterReward[1]["Percent"]= 10
	tInterServeTask_Killer_MonsterReward[1]["Content"]= string.format(tInterServeTask_Killer_Text["Ts"],30)
	tInterServeTask_Killer_MonsterReward[1]["Log"]= string.format(tInterServeTask_Killer_Log["CrossRewMjLog"],3,30)
	
	--七星断续膏  4
	tInterServeTask_Killer_MonsterReward[2] ={}
	tInterServeTask_Killer_MonsterReward[2]["Func"] = Item_AddItem
	tInterServeTask_Killer_MonsterReward[2]["Param"]= "1003010 0 20 3"
	tInterServeTask_Killer_MonsterReward[2]["Percent"]= 45
	tInterServeTask_Killer_MonsterReward[2]["Content"]= string.format(tInterServeTask_Killer_Text["dxg"],20)
	tInterServeTask_Killer_MonsterReward[2]["Log"]= string.format(tInterServeTask_Killer_Log["CrossRewMjLog"],1003010,20)
	--2个修炼礼包
	tInterServeTask_Killer_MonsterReward[3] ={}
	tInterServeTask_Killer_MonsterReward[3]["Func"] = Item_AddItem
	tInterServeTask_Killer_MonsterReward[3]["Param"]= "3002926 0 2 3"
	tInterServeTask_Killer_MonsterReward[3]["Percent"]= 45
	tInterServeTask_Killer_MonsterReward[3]["Content"]= string.format(tInterServeTask_Killer_Text["xlb"],2)
	tInterServeTask_Killer_MonsterReward[3]["Log"]= string.format(tInterServeTask_Killer_Log["CrossRewMjLog"],3002926,2)
	
local tInterServeTask_Killer_MonsterRewardEy={}
	tInterServeTask_Killer_MonsterRewardEy["Limit"] = 6
	tInterServeTask_Killer_MonsterRewardEy["CpsLimit"] = 999999969
	tInterServeTask_Killer_MonsterRewardEy["Reward"]= {}
	--2个修炼礼包
	tInterServeTask_Killer_MonsterRewardEy["Reward"][1] ={}
	tInterServeTask_Killer_MonsterRewardEy["Reward"][1]["Func"] = Item_AddItem
	tInterServeTask_Killer_MonsterRewardEy["Reward"][1]["Param"]= "3002926 0 2 3"
	tInterServeTask_Killer_MonsterRewardEy["Reward"][1]["Content"]= string.format(tInterServeTask_Killer_Text["xlb"],2)
	tInterServeTask_Killer_MonsterRewardEy["Reward"][1]["Log"]= string.format(tInterServeTask_Killer_Log["CrossRewMjLog"],3002926,2)
	
	tInterServeTask_Killer_MonsterRewardEy["Reward"][2] ={}
	--国战奖励积分
	tInterServeTask_Killer_MonsterRewardEy["Reward"][2]["Func"] = National_War_AddIntegral
	tInterServeTask_Killer_MonsterRewardEy["Reward"][2]["Param"]= "50"
	tInterServeTask_Killer_MonsterRewardEy["Reward"][2]["Content"]= string.format(tInterServeTask_Killer_Text["gzjf"],50)
	tInterServeTask_Killer_MonsterRewardEy["Reward"][2]["Log"]= string.format(tInterServeTask_Killer_Log["CrossRewMjLog"],0,50)
	
	tInterServeTask_Killer_MonsterRewardEy["Reward"][3] ={}
	--千里传音
	tInterServeTask_Killer_MonsterRewardEy["Reward"][3]["Func"] = Item_AddItem
	tInterServeTask_Killer_MonsterRewardEy["Reward"][3]["Param"]= "3002218 0 3 3"
	tInterServeTask_Killer_MonsterRewardEy["Reward"][3]["Content"]= string.format(tInterServeTask_Killer_Text["qlcy"],3)
	tInterServeTask_Killer_MonsterRewardEy["Reward"][3]["Log"]= string.format(tInterServeTask_Killer_Log["CrossRewMjLog"],3002218,3)
	
--5天石
local tInterServeTask_Killer_DirectEmoney ={}
	tInterServeTask_Killer_DirectEmoney[1] = 10
--光效
local tInterServeTask_Killer_Effect ={}
	tInterServeTask_Killer_Effect["KillMonster"] ="eidolon"
	tInterServeTask_Killer_Effect["KillBoss"] ="recovery"


	
local tInterServeTask_Killer_EmoneyLog ={}
	tInterServeTask_Killer_EmoneyLog["Killer"]="350	4301	0	0	1	"
	tInterServeTask_Killer_EmoneyLog["KillerFinish"] = "350	4302	0	0	1	"
	
	tInterServeTask_Killer_EmoneyLog["KillerBoss"] = "350	4305	0	0	1	"
	tInterServeTask_Killer_EmoneyLog["KillerBossFinish"] = "350	4306	0	0	1	"
	
	tInterServeTask_Killer_EmoneyLog["CostEmoneyFinish"] = "350	4315	10	10	1	"

local tInterServeTask_Killer_TaskSucc = {}
	tInterServeTask_Killer_TaskSucc["Succ"] = 35012
	
--随机礼包
local tInterServeTask_Killer_Gift = {}
	tInterServeTask_Killer_Gift["Reward"] ={}
	--豪华外套碎片
	tInterServeTask_Killer_Gift["Reward"][1] ={}
	tInterServeTask_Killer_Gift["Reward"][1]["Func"] = Item_AddItem
	tInterServeTask_Killer_Gift["Reward"][1]["Param"]= "3007104 0 1 3"
	tInterServeTask_Killer_Gift["Reward"][1]["Percent"]= 40
	tInterServeTask_Killer_Gift["Reward"][1]["Content"]= tInterServeTask_Killer_Text["suij1"]
	tInterServeTask_Killer_Gift["Reward"][1]["Log"]= string.format(tInterServeTask_Killer_Log["CrossSjGift"],3007104)
	
	--豪华骑宠外套碎片
	tInterServeTask_Killer_Gift["Reward"][2] ={}
	tInterServeTask_Killer_Gift["Reward"][2]["Func"] = Item_AddItem
	tInterServeTask_Killer_Gift["Reward"][2]["Param"]= "3007105 0 1 3"
	tInterServeTask_Killer_Gift["Reward"][2]["Percent"]= 30
	tInterServeTask_Killer_Gift["Reward"][2]["Content"]= tInterServeTask_Killer_Text["suij2"]
	tInterServeTask_Killer_Gift["Reward"][2]["Log"]= string.format(tInterServeTask_Killer_Log["CrossSjGift"],3007105)
	
	--豪华武器外套碎片
	tInterServeTask_Killer_Gift["Reward"][3] ={}
	tInterServeTask_Killer_Gift["Reward"][3]["Func"] = Item_AddItem
	tInterServeTask_Killer_Gift["Reward"][3]["Param"]= "3007106 0 1 3"
	tInterServeTask_Killer_Gift["Reward"][3]["Percent"]= 30
	tInterServeTask_Killer_Gift["Reward"][3]["Content"]= tInterServeTask_Killer_Text["suij3"]
	tInterServeTask_Killer_Gift["Reward"][3]["Log"]= string.format(tInterServeTask_Killer_Log["CrossSjGift"],3007106)
	
function InterServeTask_Killer_TeamEnjoy(nMosterId,nScore)
	nMosterId = tonumber(nMosterId) or Get_MonsterType()
	nScore = tonumber(nScore) or 0
	--组队共享积分
	local nPlayerNumber = Get_UserTeamNumbers()
	if  nPlayerNumber >= 2 then
		--队员分享积分
		User_TeamExeFuncByTeamer(2,"InterServeTask_Killer_HauntMonster</N>"..nMosterId.."</N>"..nScore)
	else
		InterServeTask_Killer_HauntMonster(nMosterId,nScore)
	end
end

function InterServeTask_Killer_TeamEnjoyMan(nKillUserId)
	--组队共享积分
	local nPlayerNumber = Get_UserTeamNumbers()
	if  nPlayerNumber >= 2 then
		--队员分享积分
		User_TeamExeFuncByTeamer(2,"InterServeTask_Killer_PlayerKill</N>"..nKillUserId)
	else
		InterServeTask_Killer_PlayerKill(nKillUserId)
	end
end

--怪物配置
function InterServeTask_Killer_HauntMonster(nMosterId,nWScore,nTeamUserId)
	nMosterId = tonumber(nMosterId) or Get_MonsterType()
	nWScore = tonumber(nWScore) or 0
	if FirstPerson_AddKillMonsterNum then
		FirstPerson_AddKillMonsterNum(nTeamUserId)
	end
	--本服玩家
	-- if not User_IsCross() then
		-- return 
	-- end
	
	-- local nFinEvent = tInterServeTask_Killer_FinStc["EventType"] 
	-- local nFinType = tInterServeTask_Killer_FinStc["DataType"][nMosterId]
	--是否已兑换
	-- if   Task_StcInterval(nFinEvent,nFinType,1,4) then
		-- Task_SetStatistic(nFinEvent,nFinType,0,1)
		-- Task_SetStcTimestamp(nFinEvent,nFinType,0)
	-- end
	
	--隔天兑换
	-- if not Task_ChkStcValue(nFinEvent,nFinType,"==",0) then
		 
		-- return 
	-- end

	
	
	local nUserId = nTeamUserId or Get_UserId()
	if not Task_ChkTaskDetail(tInterServeTask_Killer_TaskSucc["Succ"],nUserId) then
		if Task_AddTaskDetail(tInterServeTask_Killer_TaskSucc["Succ"],0,nUserId) then
			Task_SetTaskDetailData7(tInterServeTask_Killer_TaskSucc["Succ"],os.time(),nUserId)
		end
	end
	
	local nTaskChk = Get_TaskDetail(tInterServeTask_Killer_TaskSucc["Succ"],"6",nUserId)
	if nTaskChk == 1 then
		return 
	end
	--
	if not Task_ChkTaskDetail(tInterServeTask_Killer_Task[1],nUserId) then
		Task_AddTaskDetail(tInterServeTask_Killer_Task[1],0,nUserId)
		Task_SetTaskDetailData7(tInterServeTask_Killer_Task[1],os.time(),nUserId)
	end
	
	--隔天清除
	-- if Task_DetailInterval(tInterServeTask_Killer_Task[1],1,4) then
		-- Task_SetTaskDetailData(tInterServeTask_Killer_Task[1],0,"1")
	-- end
	
	-- for k ,v in pairs(tInterServeTask_Killer_TaskGlobal)do
		-- if not Task_ChkTaskDetail(v) then
			-- Task_AddTaskDetail(v)
		-- end
	-- end

	
	-- for k, v in pairs(tInterServeTask_Killer_TaskGlobal)do
		-- local nScore = Get_TaskDetail(v,"1") +1
		-- Task_SetTaskDetailData(v,nScore,"1")
	-- end
	
	local nTaskId = tInterServeTask_Killer_Task[1]
	

	local nAddScore = tInterServeTask_Killer_Data["KillMonster"][nMosterId] or nWScore
	
	
	local nScore = Get_TaskDetail(nTaskId,"6",nUserId)
		
	if nScore == 0 then
		Sys_SaveActionFestivalLog(tInterServeTask_Killer_Log["CrossFirstKLog"],nUserId)
	end
	
	
	
	if nScore>= tInterServeTask_Killer_Data["KillRule"][nMosterId] then
		
	
		Sys_SaveActionFestivalLog(tInterServeTask_Killer_Log["CrossLastKLog"],nUserId)
		User_TalkChannel2005(tInterServeTask_Killer_Text["KillerMax"],nUserId)
		return
	end
	
	-- local nPre = 0
	-- for k ,v in pairs(tInterServeTask_Killer_MonsterLimit) do
		
		-- if nScore <= v["Num"] then
			-- nPre =v["Pre"]
			-- break
		-- end
	-- end
	
	-- if Sys_Random(nPre,100) then
		
	-- else
		-- return
	-- end
	if  nWScore ==0 then
		nScore = nScore+ math.random(nAddScore,5)
	else
		nScore = nScore + nWScore
	end
	
	if nScore >= tInterServeTask_Killer_Data["KillRule"][nMosterId] then
		nScore = tInterServeTask_Killer_Data["KillRule"][nMosterId]
	end
	Task_SetTaskDetailData(nTaskId,nScore,"6",nUserId)
	Sys_SaveActionFestivalLog(string.format(tInterServeTask_Killer_Log["CrossoverLog"],nMosterId),nUserId)
	Sys_SaveEmoneyBuy(tInterServeTask_Killer_EmoneyLog["Killer"],nUserId)
	local sStr = string.format(tInterServeTask_Killer_Text["KillMonster"],nScore)  
	User_TalkChannel2005(sStr,nUserId)
	if nScore >= tInterServeTask_Killer_Data["KillRule"][nMosterId] and tFirstPerson_Text and tFirstPerson_Text["HasReward"] then
		Sys_MsgBox(tFirstPerson_Text["HasReward"],nil,nil,nUserId)
	end
end

--击杀BOSS
function InterServeTask_Killer_HauntMonsterBoss(nMosterId)
	nMosterId = tonumber(nMosterId) or Get_MonsterType()
	--本服玩家
	-- if not User_IsCross() then
		-- return 
	-- end
	
	
	local nTaskId = tInterServeTask_Killer_Task[2]
	
	if not Task_ChkTaskDetail(nTaskId) then
		Task_AddTaskDetail(nTaskId)
		Task_SetTaskDetailData7(nTaskId,os.time())
	end
	
	local nAddNum = tInterServeTask_Killer_Data["KillMonster"][nMosterId] 
	
	local nNum = Get_TaskDetail(nTaskId,"1") + nAddNum
	Task_SetTaskDetailData(nTaskId,nNum,"1")
	
	Sys_SaveActionFestivalLog(string.format(tInterServeTask_Killer_Log["CrossBossLog"],nMosterId))
	Sys_SaveEmoneyBuy(tInterServeTask_Killer_EmoneyLog["KillerBoss"])
	User_EffectAdd("self",tInterServeTask_Killer_Effect["KillBoss"])
	User_TalkChannel2005(tInterServeTask_Killer_Text["KillMonsterBoss"])
	Map_SendBroadcastMsg(tInterServeTask_Killer_Data["MapId"],string.format(tInterServeTask_Killer_Text["KillMonsterBoss1"],Get_UserName()))
end

--击杀玩家
function InterServeTask_Killer_PlayerKill(nKillUserId)
	--本服玩家
	-- if not User_IsCross() then
		-- return 
	-- end
	
	-- local nFinEvent = tInterServeTask_Killer_FinStc["EventType"] 
	-- local nFinType = tInterServeTask_Killer_FinStc["DataType"][7854]
	--是否已兑换
	-- if   Task_StcInterval(nFinEvent,nFinType,1,4) then
		-- Task_SetStatistic(nFinEvent,nFinType,0,1)
		-- Task_SetStcTimestamp(nFinEvent,nFinType,0)
	-- end
	
	--隔天兑换
	-- if not Task_ChkStcValue(nFinEvent,nFinType,"==",0) then
		 
		-- return 
	-- end
	
	if not Task_ChkTaskDetail(tInterServeTask_Killer_TaskSucc["Succ"]) then
		if Task_AddTaskDetail(tInterServeTask_Killer_TaskSucc["Succ"]) then
			Task_SetTaskDetailData7(tInterServeTask_Killer_TaskSucc["Succ"],os.time())
		end
	end
	
	local nTaskChk = Get_TaskDetail(tInterServeTask_Killer_TaskSucc["Succ"],"6")
	if nTaskChk == 1 then
		return 
	end
	
	--击杀国境服玩家才算
	if Get_UserMapId()~= tInterServeTask_Killer_Data["MapId"] then
		return 
	end
	
	local nTaskId = tInterServeTask_Killer_Task[1]
	if not Task_ChkTaskDetail(nTaskId) then
		Task_AddTaskDetail(nTaskId)
		Task_SetTaskDetailData7(nTaskId,os.time())
	end
	local nScore =Get_TaskDetail(nTaskId,"6") 
	
	if nScore == 0 then
		Sys_SaveActionFestivalLog(tInterServeTask_Killer_Log["CrossFirstKLog"])
	end
	
	local nAddScore = tInterServeTask_Killer_Data["Killer"] 
	
	
	if nScore>= tInterServeTask_Killer_Data["KillRule"][7854] then
		Sys_SaveActionFestivalLog(tInterServeTask_Killer_Log["CrossLastKLog"])
		User_TalkChannel2005(tInterServeTask_Killer_Text["KillerMax"])
		return
	end
	
	nScore= nScore+ nAddScore
	if nScore >= tInterServeTask_Killer_Data["KillRule"][7854] then
		nScore = tInterServeTask_Killer_Data["KillRule"][7854]
	end
	Sys_SaveActionFestivalLog(string.format(tInterServeTask_Killer_Log["CrossoverLog"],0))
	Sys_SaveEmoneyBuy(tInterServeTask_Killer_EmoneyLog["Killer"])
	Task_SetTaskDetailData(nTaskId,nScore,"6")
	
	User_TalkChannel2005(string.format(tInterServeTask_Killer_Text["Killer"],nScore))
	
end

--5天石兑换
function InterServeTask_Killer_DirectMonster(nNpcId,nMonsterId)
	local nFinEvent = tInterServeTask_Killer_FinStc["EventType"] 
	local nFinType = tInterServeTask_Killer_FinStc["DataType"][nMonsterId]
	--是否已兑换
	if   Task_StcInterval(nFinEvent,nFinType,1,4) then
		Task_SetStatistic(nFinEvent,nFinType,0,1)
		Task_SetStcTimestamp(nFinEvent,nFinType,0)
	end
	
	--隔天兑换
	if not Task_ChkStcValue(nFinEvent,nFinType,"==",0) then
		 
		LinkNpcGossipFunc_New(nNpcId,"400-8")
		return 
	end
	
	if  Get_UserEMoney() < tInterServeTask_Killer_DirectEmoney[1] then
		LinkNpcGossipFunc_New(nNpcId,"400-18")
		return 
	else
		Task_SetStatistic(nFinEvent,nFinType,1,1)
		Task_SetStcTimestamp(nFinEvent,nFinType,0)
		User_AddEMoney(-tInterServeTask_Killer_DirectEmoney[1])
		
		if not Task_ChkTaskDetail(tInterServeTask_Killer_Task[1]) then
			Task_AddTaskDetail(tInterServeTask_Killer_Task[1])
			Task_SetTaskDetailData7(tInterServeTask_Killer_Task[1],os.time())
		end
	
		--隔天清除
		-- if Task_DetailInterval(tInterServeTask_Killer_Task[1],1,4) then
			-- Task_SetTaskDetailData(tInterServeTask_Killer_Task[1],0,"1")
		-- end
		
		local nIndex = 100
		local bFlag= false
		
		for k, v in pairs(tInterServeTask_Killer_MonsterReward)do
			
			if Sys_Random(v["Percent"],nIndex) then
				
				local tParam = InterServeTask_Killer_Split(v["Param"],' ')
				
				v["Func"](table.unpack(tParam))
				if tParam[1] == 3002926 then
					bFlag =true
					Sys_SaveActionFestivalLog(v["Log"])
					break
				end
				
				Sys_SaveActionFestivalLog(v["Log"])
				User_TalkChannel2005(v["Content"])
				break
			end
			nIndex = nIndex - v["Percent"]
		end
		
		for _,v in pairs(tInterServeTask_Killer_MonsterRewardEy["Reward"])do
			local tParam = InterServeTask_Killer_Split(v["Param"],' ')
			local sTalk = v["Content"]
			v["Func"](table.unpack(tParam))
			if tParam[1] == 3002926 and bFlag then
				sTalk = string.format(tInterServeTask_Killer_Text["xlb"],4)
			end
			User_TalkChannel2005(sTalk)
			Sys_SaveActionFestivalLog(v["Log"])
		end
		
		local nTaskId = tInterServeTask_Killer_Task[1]
		Task_SetTaskDetailData(nTaskId,0,"6")
		
		if not Task_ChkTaskDetail(tInterServeTask_Killer_TaskSucc["Succ"]) then
			if Task_AddTaskDetail(tInterServeTask_Killer_TaskSucc["Succ"]) then
				Task_SetTaskDetailData7(tInterServeTask_Killer_TaskSucc["Succ"],os.time())
			end
		end
		Task_SetTaskDetailCompleteFlag(tInterServeTask_Killer_Task[1],1)
		Task_SetTaskDetailData(tInterServeTask_Killer_TaskSucc["Succ"],1,"6")
		Sys_SaveEmoneyBuy(tInterServeTask_Killer_EmoneyLog["CostEmoneyFinish"])
		User_EffectAdd("self",tInterServeTask_Killer_Effect["KillMonster"])
		LinkNpcGossipFunc_New(nNpcId,"400-16")
	end
end

--兑换
function InterServeTask_Killer_Monster(nNpcId,nMonsterId)

	local nFinEvent = tInterServeTask_Killer_FinStc["EventType"] 
	local nFinType = tInterServeTask_Killer_FinStc["DataType"][nMonsterId]
	--是否已兑换
	if   Task_StcInterval(nFinEvent,nFinType,1,4) then
		Task_SetStatistic(nFinEvent,nFinType,0,1)
		Task_SetStcTimestamp(nFinEvent,nFinType,0)
	end
	
	--隔天兑换
	if not Task_ChkStcValue(nFinEvent,nFinType,"==",0) then
		 
		LinkNpcGossipFunc_New(nNpcId,"400-8")
		return 
	end
	
	
	-- local nIndex = nMonsterId - tInterServeTask_Killer_Task["IdLimit"] 
	-- if nMonsterId == 0 then
		-- nIndex = 6
	-- end

	local nTaskId = tInterServeTask_Killer_Task[1]
	--隔天清除
	-- if Task_DetailInterval(nTaskId,1,4) then
		-- Task_SetTaskDetailData(nTaskId,0,"1")
	-- end

	
	local nScore = Get_TaskDetail(nTaskId,"6")
	
	if nScore>= tInterServeTask_Killer_Data["KillRule"][nMonsterId] then
		
	
		if not User_CheckLeftSpace(tInterServeTask_Killer_MonsterRewardEy["Limit"]) then
			
			LinkNpcGossipFunc_New(nNpcId,"400-14")
			return 
		end
		
		if Get_UserMonoEMoney() > tInterServeTask_Killer_MonsterRewardEy["CpsLimit"] then
			LinkNpcGossipFunc_New(nNpcId,"400-15")
			return 
		end
		
	
		--nScore =nScore -tInterServeTask_Killer_Data["KillRule"][nMonsterId]
		
		
		Task_SetTaskDetailData(nTaskId,0,"6")
		
	
		Task_SetStatistic(nFinEvent,nFinType,1,1)
		Task_SetStcTimestamp(nFinEvent,nFinType,0)
		
		Task_SetTaskDetailData(tInterServeTask_Killer_TaskSucc["Succ"],1,"6")
		
		local nIndex = 100
		local bFlag= false
		
		for k, v in pairs(tInterServeTask_Killer_MonsterReward)do
			
			if Sys_Random(v["Percent"],nIndex) then
				
				local tParam = InterServeTask_Killer_Split(v["Param"],' ')
				
				v["Func"](table.unpack(tParam))
				if tParam[1] == 3002926 then
					Sys_SaveActionFestivalLog(v["Log"])
					bFlag =true
					break
				end
				User_TalkChannel2005(v["Content"])
				Sys_SaveActionFestivalLog(v["Log"])
				break
			end
			nIndex = nIndex - v["Percent"]
		end
		
		for _,v in pairs(tInterServeTask_Killer_MonsterRewardEy["Reward"])do
			local tParam = InterServeTask_Killer_Split(v["Param"],' ')
			local sTalk = v["Content"]
			v["Func"](table.unpack(tParam))
			if tParam[1] == 3002926 and bFlag then
				sTalk = string.format(tInterServeTask_Killer_Text["xlb"],4)
			end
			Sys_SaveActionFestivalLog(v["Log"])
			User_TalkChannel2005(sTalk)
		end
		Sys_SaveEmoneyBuy(tInterServeTask_Killer_EmoneyLog["KillerFinish"])
		User_EffectAdd("self",tInterServeTask_Killer_Effect["KillMonster"])
		Task_SetTaskDetailCompleteFlag(tInterServeTask_Killer_Task[1],1)
		LinkNpcGossipFunc_New(nNpcId,"400-16")
	else
		--tNpcGossip[17400]["Text427"] =string.format(tInterServeTask_Killer_Text[17400]["Text127"],tInterServeTask_Killer_Data["KillRule"][nMonsterId])
		tNpcGossip[17400]["Text450"] = string.format(tInterServeTask_Killer_Text[17400]["Text137"],tInterServeTask_Killer_Data["KillRule"][nMonsterId])
		LinkNpcGossipFunc_New(nNpcId,"400-7")
	end

end

function InterServeTask_Killer_Split(s, p)
    local rt = {}
    string.gsub(s, '[^'..p..']+', function(w) table.insert(rt,tonumber(w)) end )
    return rt
end

 -- function InterServeTask_Killer_Unpack (t, i)  
     -- i = i or 1  
     -- if t[i] then  
         -- return t[i], InterServeTask_Killer_Unpack(t, i + 1)  
     -- end  
 -- end  




--设置
function Task_SetTaskDetailData(nTaskId,nData,sPos,nUserId)
	if type(nTaskId) ~= "number" or nTaskId%1 ~= 0 or nTaskId <= 0 then
		Sys_SaveAbnormalLog("函数 Task_SetTaskDetailData 第一个参数nTaskId为整型并且大于0")
		return
	end
	
	if type(nData) ~= "number" or nData%1 ~= 0 or nData < 0 then
		Sys_SaveAbnormalLog("函数 Task_SetTaskDetailData 第二个参数nData为整型并且大于等于0")
		return
	end
	
	if sPos == "CompleteFlag" then
		nIndex = G_TASKDETAIL_COMPLETE_FLAG
	elseif sPos == "NotifyFlag" then
		nIndex = G_TASKDETAIL_NOTIFY_FLAG
	elseif sPos == "1" then
		nIndex = G_TASKDETAIL_DATA1
	elseif sPos == "2" then
		nIndex = G_TASKDETAIL_DATA2
	elseif sPos == "3" then
		nIndex = G_TASKDETAIL_DATA3
	elseif sPos == "4" then
		nIndex = G_TASKDETAIL_DATA4
	elseif sPos == "5" then
		nIndex = G_TASKDETAIL_DATA5
	elseif sPos == "6" then
		nIndex = G_TASKDETAIL_DATA6
	elseif sPos == "7" then
		nIndex = G_TASKDETAIL_DATA7
	elseif sPos == "OverTime" then
		nIndex = G_TASKDETAIL_TASK_OVERTIME
	elseif sPos == "OverTimeSec" then
		nIndex = G_TASKDETAIL_TASK_OVERTIME_SEC
	end
	
	if nIndex == 0 then
		Sys_SaveAbnormalLog("函数 Task_SetTaskDetailData 中 sPos 传入的格式有错")
		return
	end
	
	
	if nUserId == nil then
		nUserId = 0
	elseif type(nUserId) ~= "number" or nUserId%1 ~= 0 or nUserId < 0 then
		Sys_SaveAbnormalLog("函数 Task_SetTaskDetailData 第三个参数nUserId为整型并且大于等于0")
		return
	end

	if Task_ChkTaskDetail(nTaskId,nUserId) then
		return SetTaskDetailData(nUserId,nTaskId,nIndex,nData)
	else
		Sys_SaveAbnormalLog(string.format("函数 Task_SetTaskDetailData 中玩家身上没有任务ID为%d的掩码",nTaskId))
		return
	end
end

--前往国境服击杀敌寇。
function InterServeTask_Killer_AddTask(nNpcId)

	--等级不足
	if not User_JudgeLevelAndMetempsychosis(tInterServeTask_Killer_Task["LevLimit"],tInterServeTask_Killer_Task["MinMetempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"400-3")
		return
	end
	
	--创建task掩码1
	local nTaskId = tInterServeTask_Killer_Task[1]
	Task_AddTaskDetail(nTaskId)
	Task_SetTaskDetailData7(nTaskId,os.time())
	
	--记录每日杀怪  与永久杀怪
	-- for k ,v in pairs(tInterServeTask_Killer_TaskGlobal)do
		-- if not Task_ChkTaskDetail(v) then
			-- Task_AddTaskDetail(v)
		-- end
	-- end
	
	--可接任务
	LinkNpcGossipFunc_New(nNpcId,"400-4")
end

--国境对抗
function InterServeTask_Killer_Confront(nNpcId)
	--本服玩家
	if  User_IsCross() then
		LinkNpcGossipFunc_New(nNpcId,"400-1")
		return 
	end
	
	LinkNpcGossipFunc_New(nNpcId,"400-2")
end

--国境妖龙
function InterServeTask_Killer_Dragon(nNpcId)
	--本服玩家
	if  User_IsCross() then
		LinkNpcGossipFunc_New(nNpcId,"400-1")
		return 
	end
	
	LinkNpcGossipFunc_New(nNpcId,"400-9")
end

--接受任务
function InterServeTask_Killer_AddTask2(nNpcId)
	--等级不足
	
	if not User_JudgeLevelAndMetempsychosis(tInterServeTask_Killer_Task["LevLimit"],tInterServeTask_Killer_Task["MinMetempsychosis"]) then 
		LinkNpcGossipFunc_New(nNpcId,"400-10")
		return
	end
	
	--创建task掩码1
	local nTaskId = tInterServeTask_Killer_Task[2]
	Task_AddTaskDetail(nTaskId)
	Task_SetTaskDetailData7(nTaskId,os.time())
	if not Task_ChkTaskDetail(tInterServeTask_Killer_TaskSucc["Succ"]) then
		if Task_AddTaskDetail(tInterServeTask_Killer_TaskSucc["Succ"]) then
			Task_SetTaskDetailData7(tInterServeTask_Killer_TaskSucc["Succ"],os.time())
		end
	end
	
	--可接任务
	LinkNpcGossipFunc_New(nNpcId,"400-13")
end

--已击杀蛟龙
function InterServeTask_Killer_DragonSucc(nNpcId,nMonsterId)
	--local nFinEvent = tInterServeTask_Killer_FinStc["EventType"] 
	--local nFinType = tInterServeTask_Killer_FinStc["DataType"][nMonsterId]
	--是否已兑换
	-- if  Task_StcInterval(nFinEvent,nFinType,1,4) then
		-- Task_SetStatistic(nFinEvent,nFinType,0,1)
		-- Task_SetStcTimestamp(nFinEvent,nFinType,0)
	
	-- end
	
	--隔天兑换
	-- if not Task_ChkStcValue(nFinEvent,nFinType,"==",0) then
		 
		-- LinkNpcGossipFunc_New(nNpcId,"400-8")
		-- return 
	-- end
	
	if not User_CheckLeftSpace(tInterServeTask_Killer_BossReward["BagFull"]) then
		LinkNpcGossipFunc_New(nNpcId,"400-14")
		return 
	end
	
	local nTaskId = tInterServeTask_Killer_Task[2]
	local nScore = Get_TaskDetail(nTaskId,"1")
	local sStr = ""
	if nScore>= tInterServeTask_Killer_Data["KillRule"][nMonsterId] then
		
	
		nScore =nScore -tInterServeTask_Killer_Data["KillRule"][nMonsterId]
		
		
		Task_SetTaskDetailData(nTaskId,nScore,"1")
		Task_SetTaskDetailCompleteFlag(nTaskId,1)
		local nIndex = 100
		
		for k, v in pairs(tInterServeTask_Killer_BossReward["Precent"])do
			
			if Sys_Random(v["Pre"],nIndex) then
				local nInner = math.random(1,#tInterServeTask_Killer_BossReward[v["TName"]])
				local nItemId = tInterServeTask_Killer_BossReward[v["TName"]][nInner]
				Item_AddItem(nItemId,0,0,0,tInterServeTask_Killer_BossReward["Time"],1)
				sStr = string.format(tInterServeTask_Killer_Text["GongXi"],Get_ItemtypeName(nItemId))
				Sys_SaveActionFestivalLog(string.format(tInterServeTask_Killer_Log["CrossRewBossLog"],nItemId,1))
				break
			end
			nIndex = nIndex - v["Pre"]
		end
		Item_AddItem(tInterServeTask_Killer_BossReward["Gift"])
		Sys_SaveActionFestivalLog(string.format(tInterServeTask_Killer_Log["CrossRewBossLog"],tInterServeTask_Killer_BossReward["Gift"],1))
		User_TalkChannel2005(sStr.."、"..Get_ItemtypeName(tInterServeTask_Killer_BossReward["Gift"]))
		Sys_SaveEmoneyBuy(tInterServeTask_Killer_EmoneyLog["KillerBossFinish"])
		LinkNpcGossipFunc_New(nNpcId,"400-11")
		User_EffectAdd("self",tInterServeTask_Killer_Effect["KillBoss"])
	else
		
		LinkNpcGossipFunc_New(nNpcId,"400-12")
	end
	
end

--排列全服排行
function InterServeTask_Killer_Rank(tPlayer,nBreIndex,nLasIndex)
	
	local tPlayerData = {}
	local nIndex = 0 
	--取原前10名
	for i = nBreIndex, nLasIndex do 
		local nGolbalId = tInterServeTask_Killer_Global[i]
		for j = 1 ,5 do
			nIndex = nIndex +1
			local nData = Get_SysDynaGlobalData(nGolbalId,j)
			local nKillData = Get_SysDynaGlobalDataStr(nGolbalId,j)
			tPlayerData[nIndex] ={}
			tPlayerData[nIndex]["PlayerId"] = nData
			tPlayerData[nIndex]["KillNum"] = nKillData == "" and 0 or tonumber(nKillData)
		end
	end
	
	--账号相同退出
	local nFlag = true
	for i = 1, 10 do 
		if tPlayerData[i]["PlayerId"] == tPlayer["PlayerId"]   then
		   tPlayerData[i]["KillNum"] = tPlayer["KillNum"]
		   nFlag =false
		end
	end
	
	
	if nFlag then
		local nTab = #tPlayerData+1
		tPlayerData[nTab] ={}
		tPlayerData[nTab]["PlayerId"] = tPlayer["PlayerId"]
		tPlayerData[nTab]["KillNum"] = tPlayer["KillNum"]
	end
	
	table.sort(tPlayerData,function(a,b)
			if  a["KillNum"] > b["KillNum"] then
				return true
			else
				return false
			end
		end
	)
	
	for i= 1, 10 do
		local nPlayerId = tPlayerData[i]["PlayerId"]
		local sKillNum = tPlayerData[i]["KillNum"]
		
		if i<= 5 then
			Sys_SetSynaGlobalData(tInterServeTask_Killer_Global[nBreIndex],i,nPlayerId)
			Sys_SetSynaGlobalDataStr(tInterServeTask_Killer_Global[nBreIndex],i,tostring(sKillNum))
		else
			Sys_SetSynaGlobalData(tInterServeTask_Killer_Global[nLasIndex],i-5,nPlayerId)
			Sys_SetSynaGlobalDataStr(tInterServeTask_Killer_Global[nLasIndex],i-5,tostring(sKillNum))
		end
		
	end
end

-- function InterServeTask_Killer_ClearGlobal()
	-- for i = 1, 2 do
		-- Sys_ResetAllSynaGlobalData(tInterServeTask_Killer_Global[i])
		-- Sys_ResetAllSynaGlobalDataStr(tInterServeTask_Killer_Global[i])
	-- end
-- end

--上线清理
--function InterServeTask_Killer_Login()
	-- local nTaskId = tInterServeTask_Killer_TaskGlobal[1]
	-- if not Task_ChkTaskDetail(nTaskId) then
		-- return
	-- end	
	-- if Task_DetailInterval(nTaskId,1,4) then
		-- Task_SetTaskDetailData(nTaskId,0,"1")
	-- end
	
	-- local tPlayer = {}
	-- tPlayer["PlayerId"]= Get_UserId()
	-- tPlayer["KillNum"] = Get_TaskDetailData1(tInterServeTask_Killer_TaskGlobal[1])
	-- InterServeTask_Killer_Rank(tPlayer,1,2)
	
	-- local tPlayer = {}
	-- tPlayer["PlayerId"]= Get_UserId()
	-- tPlayer["KillNum"] = Get_TaskDetailData1(tInterServeTask_Killer_TaskGlobal[2])
	-- InterServeTask_Killer_Rank(tPlayer,3,4)
--end

--退出国境排行
--function InterServeTask_Killer_gjf()
	-- local tPlayer = {}
	-- tPlayer["PlayerId"]= Get_UserId()
	-- tPlayer["KillNum"] = Get_TaskDetailData1(tInterServeTask_Killer_TaskGlobal[1])
	-- InterServeTask_Killer_Rank(tPlayer,1,2)
	
	-- local tPlayer = {}
	-- tPlayer["PlayerId"]= Get_UserId()
	-- tPlayer["KillNum"] = Get_TaskDetailData1(tInterServeTask_Killer_TaskGlobal[2])
	-- InterServeTask_Killer_Rank(tPlayer,3,4)
--end

--使用礼包
function InterServeTask_Killer_UseItemBox(nItemId)
	local nIndex = 100
	if Item_DelItem(nItemId) then
		for k , v in pairs(tInterServeTask_Killer_Gift["Reward"]) do
			if  Sys_Random(v["Percent"],nIndex) then
				local tParam = InterServeTask_Killer_Split(v["Param"],' ')
				v["Func"](table.unpack(tParam))
				User_TalkChannel2005(v["Content"])
				Sys_SaveActionFestivalLog(v["Log"])
				break
			end
			nIndex =nIndex - v["Percent"]
		end
	end
end


--tNpcFace[3728] = 4
tNpcGossip[17400] = tNpcGossip[17400] or DefaultNpc:new{}
tNpcGossip[17400]["OptionHidden"] = 1

--非本盟玩家
tNpcGossip[17400]["Text400-1"] = {40011,40012}
tNpcGossip[17400]["Text40011"] = tInterServeTask_Killer_Text[17400]["Text111"]
tNpcGossip[17400]["Text40012"] = tInterServeTask_Killer_Text[17400]["Text112"]
tNpcGossip[17400]["tOption400-1"] = {401}
tNpcGossip[17400]["Option401"] = tInterServeTask_Killer_Text[17400]["Option1"]

--接任务
tNpcGossip[17400]["Text400-2"] = {413,414}
tNpcGossip[17400]["Text413"] = tInterServeTask_Killer_Text[17400]["Text213"]
tNpcGossip[17400]["Text414"] = tInterServeTask_Killer_Text[17400]["Text214"]
--tNpcGossip[17400]["tOption400-2"] = {402,403,404,405}
tNpcGossip[17400]["tOption400-2"] = {402,403,404,405}
tNpcGossip[17400]["Option402"] = tInterServeTask_Killer_Text[17400]["Option2"]
tNpcGossip[17400]["Option403"] = tInterServeTask_Killer_Text[17400]["Option3"]
tNpcGossip[17400]["Option404"] = tInterServeTask_Killer_Text[17400]["Option30"]
tNpcGossip[17400]["Option405"] = tInterServeTask_Killer_Text[17400]["Option5"]

--接任务
tNpcGossip[17400]["OptionChkFunc402"] = function ()
	local nTaskId = tInterServeTask_Killer_Task[1]
	if not Task_ChkTaskDetail(nTaskId) then
		return true
	end
	
	return false
end
--前往国境服击杀敌寇。
tNpcGossip[17400]["OptionFunc402"]="InterServeTask_Killer_AddTask</N>17400"
tNpcGossip[17400]["OptionFunc403"]="InterServeTask_Killer_Monster</N>17400</N>7854"
tNpcGossip[17400]["OptionFunc404"]="InterServeTask_Killer_DirectMonster</N>17400</N>7854"

tNpcGossip[17400]["Text400-3"] = {415,416}
tNpcGossip[17400]["Text415"] = tInterServeTask_Killer_Text[17400]["Text115"]
tNpcGossip[17400]["Text416"] = tInterServeTask_Killer_Text[17400]["Text116"]
tNpcGossip[17400]["tOption400-3"] = {406}
tNpcGossip[17400]["Option406"] = tInterServeTask_Killer_Text[17400]["Option6"]

--接受成功
tNpcGossip[17400]["Text400-4"] = {417}
tNpcGossip[17400]["Text417"] = tInterServeTask_Killer_Text[17400]["Text117"]
tNpcGossip[17400]["tOption400-4"] = {407}
tNpcGossip[17400]["Option407"] = tInterServeTask_Killer_Text[17400]["Option7"]

--周排行
tNpcGossip[17400]["Text400-5"] = {418,419,420,421,422,423,424,425,426,427,428}
tNpcGossip[17400]["Text418"] = tInterServeTask_Killer_Text[17400]["Text128"]
tNpcGossip[17400]["Text419"] = tInterServeTask_Killer_Text[17400]["Text118"]
tNpcGossip[17400]["Text420"] = tInterServeTask_Killer_Text[17400]["Text119"]
tNpcGossip[17400]["Text421"] = tInterServeTask_Killer_Text[17400]["Text120"]
tNpcGossip[17400]["Text422"] = tInterServeTask_Killer_Text[17400]["Text121"]
tNpcGossip[17400]["Text423"] = tInterServeTask_Killer_Text[17400]["Text122"]
tNpcGossip[17400]["Text424"] = tInterServeTask_Killer_Text[17400]["Text123"]
tNpcGossip[17400]["Text425"] = tInterServeTask_Killer_Text[17400]["Text124"]
tNpcGossip[17400]["Text426"] = tInterServeTask_Killer_Text[17400]["Text125"]
tNpcGossip[17400]["Text427"] = tInterServeTask_Killer_Text[17400]["Text126"]
tNpcGossip[17400]["Text428"] = tInterServeTask_Killer_Text[17400]["Text127"]
tNpcGossip[17400]["tOption400-5"] = {408}
tNpcGossip[17400]["Option408"] = tInterServeTask_Killer_Text[17400]["Option7"]

tNpcGossip[17400]["ChkFunc400-5"] = function ()
	--创建task掩码1
	local nTaskId = tInterServeTask_Killer_Task[1]
	if not Task_ChkTaskDetail(nTaskId) then
		Task_AddTaskDetail(nTaskId)
	end
	
	--记录每日杀怪  与永久杀怪
	for k ,v in pairs(tInterServeTask_Killer_TaskGlobal)do
		if not Task_ChkTaskDetail(v) then
			Task_AddTaskDetail(v)
		end
	end
	
	local tPlayer = {}
	tPlayer["PlayerId"]= Get_UserId()
	tPlayer["KillNum"] = Get_TaskDetailData1(tInterServeTask_Killer_TaskGlobal[1])
	--
	InterServeTask_Killer_Rank(tPlayer,1,2)
	
	local tPlayerData = {}
	local nIndex = 0 
	--取原前10名
	for i = 1, 2 do 
		local nGolbalId = tInterServeTask_Killer_Global[i]
		for j = 1 ,5 do
			nIndex = nIndex +1
			local nData = Get_SysDynaGlobalData(nGolbalId,j)
			local nKillData = Get_SysDynaGlobalDataStr(nGolbalId,j)
			tPlayerData[nIndex] ={}
			tPlayerData[nIndex]["PlayerId"] = nData
			tPlayerData[nIndex]["KillNum"] = nKillData == "" and 0 or tonumber(nKillData)
		end
	end
	
	for i= 419,428 do
		local nIndex =  i -418
		local nBre = i - 301
		local sName =tPlayerData[nIndex]["PlayerId"] ~= 0 and Get_UserName(tPlayerData[nIndex]["PlayerId"]) or tInterServeTask_Killer_Text["NoPlayer"]
		tNpcGossip[17400]["Text"..i] = string.format(tInterServeTask_Killer_Text[17400]["Text"..nBre],sName,tPlayerData[nIndex]["KillNum"])
	end
	
	return true
end


--历史排行
tNpcGossip[17400]["Text400-6"] = {437,438,439,440,441,442,443,444,445,446,447}
tNpcGossip[17400]["Text437"] = tInterServeTask_Killer_Text[17400]["Text128"]
tNpcGossip[17400]["Text438"] = tInterServeTask_Killer_Text[17400]["Text118"]
tNpcGossip[17400]["Text439"] = tInterServeTask_Killer_Text[17400]["Text119"]
tNpcGossip[17400]["Text440"] = tInterServeTask_Killer_Text[17400]["Text120"]
tNpcGossip[17400]["Text441"] = tInterServeTask_Killer_Text[17400]["Text121"]
tNpcGossip[17400]["Text442"] = tInterServeTask_Killer_Text[17400]["Text122"]
tNpcGossip[17400]["Text443"] = tInterServeTask_Killer_Text[17400]["Text123"]
tNpcGossip[17400]["Text444"] = tInterServeTask_Killer_Text[17400]["Text124"]
tNpcGossip[17400]["Text445"] = tInterServeTask_Killer_Text[17400]["Text125"]
tNpcGossip[17400]["Text446"] = tInterServeTask_Killer_Text[17400]["Text126"]
tNpcGossip[17400]["Text447"] = tInterServeTask_Killer_Text[17400]["Text127"]
tNpcGossip[17400]["tOption400-6"] = {409}
tNpcGossip[17400]["Option409"] = tInterServeTask_Killer_Text[17400]["Option7"]

tNpcGossip[17400]["ChkFunc400-6"] = function ()
	--创建task掩码1
	local nTaskId = tInterServeTask_Killer_Task[1]
	if not Task_ChkTaskDetail(nTaskId) then
		Task_AddTaskDetail(nTaskId)
	end
	
	--记录每日杀怪  与永久杀怪
	for k ,v in pairs(tInterServeTask_Killer_TaskGlobal)do
		if not Task_ChkTaskDetail(v) then
			Task_AddTaskDetail(v)
		end
	end
	
	local tPlayer = {}
	tPlayer["PlayerId"]= Get_UserId()
	tPlayer["KillNum"] = Get_TaskDetailData1(tInterServeTask_Killer_TaskGlobal[2])
	--
	InterServeTask_Killer_Rank(tPlayer,3,4)
	
	local tPlayerData = {}
	local nIndex = 0 
	--取原前10名
	for i = 3, 4 do 
		local nGolbalId = tInterServeTask_Killer_Global[i]
		for j = 1 ,5 do
			nIndex = nIndex +1
			local nData = Get_SysDynaGlobalData(nGolbalId,j)
			local nKillData = Get_SysDynaGlobalDataStr(nGolbalId,j)
			tPlayerData[nIndex] ={}
			tPlayerData[nIndex]["PlayerId"] = nData
			tPlayerData[nIndex]["KillNum"] = nKillData == "" and 0 or tonumber(nKillData)
		end
	end
	
	for i= 438,447 do
		local nIndex =  i -437
		local nBre = i - 320
		local sName =tPlayerData[nIndex]["PlayerId"] ~= 0 and Get_UserName(tPlayerData[nIndex]["PlayerId"]) or tInterServeTask_Killer_Text["NoPlayer"]
		tNpcGossip[17400]["Text"..i] = string.format(tInterServeTask_Killer_Text[17400]["Text"..nBre],sName,tPlayerData[nIndex]["KillNum"])
	end
	
	return true
end




--等级不足
-- tNpcGossip[17400]["Text400-3"] = {415,416}
-- tNpcGossip[17400]["Text415"] = tInterServeTask_Killer_Text[17400]["Text115"]
-- tNpcGossip[17400]["Text416"] = tInterServeTask_Killer_Text[17400]["Text116"]
-- tNpcGossip[17400]["tOption400-3"] = {406}
-- tNpcGossip[17400]["Option406"] = tInterServeTask_Killer_Text[17400]["Option6"]

--可接任务
-- tNpcGossip[17400]["Text400-4"] = {417,418,419,420,421,422,423}
-- tNpcGossip[17400]["Text417"] = tInterServeTask_Killer_Text[17400]["Text117"]
-- tNpcGossip[17400]["Text418"] = tInterServeTask_Killer_Text[17400]["Text118"]
-- tNpcGossip[17400]["Text419"] = tInterServeTask_Killer_Text[17400]["Text119"]
-- tNpcGossip[17400]["Text420"] = tInterServeTask_Killer_Text[17400]["Text120"]
-- tNpcGossip[17400]["Text421"] = tInterServeTask_Killer_Text[17400]["Text121"]
-- tNpcGossip[17400]["Text422"] = tInterServeTask_Killer_Text[17400]["Text122"]
-- tNpcGossip[17400]["Text423"] = tInterServeTask_Killer_Text[17400]["Text123"]
-- tNpcGossip[17400]["tOption400-4"] = {407}
-- tNpcGossip[17400]["Option407"] = tInterServeTask_Killer_Text[17400]["Option7"]

--成功完成任务

-- tNpcGossip[17400]["Text400-5"] = {424}
-- tNpcGossip[17400]["Text424"] = tInterServeTask_Killer_Text[17400]["Text124"]
-- tNpcGossip[17400]["Option408"] = tInterServeTask_Killer_Text[17400]["Option8"]
-- tNpcGossip[17400]["Option409"] = tInterServeTask_Killer_Text[17400]["Option9"]
-- tNpcGossip[17400]["Option410"] = tInterServeTask_Killer_Text[17400]["Option10"]
-- tNpcGossip[17400]["Option411"] = tInterServeTask_Killer_Text[17400]["Option11"]
-- tNpcGossip[17400]["Option412"] = tInterServeTask_Killer_Text[17400]["Option12"]
-- tNpcGossip[17400]["Option413"] = tInterServeTask_Killer_Text[17400]["Option13"]
-- tNpcGossip[17400]["Option414"] = tInterServeTask_Killer_Text[17400]["Option14"]
-- tNpcGossip[17400]["tOption400-5"] = {408,409,410,411,412,413,414}

-- tNpcGossip[17400]["OptionFunc408"]="InterServeTask_Killer_Monster</N>17400</N>7854"
-- tNpcGossip[17400]["OptionFunc409"]="InterServeTask_Killer_Monster</N>17400</N>7855"
-- tNpcGossip[17400]["OptionFunc410"]="InterServeTask_Killer_Monster</N>17400</N>7856"
-- tNpcGossip[17400]["OptionFunc411"]="InterServeTask_Killer_Monster</N>17400</N>7857"
-- tNpcGossip[17400]["OptionFunc412"]="InterServeTask_Killer_Monster</N>17400</N>7858"
-- tNpcGossip[17400]["OptionFunc413"]="InterServeTask_Killer_Monster</N>17400</N>0"



--成功兑换
-- tNpcGossip[17400]["Text400-6"] = {425,426}
-- tNpcGossip[17400]["Text425"] = tInterServeTask_Killer_Text[17400]["Text125"]
-- tNpcGossip[17400]["Text426"] = tInterServeTask_Killer_Text[17400]["Text126"]
-- tNpcGossip[17400]["Option415"] = tInterServeTask_Killer_Text[17400]["Option15"]
-- tNpcGossip[17400]["tOption400-6"] = {415}

--未成功
tNpcGossip[17400]["Text400-7"] = {450}
tNpcGossip[17400]["Text450"] = tInterServeTask_Killer_Text[17400]["Text137"]

tNpcGossip[17400]["Option438"] = tInterServeTask_Killer_Text[17400]["Option26"]
tNpcGossip[17400]["tOption400-7"] = {438}

--天石不足
tNpcGossip[17400]["Text400-18"] = {455}
tNpcGossip[17400]["Text455"] = tInterServeTask_Killer_Text[17400]["Text145"]
tNpcGossip[17400]["Option428"] = tInterServeTask_Killer_Text[17400]["Option31"]
tNpcGossip[17400]["tOption400-18"] = {428}

--今日已兑换
tNpcGossip[17400]["Text400-8"] = {429}
tNpcGossip[17400]["Text429"] = tInterServeTask_Killer_Text[17400]["Text141"]
tNpcGossip[17400]["Option417"] = tInterServeTask_Killer_Text[17400]["Option29"]
tNpcGossip[17400]["tOption400-8"] = {417}


tNpcGossip[17400]["Option498"]=tInterServeTask_Killer_Text[17400]["Option400"]
 tNpcGossip[17400]["Option499"]=tInterServeTask_Killer_Text[17400]["Option401"]
 
tNpcGossip[17400]["Option497"]= tInterServeTask_Killer_Text[17400]["Option402"]
tNpcGossip[17400]["Option496"]= tInterServeTask_Killer_Text[17400]["Option403"]

tNpcGossip[17400]["OptionFunc497"]= "LinkNpcGossipFunc_New</N>17400</S>400-5"
tNpcGossip[17400]["OptionFunc496"]= "LinkNpcGossipFunc_New</N>17400</S>400-6"

tNpcGossip[17400]["OptionFunc498"]="InterServeTask_Killer_Confront</N>17400"
tNpcGossip[17400]["OptionFunc499"]="InterServeTask_Killer_Dragon</N>17400"

--国境妖龙
tNpcGossip[17400]["Text400-9"] = {430}
tNpcGossip[17400]["Text430"] = tInterServeTask_Killer_Text[17400]["Text130"]
tNpcGossip[17400]["Option418"] = tInterServeTask_Killer_Text[17400]["Option18"]
tNpcGossip[17400]["Option419"] = tInterServeTask_Killer_Text[17400]["Option19"]
tNpcGossip[17400]["Option420"] = tInterServeTask_Killer_Text[17400]["Option20"]
tNpcGossip[17400]["tOption400-9"] = {418,419,420}

--接任务
tNpcGossip[17400]["OptionChkFunc418"] = function ()
	local nTaskId = tInterServeTask_Killer_Task[2]
	if not Task_ChkTaskDetail(nTaskId) then
		return true
	end
	
	return false
end
tNpcGossip[17400]["OptionFunc418"] ="InterServeTask_Killer_AddTask2</N>17400"
tNpcGossip[17400]["OptionFunc419"] = "InterServeTask_Killer_DragonSucc</N>17400</N>7859"
--tNpcGossip[17400]["OptionFunc419"] ="InterServeTask_Killer_Monster</N>17400</N>7854"

--失败等级不足
tNpcGossip[17400]["Text400-10"] = {431,432}
tNpcGossip[17400]["Text431"] = tInterServeTask_Killer_Text[17400]["Text131"]
tNpcGossip[17400]["Text432"] = tInterServeTask_Killer_Text[17400]["Text132"]
tNpcGossip[17400]["Option421"] = tInterServeTask_Killer_Text[17400]["Option21"]
tNpcGossip[17400]["tOption400-10"] = {421}

--已击杀蛟龙
tNpcGossip[17400]["Text400-11"] = {433,434}
tNpcGossip[17400]["Text433"] = tInterServeTask_Killer_Text[17400]["Text133"]
tNpcGossip[17400]["Text434"] = tInterServeTask_Killer_Text[17400]["Text132"]
tNpcGossip[17400]["Option422"] = tInterServeTask_Killer_Text[17400]["Option22"]
tNpcGossip[17400]["tOption400-11"] = {422}

--未击杀
tNpcGossip[17400]["Text400-12"] = {435}
tNpcGossip[17400]["Text435"] = tInterServeTask_Killer_Text[17400]["Text134"]
tNpcGossip[17400]["Option423"] = tInterServeTask_Killer_Text[17400]["Option23"]
tNpcGossip[17400]["tOption400-12"] = {423}

--接受成功
tNpcGossip[17400]["Text400-13"] = {436}
tNpcGossip[17400]["Text436"] = tInterServeTask_Killer_Text[17400]["Text135"]
tNpcGossip[17400]["Option424"] = tInterServeTask_Killer_Text[17400]["Option24"]
tNpcGossip[17400]["tOption400-13"] = {424}

--背包已满
tNpcGossip[17400]["Text400-14"] = {451}
tNpcGossip[17400]["Text451"] = tInterServeTask_Killer_Text[17400]["Text136"] 
tNpcGossip[17400]["Option425"] = tInterServeTask_Killer_Text[17400]["Option25"]
tNpcGossip[17400]["tOption400-14"] = {425}

--天石上限已到
tNpcGossip[17400]["Text400-15"] = {452}
tNpcGossip[17400]["Text452"] = tInterServeTask_Killer_Text[17400]["Text140"] 
tNpcGossip[17400]["Option426"] = tInterServeTask_Killer_Text[17400]["Option28"]
tNpcGossip[17400]["tOption400-15"] = {426}

--成功完成
tNpcGossip[17400]["Text400-16"] = {453,454}
tNpcGossip[17400]["Text453"] =tInterServeTask_Killer_Text[17400]["Text138"]
tNpcGossip[17400]["Text454"] =tInterServeTask_Killer_Text[17400]["Text139"]
tNpcGossip[17400]["Option427"] = tInterServeTask_Killer_Text[17400]["Option27"]
tNpcGossip[17400]["tOption400-16"] = {427}



tNpcGossip[17400]["Option498"]=tInterServeTask_Killer_Text[17400]["Option400"]
tNpcGossip[17400]["Option499"]=tInterServeTask_Killer_Text[17400]["Option401"]

	
--怪物配置
-- //青龙 Boss
tMonster[7859] = tMonster[7859] or {}
tMonster[7859]["tFunction"] = tMonster[7859]["tFunction"] or {}
table.insert(tMonster[7859]["tFunction"],InterServeTask_Killer_HauntMonsterBoss)

-- //天机魔军  
tMonster[7854] = tMonster[7854] or {}
tMonster[7854]["tFunction"] = tMonster[7854]["tFunction"] or {}
table.insert(tMonster[7854]["tFunction"],InterServeTask_Killer_TeamEnjoy)

tItem[3007107] = tItem[3007107] or {}
tItem[3007107]["Function"] = function(nItemId,sItemName)
	InterServeTask_Killer_UseItemBox(nItemId)
end

-- //修为穷奇
-- tMonster[7855] = tMonster[7855] or {}
-- tMonster[7855]["tFunction"] = tMonster[7855]["tFunction"] or {}
-- table.insert(tMonster[7855]["tFunction"],InterServeTask_Killer_HauntMonsterBoss)

-- //强炼妖兽
-- tMonster[7856] = tMonster[7856] or {}
-- tMonster[7856]["tFunction"] = tMonster[7856]["tFunction"] or {}
-- table.insert(tMonster[7856]["tFunction"],InterServeTask_Killer_HauntMonsterBoss)

-- //百炼魔龙
-- tMonster[7857] = tMonster[7857] or {}
-- tMonster[7857]["tFunction"] = tMonster[7857]["tFunction"] or {}
-- table.insert(tMonster[7857]["tFunction"],InterServeTask_Killer_HauntMonsterBoss)

-- //通神炎魔
-- tMonster[7858] = tMonster[7858] or {}
-- tMonster[7858]["tFunction"] = tMonster[7858]["tFunction"] or {}
-- table.insert(tMonster[7858]["tFunction"],InterServeTask_Killer_HauntMonsterBoss)

--//杀人
tUserKilled["tFunction"] = tUserKilled["tFunction"] or {}
table.insert(tUserKilled["tFunction"],InterServeTask_Killer_TeamEnjoyMan)
--定时清
--tOntimerMin_HM[0000] = tOntimerMin_HM[0000] or {}
--table.insert(tOntimerMin_HM[0000],InterServeTask_Killer_ClearGlobal)

--table.insert(tSystem_PlayLogin_Func,InterServeTask_Killer_Login)