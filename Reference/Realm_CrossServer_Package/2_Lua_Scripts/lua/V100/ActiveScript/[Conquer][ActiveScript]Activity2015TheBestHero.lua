-----------------------------------------------------------------------------------------------------
--Name:			150716[英文征服][活动脚本]天下第一活动制作
--Purpose:		天下第一活动制作
--Creator: 		许乐
--Created:		2015/07/16
------------------------------------------------------------------------------------------------------
-- 命名前缀
--Activity2015TheBestHero_
------------------------------------------------------------------------------------------------------
-- 活动期间玩家进入场景第1层，共10层
-- 开始后玩家击杀其它玩家必得令牌，击杀小怪有概率获得令牌
-- 集齐5枚令牌就可以前进到上一层，在第10层再前进即为闯关成功
-- 被击杀的玩家掉落令牌
-- 活动结束，玩家会获得最后所在层数的结算奖励，闯关成功还可获得额外奖励
-----------------------------------------------------------------------------------------------------------
-- npc(11个)				18714-18715  18772-18780
-- npctype(2个)			3743-3744
-- map(10个)				3970-3979	
-- itemtype(11个)		3006970-3006980  3007030
-- monster(13个)		7841-7853
-- generator(43个)	17890-17932
-- cq_monster_type_magic(3个)	152-154
-- lua.ini					40085
-- logid						12000139
-- stc						13635-13636  13686-13690
-- 动态码					50932-50935

--------------- 掩码说明          
--stc(136,35) ==1		开始计时  记录玩家闯关成功的时间
--  				==2		闯关成功
--stc(136,36) ==n   	记录玩家最后所在的层数

--stc(136,86)			记录万能令牌使用时间
--stc(136,88)			记录背包信是否发放
--stc(136,89)			记录是否已领取了排名奖励
--stc(136,90)==1 		记录是否参加过此活动
--					==2 		是否已领取了活动奖励

--------------- 动态存储表说明
-- 50932	data0	记录龙珠掉落数量  1088000   限5个
-- 50932	data1	记录龙珠卷掉落数量  720028   限1个
-- 50932	data2	记录马+6掉落数量 723860  限1个
-- 50932	data3	记录赤炼石+6掉落数量 730006   限1个
-- 50932	data4	记录优质天怒宝石掉落数量 700103  限1个
-- 50932	data5	记录优质地灵宝石掉落数量 700123   限1个

-- 50933	data0	记录优质玄元宝石掉落数量 700073   限2个
-- 50933	data1	记录固化石掉落数量  723694   限1个
-- 50933	data2	记录30天时装外套（赠）掉落数量  193015   限5个
-- 50933	data3	记录外套碎片掉落数量  3006980   限5个

---------------- 排名记录
-- 50934	记录第一名玩家数据	data0	记录玩家ID	datastr0	玩家名字
-- 50934	记录第二名玩家数据	data1	记录玩家ID	datastr1		玩家名字
-- 50934	记录第三名玩家数据	data2	记录玩家ID	datastr2	玩家名字
-- 50934	记录第四名玩家数据	data3	记录玩家ID	datastr3	玩家名字
-- 50934	记录第五名玩家数据	data4	记录玩家ID	datastr4	玩家名字
-- 50934	记录第六名玩家数据	data5	记录玩家ID	datastr5	玩家名字
-- 50935	记录第七名玩家数据	data0	记录玩家ID	datastr0	玩家名字
-- 50935	记录第八名玩家数据	data1	记录玩家ID	datastr1		玩家名字
-- 50935	记录第九名玩家数据	data2	记录玩家ID	datastr2	玩家名字
-- 50935	记录第十名玩家数据	data3	记录玩家ID	datastr3	玩家名字

-----------------------------------------常量表配置-----------------------------------------------
-- 记录玩家在活动时间内通过npc出擂台时所在的层数
local nPlayerFloor = 1
-- 判断是否是第一次出现提示 105提示
local nIsFirst = true
-- 玩家身上的某种令牌数量  判断还差几个令牌
local nCardsNum = 0

local tActivity2015TheBestHero_Cont = {}
	--活动期间
	tActivity2015TheBestHero_Cont["BeforeActivity"] = "2015-07-27 00:00 2015-09-11 23:59"
	tActivity2015TheBestHero_Cont["Activity"] = "2015-09-12 00:00 2015-09-25 23:59"
	tActivity2015TheBestHero_Cont["AfterActivity"] = "2015-09-26 00:00 2016-09-01 23:59"
	
	tActivity2015TheBestHero_Cont["ActivityTime"] = "19:30 19:40"	--活动时间点
	tActivity2015TheBestHero_Cont["EndingTime"] = "19:41 23:59"	---当天擂台结束，且0点前
	tActivity2015TheBestHero_Cont["RankingTime"] = "19:30 23:59"	---当天擂台开始时到0点前
	tActivity2015TheBestHero_Cont["ClearLimit"] = "00:00 00:01"  --清理礼包限制物品表
	
	--玩家等级要求
	tActivity2015TheBestHero_Cont["Metempsychosis"] = 0
	tActivity2015TheBestHero_Cont["Level"] = 120
	tActivity2015TheBestHero_Cont["LevelTop"] = 140

--NPC坐标
local tActivity2015TheBestHero_Npc = {}
	-- 18714 擂台管理员
	tActivity2015TheBestHero_Npc[18714] = {}
	tActivity2015TheBestHero_Npc[18714]["CellX"] = 315
	tActivity2015TheBestHero_Npc[18714]["CellY"] = 288
	tActivity2015TheBestHero_Npc[18714]["Mapid"] = 1002
	tActivity2015TheBestHero_Npc[18714]["NpcId"] = 18714
	-- 18715 行脚商人(第一层)
	tActivity2015TheBestHero_Npc[18715] = {}
	tActivity2015TheBestHero_Npc[18715]["CellX"] =143
	tActivity2015TheBestHero_Npc[18715]["CellY"] = 165
	tActivity2015TheBestHero_Npc[18715]["Mapid"] = 3970
	tActivity2015TheBestHero_Npc[18715]["NpcId"] = 18715
	tActivity2015TheBestHero_Npc["BoundCX"] = 3
	tActivity2015TheBestHero_Npc["BoundCY"] = 3

local tActivity2015TheBestHero_Map = {}
	tActivity2015TheBestHero_Map[1] = 3970
	tActivity2015TheBestHero_Map[2] = 3971
	tActivity2015TheBestHero_Map[3] = 3972
	tActivity2015TheBestHero_Map[4] = 3973
	tActivity2015TheBestHero_Map[5] = 3974
	tActivity2015TheBestHero_Map[6] = 3975
	tActivity2015TheBestHero_Map[7] = 3976
	tActivity2015TheBestHero_Map[8] = 3977
	tActivity2015TheBestHero_Map[9] = 3978
	tActivity2015TheBestHero_Map[10] = 3979
	
	tActivity2015TheBestHero_Map[3970] = 1
	tActivity2015TheBestHero_Map[3971] = 2
	tActivity2015TheBestHero_Map[3972] = 3
	tActivity2015TheBestHero_Map[3973] = 4
	tActivity2015TheBestHero_Map[3974] = 5
	tActivity2015TheBestHero_Map[3975] = 6
	tActivity2015TheBestHero_Map[3976] = 7
	tActivity2015TheBestHero_Map[3977] = 8
	tActivity2015TheBestHero_Map[3978] = 9
	tActivity2015TheBestHero_Map[3979] = 10

--掩码
local tActivity2015TheBestHero_Stc = {}
	--stc(136,35) ==1		开始计时  记录玩家闯关成功的时间 	==2		闯关成功
	tActivity2015TheBestHero_Stc[1] = {}
	tActivity2015TheBestHero_Stc[1]["EventType"] = 136
	tActivity2015TheBestHero_Stc[1]["DataType"] = 35
	tActivity2015TheBestHero_Stc[1]["StcData"] = 1
	tActivity2015TheBestHero_Stc[1]["Complete"] = 2
	tActivity2015TheBestHero_Stc[1]["Time_1"] = 300
	tActivity2015TheBestHero_Stc[1]["Time_2"] = 360
	tActivity2015TheBestHero_Stc[1]["Time_3"] = 420
	tActivity2015TheBestHero_Stc[1]["Time_4"] = 480
	tActivity2015TheBestHero_Stc[1]["Time_5"] = 540
	-- stc(136,36) 记录玩家最后所在的层数   ==n  表示在第n层
	tActivity2015TheBestHero_Stc[2] = {}
	tActivity2015TheBestHero_Stc[2]["EventType"] = 136
	tActivity2015TheBestHero_Stc[2]["DataType"] = 36
	tActivity2015TheBestHero_Stc[2]["Complete"] = 11
	--stc(136,86)	记录 万能令牌 使用时间  30s
	tActivity2015TheBestHero_Stc[3] = {}
	tActivity2015TheBestHero_Stc[3]["EventType"] = 136
	tActivity2015TheBestHero_Stc[3]["DataType"] = 86
	tActivity2015TheBestHero_Stc[3]["LimitTime"] = 30
	--stc(136,89)	记录是否已领取了排名奖励
	tActivity2015TheBestHero_Stc[6] = {}
	tActivity2015TheBestHero_Stc[6]["EventType"] = 136
	tActivity2015TheBestHero_Stc[6]["DataType"] = 89
	tActivity2015TheBestHero_Stc[6]["Complete"] = 1
	--stc(136,90)	==1 		记录是否参加过此活动	==2 		记录是否已领取了活动奖励
	tActivity2015TheBestHero_Stc[7] = {}
	tActivity2015TheBestHero_Stc[7]["EventType"] = 136
	tActivity2015TheBestHero_Stc[7]["DataType"] = 90
	tActivity2015TheBestHero_Stc[7]["StcData"] = 1
	tActivity2015TheBestHero_Stc[7]["Complete"] = 2
	
--物品
local tActivity2015TheBestHero_Item = {}	
	tActivity2015TheBestHero_Item["Item_num1"] = 5		---判断令牌可兑换的数量
	tActivity2015TheBestHero_Item["Item_num2"] = 4
	tActivity2015TheBestHero_Item["Item_num3"] = 3	
	tActivity2015TheBestHero_Item["Item3006970"] = 3006970	--万能金牌
	tActivity2015TheBestHero_Item["Item3006971"] = 3006971		---侠客令牌
	tActivity2015TheBestHero_Item["Item3006972"] = 3006972	---精英令牌
	tActivity2015TheBestHero_Item["Item3006973"] = 3006973	---豪杰令牌
	tActivity2015TheBestHero_Item["Item3006974"] = 3006974	---霸主令牌
	tActivity2015TheBestHero_Item["Item3006975"] = 3006975	--增益丹
	tActivity2015TheBestHero_Item["Item3006976"] = 3006976	--增益符
	tActivity2015TheBestHero_Item["Item3006977"] = 3006977	--礼包碎片
	tActivity2015TheBestHero_Item["Item3006978"] = 3006978	--小礼包
	tActivity2015TheBestHero_Item["Item3006979"] = 3006979	--超级礼包
	tActivity2015TheBestHero_Item["Item3006980"] = 3006980	--外套碎片
	tActivity2015TheBestHero_Item["Item3007030"] = 3007030	--背包信

	--增益丹  使用后增加状态配置
	tActivity2015TheBestHero_Item[3006975] = {}
	tActivity2015TheBestHero_Item[3006975][1] = 143	-- 最终物理伤害加成 +1000
	tActivity2015TheBestHero_Item[3006975][2] = 144	-- 最终法术伤害加成 +1000
	tActivity2015TheBestHero_Item[3006975][3] = 141	-- 最终物理伤害减免 +1000
	tActivity2015TheBestHero_Item[3006975][4] = 142	-- 最终法术伤害减免  +1000
	tActivity2015TheBestHero_Item[3006975][5] = 133	-- 物理暴击 +10%
	tActivity2015TheBestHero_Item[3006975][6] = 134	-- 法术暴击 +10%
	tActivity2015TheBestHero_Item[3006975][143] = 1000
	tActivity2015TheBestHero_Item[3006975][144] = 1000
	tActivity2015TheBestHero_Item[3006975][141] = 1000
	tActivity2015TheBestHero_Item[3006975][142] = 1000
	tActivity2015TheBestHero_Item[3006975][133] = 10
	tActivity2015TheBestHero_Item[3006975][134] = 10
	tActivity2015TheBestHero_Item[3006975]["Secs"] = 60
	tActivity2015TheBestHero_Item[3006975]["Times"] = 1
	tActivity2015TheBestHero_Item[3006975]["RemainTime"] = 60
	tActivity2015TheBestHero_Item[3006975]["EndTime"] = 1
	tActivity2015TheBestHero_Item[3006975]["Recordable"] = 1
	tActivity2015TheBestHero_Item[3006975]["Log"] = "0,0,3006975,1,12000139,2,143[144][141][142][133][134],1000[1000][1000][1000][10][10]"

	tActivity2015TheBestHero_Item[3006976] = {}
	tActivity2015TheBestHero_Item[3006976][1] = 143
	tActivity2015TheBestHero_Item[3006976][2] = 144
	tActivity2015TheBestHero_Item[3006976][3] = 141
	tActivity2015TheBestHero_Item[3006976][4] = 142
	tActivity2015TheBestHero_Item[3006976][5] = 133
	tActivity2015TheBestHero_Item[3006976][6] = 134
	tActivity2015TheBestHero_Item[3006976][143] = 1000
	tActivity2015TheBestHero_Item[3006976][144] = 1000
	tActivity2015TheBestHero_Item[3006976][141] = 1000
	tActivity2015TheBestHero_Item[3006976][142] = 1000
	tActivity2015TheBestHero_Item[3006976][133] = 10
	tActivity2015TheBestHero_Item[3006976][134] = 10
	tActivity2015TheBestHero_Item[3006976]["Secs"] = 600
	tActivity2015TheBestHero_Item[3006976]["Times"] = 1
	tActivity2015TheBestHero_Item[3006976]["RemainTime"] = 600
	tActivity2015TheBestHero_Item[3006976]["EndTime"] = 1
	tActivity2015TheBestHero_Item[3006976]["Recordable"] = 1
	tActivity2015TheBestHero_Item[3006976]["Log"] = "0,0,3006976,1,12000139,2,143[144][141][142][133][134],1000[1000][1000][1000][10][10]"

local tActivity2015TheBestHero_Data = {}
	tActivity2015TheBestHero_Data["BagSpace_1"] = 1
	tActivity2015TheBestHero_Data["BagSpace_9"] = 9
	--背包信相关数据
	tActivity2015TheBestHero_Data["Add30Exp"] = 30
	tActivity2015TheBestHero_Data["Add15Cul"] = 15
	--天石购买相关
	tActivity2015TheBestHero_Data["BuyCard"] = 40
	tActivity2015TheBestHero_Data["BuyTool"] = 20
	tActivity2015TheBestHero_Data["Del40Emoney"] = -40
	tActivity2015TheBestHero_Data["Del20Emoney"] = -20
	
--获得礼包的特效
local tActivity2015TheBestHero_Effect = {}
	tActivity2015TheBestHero_Effect[1] = "self"
	tActivity2015TheBestHero_Effect[2] = {}						----升层光效
	tActivity2015TheBestHero_Effect[2][1] = "CountF2"
	tActivity2015TheBestHero_Effect[2][2] = "CountF3"
	tActivity2015TheBestHero_Effect[2][3] = "CountF4"
	tActivity2015TheBestHero_Effect[2][4] = "CountF5"
	tActivity2015TheBestHero_Effect[2][5] = "CountF6"
	tActivity2015TheBestHero_Effect[2][6] = "CountF7"
	tActivity2015TheBestHero_Effect[2][7] = "CountF8"
	tActivity2015TheBestHero_Effect[2][8] = "CountF9"
	tActivity2015TheBestHero_Effect[2][9] = "CountF10"
	tActivity2015TheBestHero_Effect[3] = "accession"		----闯关成功和升层光效
	tActivity2015TheBestHero_Effect[4] = "heal2-1"			----碎片合成礼包光效
	tActivity2015TheBestHero_Effect[5] = "eidolon"			----打开武艺超群礼包光效
	tActivity2015TheBestHero_Effect[6] = "zf2-e127"		----玩家身上存在增益状态时的光效
	tActivity2015TheBestHero_Effect[7] = "movego"			----进入地图光效
	tActivity2015TheBestHero_Effect[8] = "moveback"		----出地图光效
	tActivity2015TheBestHero_Effect[9] = "zf2-e280"		----打开盖世无双礼包光效
	tActivity2015TheBestHero_Effect[10] = "LevelUp"		----领取各种奖励光效
	tActivity2015TheBestHero_Effect[11] = "addexp01"	----击败宝箱光效
	tActivity2015TheBestHero_Effect[12] = "angelwing"	----获得令牌光效
	
--LOG
local tActivity2015TheBestHero_Log = {}
	tActivity2015TheBestHero_Log["PKOwnCards"] = {}									--玩家PK获得令牌log
	tActivity2015TheBestHero_Log["PKOwnCards"][1] = "0,0,0,0,12000139,2,3006971,1"
	tActivity2015TheBestHero_Log["PKOwnCards"][2] = "0,0,0,0,12000139,2,3006972,1"
	tActivity2015TheBestHero_Log["PKOwnCards"][3] = "0,0,0,0,12000139,2,3006973,1"
	tActivity2015TheBestHero_Log["PKOwnCards"][4] = "0,0 0,0,12000139,2,3006974,1"
	tActivity2015TheBestHero_Log["GetSmallBag"] = "0,0,3006977,5,12000139,2,3006978,1"	--通过碎片合成小礼包的log
	tActivity2015TheBestHero_Log["GetSuperBag"] = "0,0,3006978,5,12000139,2,3006979,1"	--通过小礼包合成超级礼包的log
	tActivity2015TheBestHero_Log["GetLetter"] = "0,0,0,0,12000139,2,3007030,1"	--上线获得背包信
	tActivity2015TheBestHero_Log["DelItem"] = "0,0,%s,1,12000139,2,0,0"	--令牌过时间删除log
	tActivity2015TheBestHero_Log["BuyCard"] = "350	20076	0	0	40	"	--购买万能金牌的log
	tActivity2015TheBestHero_Log["BuyTool"] = "350	20077	0	0	20	"	--购买增益符的log
	tActivity2015TheBestHero_Log["Participation"] = {}		--记录每层擂台的参与人数
	tActivity2015TheBestHero_Log["Participation"][1] = "350	20083	0	0	1	"
	tActivity2015TheBestHero_Log["Participation"][2] = "350	20084	0	0	1	"
	tActivity2015TheBestHero_Log["Participation"][3] = "350	20085	0	0	1	"
	tActivity2015TheBestHero_Log["Participation"][4] = "350	20086	0	0	1	"
	tActivity2015TheBestHero_Log["Participation"][5] = "350	20087	0	0	1	"
	tActivity2015TheBestHero_Log["Participation"][6] = "350	20088	0	0	1	"
	tActivity2015TheBestHero_Log["Participation"][7] = "350	20089	0	0	1	"
	tActivity2015TheBestHero_Log["Participation"][8] = "350	20090	0	0	1	"
	tActivity2015TheBestHero_Log["Participation"][9] = "350	20091	0	0	1	"
	tActivity2015TheBestHero_Log["Participation"][10] = "350	20092	0	0	1	"
	
 -- 动态存储表配置   (开启超级礼包中限制物品统计数量)
local tActivity2015TheBestHero_Global = {}
	tActivity2015TheBestHero_Global[1] = {}			-- 记录龙珠掉落数量  1088000   限5个
	tActivity2015TheBestHero_Global[1]["GlobalId"] = 50932
	tActivity2015TheBestHero_Global[1]["GlobalData"] = 0
	tActivity2015TheBestHero_Global[1]["MaxData"] = 5
	tActivity2015TheBestHero_Global[2] = {}			-- 记录龙珠卷掉落数量  720028   限1个
	tActivity2015TheBestHero_Global[2]["GlobalId"] = 50932
	tActivity2015TheBestHero_Global[2]["GlobalData"] = 1
	tActivity2015TheBestHero_Global[2]["MaxData"] = 1
	tActivity2015TheBestHero_Global[3] = {}			-- 记录马+6掉落数量 723860  限1个
	tActivity2015TheBestHero_Global[3]["GlobalId"] = 50932
	tActivity2015TheBestHero_Global[3]["GlobalData"] = 2
	tActivity2015TheBestHero_Global[3]["MaxData"] = 1
	tActivity2015TheBestHero_Global[4] = {}			-- 记录赤炼石+6掉落数量 730006   限1个
	tActivity2015TheBestHero_Global[4]["GlobalId"] = 50932
	tActivity2015TheBestHero_Global[4]["GlobalData"] = 3
	tActivity2015TheBestHero_Global[4]["MaxData"] = 1
	tActivity2015TheBestHero_Global[5] = {}			-- 记录优质天怒宝石掉落数量 700103  限1个
	tActivity2015TheBestHero_Global[5]["GlobalId"] = 50932
	tActivity2015TheBestHero_Global[5]["GlobalData"] = 4
	tActivity2015TheBestHero_Global[5]["MaxData"] = 1
	tActivity2015TheBestHero_Global[6] = {}			-- 记录优质地灵宝石掉落数量 700123   限1个
	tActivity2015TheBestHero_Global[6]["GlobalId"] = 50932
	tActivity2015TheBestHero_Global[6]["GlobalData"] = 5
	tActivity2015TheBestHero_Global[6]["MaxData"] = 1
	tActivity2015TheBestHero_Global[7] = {}			-- 记录优质玄元宝石掉落数量 700073   限2个
	tActivity2015TheBestHero_Global[7]["GlobalId"] = 50933
	tActivity2015TheBestHero_Global[7]["GlobalData"] = 0
	tActivity2015TheBestHero_Global[7]["MaxData"] = 2
	tActivity2015TheBestHero_Global[8] = {}			-- 记录固化石掉落数量  723694   限1个
	tActivity2015TheBestHero_Global[8]["GlobalId"] = 50933
	tActivity2015TheBestHero_Global[8]["GlobalData"] = 1
	tActivity2015TheBestHero_Global[8]["MaxData"] = 1
	tActivity2015TheBestHero_Global[9] = {}			-- 记录30天时装外套（赠）掉落数量  193015   限5个
	tActivity2015TheBestHero_Global[9]["GlobalId"] = 50933
	tActivity2015TheBestHero_Global[9]["GlobalData"] = 2
	tActivity2015TheBestHero_Global[9]["MaxData"] = 5
	tActivity2015TheBestHero_Global[10] = {}			-- 记录外套碎片掉落数量  3006980   限5个
	tActivity2015TheBestHero_Global[10]["GlobalId"] = 50933
	tActivity2015TheBestHero_Global[10]["GlobalData"] = 3
	tActivity2015TheBestHero_Global[10]["MaxData"] = 5
	
--排名动态记录
local tActivity2015TheBestHero_List = {}
	tActivity2015TheBestHero_List[1] = {}
	tActivity2015TheBestHero_List[1]["GlobalId"] = 50934
	tActivity2015TheBestHero_List[1]["GlobalPos"] = 0
	tActivity2015TheBestHero_List[2] = {}
	tActivity2015TheBestHero_List[2]["GlobalId"] = 50934
	tActivity2015TheBestHero_List[2]["GlobalPos"] = 1
	tActivity2015TheBestHero_List[3] = {}
	tActivity2015TheBestHero_List[3]["GlobalId"] = 50934
	tActivity2015TheBestHero_List[3]["GlobalPos"] = 2
	tActivity2015TheBestHero_List[4] = {}
	tActivity2015TheBestHero_List[4]["GlobalId"] = 50934
	tActivity2015TheBestHero_List[4]["GlobalPos"] = 3
	tActivity2015TheBestHero_List[5] = {}
	tActivity2015TheBestHero_List[5]["GlobalId"] = 50934
	tActivity2015TheBestHero_List[5]["GlobalPos"] = 4
	tActivity2015TheBestHero_List[6] = {}
	tActivity2015TheBestHero_List[6]["GlobalId"] = 50934
	tActivity2015TheBestHero_List[6]["GlobalPos"] = 5
	tActivity2015TheBestHero_List[7] = {}
	tActivity2015TheBestHero_List[7]["GlobalId"] = 50935
	tActivity2015TheBestHero_List[7]["GlobalPos"] = 0
	tActivity2015TheBestHero_List[8] = {}
	tActivity2015TheBestHero_List[8]["GlobalId"] = 50935
	tActivity2015TheBestHero_List[8]["GlobalPos"] = 1
	tActivity2015TheBestHero_List[9] = {}
	tActivity2015TheBestHero_List[9]["GlobalId"] = 50935
	tActivity2015TheBestHero_List[9]["GlobalPos"] = 2
	tActivity2015TheBestHero_List[10] = {}
	tActivity2015TheBestHero_List[10]["GlobalId"] = 50935
	tActivity2015TheBestHero_List[10]["GlobalPos"] = 3
	
--奖励配置
local tActivity2015TheBestHero_Reward = {}
	--升层奖励: 礼包碎片 id = 3006977
	tActivity2015TheBestHero_Reward["UpFloor"] = {}
	tActivity2015TheBestHero_Reward["UpFloor"]["SendInMap"] = 1
	tActivity2015TheBestHero_Reward["UpFloor"][3970] = 1
	tActivity2015TheBestHero_Reward["UpFloor"][3971] = 1
	tActivity2015TheBestHero_Reward["UpFloor"][3972] = 2
	tActivity2015TheBestHero_Reward["UpFloor"][3973] = 1
	tActivity2015TheBestHero_Reward["UpFloor"][3974] = 1
	tActivity2015TheBestHero_Reward["UpFloor"][3975] = 3
	tActivity2015TheBestHero_Reward["UpFloor"][3976] = 2
	tActivity2015TheBestHero_Reward["UpFloor"][3977] = 3
	tActivity2015TheBestHero_Reward["UpFloor"][3978] = 5
	--闯关成功
	tActivity2015TheBestHero_Reward["UpFloor"][3979] = 5
	tActivity2015TheBestHero_Reward["UpFloor"]["Log"] = "0,0,0,0,12000139,2,3006977,%s"

--礼包奖励
--小礼包 ID = 3006978
	tActivity2015TheBestHero_Reward[3006978] = {}
	tActivity2015TheBestHero_Reward[3006978][1] = {}
	tActivity2015TheBestHero_Reward[3006978][1]["ItemChanceSum"] = 10000
	-- 通神丹（赠）*2    -- 10%	  3003125		SpecialTrainingPill   accumulate_limit = 100
	tActivity2015TheBestHero_Reward[3006978][1][1] = {}
	tActivity2015TheBestHero_Reward[3006978][1][1]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006978][1][1]["ItemChance"] = 1000
	tActivity2015TheBestHero_Reward[3006978][1][1]["Item_1"] = 3003125
	tActivity2015TheBestHero_Reward[3006978][1][1]["ItemAttr"] = "0 2 3"
	tActivity2015TheBestHero_Reward[3006978][1][1]["Index"] = 1
	tActivity2015TheBestHero_Reward[3006978][1][1]["Log"] = "0,0,0,0,12000139,2,3003125,2"
	-- 免费强炼丹（赠）*2    -- 10%   3003124		FavoredTrainingPill   accumulate_limit = 100
	tActivity2015TheBestHero_Reward[3006978][1][2] = {}
	tActivity2015TheBestHero_Reward[3006978][1][2]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006978][1][2]["ItemChance"] = 1000
	tActivity2015TheBestHero_Reward[3006978][1][2]["Item_1"] = 3003124
	tActivity2015TheBestHero_Reward[3006978][1][2]["ItemAttr"] = "0 2 3"
	tActivity2015TheBestHero_Reward[3006978][1][2]["Index"] = 2
	tActivity2015TheBestHero_Reward[3006978][1][2]["Log"] = "0,0,0,0,12000139,2,3003124,2"
	-- 聚神丹（赠）*2     -- 10%  723700		ExpBall	 accumulate_limit = 10
	tActivity2015TheBestHero_Reward[3006978][1][3] = {}
	tActivity2015TheBestHero_Reward[3006978][1][3]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006978][1][3]["ItemChance"] = 1000
	tActivity2015TheBestHero_Reward[3006978][1][3]["Item_1"] = 723700
	tActivity2015TheBestHero_Reward[3006978][1][3]["ItemAttr"] = "0 2 3"
	tActivity2015TheBestHero_Reward[3006978][1][3]["Index"] = 3
	tActivity2015TheBestHero_Reward[3006978][1][3]["Log"] = "0,0,0,0,12000139,2,723700,2"
	-- 200气力包（赠）   -- 10%   3001411		200PointsChiPack
	tActivity2015TheBestHero_Reward[3006978][1][4] = {}
	tActivity2015TheBestHero_Reward[3006978][1][4]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006978][1][4]["ItemChance"] = 1000
	tActivity2015TheBestHero_Reward[3006978][1][4]["Item_1"] = 3001411
	tActivity2015TheBestHero_Reward[3006978][1][4]["ItemAttr"] = "0 1 3"
	tActivity2015TheBestHero_Reward[3006978][1][4]["Index"] = 4
	tActivity2015TheBestHero_Reward[3006978][1][4]["Log"] = "0,0,0,0,12000139,2,3001411,1"
	-- 流星卷   -- 10%   720027		MeteorScroll
	tActivity2015TheBestHero_Reward[3006978][1][5] = {}
	tActivity2015TheBestHero_Reward[3006978][1][5]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006978][1][5]["ItemChance"] = 1000
	tActivity2015TheBestHero_Reward[3006978][1][5]["Item_1"] = 720027
	tActivity2015TheBestHero_Reward[3006978][1][5]["ItemAttr"] = "0 1"
	tActivity2015TheBestHero_Reward[3006978][1][5]["Index"] = 5
	tActivity2015TheBestHero_Reward[3006978][1][5]["Log"] = "0,0,0,0,12000139,2,720027,1"
	-- 龙珠（赠）   -- 1%   1088000		DragonBall
	tActivity2015TheBestHero_Reward[3006978][1][6] = {}
	tActivity2015TheBestHero_Reward[3006978][1][6]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006978][1][6]["ItemChance"] = 100
	tActivity2015TheBestHero_Reward[3006978][1][6]["Item_1"] = 1088000
	tActivity2015TheBestHero_Reward[3006978][1][6]["ItemAttr"] = "0 1 3"
	tActivity2015TheBestHero_Reward[3006978][1][6]["Index"] = 6
	tActivity2015TheBestHero_Reward[3006978][1][6]["Log"] = "0,0,0,0,12000139,2,1088000,1"
	-- 马+1（赠）*2    -- 6%   723855		+1MaroonSteedPack
	tActivity2015TheBestHero_Reward[3006978][1][7] = {}
	tActivity2015TheBestHero_Reward[3006978][1][7]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006978][1][7]["ItemChance"] = 600
	tActivity2015TheBestHero_Reward[3006978][1][7]["Item_1"] = 723855
	tActivity2015TheBestHero_Reward[3006978][1][7]["ItemAttr"] = "0 2 3"
	tActivity2015TheBestHero_Reward[3006978][1][7]["Index"] = 7
	tActivity2015TheBestHero_Reward[3006978][1][7]["Log"] = "0,0,0,0,12000139,2,723855,2"
	-- 马+2（赠）    -- 5%   3001414		+2MaroonSteedBox
	tActivity2015TheBestHero_Reward[3006978][1][8] = {}
	tActivity2015TheBestHero_Reward[3006978][1][8]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006978][1][8]["ItemChance"] = 500
	tActivity2015TheBestHero_Reward[3006978][1][8]["Item_1"] = 3001414
	tActivity2015TheBestHero_Reward[3006978][1][8]["ItemAttr"] = "0 1 3"
	tActivity2015TheBestHero_Reward[3006978][1][8]["Index"] = 8
	tActivity2015TheBestHero_Reward[3006978][1][8]["Log"] = "0,0,0,0,12000139,2,3001414,1"
	-- 赤炼石+1（赠）*2      -- 10%   730001		Stone
	tActivity2015TheBestHero_Reward[3006978][1][9] = {}
	tActivity2015TheBestHero_Reward[3006978][1][9]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006978][1][9]["ItemChance"] = 1000
	tActivity2015TheBestHero_Reward[3006978][1][9]["Item_1"] = 730001
	tActivity2015TheBestHero_Reward[3006978][1][9]["ItemAttr"] = "0 2 3"
	tActivity2015TheBestHero_Reward[3006978][1][9]["Index"] = 9
	tActivity2015TheBestHero_Reward[3006978][1][9]["Log"] = "0,0,0,0,12000139,2,730001,2"
	-- 赤炼石+2（赠）   -- 5%	730002		Stone
	tActivity2015TheBestHero_Reward[3006978][1][10] = {}
	tActivity2015TheBestHero_Reward[3006978][1][10]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006978][1][10]["ItemChance"] = 500
	tActivity2015TheBestHero_Reward[3006978][1][10]["Item_1"] = 730002
	tActivity2015TheBestHero_Reward[3006978][1][10]["ItemAttr"] = "0 1 3"
	tActivity2015TheBestHero_Reward[3006978][1][10]["Index"] = 10
	tActivity2015TheBestHero_Reward[3006978][1][10]["Log"] = "0,0,0,0,12000139,2,730002,1"
	-- 良品随机宝石袋*2     -- 10%   3003879		EliteGemBag
	tActivity2015TheBestHero_Reward[3006978][1][11] = {}
	tActivity2015TheBestHero_Reward[3006978][1][11]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006978][1][11]["ItemChance"] = 1000
	tActivity2015TheBestHero_Reward[3006978][1][11]["Item_1"] = 3003879
	tActivity2015TheBestHero_Reward[3006978][1][11]["ItemAttr"] = "0 2"
	tActivity2015TheBestHero_Reward[3006978][1][11]["Index"] = 11
	tActivity2015TheBestHero_Reward[3006978][1][11]["Log"] = "0,0,0,0,12000139,2,3003879,2"
	-- 六阶神魂随机包 -- 5%   3004059			P6RandomSoulPack
	tActivity2015TheBestHero_Reward[3006978][1][12] = {}
	tActivity2015TheBestHero_Reward[3006978][1][12]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006978][1][12]["ItemChance"] = 500
	tActivity2015TheBestHero_Reward[3006978][1][12]["Item_1"] = 3004059
	tActivity2015TheBestHero_Reward[3006978][1][12]["ItemAttr"] = "0 1"
	tActivity2015TheBestHero_Reward[3006978][1][12]["Index"] = 12
	tActivity2015TheBestHero_Reward[3006978][1][12]["Log"] = "0,0,0,0,12000139,2,3004059,1"
	-- 7天时装外套（赠）   -- 8%    193015		FlameDragon
	tActivity2015TheBestHero_Reward[3006978][1][13] = {}
	tActivity2015TheBestHero_Reward[3006978][1][13]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006978][1][13]["ItemChance"] = 800
	tActivity2015TheBestHero_Reward[3006978][1][13]["Item_1"] = 193015
	tActivity2015TheBestHero_Reward[3006978][1][13]["ItemAttr"] = "0 1 3 10080"
	tActivity2015TheBestHero_Reward[3006978][1][13]["Index"] = 13
	tActivity2015TheBestHero_Reward[3006978][1][13]["Log"] = "0,0,0,0,12000139,2,193015,1"

--超级礼包 ID = 3006979
	tActivity2015TheBestHero_Reward[3006979] = {}
	tActivity2015TheBestHero_Reward[3006979][1] = {}
	tActivity2015TheBestHero_Reward[3006979][1]["ItemChanceSum"] = 10000
	-- 回气丹（赠）	  10.00%     729242		Vital~Pill
	tActivity2015TheBestHero_Reward[3006979][1][1] = {}
	tActivity2015TheBestHero_Reward[3006979][1][1]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][1]["ItemChance"] = 1000
	tActivity2015TheBestHero_Reward[3006979][1][1]["Item_1"] = 729242
	tActivity2015TheBestHero_Reward[3006979][1][1]["ItemAttr"] = "0 1 3"
	tActivity2015TheBestHero_Reward[3006979][1][1]["Index"] = 1
	tActivity2015TheBestHero_Reward[3006979][1][1]["Log"] = "0,0,0,0,12000139,2,729242,1"
	-- 护心丹*2	10.00%     3002029		ProtectionPill
	tActivity2015TheBestHero_Reward[3006979][1][2] = {}
	tActivity2015TheBestHero_Reward[3006979][1][2]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][2]["ItemChance"] = 1000
	tActivity2015TheBestHero_Reward[3006979][1][2]["Item_1"] = 3002029
	tActivity2015TheBestHero_Reward[3006979][1][2]["ItemAttr"] = "0 2 0 0 1"
	tActivity2015TheBestHero_Reward[3006979][1][2]["Index"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][2]["Log"] = "0,0,0,0,12000139,2,3002029,2"
	-- 梦幻强炼丹礼包/5个丹（赠）	    10.00%    3003134		FavoredTrainingPack(5)
	-- 改为 免费强炼丹（赠）*5		3003124
	tActivity2015TheBestHero_Reward[3006979][1][3] = {}
	tActivity2015TheBestHero_Reward[3006979][1][3]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][3]["ItemChance"] = 1000
	tActivity2015TheBestHero_Reward[3006979][1][3]["Item_1"] = 3003124
	tActivity2015TheBestHero_Reward[3006979][1][3]["ItemAttr"] = "0 5 3"
	tActivity2015TheBestHero_Reward[3006979][1][3]["Index"] = 3
	tActivity2015TheBestHero_Reward[3006979][1][3]["Log"] = "0,0,0,0,12000139,2,3003124,5"
	-- 梦幻通神丹礼包/5个丹（赠）	9.00%      3003141		SpecialTrainingPack(5)
	-- 改为 通神丹（赠）*5		3003125
	tActivity2015TheBestHero_Reward[3006979][1][4] = {}
	tActivity2015TheBestHero_Reward[3006979][1][4]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][4]["ItemChance"] = 900
	tActivity2015TheBestHero_Reward[3006979][1][4]["Item_1"] = 3003125
	tActivity2015TheBestHero_Reward[3006979][1][4]["ItemAttr"] = "0 5 3"
	tActivity2015TheBestHero_Reward[3006979][1][4]["Index"] = 4
	tActivity2015TheBestHero_Reward[3006979][1][4]["Log"] = "0,0,0,0,12000139,2,3003125,5"
	-- 究极通神丹（赠）		9.00%m     3003126		SeniorTrainingPill    accumulate_limit = 100
	tActivity2015TheBestHero_Reward[3006979][1][5] = {}
	tActivity2015TheBestHero_Reward[3006979][1][5]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][5]["ItemChance"] = 900
	tActivity2015TheBestHero_Reward[3006979][1][5]["Item_1"] = 3003126
	tActivity2015TheBestHero_Reward[3006979][1][5]["ItemAttr"] = "0 1 3"
	tActivity2015TheBestHero_Reward[3006979][1][5]["Index"] = 5
	tActivity2015TheBestHero_Reward[3006979][1][5]["Log"] = "0,0,0,0,12000139,2,3003126,1"
	-- 优质龙恨宝石		5.00%     700013		DragonGem
	tActivity2015TheBestHero_Reward[3006979][1][6] = {}
	tActivity2015TheBestHero_Reward[3006979][1][6]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][6]["ItemChance"] = 500
	tActivity2015TheBestHero_Reward[3006979][1][6]["Item_1"] = 700013
	tActivity2015TheBestHero_Reward[3006979][1][6]["ItemAttr"] = "0 1"
	tActivity2015TheBestHero_Reward[3006979][1][6]["Index"] = 6
	tActivity2015TheBestHero_Reward[3006979][1][6]["Log"] = "0,0,0,0,12000139,2,700013,1"
	-- 优质凤吟宝石		2.00%      700003		PhoenixGem
	tActivity2015TheBestHero_Reward[3006979][1][7] = {}
	tActivity2015TheBestHero_Reward[3006979][1][7]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][7]["ItemChance"] = 200
	tActivity2015TheBestHero_Reward[3006979][1][7]["Item_1"] = 700003
	tActivity2015TheBestHero_Reward[3006979][1][7]["ItemAttr"] = "0 1"
	tActivity2015TheBestHero_Reward[3006979][1][7]["Index"] = 7
	tActivity2015TheBestHero_Reward[3006979][1][7]["Log"] = "0,0,0,0,12000139,2,700003,1"
	-- 龙珠		2.50%     限量（每天限5个）  1088000		DragonBall
	tActivity2015TheBestHero_Reward[3006979][1][8] = {}
	tActivity2015TheBestHero_Reward[3006979][1][8]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][8]["ItemChance"] = 250
	tActivity2015TheBestHero_Reward[3006979][1][8]["Item_1"] = 1088000
	tActivity2015TheBestHero_Reward[3006979][1][8]["IsLimited"] = true
	tActivity2015TheBestHero_Reward[3006979][1][8]["LimitIndex"] = 1
	tActivity2015TheBestHero_Reward[3006979][1][8]["LimitedNum"] = 5
	tActivity2015TheBestHero_Reward[3006979][1][8]["ItemAttr"] = "0 1"
	tActivity2015TheBestHero_Reward[3006979][1][8]["Index"] = 8
	tActivity2015TheBestHero_Reward[3006979][1][8]["Log"] = "0,0,0,0,12000139,2,1088000,1"
	-- 龙珠卷	0.20%    限量（每天限1个）   720028		DBScroll
	tActivity2015TheBestHero_Reward[3006979][1][9] = {}
	tActivity2015TheBestHero_Reward[3006979][1][9]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][9]["ItemChance"] = 20
	tActivity2015TheBestHero_Reward[3006979][1][9]["Item_1"] = 720028
	tActivity2015TheBestHero_Reward[3006979][1][9]["IsLimited"] = true
	tActivity2015TheBestHero_Reward[3006979][1][9]["LimitIndex"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][9]["LimitedNum"] = 1
	tActivity2015TheBestHero_Reward[3006979][1][9]["ItemAttr"] = "0 1"
	tActivity2015TheBestHero_Reward[3006979][1][9]["Index"] = 9
	tActivity2015TheBestHero_Reward[3006979][1][9]["Log"] = "0,0,0,0,12000139,2,720028,1"
	-- 流星卷1个	4.00%    3004611		MeteorPack
	tActivity2015TheBestHero_Reward[3006979][1][10] = {}
	tActivity2015TheBestHero_Reward[3006979][1][10]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][10]["ItemChance"] = 400
	tActivity2015TheBestHero_Reward[3006979][1][10]["Item_1"] = 3004611
	tActivity2015TheBestHero_Reward[3006979][1][10]["ItemAttr"] = "0 1"
	tActivity2015TheBestHero_Reward[3006979][1][10]["Index"] = 10
	tActivity2015TheBestHero_Reward[3006979][1][10]["Log"] = "0,0,0,0,12000139,2,3004611,1"
	-- 马+3（赠）	5.00%    723860		+3MaroonSteedPack
	tActivity2015TheBestHero_Reward[3006979][1][11] = {}
	tActivity2015TheBestHero_Reward[3006979][1][11]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][11]["ItemChance"] = 500
	tActivity2015TheBestHero_Reward[3006979][1][11]["Item_1"] = 723860
	tActivity2015TheBestHero_Reward[3006979][1][11]["ItemAttr"] = "0 1 3"
	tActivity2015TheBestHero_Reward[3006979][1][11]["Index"] = 11
	tActivity2015TheBestHero_Reward[3006979][1][11]["Log"] = "0,0,0,0,12000139,2,723860,1"
	-- 马+6  	0.10%        限量（每天限1个）    723863		+6MaroonSteedPack
	tActivity2015TheBestHero_Reward[3006979][1][12] = {}
	tActivity2015TheBestHero_Reward[3006979][1][12]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][12]["ItemChance"] = 10
	tActivity2015TheBestHero_Reward[3006979][1][12]["Item_1"] = 723863
	tActivity2015TheBestHero_Reward[3006979][1][12]["IsLimited"] = true
	tActivity2015TheBestHero_Reward[3006979][1][12]["LimitIndex"] = 3
	tActivity2015TheBestHero_Reward[3006979][1][12]["LimitedNum"] = 1
	tActivity2015TheBestHero_Reward[3006979][1][12]["ItemAttr"] = "0 1"
	tActivity2015TheBestHero_Reward[3006979][1][12]["Index"] = 12
	tActivity2015TheBestHero_Reward[3006979][1][12]["Log"] = "0,0,0,0,12000139,2,723863,1"
	-- 赤炼石+3（赠）	5.00%    730003		Stone
	tActivity2015TheBestHero_Reward[3006979][1][13] = {}
	tActivity2015TheBestHero_Reward[3006979][1][13]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][13]["ItemChance"] = 500
	tActivity2015TheBestHero_Reward[3006979][1][13]["Item_1"] = 730003
	tActivity2015TheBestHero_Reward[3006979][1][13]["ItemAttr"] = "0 1 3"
	tActivity2015TheBestHero_Reward[3006979][1][13]["Index"] = 13
	tActivity2015TheBestHero_Reward[3006979][1][13]["Log"] = "0,0,0,0,12000139,2,730003,1"
	-- 赤炼石+6 	 0.10%    限量（每天限1个）    730006		Stone
	tActivity2015TheBestHero_Reward[3006979][1][14] = {}
	tActivity2015TheBestHero_Reward[3006979][1][14]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][14]["ItemChance"] = 10
	tActivity2015TheBestHero_Reward[3006979][1][14]["Item_1"] = 730006
	tActivity2015TheBestHero_Reward[3006979][1][14]["IsLimited"] = true
	tActivity2015TheBestHero_Reward[3006979][1][14]["LimitIndex"] = 4
	tActivity2015TheBestHero_Reward[3006979][1][14]["LimitedNum"] = 1
	tActivity2015TheBestHero_Reward[3006979][1][14]["ItemAttr"] = "0 1"
	tActivity2015TheBestHero_Reward[3006979][1][14]["Index"] = 14
	tActivity2015TheBestHero_Reward[3006979][1][14]["Log"] = "0,0,0,0,12000139,2,730006,1"
	-- 良品天怒宝石	3.00%       700102		ThunderGem
	tActivity2015TheBestHero_Reward[3006979][1][15] = {}
	tActivity2015TheBestHero_Reward[3006979][1][15]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][15]["ItemChance"] = 300
	tActivity2015TheBestHero_Reward[3006979][1][15]["Item_1"] = 700102
	tActivity2015TheBestHero_Reward[3006979][1][15]["ItemAttr"] = "0 1"
	tActivity2015TheBestHero_Reward[3006979][1][15]["Index"] = 15
	tActivity2015TheBestHero_Reward[3006979][1][15]["Log"] = "0,0,0,0,12000139,2,700102,1"
	-- 良品地灵宝石	3.00%    700122		GloryGem
	tActivity2015TheBestHero_Reward[3006979][1][16] = {}
	tActivity2015TheBestHero_Reward[3006979][1][16]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][16]["ItemChance"] = 300
	tActivity2015TheBestHero_Reward[3006979][1][16]["Item_1"] = 700122
	tActivity2015TheBestHero_Reward[3006979][1][16]["ItemAttr"] = "0 1"
	tActivity2015TheBestHero_Reward[3006979][1][16]["Index"] = 16
	tActivity2015TheBestHero_Reward[3006979][1][16]["Log"] = "0,0,0,0,12000139,2,700122,1"
	-- 良品玄元宝石	5.00%        700072		TortoiseGem
	tActivity2015TheBestHero_Reward[3006979][1][17] = {}
	tActivity2015TheBestHero_Reward[3006979][1][17]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][17]["ItemChance"] = 500
	tActivity2015TheBestHero_Reward[3006979][1][17]["Item_1"] = 700072
	tActivity2015TheBestHero_Reward[3006979][1][17]["ItemAttr"] = "0 1"
	tActivity2015TheBestHero_Reward[3006979][1][17]["Index"] = 17
	tActivity2015TheBestHero_Reward[3006979][1][17]["Log"] = "0,0,0,0,12000139,2,700072,1"
	-- 优质天怒宝石  	0.30%   限量（每天限1个）       700103		ThunderGem
	tActivity2015TheBestHero_Reward[3006979][1][18] = {}
	tActivity2015TheBestHero_Reward[3006979][1][18]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][18]["ItemChance"] = 30
	tActivity2015TheBestHero_Reward[3006979][1][18]["Item_1"] = 700103
	tActivity2015TheBestHero_Reward[3006979][1][18]["IsLimited"] = true
	tActivity2015TheBestHero_Reward[3006979][1][18]["LimitIndex"] = 5
	tActivity2015TheBestHero_Reward[3006979][1][18]["LimitedNum"] = 1
	tActivity2015TheBestHero_Reward[3006979][1][18]["ItemAttr"] = "0 1"
	tActivity2015TheBestHero_Reward[3006979][1][18]["Index"] = 18
	tActivity2015TheBestHero_Reward[3006979][1][18]["Log"] = "0,0,0,0,12000139,2,700103,1"
	-- 优质地灵宝石	0.30%    限量（每天限1个）     700123		GloryGem
	tActivity2015TheBestHero_Reward[3006979][1][19] = {}
	tActivity2015TheBestHero_Reward[3006979][1][19]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][19]["ItemChance"] = 30
	tActivity2015TheBestHero_Reward[3006979][1][19]["Item_1"] = 700123
	tActivity2015TheBestHero_Reward[3006979][1][19]["IsLimited"] = true
	tActivity2015TheBestHero_Reward[3006979][1][19]["LimitIndex"] = 6
	tActivity2015TheBestHero_Reward[3006979][1][19]["LimitedNum"] = 1
	tActivity2015TheBestHero_Reward[3006979][1][19]["ItemAttr"] = "0 1"
	tActivity2015TheBestHero_Reward[3006979][1][19]["Index"] = 19
	tActivity2015TheBestHero_Reward[3006979][1][19]["Log"] = "0,0,0,0,12000139,2,700123,1"
	-- 优质玄元宝石	  1.00%    限量（每天限2个）        700073		TortoiseGem
	tActivity2015TheBestHero_Reward[3006979][1][20] = {}
	tActivity2015TheBestHero_Reward[3006979][1][20]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][20]["ItemChance"] = 100
	tActivity2015TheBestHero_Reward[3006979][1][20]["Item_1"] = 700073
	tActivity2015TheBestHero_Reward[3006979][1][20]["IsLimited"] = true
	tActivity2015TheBestHero_Reward[3006979][1][20]["LimitIndex"] = 7
	tActivity2015TheBestHero_Reward[3006979][1][20]["LimitedNum"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][20]["ItemAttr"] = "0 1"
	tActivity2015TheBestHero_Reward[3006979][1][20]["Index"] = 20
	tActivity2015TheBestHero_Reward[3006979][1][20]["Log"] = "0,0,0,0,12000139,2,700073,1"
	-- 固化石 	0.50%     限量（每天限1个）     723694		PermanentStone
	tActivity2015TheBestHero_Reward[3006979][1][21] = {}
	tActivity2015TheBestHero_Reward[3006979][1][21]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][21]["ItemChance"] = 50
	tActivity2015TheBestHero_Reward[3006979][1][21]["Item_1"] = 723694
	tActivity2015TheBestHero_Reward[3006979][1][21]["IsLimited"] = true
	tActivity2015TheBestHero_Reward[3006979][1][21]["LimitIndex"] = 8
	tActivity2015TheBestHero_Reward[3006979][1][21]["LimitedNum"] = 1
	tActivity2015TheBestHero_Reward[3006979][1][21]["ItemAttr"] = "0 1"
	tActivity2015TheBestHero_Reward[3006979][1][21]["Index"] = 21
	tActivity2015TheBestHero_Reward[3006979][1][21]["Log"] = "0,0,0,0,12000139,2,723694,1"
	-- 7阶武器神魂礼包（赠）	2.00%  同步简体 3006745
	tActivity2015TheBestHero_Reward[3006979][1][22] = {}
	tActivity2015TheBestHero_Reward[3006979][1][22]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][22]["ItemChance"] = 200
	tActivity2015TheBestHero_Reward[3006979][1][22]["Item_1"] = 3006745
	tActivity2015TheBestHero_Reward[3006979][1][22]["ItemAttr"] = "0 1 3"
	tActivity2015TheBestHero_Reward[3006979][1][22]["Index"] = 22
	tActivity2015TheBestHero_Reward[3006979][1][22]["Log"] = "0,0,0,0,12000139,2,3006745,1"
	-- 7阶防具配饰神魂礼包（赠）	3.00%   同步简体 3006746
	tActivity2015TheBestHero_Reward[3006979][1][23] = {}
	tActivity2015TheBestHero_Reward[3006979][1][23]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][23]["ItemChance"] = 300
	tActivity2015TheBestHero_Reward[3006979][1][23]["Item_1"] = 3006746
	tActivity2015TheBestHero_Reward[3006979][1][23]["ItemAttr"] = "0 1 3"
	tActivity2015TheBestHero_Reward[3006979][1][23]["Index"] = 23
	tActivity2015TheBestHero_Reward[3006979][1][23]["Log"] = "0,0,0,0,12000139,2,3006746,1"
	-- 30天时装外套（赠）	5.00%    限量（每天限5个）  193015		FlameDragon
	tActivity2015TheBestHero_Reward[3006979][1][24] = {}
	tActivity2015TheBestHero_Reward[3006979][1][24]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][24]["ItemChance"] = 500
	tActivity2015TheBestHero_Reward[3006979][1][24]["Item_1"] = 193015
	tActivity2015TheBestHero_Reward[3006979][1][24]["IsLimited"] = true
	tActivity2015TheBestHero_Reward[3006979][1][24]["LimitIndex"] = 9
	tActivity2015TheBestHero_Reward[3006979][1][24]["LimitedNum"] = 5
	tActivity2015TheBestHero_Reward[3006979][1][24]["ItemAttr"] = "0 1 3 43200"
	tActivity2015TheBestHero_Reward[3006979][1][24]["Index"] = 24
	tActivity2015TheBestHero_Reward[3006979][1][24]["Log"] = "0,0,0,0,12000139,2,193015,1"
	-- 外套碎片	5.00%     限量（每天限5个）
	tActivity2015TheBestHero_Reward[3006979][1][25] = {}
	tActivity2015TheBestHero_Reward[3006979][1][25]["RandomItemChanceType"] = 2
	tActivity2015TheBestHero_Reward[3006979][1][25]["ItemChance"] = 500
	tActivity2015TheBestHero_Reward[3006979][1][25]["Item_1"] = 3006980
	tActivity2015TheBestHero_Reward[3006979][1][25]["IsLimited"] = true
	tActivity2015TheBestHero_Reward[3006979][1][25]["LimitIndex"] = 10
	tActivity2015TheBestHero_Reward[3006979][1][25]["LimitedNum"] = 5
	tActivity2015TheBestHero_Reward[3006979][1][25]["ItemAttr"] = "0 1"
	tActivity2015TheBestHero_Reward[3006979][1][25]["Index"] = 25
	tActivity2015TheBestHero_Reward[3006979][1][25]["Log"] = "0,0,0,0,12000139,2,3006980,1"
	
	--击杀boss奖励
	tActivity2015TheBestHero_Reward["KillBOSS"] = {}
	tActivity2015TheBestHero_Reward["KillBOSS"]["TopCultivateTimes"] = 1000000
	
	tActivity2015TheBestHero_Reward["KillBOSS"][7851] = {}
	tActivity2015TheBestHero_Reward["KillBOSS"][7851]["Strength"] = 30       		---气力值
	tActivity2015TheBestHero_Reward["KillBOSS"][7851]["CultivateTimes"] = 10000      ---修炼次数
	tActivity2015TheBestHero_Reward["KillBOSS"][7851]["ItemId"] = 3006971    ---侠客令牌
	tActivity2015TheBestHero_Reward["KillBOSS"][7851]["ItemNum"] = 5    		---侠客令牌个数
	tActivity2015TheBestHero_Reward["KillBOSS"][7851]["Floor"] = 3    				---层数
	tActivity2015TheBestHero_Reward["KillBOSS"][7851]["Log"] = {}
	tActivity2015TheBestHero_Reward["KillBOSS"][7851]["Log"][1] = "0,0,0,0,12000139,2,12[3006971],30[5]"					-- 无自创武功
	tActivity2015TheBestHero_Reward["KillBOSS"][7851]["Log"][2] = "0,0,0,0,12000139,2,12[17][3006971],30[10000][5]"

	tActivity2015TheBestHero_Reward["KillBOSS"][7852] = {}
	tActivity2015TheBestHero_Reward["KillBOSS"][7852]["Strength"] = 40
	tActivity2015TheBestHero_Reward["KillBOSS"][7852]["CultivateTimes"] = 10000
	tActivity2015TheBestHero_Reward["KillBOSS"][7852]["ItemId"] = 3006972    	---精英令牌
	tActivity2015TheBestHero_Reward["KillBOSS"][7852]["ItemNum"] = 4    			---精英令牌个数
	tActivity2015TheBestHero_Reward["KillBOSS"][7852]["Floor"] = 6    				---层数
	tActivity2015TheBestHero_Reward["KillBOSS"][7852]["Log"] = {}
	tActivity2015TheBestHero_Reward["KillBOSS"][7852]["Log"][1] = "0,0,0,0,12000139,2,12[3006972],40[4]"					-- 无自创武功
	tActivity2015TheBestHero_Reward["KillBOSS"][7852]["Log"][2] = "0,0,0,0,12000139,2,12[17][3006972],40[10000][4]"

	tActivity2015TheBestHero_Reward["KillBOSS"][7853] = {}
	tActivity2015TheBestHero_Reward["KillBOSS"][7853]["Strength"] = 50
	tActivity2015TheBestHero_Reward["KillBOSS"][7853]["CultivateTimes"] = 10000
	tActivity2015TheBestHero_Reward["KillBOSS"][7853]["ItemId"] = 3006973    			---豪杰令牌
	tActivity2015TheBestHero_Reward["KillBOSS"][7853]["ItemNum"] = 3    					---豪杰令牌个数
	tActivity2015TheBestHero_Reward["KillBOSS"][7853]["Floor"] = 9    				---层数
	tActivity2015TheBestHero_Reward["KillBOSS"][7853]["ItemId_2"] = 3003126   		 ---究极通神丹（赠）
	tActivity2015TheBestHero_Reward["KillBOSS"][7853]["ItemAttr"] = "0 1 3" 
	tActivity2015TheBestHero_Reward["KillBOSS"][7853]["Log"] = {}
	tActivity2015TheBestHero_Reward["KillBOSS"][7853]["Log"][1] = "0,0,0,0,12000139,2,12[3003126][3006973],50[1][3]"				-- 无自创武功
	tActivity2015TheBestHero_Reward["KillBOSS"][7853]["Log"][2] = "0,0,0,0,12000139,2,12[17][3003126][3006973],50[10000][1][3]"

	--结算奖励
	tActivity2015TheBestHero_Reward["EachFloor"] = {}
	tActivity2015TheBestHero_Reward["EachFloor"][1] = {}
	tActivity2015TheBestHero_Reward["EachFloor"][1]["EXP"] = 60
	tActivity2015TheBestHero_Reward["EachFloor"][1]["Strength"] = 20
	tActivity2015TheBestHero_Reward["EachFloor"][1]["Log"] = "0,0,0,0,12000139,2,%s,%s"

	tActivity2015TheBestHero_Reward["EachFloor"][2] = {}
	tActivity2015TheBestHero_Reward["EachFloor"][2]["EXP"] = 90
	tActivity2015TheBestHero_Reward["EachFloor"][2]["Strength"] = 30
	tActivity2015TheBestHero_Reward["EachFloor"][2]["Log"] = "0,0,0,0,12000139,2,%s,%s"

	tActivity2015TheBestHero_Reward["EachFloor"][3] = {}
	tActivity2015TheBestHero_Reward["EachFloor"][3]["EXP"] = 120
	tActivity2015TheBestHero_Reward["EachFloor"][3]["Strength"] = 40
	tActivity2015TheBestHero_Reward["EachFloor"][3]["Log"] = "0,0,0,0,12000139,2,%s,%s"

	tActivity2015TheBestHero_Reward["EachFloor"][4] = {}
	tActivity2015TheBestHero_Reward["EachFloor"][4]["EXP"] = 150
	tActivity2015TheBestHero_Reward["EachFloor"][4]["Strength"] = 50
	tActivity2015TheBestHero_Reward["EachFloor"][4]["Log"] = "0,0,0,0,12000139,2,%s,%s"

	tActivity2015TheBestHero_Reward["EachFloor"][5] = {}
	tActivity2015TheBestHero_Reward["EachFloor"][5]["EXP"] = 180
	tActivity2015TheBestHero_Reward["EachFloor"][5]["Strength"] = 60
	tActivity2015TheBestHero_Reward["EachFloor"][5]["Log"] = "0,0,0,0,12000139,2,%s,%s"

	tActivity2015TheBestHero_Reward["EachFloor"][6] = {}
	tActivity2015TheBestHero_Reward["EachFloor"][6]["EXP"] = 210
	tActivity2015TheBestHero_Reward["EachFloor"][6]["Strength"] = 70
	tActivity2015TheBestHero_Reward["EachFloor"][6]["Log"] = "0,0,0,0,12000139,2,%s,%s"

	tActivity2015TheBestHero_Reward["EachFloor"][7] = {}
	tActivity2015TheBestHero_Reward["EachFloor"][7]["EXP"] = 240
	tActivity2015TheBestHero_Reward["EachFloor"][7]["Strength"] = 80
	tActivity2015TheBestHero_Reward["EachFloor"][7]["Log"] = "0,0,0,0,12000139,2,%s,%s"

	tActivity2015TheBestHero_Reward["EachFloor"][8] = {}
	tActivity2015TheBestHero_Reward["EachFloor"][8]["EXP"] = 270
	tActivity2015TheBestHero_Reward["EachFloor"][8]["Strength"] = 90
	tActivity2015TheBestHero_Reward["EachFloor"][8]["Item"] = 3003125   ---通神丹（赠）*5
	tActivity2015TheBestHero_Reward["EachFloor"][8]["ItemAttr"] = "0 5 3"
	tActivity2015TheBestHero_Reward["EachFloor"][8]["Num"] = 5
	tActivity2015TheBestHero_Reward["EachFloor"][8]["Log"] = "0,0,0,0,12000139,2,%s,%s"

	tActivity2015TheBestHero_Reward["EachFloor"][9] = {}
	tActivity2015TheBestHero_Reward["EachFloor"][9]["EXP"] = 300
	tActivity2015TheBestHero_Reward["EachFloor"][9]["Strength"] = 100
	tActivity2015TheBestHero_Reward["EachFloor"][9]["Item"] = 3003124    ---免费强炼丹（赠）*3
	tActivity2015TheBestHero_Reward["EachFloor"][9]["ItemAttr"] = "0 3 3"
	tActivity2015TheBestHero_Reward["EachFloor"][9]["Num"] = 3
	tActivity2015TheBestHero_Reward["EachFloor"][9]["Log"] = "0,0,0,0,12000139,2,%s,%s"

	tActivity2015TheBestHero_Reward["EachFloor"][10] = {}
	tActivity2015TheBestHero_Reward["EachFloor"][10]["EXP"] = 330
	tActivity2015TheBestHero_Reward["EachFloor"][10]["Strength"] = 110
	tActivity2015TheBestHero_Reward["EachFloor"][10]["Item"] = 3002029    ---护心丹*2
	tActivity2015TheBestHero_Reward["EachFloor"][10]["ItemAttr"] = "0 2 0 0 1"
	tActivity2015TheBestHero_Reward["EachFloor"][10]["Num"] = 2
	tActivity2015TheBestHero_Reward["EachFloor"][10]["Log"] = "0,0,0,0,12000139,2,%s,%s"
	--闯关成功
	tActivity2015TheBestHero_Reward["EachFloor"][11] = {}
	tActivity2015TheBestHero_Reward["EachFloor"][11]["EXP"] = 360
	tActivity2015TheBestHero_Reward["EachFloor"][11]["Strength"] = 120
	tActivity2015TheBestHero_Reward["EachFloor"][11]["Item"] = 3003126    ---究极通神丹（赠）
	tActivity2015TheBestHero_Reward["EachFloor"][11]["ItemAttr"] = "0 1 3"
	tActivity2015TheBestHero_Reward["EachFloor"][11]["Num"] = 1
	tActivity2015TheBestHero_Reward["EachFloor"][11]["Log"] = "0,0,0,0,12000139,2,%s,%s"

	--闯关奖励  奖励气力值
	tActivity2015TheBestHero_Reward["FinalReward"] = {}
	tActivity2015TheBestHero_Reward["FinalReward"][1] = {}  
	tActivity2015TheBestHero_Reward["FinalReward"][1]["Strength"] = 300    		---300点气力值
	tActivity2015TheBestHero_Reward["FinalReward"][1]["Time"] = 5    					---5分钟内
	tActivity2015TheBestHero_Reward["FinalReward"][2] = {}
	tActivity2015TheBestHero_Reward["FinalReward"][2]["Strength"]  = 250    	---250点气力值
	tActivity2015TheBestHero_Reward["FinalReward"][2]["Time"] = 6    				---6分钟
	tActivity2015TheBestHero_Reward["FinalReward"][3] = {}  
	tActivity2015TheBestHero_Reward["FinalReward"][3]["Strength"] = 200    	---200点气力值
	tActivity2015TheBestHero_Reward["FinalReward"][3]["Time"] = 7    				---7分钟内
	tActivity2015TheBestHero_Reward["FinalReward"][4] = {}
	tActivity2015TheBestHero_Reward["FinalReward"][4]["Strength"]  = 150    	---150点气力值
	tActivity2015TheBestHero_Reward["FinalReward"][4]["Time"] = 8    				---8分钟
	tActivity2015TheBestHero_Reward["FinalReward"][5] = {}
	tActivity2015TheBestHero_Reward["FinalReward"][5]["Strength"]  = 100    	---100点气力值
	tActivity2015TheBestHero_Reward["FinalReward"][5]["Time"] = 9    				---9分钟
	tActivity2015TheBestHero_Reward["FinalReward"]["Log"] = "0,0,0,0,12000139,2,12,%s" 

	--排名奖励
	tActivity2015TheBestHero_Reward["RankReward"] = {}
	tActivity2015TheBestHero_Reward["RankReward"][1] = {}
	tActivity2015TheBestHero_Reward["RankReward"][1]["BagSpace"] = 4
	tActivity2015TheBestHero_Reward["RankReward"][1]["Item"] = {}
	tActivity2015TheBestHero_Reward["RankReward"][1]["ItemAttr"] = {}
	tActivity2015TheBestHero_Reward["RankReward"][1]["Strength"] = 600
	tActivity2015TheBestHero_Reward["RankReward"][1]["Item"][1] = 3003124   ---免费强炼丹（赠）*10
	tActivity2015TheBestHero_Reward["RankReward"][1]["ItemAttr"][1] = "0 10 3"
	tActivity2015TheBestHero_Reward["RankReward"][1]["Item"][2] = 3003126   ---究极通神丹
	tActivity2015TheBestHero_Reward["RankReward"][1]["ItemAttr"][2] = "0 1"
	tActivity2015TheBestHero_Reward["RankReward"][1]["Item"][3] = 1088000   ---龙珠
	tActivity2015TheBestHero_Reward["RankReward"][1]["ItemAttr"][3] = "0 1"
	tActivity2015TheBestHero_Reward["RankReward"][1]["Item"][4] = 3006980   ---外套碎片*5
	tActivity2015TheBestHero_Reward["RankReward"][1]["ItemAttr"][4] = "0 5"
	tActivity2015TheBestHero_Reward["RankReward"][1]["Log"] = "0,0,0,0,12000139,2,12[3003124][3003126][1088000][3006980],600[10][1][1][5]"

	tActivity2015TheBestHero_Reward["RankReward"][2] = {}
	tActivity2015TheBestHero_Reward["RankReward"][2]["BagSpace"] = 3
	tActivity2015TheBestHero_Reward["RankReward"][2]["Item"] = {}
	tActivity2015TheBestHero_Reward["RankReward"][2]["ItemAttr"] = {}
	tActivity2015TheBestHero_Reward["RankReward"][2]["Strength"] = 500
	tActivity2015TheBestHero_Reward["RankReward"][2]["Item"][1] = 3003124   ---免费强炼丹（赠）*7
	tActivity2015TheBestHero_Reward["RankReward"][2]["ItemAttr"][1] = "0 7 3"
	tActivity2015TheBestHero_Reward["RankReward"][2]["Item"][2] = 3003126   ---究极通神丹
	tActivity2015TheBestHero_Reward["RankReward"][2]["ItemAttr"][2] = "0 1"
	tActivity2015TheBestHero_Reward["RankReward"][2]["Item"][3] = 3006980   ---外套碎片*3
	tActivity2015TheBestHero_Reward["RankReward"][2]["ItemAttr"][3] = "0 3"
	tActivity2015TheBestHero_Reward["RankReward"][2]["Log"] = "0,0,0,0,12000139,2,12[3003124][3003126][3006980],500[7][1][3]"

	tActivity2015TheBestHero_Reward["RankReward"][3] = {}
	tActivity2015TheBestHero_Reward["RankReward"][3]["BagSpace"] = 3
	tActivity2015TheBestHero_Reward["RankReward"][3]["Item"] = {}
	tActivity2015TheBestHero_Reward["RankReward"][3]["ItemAttr"] = {}
	tActivity2015TheBestHero_Reward["RankReward"][3]["Strength"] = 400
	tActivity2015TheBestHero_Reward["RankReward"][3]["Item"][1] = 3003124   ---免费强炼丹（赠）*5
	tActivity2015TheBestHero_Reward["RankReward"][3]["ItemAttr"][1] = "0 5 3"
	tActivity2015TheBestHero_Reward["RankReward"][3]["Item"][2] = 3002029    ---护心丹
	tActivity2015TheBestHero_Reward["RankReward"][3]["ItemAttr"][2] = "0 1 0 0 1"
	tActivity2015TheBestHero_Reward["RankReward"][3]["Item"][3] = 3006980    ---外套碎片*2
	tActivity2015TheBestHero_Reward["RankReward"][3]["ItemAttr"][3] = "0 2"
	tActivity2015TheBestHero_Reward["RankReward"][3]["Log"] = "0,0,0,0,12000139,2,12[3003124][3002029][3006980],400[5][1][2]"
	--4-6
	tActivity2015TheBestHero_Reward["RankReward"][4] = {}
	tActivity2015TheBestHero_Reward["RankReward"][4]["BagSpace"] = 3
	tActivity2015TheBestHero_Reward["RankReward"][4]["Item"] = {}
	tActivity2015TheBestHero_Reward["RankReward"][4]["ItemAttr"] = {}
	tActivity2015TheBestHero_Reward["RankReward"][4]["Strength"] = 300
	tActivity2015TheBestHero_Reward["RankReward"][4]["Item"][1] = 3003124   ---免费强炼丹（赠）*3
	tActivity2015TheBestHero_Reward["RankReward"][4]["ItemAttr"][1] = "0 3 3"
	tActivity2015TheBestHero_Reward["RankReward"][4]["Item"][2] = 3003125    ---通神丹
	tActivity2015TheBestHero_Reward["RankReward"][4]["ItemAttr"][2] = "0 1"
	tActivity2015TheBestHero_Reward["RankReward"][4]["Item"][3] = 3006980    ---外套碎片*1
	tActivity2015TheBestHero_Reward["RankReward"][4]["ItemAttr"][3] = "0 1"
	tActivity2015TheBestHero_Reward["RankReward"][4]["Log"] = "0,0,0,0,12000139,2,12[3003124][3003125][3006980],300[3][1][1]"
	
	tActivity2015TheBestHero_Reward["RankReward"][5] = {}
	tActivity2015TheBestHero_Reward["RankReward"][5]["BagSpace"] = 3
	tActivity2015TheBestHero_Reward["RankReward"][5]["Item"] = {}
	tActivity2015TheBestHero_Reward["RankReward"][5]["ItemAttr"] = {}
	tActivity2015TheBestHero_Reward["RankReward"][5]["Strength"] = 300
	tActivity2015TheBestHero_Reward["RankReward"][5]["Item"][1] = 3003124   ---免费强炼丹（赠）*3
	tActivity2015TheBestHero_Reward["RankReward"][5]["ItemAttr"][1] = "0 3 3"
	tActivity2015TheBestHero_Reward["RankReward"][5]["Item"][2] = 3003125    ---通神丹
	tActivity2015TheBestHero_Reward["RankReward"][5]["ItemAttr"][2] = "0 1"
	tActivity2015TheBestHero_Reward["RankReward"][5]["Item"][3] = 3006980    ---外套碎片*1
	tActivity2015TheBestHero_Reward["RankReward"][5]["ItemAttr"][3] = "0 1"
	tActivity2015TheBestHero_Reward["RankReward"][5]["Log"] = "0,0,0,0,12000139,2,12[3003124][3003125][3006980],300[3][1][1]"
	
	tActivity2015TheBestHero_Reward["RankReward"][6] = {}
	tActivity2015TheBestHero_Reward["RankReward"][6]["BagSpace"] = 3
	tActivity2015TheBestHero_Reward["RankReward"][6]["Item"] = {}
	tActivity2015TheBestHero_Reward["RankReward"][6]["ItemAttr"] = {}
	tActivity2015TheBestHero_Reward["RankReward"][6]["Strength"] = 300
	tActivity2015TheBestHero_Reward["RankReward"][6]["Item"][1] = 3003124   ---免费强炼丹（赠）*3
	tActivity2015TheBestHero_Reward["RankReward"][6]["ItemAttr"][1] = "0 3 3"
	tActivity2015TheBestHero_Reward["RankReward"][6]["Item"][2] = 3003125    ---通神丹
	tActivity2015TheBestHero_Reward["RankReward"][6]["ItemAttr"][2] = "0 1"
	tActivity2015TheBestHero_Reward["RankReward"][6]["Item"][3] = 3006980    ---外套碎片*1
	tActivity2015TheBestHero_Reward["RankReward"][6]["ItemAttr"][3] = "0 1"
	tActivity2015TheBestHero_Reward["RankReward"][6]["Log"] = "0,0,0,0,12000139,2,12[3003124][3003125][3006980],300[3][1][1]"
	--7-10
	tActivity2015TheBestHero_Reward["RankReward"][7] = {}
	tActivity2015TheBestHero_Reward["RankReward"][7]["BagSpace"] = 2
	tActivity2015TheBestHero_Reward["RankReward"][7]["Item"] = {}
	tActivity2015TheBestHero_Reward["RankReward"][7]["ItemAttr"] = {}
	tActivity2015TheBestHero_Reward["RankReward"][7]["Strength"] = 200
	tActivity2015TheBestHero_Reward["RankReward"][7]["Item"][1] = 3003124   ---免费强炼丹（赠）
	tActivity2015TheBestHero_Reward["RankReward"][7]["ItemAttr"][1] = "0 1 3"
	tActivity2015TheBestHero_Reward["RankReward"][7]["Item"][2] = 3006980   ---外套碎片*1
	tActivity2015TheBestHero_Reward["RankReward"][7]["ItemAttr"][2] = "0 1"
	tActivity2015TheBestHero_Reward["RankReward"][7]["Log"] = "0,0,0,0,12000139,2,12[3003124][3006980],200[1][1]"
	
	tActivity2015TheBestHero_Reward["RankReward"][8] = {}
	tActivity2015TheBestHero_Reward["RankReward"][8]["BagSpace"] = 2
	tActivity2015TheBestHero_Reward["RankReward"][8]["Item"] = {}
	tActivity2015TheBestHero_Reward["RankReward"][8]["ItemAttr"] = {}
	tActivity2015TheBestHero_Reward["RankReward"][8]["Strength"] = 200
	tActivity2015TheBestHero_Reward["RankReward"][8]["Item"][1] = 3003124   ---免费强炼丹（赠）
	tActivity2015TheBestHero_Reward["RankReward"][8]["ItemAttr"][1] = "0 1 3"
	tActivity2015TheBestHero_Reward["RankReward"][8]["Item"][2] = 3006980   ---外套碎片*1
	tActivity2015TheBestHero_Reward["RankReward"][8]["ItemAttr"][2] = "0 1"
	tActivity2015TheBestHero_Reward["RankReward"][8]["Log"] = "0,0,0,0,12000139,2,12[3003124][3006980],200[1][1]"

	tActivity2015TheBestHero_Reward["RankReward"][9] = {}
	tActivity2015TheBestHero_Reward["RankReward"][9]["BagSpace"] = 2
	tActivity2015TheBestHero_Reward["RankReward"][9]["Item"] = {}
	tActivity2015TheBestHero_Reward["RankReward"][9]["ItemAttr"] = {}
	tActivity2015TheBestHero_Reward["RankReward"][9]["Strength"] = 200
	tActivity2015TheBestHero_Reward["RankReward"][9]["Item"][1] = 3003124   ---免费强炼丹（赠）
	tActivity2015TheBestHero_Reward["RankReward"][9]["ItemAttr"][1] = "0 1 3"
	tActivity2015TheBestHero_Reward["RankReward"][9]["Item"][2] = 3006980   ---外套碎片*1
	tActivity2015TheBestHero_Reward["RankReward"][9]["ItemAttr"][2] = "0 1"
	tActivity2015TheBestHero_Reward["RankReward"][9]["Log"] = "0,0,0,0,12000139,2,12[3003124][3006980],200[1][1]"
	
	tActivity2015TheBestHero_Reward["RankReward"][10] = {}
	tActivity2015TheBestHero_Reward["RankReward"][10]["BagSpace"] = 2
	tActivity2015TheBestHero_Reward["RankReward"][10]["Item"] = {}
	tActivity2015TheBestHero_Reward["RankReward"][10]["ItemAttr"] = {}
	tActivity2015TheBestHero_Reward["RankReward"][10]["Strength"] = 200
	tActivity2015TheBestHero_Reward["RankReward"][10]["Item"][1] = 3003124   ---免费强炼丹（赠）
	tActivity2015TheBestHero_Reward["RankReward"][10]["ItemAttr"][1] = "0 1 3"
	tActivity2015TheBestHero_Reward["RankReward"][10]["Item"][2] = 3006980   ---外套碎片*1
	tActivity2015TheBestHero_Reward["RankReward"][10]["ItemAttr"][2] = "0 1"
	tActivity2015TheBestHero_Reward["RankReward"][10]["Log"] = "0,0,0,0,12000139,2,12[3003124][3006980],200[1][1]"
	
--外套碎片合成  3006980
local tActivity2015TheBestHero_Clothes = {}
	tActivity2015TheBestHero_Clothes[3006980] = {}
	--5个碎片可以合成7天的外套（神佑1%）10080
	tActivity2015TheBestHero_Clothes[3006980][1] = {}
	tActivity2015TheBestHero_Clothes[3006980][1]["ItemId"] = 193015
	tActivity2015TheBestHero_Clothes[3006980][1]["DelNum"] = 5
	tActivity2015TheBestHero_Clothes[3006980][1]["ItemAttr"] = "0 1 0 10080 0 0 0 1"
	tActivity2015TheBestHero_Clothes[3006980][1]["Log"] = "0,0,3006980,5,12000139,2,193015,1"
	--10个碎片可以合成15天的外套（神佑1%）21600
	tActivity2015TheBestHero_Clothes[3006980][2] = {}
	tActivity2015TheBestHero_Clothes[3006980][2]["ItemId"] = 193015
	tActivity2015TheBestHero_Clothes[3006980][2]["DelNum"] = 10
	tActivity2015TheBestHero_Clothes[3006980][2]["ItemAttr"] = "0 1 0 21600 0 0 0 1"
	tActivity2015TheBestHero_Clothes[3006980][2]["Log"] = "0,0,3006980,10,12000139,2,193015,1"
	--20个碎片可以合成30天的外套（神佑1%）43200
	tActivity2015TheBestHero_Clothes[3006980][3] = {}
	tActivity2015TheBestHero_Clothes[3006980][3]["ItemId"] = 193015
	tActivity2015TheBestHero_Clothes[3006980][3]["DelNum"] = 20
	tActivity2015TheBestHero_Clothes[3006980][3]["ItemAttr"] = "0 1 0 43200 0 0 0 1"
	tActivity2015TheBestHero_Clothes[3006980][3]["Log"] = "0,0,3006980,20,12000139,2,193015,1"
	--60个碎片可以合成永久的外套（神佑1%）
	tActivity2015TheBestHero_Clothes[3006980][4] = {}
	tActivity2015TheBestHero_Clothes[3006980][4]["ItemId"] = 193015
	tActivity2015TheBestHero_Clothes[3006980][4]["DelNum"] = 60
	tActivity2015TheBestHero_Clothes[3006980][4]["ItemAttr"] = "0 1 0 0 0 0 0 1"
	tActivity2015TheBestHero_Clothes[3006980][4]["Log"] = "0,0,3006980,60,12000139,2,193015,1"

--全服邀请设置
local tActivity2015TheBestHero_Invite ={}
	tActivity2015TheBestHero_Invite["MapId"] = 1002
	tActivity2015TheBestHero_Invite["Activity_Invite_1"] = "level >= 1"
	tActivity2015TheBestHero_Invite["Activity_InviteId"] = 5
	--全服邀请任意8个点
	tActivity2015TheBestHero_Invite["Invite_Pos"] ={}
	tActivity2015TheBestHero_Invite["Invite_Pos"][1] = {}
	tActivity2015TheBestHero_Invite["Invite_Pos"][1]["X"] = 318
	tActivity2015TheBestHero_Invite["Invite_Pos"][1]["Y"] = 287
	
	tActivity2015TheBestHero_Invite["Invite_Pos"][2] = {}
	tActivity2015TheBestHero_Invite["Invite_Pos"][2]["X"] = 310
	tActivity2015TheBestHero_Invite["Invite_Pos"][2]["Y"] = 287
	
	tActivity2015TheBestHero_Invite["Invite_Pos"][3] = {}
	tActivity2015TheBestHero_Invite["Invite_Pos"][3]["X"] = 311
	tActivity2015TheBestHero_Invite["Invite_Pos"][3]["Y"] = 289
	
	tActivity2015TheBestHero_Invite["Invite_Pos"][4] = {}
	tActivity2015TheBestHero_Invite["Invite_Pos"][4]["X"] = 320
	tActivity2015TheBestHero_Invite["Invite_Pos"][4]["Y"] = 289
	
	tActivity2015TheBestHero_Invite["Invite_Pos"][5] = {}
	tActivity2015TheBestHero_Invite["Invite_Pos"][5]["X"] = 319
	tActivity2015TheBestHero_Invite["Invite_Pos"][5]["Y"] = 289
	
	tActivity2015TheBestHero_Invite["Invite_Pos"][6] = {}
	tActivity2015TheBestHero_Invite["Invite_Pos"][6]["X"] = 322
	tActivity2015TheBestHero_Invite["Invite_Pos"][6]["Y"] = 288
	
	tActivity2015TheBestHero_Invite["Invite_Pos"][7] = {}
	tActivity2015TheBestHero_Invite["Invite_Pos"][7]["X"] = 317
	tActivity2015TheBestHero_Invite["Invite_Pos"][7]["Y"] = 291
	
	tActivity2015TheBestHero_Invite["Invite_Pos"][8] = {}
	tActivity2015TheBestHero_Invite["Invite_Pos"][8]["X"] = 327
	tActivity2015TheBestHero_Invite["Invite_Pos"][8]["Y"] = 292
	--全服邀请对白
	tActivity2015TheBestHero_Invite["InviteSendId"] = 10550   --英文征服 ini/StrRes.ini  序号顺延，提示框对白
	tActivity2015TheBestHero_Invite["InviteSendOkId"] = 10551		--英文征服 ini/StrRes.ini  序号顺延，传送进入提示语
	--全服邀请倒计时
	tActivity2015TheBestHero_Invite["InviteCountDown"] = 30
	
-- 刷宝箱数据配置
local tActivity2015TheBestHero_BrushBox = {}
	tActivity2015TheBestHero_BrushBox["nGenId"] = {}
	tActivity2015TheBestHero_BrushBox["nGenId"][1] = 18001
	tActivity2015TheBestHero_BrushBox["nGenId"][2] = 18002
	tActivity2015TheBestHero_BrushBox["nGenId"][3] = 18003
	tActivity2015TheBestHero_BrushBox["nGenId"][4] = 18004
	
	tActivity2015TheBestHero_BrushBox["CellX"] = {}
	tActivity2015TheBestHero_BrushBox["CellX"][1] = 198
	tActivity2015TheBestHero_BrushBox["CellX"][2] = 199
	tActivity2015TheBestHero_BrushBox["CellX"][3] = 129
	tActivity2015TheBestHero_BrushBox["CellX"][4] = 127
	
	tActivity2015TheBestHero_BrushBox["CellY"] = {}
	tActivity2015TheBestHero_BrushBox["CellY"][1] = 207
	tActivity2015TheBestHero_BrushBox["CellY"][2] = 135
	tActivity2015TheBestHero_BrushBox["CellY"][3] = 136
	tActivity2015TheBestHero_BrushBox["CellY"][4] = 210
	
	tActivity2015TheBestHero_BrushBox[1] = 7863
	tActivity2015TheBestHero_BrushBox[2] = 7864
	tActivity2015TheBestHero_BrushBox[3] = 7865
	tActivity2015TheBestHero_BrushBox[4] = 7866
	tActivity2015TheBestHero_BrushBox[5] = 7867
	tActivity2015TheBestHero_BrushBox[6] = 7868
	tActivity2015TheBestHero_BrushBox[7] = 7869
	tActivity2015TheBestHero_BrushBox[8] = 7870
	tActivity2015TheBestHero_BrushBox[9] = 7871
	tActivity2015TheBestHero_BrushBox[10] = 7872

------------------------------------------------逻辑部分-------------------------------------------------
--活动时间判断
function Activity2015TheBestHero_TimeJudgement()
	if Sys_ChkFullTime(tActivity2015TheBestHero_Cont["Activity"]) then
		if Sys_ChkDayTime(tActivity2015TheBestHero_Cont["ActivityTime"]) then
			return true
		else
			return false
		end
	else
		return false
	end
end

--玩家等级判断
function Activity2015TheBestHero_LevelJudgement()
	local nLevel = tActivity2015TheBestHero_Cont["Level"]
	local nMete = tActivity2015TheBestHero_Cont["Metempsychosis"]
	if User_JudgeLevelAndMetempsychosis(nLevel,nMete) then
		return true
	else
		return false
	end
end

--传送地图逻辑
function Activity2015TheBestHero_ChgMap(nNpcId)
	local nMapId = tActivity2015TheBestHero_Npc[nNpcId]["Mapid"]
	local nBoundX = tActivity2015TheBestHero_Npc[nNpcId]["CellX"]
	local nBoundY = tActivity2015TheBestHero_Npc[nNpcId]["CellY"]
	local nBoundCX = tActivity2015TheBestHero_Npc["BoundCX"]
	local nBoundCY = tActivity2015TheBestHero_Npc["BoundCY"]
	User_UserRandBoundTrans(nMapId,nBoundX,nBoundY,nBoundCX,nBoundCY,0,0)
end

--判断玩家是否在活动地图中(1-10层)
function Activity2015TheBestHero_IsInMap()
	local nMapId = Get_UserMapId()
	if nMapId >= tActivity2015TheBestHero_Map[1] and nMapId <= tActivity2015TheBestHero_Map[10] then
		return true
	else
		return false
	end
end

-- stc(136,35)记录玩家是否闯关成功 nStcNum = 1
-- stc(136,36) 记录玩家最后所在的层数   ==n  表示在第n层  nStcNum = 2
-- stc(136,89)	记录是否已领取了排名奖励  nStcNum = 6
-- stc(136,90)	记录是否已领取了活动奖励  nStcNum = 7
function Activity2015TheBestHero_ChkStcComplete(nStcNum)
	local nEvent = tActivity2015TheBestHero_Stc[nStcNum]["EventType"]
	local nType = tActivity2015TheBestHero_Stc[nStcNum]["DataType"]
	local nComplete = tActivity2015TheBestHero_Stc[nStcNum]["Complete"]

	if Task_ChkStcValue(nEvent,nType,">=",nComplete) then
		-- 判断是否隔天
		if Task_StcInterval(nEvent,nType,1,4) then
			Task_SetStatistic(nEvent,nType,0,1,0)
			Task_SetStcTimestamp(nEvent,nType,0,0)	
			return false
		else
			return true
		end
	else
		return false
	end
end

--玩家之间pk  玩家击败玩家  
--actionid=80000001 PK时杀人触发
function Activity2015TheBestHero_PlayerPK()
	if not Activity2015TheBestHero_IsInMap() then
		return
	end
	
	--在对应层获得对应令牌1枚
	local nMapId = Get_UserMapId()
	if nMapId < tActivity2015TheBestHero_Map[4] then
		Item_AddItem(tActivity2015TheBestHero_Item["Item3006971"])
		nCardsNum = nCardsNum + 1
		User_TalkChannel2005(tActivity2015TheBestHero_Text["PKOwnCards"][1])
		Sys_SaveActionFestivalLog(tActivity2015TheBestHero_Log["PKOwnCards"][1])
		User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[12])
	elseif nMapId < tActivity2015TheBestHero_Map[7] then
		Item_AddItem(tActivity2015TheBestHero_Item["Item3006972"])
		nCardsNum = nCardsNum + 1
		User_TalkChannel2005(tActivity2015TheBestHero_Text["PKOwnCards"][2])
		Sys_SaveActionFestivalLog(tActivity2015TheBestHero_Log["PKOwnCards"][2])
		User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[12])
	elseif nMapId < tActivity2015TheBestHero_Map[10] then
		Item_AddItem(tActivity2015TheBestHero_Item["Item3006973"])
		nCardsNum = nCardsNum + 1
		User_TalkChannel2005(tActivity2015TheBestHero_Text["PKOwnCards"][3])
		Sys_SaveActionFestivalLog(tActivity2015TheBestHero_Log["PKOwnCards"][3])
		User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[12])
	elseif nMapId == tActivity2015TheBestHero_Map[10] then
		Item_AddItem(tActivity2015TheBestHero_Item["Item3006974"])
		nCardsNum = nCardsNum + 1
		User_TalkChannel2005(tActivity2015TheBestHero_Text["PKOwnCards"][4])
		Sys_SaveActionFestivalLog(tActivity2015TheBestHero_Log["PKOwnCards"][4])
		User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[12])
	end
	
	local nFloor = tActivity2015TheBestHero_Map[nMapId]
	local nNum1 = tActivity2015TheBestHero_Item["Item_num1"]
	local nNum2 = tActivity2015TheBestHero_Item["Item_num2"]
	local nNum3 = tActivity2015TheBestHero_Item["Item_num3"]
	
	local nItemId_1 = tActivity2015TheBestHero_Item["Item3006971"]
	local nItemId_2 = tActivity2015TheBestHero_Item["Item3006972"]
	local nItemId_3 = tActivity2015TheBestHero_Item["Item3006973"]
	local nItemId_4 = tActivity2015TheBestHero_Item["Item3006974"]
	
	-- 玩家在每层第一次，背包有5个令牌时，弹出105弹窗，无论他点确定还是取消都会升层
	if Item_ChkMulItem(nItemId_1,nItemId_1,nNum1) then 
		-- 侠客令牌 3006971 
		if nFloor <= 3 and nFloor >= 1 then
			if nIsFirst == true then
				nIsFirst = false
				local str = string.format(tActivity2015TheBestHero_Text["CardTips"],nNum1)
				Sys_MsgBox(str,"</F>Activity2015TheBestHero_UpFloor</N>"..nItemId_1.."</N>"..nNum1,"</F>Activity2015TheBestHero_UpFloor</N>"..nItemId_1.."</N>"..nNum1)
			else
				User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["CardsEnough"],nNum1))
			end
		end
	elseif Item_ChkMulItem(nItemId_2,nItemId_2,nNum2) then 
		-- 精英令牌 3006972
		if nFloor <= 6 and nFloor >= 4 then
			if nIsFirst == true then
				nIsFirst = false
				local str = string.format(tActivity2015TheBestHero_Text["CardTips"],nNum2)
				Sys_MsgBox(str,"</F>Activity2015TheBestHero_UpFloor</N>"..nItemId_2.."</N>"..nNum2,"</F>Activity2015TheBestHero_UpFloor</N>"..nItemId_2.."</N>"..nNum2)
			else
				User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["CardsEnough"],nNum2))
			end
		end
	elseif Item_ChkMulItem(nItemId_3,nItemId_3,nNum3) then 
		-- 豪杰令牌 3006973
		if nFloor <= 9 and nFloor >= 7 then
			if nIsFirst == true then
				nIsFirst = false
				local str = string.format(tActivity2015TheBestHero_Text["CardTips"],nNum3)
				Sys_MsgBox(str,"</F>Activity2015TheBestHero_UpFloor</N>"..nItemId_3.."</N>"..nNum3,"</F>Activity2015TheBestHero_UpFloor</N>"..nItemId_3.."</N>"..nNum3)
			else
				User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["CardsEnough"],nNum3))
			end
		end
	elseif Item_ChkMulItem(nItemId_4,nItemId_4,nNum3) then 
		-- 霸主令牌 3006974
		if nFloor == 10 then	
			if nIsFirst == true then
				nIsFirst = false
				local str = string.format(tActivity2015TheBestHero_Text["CardTips"],nNum3)
				Sys_MsgBox(str,"</F>Activity2015TheBestHero_UpFloor</N>"..nItemId_4.."</N>"..nNum3,"</F>Activity2015TheBestHero_UpFloor</N>"..nItemId_4.."</N>"..nNum3)
			else
				User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["CardsEnough"],nNum3))
			end
		end
	end
end

-- --玩家死亡触发   
-- function Activity2015TheBestHero_PlayerDead()
	-- --玩家死亡、下线或者离开活动场景，增益效果将被去除
	-- -- local nUserId = Get_UserId()
	-- -- User_DelAllAttribStatus(nUserId)
	-- Activity2015TheBestHero_ChkToolStatus(tActivity2015TheBestHero_Item["Item3006975"])
	-- Activity2015TheBestHero_ChkToolStatus(tActivity2015TheBestHero_Item["Item3006976"])
	
	-- if	nCardsNum ~= 0 then
		-- nCardsNum = nCardsNum - 1
	-- end
-- end

-- 18714  擂台管理员
--Option4: 送我入场。
function Activity2015TheBestHero_NPCSendIn(nNpcId)
	if not Activity2015TheBestHero_TimeJudgement() then
		return
	end
	
	if not Activity2015TheBestHero_LevelJudgement() then
		return
	end
	
	if Activity2015TheBestHero_ChkStcComplete(1) then
		--玩家已闯关成功，提示不需要再进入地图
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
	end

	--开始计时闯关时间
	local nEvent1 = tActivity2015TheBestHero_Stc[1]["EventType"]
	local nType1 = tActivity2015TheBestHero_Stc[1]["DataType"]
	local nData1 = tActivity2015TheBestHero_Stc[1]["StcData"]
	Task_SetStatistic(nEvent1,nType1,nData1,1,0)
	Task_SetStcTimestamp(nEvent1,nType1,0,0)
	
	--stc(136,90)==1  参加了此活动
	if not Activity2015TheBestHero_ChkStcComplete(7) then
		local nEvent = tActivity2015TheBestHero_Stc[7]["EventType"]
		local nType  = tActivity2015TheBestHero_Stc[7]["DataType"]
		local nData = tActivity2015TheBestHero_Stc[7]["StcData"]
		Task_SetStatistic(nEvent,nType,nData,1,0)
		Task_SetStcTimestamp(nEvent,nType,0,0)
	end
	
	--进入地图，第一层，奖励礼包碎片	
	Activity2015TheBestHero_ChgMap(tActivity2015TheBestHero_Npc[18715]["NpcId"])
	User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[7])
	User_TalkChannel2005(tActivity2015TheBestHero_Text["SendIn"])

	local nEvent = tActivity2015TheBestHero_Stc[2]["EventType"]
	local nType = tActivity2015TheBestHero_Stc[2]["DataType"]
	if Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1,0)
		Task_SetStcTimestamp(nEvent,nType,0,0)	
	end
	
	if not Activity2015TheBestHero_ChkStcComplete(2) then
		if Task_ChkStcValue(nEvent,nType,">=",1) then  --玩家第二次进入擂台，记录上次出擂台时所在最高层
			nPlayerFloor = Get_UserStatisticValue(nEvent,nType)
			return
		else
			Task_SetStatistic(nEvent,nType,1,1,0)
			Task_SetStcTimestamp(nEvent,nType,0,0)
		end
	end
	--记录每层擂台的参与人数
	Sys_SaveEmoneyBuy(tActivity2015TheBestHero_Log["Participation"][1])

	--判断背包空间
	if not Item_ChkItem(tActivity2015TheBestHero_Item["Item3006977"]) then
		if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
			User_TalkChannel2005(tActivity2015TheBestHero_Text["FullBag"])
			return
		end
	end
	Item_AddItem(tActivity2015TheBestHero_Item["Item3006977"],0,tActivity2015TheBestHero_Reward["UpFloor"]["SendInMap"])
	local str = string.format(tActivity2015TheBestHero_Reward["UpFloor"]["Log"],tActivity2015TheBestHero_Reward["UpFloor"]["SendInMap"])
	Sys_SaveActionFestivalLog(str)
end

--Option5: 领取活动奖励。
function Activity2015TheBestHero_GetActiveRewards(nNpcId)
	--stc(136,90)隔天重置
	local nEvent = tActivity2015TheBestHero_Stc[7]["EventType"]
	local nType  = tActivity2015TheBestHero_Stc[7]["DataType"]
	if Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1,0)
		Task_SetStcTimestamp(nEvent,nType,0,0)
	end
	
	--stc(136,90)	记录是否已领取了活动奖励
	if Activity2015TheBestHero_ChkStcComplete(7) then
		--接已领取奖励对白
		LinkNpcGossipFunc_New(nNpcId,"5-3")
		return
	elseif Task_ChkStcValue(nEvent,nType,"==",0) then
		LinkNpcGossipFunc_New(nNpcId,"5-4")
		return 
	end
	
	-- -- stc(136,36) 记录玩家最后所在的层数   ==n  表示在第n层
	local nEvent1 = tActivity2015TheBestHero_Stc[2]["EventType"]
	local nType1  = tActivity2015TheBestHero_Stc[2]["DataType"]
	local nComplete1 = tActivity2015TheBestHero_Stc[2]["Complete"]
	
	if Task_ChkStcValue(nEvent1,nType1,">=",nComplete1) then
		LinkNpcGossipFunc_New(nNpcId,"5-2")
		return
	else
		LinkNpcGossipFunc_New(nNpcId,"5-1")
		return
	end
end

--	活动结束后，玩家在第1—10层，未通关
function Activity2015TheBestHero_GetFloorRewards(nNpcId,nChoose)
	--stc(136,90)	记录是否已领取了活动奖励
	if Activity2015TheBestHero_ChkStcComplete(7) then
		--接已领取奖励对白
		LinkNpcGossipFunc_New(nNpcId,"5-3")
		return
	end
	
	local nEvent = tActivity2015TheBestHero_Stc[2]["EventType"]
	local nType  = tActivity2015TheBestHero_Stc[2]["DataType"]
	local nFloor = Get_UserStatisticValue(nEvent,nType)
	if nPlayerFloor >= nFloor then
		nFloor = nPlayerFloor
	end
	
	local nGetType = 1
	local nGetNum = 1
	
	--设置掩码，表示已领取奖励
	local nEvent1 = tActivity2015TheBestHero_Stc[7]["EventType"]
	local nType1 = tActivity2015TheBestHero_Stc[7]["DataType"]
	local nComplete1 = tActivity2015TheBestHero_Stc[7]["Complete"]

	if nChoose == 1 then
		--判断等级
		local nLevelTop = tActivity2015TheBestHero_Cont["LevelTop"]
		local nUserLevel = Get_UserLevel()
		if nUserLevel >= nLevelTop then
			LinkNpcGossipFunc_New(nNpcId,"10-1")
			return
		else
			Task_SetStatistic(nEvent1,nType1,nComplete1,1,0)
			User_AddExpTime(tActivity2015TheBestHero_Reward["EachFloor"][nFloor]["EXP"])
			nGetType = 4
			nGetNum = tActivity2015TheBestHero_Reward["EachFloor"][nFloor]["EXP"]
			User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["GetFloorReward"][nFloor],tNpcGossip[18714]["Option10"]))
		end
	elseif nChoose == 2 then
		Task_SetStatistic(nEvent1,nType1,nComplete1,1,0)
		--给气力值
		User_AddStrengthValue(tActivity2015TheBestHero_Reward["EachFloor"][nFloor]["Strength"])
		nGetType = 12
		nGetNum = tActivity2015TheBestHero_Reward["EachFloor"][nFloor]["Strength"]
		User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["GetFloorReward"][nFloor],tNpcGossip[18714]["Option11"]))
	elseif nChoose == 3 then   --8-10层有此选项
		--给物品
		--判断背包空间
		if nFloor == 10 then  --10层  给物品 两个护心丹
			if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_2"]) then
				LinkNpcGossipFunc_New(nNpcId,"12-1")
				return
			end
		else
			if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
				LinkNpcGossipFunc_New(nNpcId,"12-1")
				return
			end
		end
		Task_SetStatistic(nEvent1,nType1,nComplete1,1,0)
		Item_AddNewItem(tActivity2015TheBestHero_Reward["EachFloor"][nFloor]["Item"],tActivity2015TheBestHero_Reward["EachFloor"][nFloor]["ItemAttr"])
		nGetType = tActivity2015TheBestHero_Reward["EachFloor"][nFloor]["Item"]
		nGetNum = tActivity2015TheBestHero_Reward["EachFloor"][nFloor]["Num"]
		User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["GetFloorReward"][nFloor],tNpcGossip[18714]["Option12"]))
	end
	
	User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[10])
	local str = string.format(tActivity2015TheBestHero_Reward["EachFloor"][nFloor]["Log"],tostring(nGetType),tostring(nGetNum))
	Sys_SaveActionFestivalLog(str)
end

--玩家闯关成功
function Activity2015TheBestHero_GetSuccessRewards(nNpcId,nChoose)
	--stc(136,90)	记录是否已领取了活动奖励
	if Activity2015TheBestHero_ChkStcComplete(7) then
		--接已领取奖励对白
		LinkNpcGossipFunc_New(nNpcId,"5-3")
		return
	end

	local nComplete = tActivity2015TheBestHero_Stc[2]["Complete"]
	local nGetType = 1
	local nGetNum = 1
	--设置掩码，表示已领取奖励
	local nEvent1 = tActivity2015TheBestHero_Stc[7]["EventType"]
	local nType1 = tActivity2015TheBestHero_Stc[7]["DataType"]
	local nComplete1 = tActivity2015TheBestHero_Stc[7]["Complete"]
	
	if nChoose == 1 then
		--判断等级
		local nLevelTop = tActivity2015TheBestHero_Cont["LevelTop"]
		local nUserLevel = Get_UserLevel()
		if nUserLevel >= nLevelTop then
			LinkNpcGossipFunc_New(nNpcId,"16-1")
			return
		else
			Task_SetStatistic(nEvent1,nType1,nComplete1,1,0)
			User_AddExpTime(tActivity2015TheBestHero_Reward["EachFloor"][nComplete]["EXP"])
			nGetType = 4
			nGetNum = tActivity2015TheBestHero_Reward["EachFloor"][nComplete]["EXP"]
			local str1 = tActivity2015TheBestHero_Text[18714]["Option16"]
			User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["GetPassReward"],str1))
		end
	elseif nChoose == 2 then
		Task_SetStatistic(nEvent1,nType1,nComplete1,1,0)
		--给气力值
		User_AddStrengthValue(tActivity2015TheBestHero_Reward["EachFloor"][nComplete]["Strength"])
		nGetType = 12
		nGetNum = tActivity2015TheBestHero_Reward["EachFloor"][nComplete]["Strength"]
		local str2 = tActivity2015TheBestHero_Text[18714]["Option17"]
		User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["GetPassReward"],str2))
	elseif nChoose == 3 then 
		--给物品
		--判断背包空间
		if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
			LinkNpcGossipFunc_New(nNpcId,"18-1")
			return
		end
		Task_SetStatistic(nEvent1,nType1,nComplete1,1,0)
		Item_AddNewItem(tActivity2015TheBestHero_Reward["EachFloor"][nComplete]["Item"],tActivity2015TheBestHero_Reward["EachFloor"][nComplete]["ItemAttr"]) 
		nGetType = tActivity2015TheBestHero_Reward["EachFloor"][nComplete]["Item"]
		nGetNum = tActivity2015TheBestHero_Reward["EachFloor"][nComplete]["Num"]
		local str3 = tActivity2015TheBestHero_Text[18714]["Option18"]
		User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["GetPassReward"],str3))
	end

	User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[10])
	local str = string.format(tActivity2015TheBestHero_Reward["EachFloor"][nComplete]["Log"],tostring(nGetType),tostring(nGetNum))
	Sys_SaveActionFestivalLog(str)
end

--设置玩家排名
function Activity2015TheBestHero_SetRankingList()
	--设置当前闯关玩家的信息，记录到动态表中
	local nUserId = Get_UserId()
	local sUserName = Get_UserName()
	for nIndex = 1,#tActivity2015TheBestHero_List do
		local nGlobalId = tActivity2015TheBestHero_List[nIndex]["GlobalId"]
		local nPos = tActivity2015TheBestHero_List[nIndex]["GlobalPos"]
		local nData = Get_SysDynaGlobalData(nGlobalId,nPos)
		
		if nData == 0 then
			Sys_SetSynaGlobalData(nGlobalId,nPos,nUserId)
			Sys_SetSynaGlobalDataStr(nGlobalId,nPos,sUserName)
			break
		end
	end
end

-- 当第一个玩家成功通关时播放公告
function Activity2015TheBestHero_CallNumberOne()
	if string.len(Get_SysDynaGlobalDataStr0(tActivity2015TheBestHero_List[1]["GlobalId"])) ~= 0  and string.len(Get_SysDynaGlobalDataStr1(tActivity2015TheBestHero_List[2]["GlobalId"])) == 0 then
		local str = string.format(tActivity2015TheBestHero_Text["NumberOne"],Get_SysDynaGlobalDataStr0(tActivity2015TheBestHero_List[1]["GlobalId"]))
		Sys_GmBroadcast(str)
		Sys_SystemBroadcast(str)
	end
end

--判断玩家是否在排行榜内
function Activity2015TheBestHero_InTheList()
	local nUserId = Get_UserId()
	local sUserName = Get_UserName()
	for nIndex = 1,#tActivity2015TheBestHero_List do
		local nGlobalId = tActivity2015TheBestHero_List[nIndex]["GlobalId"]
		local nPos = tActivity2015TheBestHero_List[nIndex]["GlobalPos"]
		local nData = Get_SysDynaGlobalData(nGlobalId,nPos)
		if nUserId == nData then
			return true
		end
	end
	return false
end

--接Option6：领取排行奖励
function Activity2015TheBestHero_GetRankingDetail(nNpcId)
	--stc(136,90) 判断是否参加了此活动
	local nEvent = tActivity2015TheBestHero_Stc[7]["EventType"]
	local nType  = tActivity2015TheBestHero_Stc[7]["DataType"]
	if Task_StcInterval(nEvent,nType,1,4) then
		Task_SetStatistic(nEvent,nType,0,1,0)
		Task_SetStcTimestamp(nEvent,nType,0,0)
	end
	
	--stc(136,90) 判断是否参加了此活动
	if not Activity2015TheBestHero_ChkStcComplete(7) then
		if Task_ChkStcValue(nEvent,nType,"==",0) then
			LinkNpcGossipFunc_New(nNpcId,"6-3")
			return 
		end
	end
	LinkNpcGossipFunc_New(nNpcId,"6-1")
end

--Option22:领取排行奖励。
function Activity2015TheBestHero_GetRankingRewards(nNpcId)
	--未上榜，无法领取
	if not Activity2015TheBestHero_InTheList() then
		LinkNpcGossipFunc_New(nNpcId,"22-1")
		return
	end
	
	--已领取，无法领取
	if Activity2015TheBestHero_ChkStcComplete(6) then
		LinkNpcGossipFunc_New(nNpcId,"22-2")
		return
	end

	--领取奖励
	if Activity2015TheBestHero_InTheList() then
		local nUserId = Get_UserId()
		local sUserName = Get_UserName()		
		for nIndex = 1,#tActivity2015TheBestHero_List do
			local nGlobalId = tActivity2015TheBestHero_List[nIndex]["GlobalId"]
			local nPos = tActivity2015TheBestHero_List[nIndex]["GlobalPos"]
			local nData = Get_SysDynaGlobalData(nGlobalId,nPos)
			if nUserId == nData then			
				--背包满，无法领取
				if not User_CheckLeftSpace(tActivity2015TheBestHero_Reward["RankReward"][nIndex]["BagSpace"]) then
					LinkNpcGossipFunc_New(nNpcId,"22-3")
					return
				end	
				--成功领取
				local nEvent = tActivity2015TheBestHero_Stc[6]["EventType"]
				local nType = tActivity2015TheBestHero_Stc[6]["DataType"]
				local nComplete = tActivity2015TheBestHero_Stc[6]["Complete"]
				Task_SetStatistic(nEvent,nType,nComplete,1,0)
				Task_SetStcTimestamp(nEvent,nType,0,0)
				for nItemNum = 1, #tActivity2015TheBestHero_Reward["RankReward"][nIndex]["Item"] do
					Item_AddNewItem(tActivity2015TheBestHero_Reward["RankReward"][nIndex]["Item"][nItemNum],tActivity2015TheBestHero_Reward["RankReward"][nIndex]["ItemAttr"][nItemNum])
					Sys_SaveActionFestivalLog(tActivity2015TheBestHero_Reward["RankReward"][nIndex]["Log"])
				end
				User_AddStrengthValue(tActivity2015TheBestHero_Reward["RankReward"][nIndex]["Strength"])	
				User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[10])
				User_TalkChannel2005(tActivity2015TheBestHero_Text["GetRankReward"][nIndex])
			end
		end
	end
end

-- 18715  18772-18780  行脚商人(1-10层)
--Option1:购买万能金牌（40点天石）
function Activity2015TheBestHero_BuyPowerCard()
	local nNpcId = Get_NpcId()
	--天石不足
	local nEmoney = Get_UserEMoney()
	if nEmoney < tActivity2015TheBestHero_Data["BuyCard"] then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	--背包满
	--如果当前背包中没有万能金牌，则需判断空间
	if not Item_ChkItem(tActivity2015TheBestHero_Item["Item3006970"]) then
		if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
			LinkNpcGossipFunc_New(nNpcId,"2-2")
			return
		end
	end
	--二次确认
	LinkNpcGossipFunc_New(nNpcId,"2-3")
end

--Option6:确定
function Activity2015TheBestHero_SureToBuyCard()
	local nNpcId = Get_NpcId()

	--天石不足
	local nEmoney = Get_UserEMoney()
	if nEmoney < tActivity2015TheBestHero_Data["BuyCard"] then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	--背包满
	--如果当前背包中没有万能金牌，则需判断空间
	if not Item_ChkItem(tActivity2015TheBestHero_Item["Item3006970"]) then
		if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
			LinkNpcGossipFunc_New(nNpcId,"2-2")
			return
		end
	end
	--确定
	User_AddEMoney(tActivity2015TheBestHero_Data["Del40Emoney"])
	Item_AddItem(tActivity2015TheBestHero_Item["Item3006970"])
	Sys_SaveEmoneyBuy(tActivity2015TheBestHero_Log["BuyCard"])
	Sys_MsgBox(tActivity2015TheBestHero_Text["BuySuccess_1"])
end

--Option2:购买增益符（20点天石）
function Activity2015TheBestHero_BuyTool()
	local nNpcId = Get_NpcId()

	--天石不足
	local nEmoney = Get_UserEMoney()
	if nEmoney < tActivity2015TheBestHero_Data["BuyTool"] then
		LinkNpcGossipFunc_New(nNpcId,"2-4")
		return
	end
	--背包满
	--如果当前背包中没有增益符，则需判断空间
	if not Item_ChkItem(tActivity2015TheBestHero_Item["Item3006976"]) then
		if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
			LinkNpcGossipFunc_New(nNpcId,"2-5")
			return
		end
	end
	--二次确认		
	LinkNpcGossipFunc_New(nNpcId,"2-6")
end

--Option8:确定
function Activity2015TheBestHero_SureToBuyTool()
	local nNpcId = Get_NpcId()

	--天石不足
	local nEmoney = Get_UserEMoney()
	if nEmoney < tActivity2015TheBestHero_Data["BuyTool"] then
		LinkNpcGossipFunc_New(nNpcId,"2-4")
		return
	end
	--背包满
	--如果当前背包中没有增益符，则需判断空间
	if not Item_ChkItem(tActivity2015TheBestHero_Item["Item3006976"]) then
		if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
			LinkNpcGossipFunc_New(nNpcId,"2-5")
			return
		end
	end
	User_AddEMoney(tActivity2015TheBestHero_Data["Del20Emoney"])	
	Item_AddItem(tActivity2015TheBestHero_Item["Item3006976"],0,0,0,10,1)
	Sys_SaveEmoneyBuy(tActivity2015TheBestHero_Log["BuyTool"])
	Sys_MsgBox(tActivity2015TheBestHero_Text["BuySuccess_2"])
end

--Option9:回双龙城。
function Activity2015TheBestHero_BackToTown()
	if Activity2015TheBestHero_IsInMap() then
		Activity2015TheBestHero_ChgMap(tActivity2015TheBestHero_Npc[18714]["NpcId"])
		User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[8])
		nCardsNum = 0
		
		-- --清除玩家身上相关物品(侠客,精英,豪杰,霸主令牌,增益丹)
		if Item_ChkItem(tActivity2015TheBestHero_Item["Item3006971"]) then
			Item_DelAllItemByType(tActivity2015TheBestHero_Item["Item3006971"])
		end
		if Item_ChkItem(tActivity2015TheBestHero_Item["Item3006972"]) then
			Item_DelAllItemByType(tActivity2015TheBestHero_Item["Item3006972"])
		end
		if Item_ChkItem(tActivity2015TheBestHero_Item["Item3006973"]) then
			Item_DelAllItemByType(tActivity2015TheBestHero_Item["Item3006973"])
		end
		if Item_ChkItem(tActivity2015TheBestHero_Item["Item3006974"]) then
			Item_DelAllItemByType(tActivity2015TheBestHero_Item["Item3006974"])
		end
		if Item_ChkItem(tActivity2015TheBestHero_Item["Item3006975"]) then
			Item_DelAllItemByType(tActivity2015TheBestHero_Item["Item3006975"])
		end
		
		-- --清除状态
		-- local nUserId = Get_UserId()
		-- User_DelAllAttribStatus(nUserId)
		Activity2015TheBestHero_ChkToolStatus(tActivity2015TheBestHero_Item["Item3006975"])
		Activity2015TheBestHero_ChkToolStatus(tActivity2015TheBestHero_Item["Item3006976"])
	end
end

--stc(136,35) 记录玩家闯关成功的时间
--消耗时间掩码,在9分钟内闯关的玩家给对应奖励
function Activity2015TheBestHero_GetFinalRewards()
	local nEvent = tActivity2015TheBestHero_Stc[1]["EventType"]
	local nType  = tActivity2015TheBestHero_Stc[1]["DataType"]
	local nData1 = tActivity2015TheBestHero_Stc[1]["Time_1"]
	local nData2 = tActivity2015TheBestHero_Stc[1]["Time_2"]
	local nData3 = tActivity2015TheBestHero_Stc[1]["Time_3"]
	local nData4 = tActivity2015TheBestHero_Stc[1]["Time_4"]
	local nData5 = tActivity2015TheBestHero_Stc[1]["Time_5"]
	
	if Activity2015TheBestHero_ChkStcComplete(1) then
		if not Task_StcInterval(nEvent,nType,nData1,0) then
			--5分钟内
			User_AddStrengthValue(tActivity2015TheBestHero_Reward["FinalReward"][1]["Strength"])
			Sys_SaveActionFestivalLog(string.format(tActivity2015TheBestHero_Reward["FinalReward"]["Log"],tActivity2015TheBestHero_Reward["FinalReward"][1]["Strength"]))
			User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["SuccessReward"],tActivity2015TheBestHero_Reward["FinalReward"][1]["Time"],tActivity2015TheBestHero_Reward["FinalReward"][1]["Strength"]))
		elseif not Task_StcInterval(nEvent,nType,nData2,0) then
			--5-6分钟
			User_AddStrengthValue(tActivity2015TheBestHero_Reward["FinalReward"][2]["Strength"])
			Sys_SaveActionFestivalLog(string.format(tActivity2015TheBestHero_Reward["FinalReward"]["Log"],tActivity2015TheBestHero_Reward["FinalReward"][2]["Strength"]))
			User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["SuccessReward"],tActivity2015TheBestHero_Reward["FinalReward"][2]["Time"],tActivity2015TheBestHero_Reward["FinalReward"][2]["Strength"]))
		elseif not Task_StcInterval(nEvent,nType,nData3,0) then
			--6-7分钟
			User_AddStrengthValue(tActivity2015TheBestHero_Reward["FinalReward"][3]["Strength"])
			Sys_SaveActionFestivalLog(string.format(tActivity2015TheBestHero_Reward["FinalReward"]["Log"],tActivity2015TheBestHero_Reward["FinalReward"][3]["Strength"]))
			User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["SuccessReward"],tActivity2015TheBestHero_Reward["FinalReward"][3]["Time"],tActivity2015TheBestHero_Reward["FinalReward"][3]["Strength"]))
		elseif not Task_StcInterval(nEvent,nType,nData4,0) then
			--7-8分钟
			User_AddStrengthValue(tActivity2015TheBestHero_Reward["FinalReward"][4]["Strength"])
			Sys_SaveActionFestivalLog(string.format(tActivity2015TheBestHero_Reward["FinalReward"]["Log"],tActivity2015TheBestHero_Reward["FinalReward"][4]["Strength"]))
			User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["SuccessReward"],tActivity2015TheBestHero_Reward["FinalReward"][4]["Time"],tActivity2015TheBestHero_Reward["FinalReward"][4]["Strength"]))
		elseif not Task_StcInterval(nEvent,nType,nData5,0) then
			--8-9分钟
			User_AddStrengthValue(tActivity2015TheBestHero_Reward["FinalReward"][5]["Strength"])
			Sys_SaveActionFestivalLog(string.format(tActivity2015TheBestHero_Reward["FinalReward"]["Log"],tActivity2015TheBestHero_Reward["FinalReward"][5]["Strength"]))
			User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["SuccessReward"],tActivity2015TheBestHero_Reward["FinalReward"][5]["Time"],tActivity2015TheBestHero_Reward["FinalReward"][5]["Strength"]))
		end
	end
end

-------------------------------------------使用物品逻辑----------------------------------------------------------
--使用背包信 3007030
function Activity2015TheBestHero_UseLetter(nItemId)
	if not Sys_ChkFullTime(tActivity2015TheBestHero_Cont["Activity"]) then
		--不在活动时间，删除物品
		Item_DelAllItemByType(nItemId)
		local str = string.format(tActivity2015TheBestHero_Log["DelItem"],tostring(nItemId))
		Sys_SaveActionFestivalLog(str)
		return
	end
	
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		--自动寻路	
		Sys_GotoSomeWhere(tActivity2015TheBestHero_Npc[18714]["CellX"],tActivity2015TheBestHero_Npc[18714]["CellY"],tActivity2015TheBestHero_Npc[18714]["Mapid"])
		local nLevelTop = tActivity2015TheBestHero_Cont["LevelTop"]
		local nUserLevel = Get_UserLevel()
		if nUserLevel >= nLevelTop then
			User_AddCultivation(tActivity2015TheBestHero_Data["Add15Cul"])
			User_TalkChannel2005(tActivity2015TheBestHero_Text[3007030]["Get15Cul"])
		else
			User_AddExpTime(tActivity2015TheBestHero_Data["Add30Exp"])
			User_TalkChannel2005(tActivity2015TheBestHero_Text[3007030]["Get30Exp"])
		end
	end
end

--清理令牌
function Activity2015TheBestHero_ClearAllCards()
	nCardsNum = 0
	if Item_ChkItem(tActivity2015TheBestHero_Item["Item3006971"]) then
		Item_DelAllItemByType(tActivity2015TheBestHero_Item["Item3006971"])
	end
	if Item_ChkItem(tActivity2015TheBestHero_Item["Item3006972"]) then
		Item_DelAllItemByType(tActivity2015TheBestHero_Item["Item3006972"])
	end
	if Item_ChkItem(tActivity2015TheBestHero_Item["Item3006973"]) then
		Item_DelAllItemByType(tActivity2015TheBestHero_Item["Item3006973"])
	end
	if Item_ChkItem(tActivity2015TheBestHero_Item["Item3006974"]) then
		Item_DelAllItemByType(tActivity2015TheBestHero_Item["Item3006974"])
	end
end

--万能金牌
function Activity2015TheBestHero_UseItem_3006970(nItemId)
	if not Sys_ChkFullTime(tActivity2015TheBestHero_Cont["Activity"]) then
		--不在活动时间，删除物品
		Item_DelAllItemByType(nItemId)
		local str = string.format(tActivity2015TheBestHero_Log["DelItem"],tostring(nItemId))
		Sys_SaveActionFestivalLog(str)
		User_TalkChannel2005(tActivity2015TheBestHero_Text["EndDisappear"])
		return
	end
	
	--判断不在活动地图中
	local nMapId = Get_UserMapId()
	if not Activity2015TheBestHero_IsInMap() then
		User_TalkChannel2005(tActivity2015TheBestHero_Text["CannotUse"])
		return
	end
	
	-- 在第十层，不可使用
	if nMapId == tActivity2015TheBestHero_Map[10] then
		User_TalkChannel2005(tActivity2015TheBestHero_Text["CardCannot"])
		return
	end
	
	--道具使用冷却时间为30秒，CD内使用提示玩家使用太频繁
	--设置时间掩码
	local nEvent1 = tActivity2015TheBestHero_Stc[3]["EventType"]
	local nType1 = tActivity2015TheBestHero_Stc[3]["DataType"]
	local nLimit1 = tActivity2015TheBestHero_Stc[3]["LimitTime"]
	if Task_ChkStcValue(nEvent1,nType1,"==",1) then
		if	not Task_StcInterval(nEvent1,nType1,nLimit1,0) then
			User_TalkChannel2005(tActivity2015TheBestHero_Text["30SecLimit"])
			return
		else
			Task_SetStatistic(nEvent1,nType1,0,1,0)
			Task_SetStcTimestamp(nEvent1,nType1,0,0)
		end
	end
	
	-- stc(136,36) 记录玩家最后所在的层数   ==n  表示在第n层
	local nEvent2 = tActivity2015TheBestHero_Stc[2]["EventType"]
	local nType2  = tActivity2015TheBestHero_Stc[2]["DataType"]
	local nFloor = tActivity2015TheBestHero_Map[nMapId]
	--使用后升层
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		Task_SetStatistic(nEvent1,nType1,1,1,0)
		Task_SetStcTimestamp(nEvent1,nType1,0,0)
		User_UserRandTrans(tonumber(nMapId + 1))
		nIsFirst = true
		User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[2][nFloor])
		User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[3])
		
		--当玩家来到3 6 9层时给玩家一个系统提示“击败本层地图中央的BOSS可获得奖励！”
		if nFloor == 2 or nFloor == 5 or nFloor == 8 then
			User_TalkChannel2005(tActivity2015TheBestHero_Text["InBossFloor"])
		end
		
		--清理令牌
		Activity2015TheBestHero_ClearAllCards()
		nCardsNum = 0
		
		--设置掩码 记录玩家在第几层
		if nPlayerFloor <= nFloor then
			Task_SetStatistic(nEvent2,nType2,nFloor+1,1,0)
		else
			User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["UpFloorWithOutReward"],nFloor+1))
			return
		end
		--记录每层擂台的参与人数
		local nLevel = nFloor + 1
		Sys_SaveEmoneyBuy(tActivity2015TheBestHero_Log["Participation"][nLevel])

		--升层奖励礼包碎片
		Item_AddItem(tActivity2015TheBestHero_Item["Item3006977"],0,tActivity2015TheBestHero_Reward["UpFloor"][nMapId])
		local str = string.format(tActivity2015TheBestHero_Reward["UpFloor"]["Log"],tActivity2015TheBestHero_Reward["UpFloor"][nMapId])
		Sys_SaveActionFestivalLog(str)
		User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["UpFloorReward"],nFloor+1,tActivity2015TheBestHero_Reward["UpFloor"][nMapId]))
	end
end

-- 侠客令牌 3006971  使用该符最多到达第4层
-- 精英令牌 3006972  使用该符最多到达第7层
-- 豪杰令牌 3006973  使用该符最多到达第10层
-- 霸主令牌 3006974  在第10层使用霸主令牌能使玩家闯关成功
function Activity2015TheBestHero_UseCard(nItemId,nNum)
	if not Activity2015TheBestHero_TimeJudgement() then
		--不在活动时间，删除物品
		Item_DelAllItemByType(nItemId)
		local str = string.format(tActivity2015TheBestHero_Log["DelItem"],tostring(nItemId))
		Sys_SaveActionFestivalLog(str)
		User_TalkChannel2005(tActivity2015TheBestHero_Text["Disappear"])
		return
	end
	
	-- 判断玩家等级
	local nLevel = tActivity2015TheBestHero_Cont["Level"]
	local nMete = tActivity2015TheBestHero_Cont["Metempsychosis"]
	if not User_JudgeLevelAndMetempsychosis(nLevel,nMete) then
		User_TalkChannel2005(tActivity2015TheBestHero_Text["Level"])
		return
	end
	
	--判断是否在活动地图中
	if not Activity2015TheBestHero_IsInMap() then
		User_TalkChannel2005(tActivity2015TheBestHero_Text["WrongMap"])
		return
	end
	
	--令牌数>=5，则删掉所有对应的令牌，升一层
	local nMapId = Get_UserMapId()
	local nEvent = tActivity2015TheBestHero_Stc[2]["EventType"]
	local nType  = tActivity2015TheBestHero_Stc[2]["DataType"]
	local nComplete = tActivity2015TheBestHero_Stc[2]["Complete"]
	local nFloor = tActivity2015TheBestHero_Map[nMapId]

	--判断令牌在对应层是否可用
	if nItemId == tActivity2015TheBestHero_Item["Item3006971"] then
		if nFloor > 3 then
			User_TalkChannel2005(tActivity2015TheBestHero_Text["WrongMap"])
			return
		end
	end
	if nItemId == tActivity2015TheBestHero_Item["Item3006972"] then
		if nFloor < 4 or nFloor > 6 then
			User_TalkChannel2005(tActivity2015TheBestHero_Text["WrongMap"])
			return
		end
	end
	if nItemId == tActivity2015TheBestHero_Item["Item3006973"] then
		if nFloor < 7 or nFloor > 9 then
			User_TalkChannel2005(tActivity2015TheBestHero_Text["WrongMap"])
			return
		end
	end
	if nItemId == tActivity2015TheBestHero_Item["Item3006974"] then
		if nFloor < 10  then
			User_TalkChannel2005(tActivity2015TheBestHero_Text["WrongMap"])
			return
		end
	end
	
	if nFloor < 10 then
		if Item_ChkMulItem(nItemId,nItemId,nNum) then
			--清理令牌
			Activity2015TheBestHero_ClearAllCards()
			nCardsNum = 0
			User_UserRandTrans(tonumber(nMapId + 1))			--升层
			nIsFirst = true
			User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[2][nFloor])
			User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[3])
			
			--当玩家来到3 6 9层时给玩家一个系统提示“击败本层地图中央的BOSS可获得奖励！”
			if nFloor == 2 or nFloor == 5 or nFloor == 8 then
				User_TalkChannel2005(tActivity2015TheBestHero_Text["InBossFloor"])
			end
			
			--设置掩码 记录玩家在第几层
			if nPlayerFloor <=  nFloor then
				Task_SetStatistic(nEvent,nType,nFloor+1,1,0)
			else
				User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["UpFloorWithOutReward"],nFloor+1))
				return
			end
			--记录每层擂台的参与人数
			local nLevel = nFloor + 1
			Sys_SaveEmoneyBuy(tActivity2015TheBestHero_Log["Participation"][nLevel])

			--升层奖励礼包碎片
			Item_AddItem(tActivity2015TheBestHero_Item["Item3006977"],0,tActivity2015TheBestHero_Reward["UpFloor"][nMapId])
			local str = string.format(tActivity2015TheBestHero_Reward["UpFloor"]["Log"],tActivity2015TheBestHero_Reward["UpFloor"][nMapId])
			Sys_SaveActionFestivalLog(str)
			User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["UpFloorReward"],nFloor+1,tActivity2015TheBestHero_Reward["UpFloor"][nMapId]))
		else
			local nNeed = nNum - nCardsNum
			User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["NotEnough"],nNeed,tActivity2015TheBestHero_Text["CardsName"][nFloor]))
		end
	elseif nFloor == 10 then			
		if Item_ChkMulItem(nItemId,nItemId,nNum) then
			--清理令牌
			Activity2015TheBestHero_ClearAllCards()
			nCardsNum = 0
			--设置掩码 记录玩家在第几层
			Task_SetStatistic(nEvent,nType,nComplete,1,0)
			Task_SetStcTimestamp(nEvent,nType,0,0)
			
			--设置玩家排名
			Activity2015TheBestHero_SetRankingList()
			-- 当第一个玩家成功通关时播放公告
			Activity2015TheBestHero_CallNumberOne()
			
			--设置闯关掩码
			local nEvent1 = tActivity2015TheBestHero_Stc[1]["EventType"]
			local nType1  = tActivity2015TheBestHero_Stc[1]["DataType"]
			local nComplete1 = tActivity2015TheBestHero_Stc[1]["Complete"]
			Task_SetStatistic(nEvent1,nType1,nComplete1,1,0)
			--Task_SetStcTimestamp(nEvent1,nType1,0,0)	
			
			--记录消耗时间掩码,在9分钟内闯关的玩家给对应奖励
			Activity2015TheBestHero_GetFinalRewards()
			
			--升层奖励礼包碎片
			Item_AddItem(tActivity2015TheBestHero_Item["Item3006977"],0,tActivity2015TheBestHero_Reward["UpFloor"][nMapId])
			local str = string.format(tActivity2015TheBestHero_Reward["UpFloor"]["Log"],tActivity2015TheBestHero_Reward["UpFloor"][nMapId])
			Sys_SaveActionFestivalLog(str)
			User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["UpToTopFloor"],tActivity2015TheBestHero_Reward["UpFloor"][nMapId]))
			
			Activity2015TheBestHero_ChgMap(tActivity2015TheBestHero_Npc[18714]["NpcId"]) 		--出地图，闯关成功
			-- --清除状态
			-- local nUserId = Get_UserId()
			-- User_DelAllAttribStatus(nUserId)
			Activity2015TheBestHero_ChkToolStatus(tActivity2015TheBestHero_Item["Item3006975"])
			Activity2015TheBestHero_ChkToolStatus(tActivity2015TheBestHero_Item["Item3006976"])

			nIsFirst = true
			User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[3])
		else
			local nNeed = nNum - nCardsNum
			User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["NotEnough"],nNeed,tActivity2015TheBestHero_Text["CardsName"][nFloor]))
		end		
	end
end

--增益属性丹
--增益属性符
function Activity2015TheBestHero_UseTools(nItemId)
	--判断是否在活动地图中
	if not Activity2015TheBestHero_IsInMap() then
		User_TalkChannel2005(tActivity2015TheBestHero_Text["CannotUse"])
		return
	end

	local nSecs = tActivity2015TheBestHero_Item[nItemId]["Secs"]
	local nTimes = tActivity2015TheBestHero_Item[nItemId]["Times"]
	local nRemainTime = tActivity2015TheBestHero_Item[nItemId]["RemainTime"]
	local nEndTime = tActivity2015TheBestHero_Item[nItemId]["EndTime"]
	local nRecordable = tActivity2015TheBestHero_Item[nItemId]["Recordable"]
	local nUserId = Get_UserId()
	--增益丹，使用后删除
	if nItemId == tActivity2015TheBestHero_Item["Item3006975"] then
		if Item_ChkItem(nItemId) then
			--若身上有状态，则不使用
			for j = 1,6 do
				local nStatus = tActivity2015TheBestHero_Item[nItemId][j] 
				if User_ChkRoleStatus(nStatus,nUserId) then
					User_TalkChannel2005(tActivity2015TheBestHero_Text["UseRepeat"])
					return
				end
			end
			Item_DelItem(nItemId) 
			for i = 1,6 do
				local nStatus = tActivity2015TheBestHero_Item[nItemId][i] 
				local nPower = tActivity2015TheBestHero_Item[nItemId][nStatus]
				User_AddRoleStatus(nStatus,nPower,nSecs,nTimes,nRemainTime,nEndTime,nRecordable,0,0,nUserId)
			end
			User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[6])
			Sys_SaveActionFestivalLog(tActivity2015TheBestHero_Item[nItemId]["Log"])
			User_TalkChannel2005(tActivity2015TheBestHero_Text["UseSuccess"])
		end
	elseif  nItemId == tActivity2015TheBestHero_Item["Item3006976"] then
		--增益符，使用不删除，10分钟期限到自动删除
		if Item_ChkItem(nItemId) then
			Activity2015TheBestHero_ChkToolStatus(nItemId)
			for i = 1,6 do
				local nStatus = tActivity2015TheBestHero_Item[nItemId][i] 
				local nPower = tActivity2015TheBestHero_Item[nItemId][nStatus]
				User_AddRoleStatus(nStatus,nPower,nSecs,nTimes,nRemainTime,nEndTime,nRecordable,0,0,nUserId)
			end
			User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[6])
			Sys_SaveActionFestivalLog(tActivity2015TheBestHero_Item[nItemId]["Log"])
			User_TalkChannel2005(tActivity2015TheBestHero_Text["Using"])
		end
	end
end

--身上有状态加成则删除
function Activity2015TheBestHero_ChkToolStatus(nItemId)
	local i = 0
	local nUserId = Get_UserId()
	
	for j = 1,6 do
		local nStatus = tActivity2015TheBestHero_Item[nItemId][j] 
		if User_ChkRoleStatus(nStatus,nUserId) then
			i = i + 1
		end
	end
	if i == 6 then 
		for k = 1,6 do
			local nStatus = tActivity2015TheBestHero_Item[nItemId][k] 
			User_DelRoleStatus(nStatus,nUserId)
		end
	end
end

--礼包碎片
function Activity2015TheBestHero_UseItem_3006977(nItemId)
	--判断数量
	-- >=5  合成小礼包  3006978
	if not Item_ChkMulItem(nItemId,nItemId,5) then
		User_TalkChannel2005(tActivity2015TheBestHero_Text[nItemId]["NoItem"])
		return
	end
	
	--判断背包空间
	if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
		User_TalkChannel2005(tActivity2015TheBestHero_Text[nItemId]["FullBag"])
		return
	end
	
	if Item_DelMulItem(nItemId,nItemId,5) then
		-- 添加物品
		Item_AddItem(tActivity2015TheBestHero_Item["Item3006978"])
		User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[4])
		Sys_SaveActionFestivalLog(tActivity2015TheBestHero_Log["GetSmallBag"])
		User_TalkChannel2005(tActivity2015TheBestHero_Text[nItemId]["CompoundItem"])
	end
end

--小礼包
function Activity2015TheBestHero_UseItem_3006978(nItemId,nChoose)
	--直接打开
	if nChoose == 1 then
		if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
			LinkItemGossipFunc_New(nItemId,"2-1")
			return
		end
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			--使用后，随机获得物品
			local nFlat,tAward = Probabil_RandomAward(tActivity2015TheBestHero_Reward[3006978],1)
			local nItem = tAward[1]["tAward"][1]["Item_1"]
			
			--判断背包空间
			--723855     730001   3003879   2个
			if nItem == 723855 or nItem == 730001 or nItem == 3003879 then
				if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
					LinkItemGossipFunc_New(nItemId,"2-1")
					return
				end
			end
			
			Item_AddNewItem(nItem,tAward[1]["tAward"][1]["ItemAttr"])
			User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[5])
			Sys_SaveActionFestivalLog(tAward[1]["tAward"][1]["Log"])
			local nIndex = tAward[1]["tAward"][1]["Index"]
			User_TalkChannel2005(tActivity2015TheBestHero_Text[nItemId][nIndex])
		end
	end
	
	-- >=5  合成超级礼包  3006979
	if nChoose == 2 then
		if not Item_ChkMulItem(nItemId,nItemId,5) then
			LinkItemGossipFunc_New(nItemId,"2-3")
			return
		end
		
		--判断背包空间
		if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
			LinkItemGossipFunc_New(nItemId,"2-2")
			return
		end
		
		if Item_DelMulItem(nItemId,nItemId,5) then
			-- 添加物品
			Item_AddItem(tActivity2015TheBestHero_Item["Item3006979"])
			User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[4])
			Sys_SaveActionFestivalLog(tActivity2015TheBestHero_Log["GetSuperBag"])
			User_TalkChannel2005(tActivity2015TheBestHero_Text[nItemId]["CompoundItem"])
		end
	end
end

--超级礼包
function Activity2015TheBestHero_UseItem_3006979(nItemId)
	if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
		User_TalkChannel2005(tActivity2015TheBestHero_Text[nItemId]["FullBag"])
		return
	end
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		---使用后，随机获得物品
		local nFlat,tAward = Probabil_RandomAward(tActivity2015TheBestHero_Reward[nItemId],1)
		--判断是否是限量物品	
		if tAward[1]["tAward"][1]["IsLimited"] ~= nil then
			local nIndex = tAward[1]["tAward"][1]["LimitIndex"]
			local nGlobalId = tActivity2015TheBestHero_Global[nIndex]["GlobalId"]
			local nGlobalData = tActivity2015TheBestHero_Global[nIndex]["GlobalData"]
			local nData = Get_SysDynaGlobalData(nGlobalId,nGlobalData)
			if nData < tActivity2015TheBestHero_Global[nIndex]["MaxData"] then
				Sys_SetSynaGlobalData(nGlobalId,nGlobalData,nData + 1)
			else
				--如果达到限制个数  默认给3003141	梦幻通神丹礼包/5个丹（赠）
				-- 改为3003125
				Item_AddNewItem(tActivity2015TheBestHero_Reward[nItemId][1][4]["Item_1"],tActivity2015TheBestHero_Reward[nItemId][1][4]["ItemAttr"])
				User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[9])
				Sys_SaveActionFestivalLog(tActivity2015TheBestHero_Reward[3006979][1][4]["Log"])
				User_TalkChannel2005(tActivity2015TheBestHero_Text[nItemId][4])
				return
			end
		end	
		--物品ID
		local nItem = tAward[1]["tAward"][1]["Item_1"]
		--判断背包空间
		--3002029  2个
		if nItem == 3002029 then
			if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
				User_TalkChannel2005(tActivity2015TheBestHero_Text[nItemId]["FullBag"])
				return
			end
		end

		Item_AddNewItem(nItem,tAward[1]["tAward"][1]["ItemAttr"])
		User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[9])
		Sys_SaveActionFestivalLog(tAward[1]["tAward"][1]["Log"])
		local nIndex = tAward[1]["tAward"][1]["Index"]
		User_TalkChannel2005(tActivity2015TheBestHero_Text[nItemId][nIndex])
	end
end

--外套碎片
function Activity2015TheBestHero_UseItem_3006980(nItemId,nIndex)
	local nDelNum = tActivity2015TheBestHero_Clothes[nItemId][nIndex]["DelNum"]
	if not Item_ChkMulItem(nItemId,nItemId,nDelNum) then
		LinkItemGossipFunc_New(nItemId,"2-5")
		return
	end
	
	--判断背包空间
	if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
		LinkItemGossipFunc_New(nItemId,"2-6")
		return
	end
	
	if Item_DelMulItem(nItemId,nItemId,nDelNum) then
		-- 获得外套
		local nAddItemId = tActivity2015TheBestHero_Clothes[nItemId][nIndex]["ItemId"]
		Item_AddNewItem(nAddItemId,tActivity2015TheBestHero_Clothes[nItemId][nIndex]["ItemAttr"])
		User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[4])
		Sys_SaveActionFestivalLog(tActivity2015TheBestHero_Clothes[nItemId][nIndex]["Log"])
		User_TalkChannel2005(tActivity2015TheBestHero_Text[nItemId][nIndex])
	end
end

-----------------------------------------杀怪逻辑-------------------------------------------------------------
--普通怪
function Activity2015TheBestHero_KillNormalMonster(nMonsterId)
	-- 判断活动时间
	if not Activity2015TheBestHero_TimeJudgement() then
		return
	end

	local nItemId_1 = tActivity2015TheBestHero_Item["Item3006971"]
	local nItemId_2 = tActivity2015TheBestHero_Item["Item3006972"]
	local nItemId_3 = tActivity2015TheBestHero_Item["Item3006973"]
	local nItemId_4 = tActivity2015TheBestHero_Item["Item3006974"]
	
	--击杀小怪有概率获得令牌  3006971-3006974
	local nMapId = Get_UserMapId()
	local nFloor = tActivity2015TheBestHero_Map[nMapId]
	if nMapId <= tActivity2015TheBestHero_Map[3]  then
		--1-3层掉侠客令牌
		if Sys_Random(100,1000) then
			--判断背包空间
			if not Item_ChkItem(nItemId_1) then
				if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
					User_TalkChannel2005(tActivity2015TheBestHero_Text["FullBag"])
					return
				end
			end
			Item_AddItem(nItemId_1)
			nCardsNum = nCardsNum + 1
			User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["KillMonsCards"][1],tActivity2015TheBestHero_Text["Name"][nFloor]))
			User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[12])
		end
	elseif nMapId <= tActivity2015TheBestHero_Map[6]  then
		--4-6层掉精英令牌
		if Sys_Random(80,1000) then
			--判断背包空间
			if not Item_ChkItem(nItemId_2) then
				if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
					User_TalkChannel2005(tActivity2015TheBestHero_Text["FullBag"])
					return
				end
			end
			Item_AddItem(nItemId_2)
			nCardsNum = nCardsNum + 1
			User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["KillMonsCards"][2],tActivity2015TheBestHero_Text["Name"][nFloor]))
			User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[12])
		end
	elseif nMapId <= tActivity2015TheBestHero_Map[9]  then
		--7-9层掉豪杰令牌
		if Sys_Random(60,1000) then
			--判断背包空间
			if not Item_ChkItem(nItemId_3) then
				if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
					User_TalkChannel2005(tActivity2015TheBestHero_Text["FullBag"])
					return
				end
			end
			Item_AddItem(nItemId_3)
			nCardsNum = nCardsNum + 1
			User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["KillMonsCards"][3],tActivity2015TheBestHero_Text["Name"][nFloor]))
			User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[12])
		end
	elseif nMapId == tActivity2015TheBestHero_Map[10]  then
		--10层掉霸主令牌
		if Sys_Random(40,1000) then
			--判断背包空间
			if not Item_ChkItem(nItemId_4) then
				if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
					User_TalkChannel2005(tActivity2015TheBestHero_Text["FullBag"])
					return
				end
			end
			Item_AddItem(nItemId_4)
			nCardsNum = nCardsNum + 1
			User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["KillMonsCards"][4],tActivity2015TheBestHero_Text["Name"][nFloor]))
			User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[12])
		end
	end
	
	--击杀小怪1.5%概率给属性丹
	if Sys_Random(15,1000) then
		--如果当前背包中没有属性丹，判断背包空间
		if not Item_ChkItem(tActivity2015TheBestHero_Item["Item3006975"]) then
			if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
				User_TalkChannel2005(tActivity2015TheBestHero_Text["FullBag"])
				return
			end
		end
		Item_AddItem(tActivity2015TheBestHero_Item["Item3006975"])
		User_TalkChannel2005(tActivity2015TheBestHero_Text["GetPill"])
	end
	
	local nNum1 = tActivity2015TheBestHero_Item["Item_num1"]
	local nNum2 = tActivity2015TheBestHero_Item["Item_num2"]
	local nNum3 = tActivity2015TheBestHero_Item["Item_num3"]
	
	-- 玩家在每层第一次，背包有5个令牌时，弹出105弹窗，无论他点确定还是取消都会升层
	if Item_ChkMulItem(nItemId_1,nItemId_1,nNum1) then 
		-- 侠客令牌 3006971 
		if nFloor <= 3 and nFloor >= 1 then
			if nIsFirst == true then
				nIsFirst = false
				local str = string.format(tActivity2015TheBestHero_Text["CardTips"],nNum1)
				Sys_MsgBox(str,"</F>Activity2015TheBestHero_UpFloor</N>"..nItemId_1.."</N>"..nNum1,"</F>Activity2015TheBestHero_UpFloor</N>"..nItemId_1.."</N>"..nNum1)
			else
				User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["CardsEnough"],nNum1))
			end
		end
	elseif Item_ChkMulItem(nItemId_2,nItemId_2,nNum2) then 
		-- 精英令牌 3006972
		if nFloor <= 6 and nFloor >= 4 then
			if nIsFirst == true then
				nIsFirst = false
				local str = string.format(tActivity2015TheBestHero_Text["CardTips"],nNum2)
				Sys_MsgBox(str,"</F>Activity2015TheBestHero_UpFloor</N>"..nItemId_2.."</N>"..nNum2,"</F>Activity2015TheBestHero_UpFloor</N>"..nItemId_2.."</N>"..nNum2)
			else
				User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["CardsEnough"],nNum2))
			end
		end
	elseif Item_ChkMulItem(nItemId_3,nItemId_3,nNum3) then 
		-- 豪杰令牌 3006973
		if nFloor <= 9 and nFloor >= 7 then
			if nIsFirst == true then
				nIsFirst = false
				local str = string.format(tActivity2015TheBestHero_Text["CardTips"],nNum3)
				Sys_MsgBox(str,"</F>Activity2015TheBestHero_UpFloor</N>"..nItemId_3.."</N>"..nNum3,"</F>Activity2015TheBestHero_UpFloor</N>"..nItemId_3.."</N>"..nNum3)
			else
				User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["CardsEnough"],nNum3))
			end
		end
	elseif Item_ChkMulItem(nItemId_4,nItemId_4,nNum3) then 
		-- 霸主令牌 3006974
		if nFloor == 10 then	
			if nIsFirst == true then
				nIsFirst = false
				local str = string.format(tActivity2015TheBestHero_Text["CardTips"],nNum3)
				Sys_MsgBox(str,"</F>Activity2015TheBestHero_UpFloor</N>"..nItemId_4.."</N>"..nNum3,"</F>Activity2015TheBestHero_UpFloor</N>"..nItemId_4.."</N>"..nNum3)
			else
				User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["CardsEnough"],nNum3))
			end
		end
	end
end

--boss
function Activity2015TheBestHero_KillBOSS(nMonsterId)
	-- 判断活动时间
	if not Activity2015TheBestHero_TimeJudgement() then
		return
	end
	
	--击杀小怪1.5%概率给属性丹
	if Sys_Random(15,1000) then
		--如果当前背包中没有属性丹，判断背包空间
		if not Item_ChkItem(tActivity2015TheBestHero_Item["Item3006975"]) then
			if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
				User_TalkChannel2005(tActivity2015TheBestHero_Text["FullBag"])
				return
			end
		end
		Item_AddItem(tActivity2015TheBestHero_Item["Item3006975"])
		User_TalkChannel2005(tActivity2015TheBestHero_Text["GetPill"])
	end
	
	--击杀boss奖励
	--掉令牌   气力值 + 免费修炼次数（+物品）
	local nMapId = Get_UserMapId()
	User_AddStrengthValue(tActivity2015TheBestHero_Reward["KillBOSS"][nMonsterId]["Strength"])
	
	--判断背包空间
	if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
		User_TalkChannel2005(tActivity2015TheBestHero_Text["FullBag"])
	else
		Item_AddItem(tActivity2015TheBestHero_Reward["KillBOSS"][nMonsterId]["ItemId"],0,tActivity2015TheBestHero_Reward["KillBOSS"][nMonsterId]["ItemNum"])
		nCardsNum = nCardsNum + tActivity2015TheBestHero_Reward["KillBOSS"][nMonsterId]["ItemNum"]
		User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[12])
	end
	if nMapId == tActivity2015TheBestHero_Map[9] then
		--判断背包空间
		if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
			User_TalkChannel2005(tActivity2015TheBestHero_Text["FullBag"])
		else
			Item_AddNewItem(tActivity2015TheBestHero_Reward["KillBOSS"][nMonsterId]["ItemId_2"],tActivity2015TheBestHero_Reward["KillBOSS"][nMonsterId]["ItemAttr"])
		end
	end
	
	--判断玩家是否有自创功夫
	if User_IsAlreadyCreateGongFu(Get_UserId()) then
		if Get_UserGongFureePractNum() <= tActivity2015TheBestHero_Reward["KillBOSS"]["TopCultivateTimes"] - tActivity2015TheBestHero_Reward["KillBOSS"][nMonsterId]["CultivateTimes"] then
			User_AddGongFuFreePractNum(tActivity2015TheBestHero_Reward["KillBOSS"][nMonsterId]["CultivateTimes"])
			User_TalkChannel2005(tActivity2015TheBestHero_Text["KillBossUpFloor"][nMonsterId][2])
			Sys_SaveActionFestivalLog(tActivity2015TheBestHero_Reward["KillBOSS"][nMonsterId]["Log"][2])
		else
			User_TalkChannel2005(tActivity2015TheBestHero_Text["KillBossUpFloor"][nMonsterId][1])
			Sys_SaveActionFestivalLog(tActivity2015TheBestHero_Reward["KillBOSS"][nMonsterId]["Log"][1])
		end
	else
		User_TalkChannel2005(tActivity2015TheBestHero_Text["KillBossUpFloor"][nMonsterId][1])
		Sys_SaveActionFestivalLog(tActivity2015TheBestHero_Reward["KillBOSS"][nMonsterId]["Log"][1])
	end
	
	local nFloor = tActivity2015TheBestHero_Map[nMapId]
	local nItemId_1 = tActivity2015TheBestHero_Item["Item3006971"]
	local nItemId_2 = tActivity2015TheBestHero_Item["Item3006972"]
	local nItemId_3 = tActivity2015TheBestHero_Item["Item3006973"]
	local nNum1 = tActivity2015TheBestHero_Item["Item_num1"]
	local nNum2 = tActivity2015TheBestHero_Item["Item_num2"]
	local nNum3 = tActivity2015TheBestHero_Item["Item_num3"]
	
	-- 玩家在每层第一次，背包有5个令牌时，弹出105弹窗，无论他点确定还是取消都会升层
	if Item_ChkMulItem(nItemId_1,nItemId_1,nNum1) then 
		-- 侠客令牌 3006971 
		if nFloor == 3 then
			if nIsFirst == true then
				nIsFirst = false
				local str = string.format(tActivity2015TheBestHero_Text["CardTips"],nNum1)
				Sys_MsgBox(str,"</F>Activity2015TheBestHero_UpFloor</N>"..nItemId_1.."</N>"..nNum1,"</F>Activity2015TheBestHero_UpFloor</N>"..nItemId_1.."</N>"..nNum1)
			else
				User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["CardsEnough"],nNum1))
			end
		end
	elseif Item_ChkMulItem(nItemId_2,nItemId_2,nNum2) then 
		-- 精英令牌 3006972
		if nFloor == 6 then
			if nIsFirst == true then
				nIsFirst = false
				local str = string.format(tActivity2015TheBestHero_Text["CardTips"],nNum2)
				Sys_MsgBox(str,"</F>Activity2015TheBestHero_UpFloor</N>"..nItemId_2.."</N>"..nNum2,"</F>Activity2015TheBestHero_UpFloor</N>"..nItemId_2.."</N>"..nNum2)
			else
				User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["CardsEnough"],nNum2))
			end
		end
	elseif Item_ChkMulItem(nItemId_3,nItemId_3,nNum3) then 
		-- 豪杰令牌 3006973
		if nFloor == 9 then
			if nIsFirst == true then
				nIsFirst = false
				local str = string.format(tActivity2015TheBestHero_Text["CardTips"],nNum3)
				Sys_MsgBox(str,"</F>Activity2015TheBestHero_UpFloor</N>"..nItemId_3.."</N>"..nNum3,"</F>Activity2015TheBestHero_UpFloor</N>"..nItemId_3.."</N>"..nNum3)
			else
				User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["CardsEnough"],nNum3))
			end
		end
	end
end
 
 --在每层第一次自动升层  105提示框
function Activity2015TheBestHero_UpFloor(nItemId,nNum)
	local nMapId = Get_UserMapId()
	local nFloor = tActivity2015TheBestHero_Map[nMapId]
	
	local nEvent = tActivity2015TheBestHero_Stc[2]["EventType"]
	local nType  = tActivity2015TheBestHero_Stc[2]["DataType"]
	local nComplete = tActivity2015TheBestHero_Stc[2]["Complete"]

	if nFloor ~= 10 then
		if Item_ChkMulItem(nItemId,nItemId,nNum) then
			Activity2015TheBestHero_ClearAllCards()
			--升层
			User_UserRandTrans(tonumber(nMapId + 1))
			nCardsNum = 0
			nIsFirst = true
			User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[2][nFloor])
			User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[3])
			
			--当玩家来到3 6 9层时给玩家一个系统提示“击败本层地图中央的BOSS可获得奖励！”
			if nFloor == 2 or nFloor == 5 or nFloor == 8 then
				User_TalkChannel2005(tActivity2015TheBestHero_Text["InBossFloor"])
			end
			
			--设置掩码 记录玩家在第几层
			if nPlayerFloor <= nFloor then
				Task_SetStatistic(nEvent,nType,nFloor+1,1,0)
			else
				User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["UpFloorWithOutReward"],nFloor+1))
				return
			end
			
			--记录每层擂台的参与人数
			local nLevel = nFloor + 1
			Sys_SaveEmoneyBuy(tActivity2015TheBestHero_Log["Participation"][nLevel])

			--升层奖励礼包碎片
			Item_AddItem(tActivity2015TheBestHero_Item["Item3006977"],0,tActivity2015TheBestHero_Reward["UpFloor"][nMapId])
			local str = string.format(tActivity2015TheBestHero_Reward["UpFloor"]["Log"],tActivity2015TheBestHero_Reward["UpFloor"][nMapId])
			Sys_SaveActionFestivalLog(str)
			User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["UpFloorReward"],nFloor+1,tActivity2015TheBestHero_Reward["UpFloor"][nMapId]))
		else
			nCardsNum = nCardsNum + 0
			return
		end
	else
		--闯关成功
		if Item_ChkMulItem(nItemId,nItemId,nNum) then
			Activity2015TheBestHero_ClearAllCards()
			nCardsNum = 0
			--设置掩码 记录玩家在第几层
			Task_SetStatistic(nEvent,nType,nComplete,1,0)
			Task_SetStcTimestamp(nEvent,nType,0,0)
			--设置玩家排名
			Activity2015TheBestHero_SetRankingList()
			-- 当第一个玩家成功通关时播放公告
			Activity2015TheBestHero_CallNumberOne()
			
			--设置闯关掩码
			local nEvent1 = tActivity2015TheBestHero_Stc[1]["EventType"]
			local nType1  = tActivity2015TheBestHero_Stc[1]["DataType"]
			local nComplete1 = tActivity2015TheBestHero_Stc[1]["Complete"]
			Task_SetStatistic(nEvent1,nType1,nComplete1,1,0)
			--Task_SetStcTimestamp(nEvent1,nType1,0,0)	
			
			--记录消耗时间掩码,在9分钟内闯关的玩家给对应奖励
			Activity2015TheBestHero_GetFinalRewards()
			
			--升层奖励礼包碎片
			Item_AddItem(tActivity2015TheBestHero_Item["Item3006977"],0,tActivity2015TheBestHero_Reward["UpFloor"][nMapId])
			local str = string.format(tActivity2015TheBestHero_Reward["UpFloor"]["Log"],tActivity2015TheBestHero_Reward["UpFloor"][nMapId])
			Sys_SaveActionFestivalLog(str)
			User_TalkChannel2005(string.format(tActivity2015TheBestHero_Text["UpToTopFloor"],tActivity2015TheBestHero_Reward["UpFloor"][nMapId]))
			
			Activity2015TheBestHero_ChgMap(tActivity2015TheBestHero_Npc[18714]["NpcId"]) --出地图，闯关成功
			-- --清除状态
			-- local nUserId = Get_UserId()
			-- User_DelAllAttribStatus(nUserId)
			Activity2015TheBestHero_ChkToolStatus(tActivity2015TheBestHero_Item["Item3006975"])
			Activity2015TheBestHero_ChkToolStatus(tActivity2015TheBestHero_Item["Item3006976"])
			
			nIsFirst = true
			User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[3])
		else
			nCardsNum = 0
			return
		end
	end
end
 
--宝箱  击败宝箱概率获得当前层数令牌、万年令牌、增益符、增益丹
function Activity2015TheBestHero_KillBox(nMonsterId)
	-- 判断活动时间
	if not Activity2015TheBestHero_TimeJudgement() then
		return
	end

	local nItemId_1 = tActivity2015TheBestHero_Item["Item3006971"]
	local nItemId_2 = tActivity2015TheBestHero_Item["Item3006972"]
	local nItemId_3 = tActivity2015TheBestHero_Item["Item3006973"]
	local nItemId_4 = tActivity2015TheBestHero_Item["Item3006974"]
	-- 当前层数令牌 25%
	if Sys_Random(2500,10000) then
		--有概率获得令牌  3006971-3006974
		local nMapId = Get_UserMapId()
		if nMapId <= tActivity2015TheBestHero_Map[3]  then
			--1-3层掉侠客令牌
			if not Item_ChkItem(nItemId_1) then
				if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
					User_TalkChannel2005(tActivity2015TheBestHero_Text["FullBag"])
					return
				end
			end
			Item_AddItem(nItemId_1)
			nCardsNum = nCardsNum + 1
			User_TalkChannel2005(tActivity2015TheBestHero_Text["KillBox"][1])
			User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[12])
		elseif nMapId <= tActivity2015TheBestHero_Map[6]  then
			--4-6层掉精英令牌
			if not Item_ChkItem(nItemId_2) then
				if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
					User_TalkChannel2005(tActivity2015TheBestHero_Text["FullBag"])
					return
				end
			end
			Item_AddItem(nItemId_2)
			nCardsNum = nCardsNum + 1
			User_TalkChannel2005(tActivity2015TheBestHero_Text["KillBox"][2])
			User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[12])
		elseif nMapId <= tActivity2015TheBestHero_Map[9]  then
			--7-9层掉豪杰令牌
			if not Item_ChkItem(nItemId_3) then
				if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
					User_TalkChannel2005(tActivity2015TheBestHero_Text["FullBag"])
					return
				end
			end
			Item_AddItem(nItemId_3)
			nCardsNum = nCardsNum + 1
			User_TalkChannel2005(tActivity2015TheBestHero_Text["KillBox"][3])
			User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[12])
		elseif nMapId == tActivity2015TheBestHero_Map[10]  then
			--10层掉霸主令牌
			if not Item_ChkItem(nItemId_4) then
				if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
					User_TalkChannel2005(tActivity2015TheBestHero_Text["FullBag"])
					return
				end
			end
			Item_AddItem(nItemId_4)
			nCardsNum = nCardsNum + 1
			User_TalkChannel2005(tActivity2015TheBestHero_Text["KillBox"][4])
			User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[12])
		end
	elseif Sys_Random(500,7500) then		-- 万能令牌 5%
		if nMapId ~= tActivity2015TheBestHero_Map[10]  then
			if not Item_ChkItem(tActivity2015TheBestHero_Item["Item3006970"]) then
				if not User_CheckLeftSpace(tActivity2015TheBestHero_Data["BagSpace_1"]) then
					User_TalkChannel2005(tActivity2015TheBestHero_Text["FullBag"])
					return
				end
			end
			Item_AddItem(tActivity2015TheBestHero_Item["Item3006970"])
			User_TalkChannel2005(tActivity2015TheBestHero_Text["BuySuccess_1"])
			User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[12])
		end
	elseif Sys_Random(6000,7000) then	-- 增益丹 60%
		--直接加状态
		local nItemId = tActivity2015TheBestHero_Item["Item3006975"]
		local nSecs = tActivity2015TheBestHero_Item[nItemId]["Secs"]
		local nTimes = tActivity2015TheBestHero_Item[nItemId]["Times"]
		local nRemainTime = tActivity2015TheBestHero_Item[nItemId]["RemainTime"]
		local nEndTime = tActivity2015TheBestHero_Item[nItemId]["EndTime"]
		local nRecordable = tActivity2015TheBestHero_Item[nItemId]["Recordable"]
		local nUserId = Get_UserId()
		--若身上有状态，则不加
		for j = 1,6 do
			local nStatus = tActivity2015TheBestHero_Item[nItemId][j] 
			if User_ChkRoleStatus(nStatus,nUserId) then
				User_TalkChannel2005(tActivity2015TheBestHero_Text["UseRepeat"])
				return
			end
		end
		for i = 1,6 do
			local nStatus = tActivity2015TheBestHero_Item[nItemId][i] 
			local nPower = tActivity2015TheBestHero_Item[nItemId][nStatus]
			User_AddRoleStatus(nStatus,nPower,nSecs,nTimes,nRemainTime,nEndTime,nRecordable,0,0,nUserId)
		end
		User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[6])
		User_TalkChannel2005(tActivity2015TheBestHero_Text["UseSuccess"])
	else			-- 增益符 10%
		local nItemId = tActivity2015TheBestHero_Item["Item3006976"]
		local nSecs = tActivity2015TheBestHero_Item[nItemId]["Secs"]
		local nTimes = tActivity2015TheBestHero_Item[nItemId]["Times"]
		local nRemainTime = tActivity2015TheBestHero_Item[nItemId]["RemainTime"]
		local nEndTime = tActivity2015TheBestHero_Item[nItemId]["EndTime"]
		local nRecordable = tActivity2015TheBestHero_Item[nItemId]["Recordable"]
		local nUserId = Get_UserId()
		Activity2015TheBestHero_ChkToolStatus(nItemId)  		--身上有状态加成则删除
		--直接加状态
		for i = 1,6 do
			local nStatus = tActivity2015TheBestHero_Item[nItemId][i] 
			local nPower = tActivity2015TheBestHero_Item[nItemId][nStatus]
			User_AddRoleStatus(nStatus,nPower,nSecs,nTimes,nRemainTime,nEndTime,nRecordable,0,0,nUserId)
		end
		User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[6])
		User_TalkChannel2005(tActivity2015TheBestHero_Text["Using"])
	end
	User_EffectAdd(tActivity2015TheBestHero_Effect[1],tActivity2015TheBestHero_Effect[11])
end
 
--定点刷宝箱怪
function Activity2015TheBestHero_BrushBox()
	for i = 1,10 do
		local nMapId = tActivity2015TheBestHero_Map[i]
		local nMonsterId = tActivity2015TheBestHero_BrushBox[i]
		for j = 1,4 do
			local nCellx = tActivity2015TheBestHero_BrushBox["CellX"][j]
			local nCelly = tActivity2015TheBestHero_BrushBox["CellY"][j]
			local nGenId = tActivity2015TheBestHero_BrushBox["nGenId"][j]
			Monster_AddMonster(nMapId,nCellx,nCelly,nGenId,nMonsterId)
		end
	end
end

--------------------------------------------时间触发-----------------------------------------------------------
--19：30-19：40
--前三分钟 发出活动即将开始的公告
function Activity2015TheBestHero_TimeComing()
	if Sys_ChkFullTime(tActivity2015TheBestHero_Cont["Activity"]) then
		Sys_SystemBroadcast(tActivity2015TheBestHero_Text["TimeComing"])
		
		--定点刷宝箱
		for i = 1,10 do
			local nMapId = tActivity2015TheBestHero_Map[i]
			local nMonsterId = tActivity2015TheBestHero_BrushBox[i]
			for j = 1,4 do	
				local nGenId = tActivity2015TheBestHero_BrushBox["nGenId"][j]
				local nNum = Monster_GetMonsterByGenId(nMapId,nGenId)
				if nNum > 0 then
					Monster_DelMonster(nMapId,nMonsterId)
				end
			end
		end
		Activity2015TheBestHero_BrushBox()
	end
end

--前一分钟  弹出全服邀请
function Activity2015TheBestHero_SendInMap()
	if Sys_ChkFullTime(tActivity2015TheBestHero_Cont["Activity"]) then
		if Sys_InviteFilter(tActivity2015TheBestHero_Invite["Activity_InviteId"],tActivity2015TheBestHero_Invite["Activity_Invite_1"]) then
			Sys_InviteTrans(tActivity2015TheBestHero_Invite["MapId"],tActivity2015TheBestHero_Invite["Invite_Pos"],tActivity2015TheBestHero_Invite["InviteSendId"],tActivity2015TheBestHero_Invite["InviteSendOkId"],tActivity2015TheBestHero_Invite["Activity_InviteId"],tActivity2015TheBestHero_Invite["InviteCountDown"])
		end
	end
end

--结束前一分钟
function Activity2015TheBestHero_TimeEnding()
	if Sys_ChkFullTime(tActivity2015TheBestHero_Cont["Activity"]) then
		Sys_SystemBroadcast(tActivity2015TheBestHero_Text["TimeEnding"])
	end
end

--活动结束，传出地图
function Activity2015TheBestHero_SendOut()
	if Sys_ChkFullTime(tActivity2015TheBestHero_Cont["Activity"]) then
		local nMapId = tActivity2015TheBestHero_Map[1]
		for i = 1,10 do 
			nMapId = tActivity2015TheBestHero_Map[i]	
			Map_UserExeFunc(nMapId,-1,"</F>Activity2015TheBestHero_SendOutMap")
		end
	end
end

function Activity2015TheBestHero_SendOutMap()
	local nNpcId = tActivity2015TheBestHero_Npc[18714]["NpcId"]
	local nMapId = tActivity2015TheBestHero_Npc[nNpcId]["Mapid"]
	local nBoundX = tActivity2015TheBestHero_Npc[nNpcId]["CellX"]
	local nBoundY = tActivity2015TheBestHero_Npc[nNpcId]["CellY"]
	local nBoundCX = tActivity2015TheBestHero_Npc["BoundCX"]
	local nBoundCY = tActivity2015TheBestHero_Npc["BoundCY"]
	User_UserRandBoundTrans(nMapId,nBoundX,nBoundY,nBoundCX,nBoundCY,0,0)
	--保存记录点 在双龙城,防止玩家复活再次回到擂台
	local nCellx = nBoundX + nBoundCX
	local nCelly = nBoundY + nBoundCY
	User_RecordPoint(nMapId,nCellx,nCelly)
	User_TalkChannel2005(tActivity2015TheBestHero_Text["SendOut"])
	-- --清理掩码
	--stc(136,86)		记录万能令牌使用时间
	Task_SetStatistic(tActivity2015TheBestHero_Stc[3]["EventType"],tActivity2015TheBestHero_Stc[3]["DataType"],0,1,0)
	Task_SetStcTimestamp(tActivity2015TheBestHero_Stc[3]["EventType"],tActivity2015TheBestHero_Stc[3]["DataType"],0,0)
	--清理令牌
	Activity2015TheBestHero_ClearAllCards()
	-- --删除所有状态
	-- local nUserId = Get_UserId()
	-- User_DelAllAttribStatus(nUserId)
	Activity2015TheBestHero_ChkToolStatus(tActivity2015TheBestHero_Item["Item3006975"])
	Activity2015TheBestHero_ChkToolStatus(tActivity2015TheBestHero_Item["Item3006976"])
end

--清理排行榜 和 礼包限制
function Activity2015TheBestHero_ClearRankingList()
	for nIndex = 1,#tActivity2015TheBestHero_List do
		local nGlobalId = tActivity2015TheBestHero_List[nIndex]["GlobalId"]
		local nPos = tActivity2015TheBestHero_List[nIndex]["GlobalPos"]
		Sys_ResetAllSynaGlobalData(nGlobalId)
		Sys_ResetAllSynaGlobalDataStr(nGlobalId)
	end
	
	if Sys_ChkDayTime(tActivity2015TheBestHero_Cont["ClearLimit"]) then
		for nIndex = 1,#tActivity2015TheBestHero_Global do
			local nGlobalId = tActivity2015TheBestHero_Global[nIndex]["GlobalId"]
			Sys_ResetAllSynaGlobalData(nGlobalId)
		end
	end
	-- 记录玩家在活动时间内通过npc出擂台时所在的层数
	nPlayerFloor = 1
	-- 玩家身上的某种令牌数量  判断还差几个令牌
	nCardsNum = 0
end

--上线删除所有状态
function Activity2015TheBestHero_ClearStatus()
	-- local nUserId = Get_UserId()
	-- User_DelAllAttribStatus(nUserId)
	Activity2015TheBestHero_ChkToolStatus(tActivity2015TheBestHero_Item["Item3006975"])
	Activity2015TheBestHero_ChkToolStatus(tActivity2015TheBestHero_Item["Item3006976"])
	
	-- --清理掩码
	--stc(136,86)		记录万能令牌使用时间
	Task_SetStatistic(tActivity2015TheBestHero_Stc[3]["EventType"],tActivity2015TheBestHero_Stc[3]["DataType"],0,1,0)
	Task_SetStcTimestamp(tActivity2015TheBestHero_Stc[3]["EventType"],tActivity2015TheBestHero_Stc[3]["DataType"],0,0)
end

-- boss刷新时”本层地图中央的BOSS已重新出现，击败他就可获得奖励！“
function Activity2015TheBestHero_BossShowUp()
	if Activity2015TheBestHero_TimeJudgement() then
		local sMonsterName1 = tActivity2015TheBestHero_Text["BossName"][3]
		local nMapId1 = tActivity2015TheBestHero_Map[3]
		if Monster_GetMonsterByName(nMapId1,sMonsterName1) > 0 then
			Map_SendBroadcastMsg(nMapId1, tActivity2015TheBestHero_Text["BossShowUp"])
		end		
		
		local sMonsterName2 = tActivity2015TheBestHero_Text["BossName"][6]
		local nMapId2 = tActivity2015TheBestHero_Map[6]
		if Monster_GetMonsterByName(nMapId2,sMonsterName2) > 0 then
			Map_SendBroadcastMsg(nMapId2, tActivity2015TheBestHero_Text["BossShowUp"])
		end
		
		local sMonsterName3 = tActivity2015TheBestHero_Text["BossName"][9]
		local nMapId3 = tActivity2015TheBestHero_Map[9]
		if Monster_GetMonsterByName(nMapId3,sMonsterName3) > 0 then
			Map_SendBroadcastMsg(nMapId3, tActivity2015TheBestHero_Text["BossShowUp"])
		end
	end
end

-- 实时检测
table.insert(tSystem_Prompet_Func,Activity2015TheBestHero_BossShowUp)

--上线触发
tSystem_PlayLogin_Func = tSystem_PlayLogin_Func or {}
table.insert(tSystem_PlayLogin_Func,Activity2015TheBestHero_ClearStatus)

--前三分钟
tOntimerMin_HM[1927] = tOntimerMin_HM[1927] or {}
table.insert(tOntimerMin_HM[1927],Activity2015TheBestHero_TimeComing)

--前一分钟
tOntimerMin_HM[1929] = tOntimerMin_HM[1929] or {}
table.insert(tOntimerMin_HM[1929],Activity2015TheBestHero_SendInMap)

--结束前一分钟
tOntimerMin_HM[1937] = tOntimerMin_HM[1937] or {}
table.insert(tOntimerMin_HM[1937],Activity2015TheBestHero_TimeEnding)
tOntimerMin_HM[1938] = tOntimerMin_HM[1938] or {}
table.insert(tOntimerMin_HM[1938],Activity2015TheBestHero_TimeEnding)
tOntimerMin_HM[1939] = tOntimerMin_HM[1939] or {}
table.insert(tOntimerMin_HM[1939],Activity2015TheBestHero_TimeEnding)

--活动结束，玩家传出地图
tOntimerMin_HM[1941] = tOntimerMin_HM[1941] or {}
table.insert(tOntimerMin_HM[1941],Activity2015TheBestHero_SendOut)
tOntimerMin_HM[1942] = tOntimerMin_HM[1942] or {}
table.insert(tOntimerMin_HM[1942],Activity2015TheBestHero_SendOut)
tOntimerMin_HM[1943] = tOntimerMin_HM[1943] or {}
table.insert(tOntimerMin_HM[1943],Activity2015TheBestHero_SendOut)
tOntimerMin_HM[1944] = tOntimerMin_HM[1944] or {}
table.insert(tOntimerMin_HM[1944],Activity2015TheBestHero_SendOut)
tOntimerMin_HM[1945] = tOntimerMin_HM[1945] or {}
table.insert(tOntimerMin_HM[1945],Activity2015TheBestHero_SendOut)

--清理排行榜
tOntimerMin_HM[0000] = tOntimerMin_HM[0000] or {}
table.insert(tOntimerMin_HM[0000],Activity2015TheBestHero_ClearRankingList)
tOntimerMin_HM[0005] = tOntimerMin_HM[0005] or {}
table.insert(tOntimerMin_HM[0005],Activity2015TheBestHero_ClearRankingList)
tOntimerMin_HM[1920] = tOntimerMin_HM[1920] or {}
table.insert(tOntimerMin_HM[1920],Activity2015TheBestHero_ClearRankingList)
tOntimerMin_HM[1925] = tOntimerMin_HM[1925] or {}
table.insert(tOntimerMin_HM[1925],Activity2015TheBestHero_ClearRankingList)

------------------------------------------------NPC模块--------------------------------------------------
-- 18714   擂台管理员
tNpcFace[3743] = 8 
tNpcGossip[18714] = tNpcGossip[18714] or DefaultNpc:new{}
tNpcGossip[18714]["OptionHidden"] = 1
--活动前对白
tNpcGossip[18714]["Text1-1"] = {111}
tNpcGossip[18714]["Text111"] = tActivity2015TheBestHero_Text[18714]["Text111"]
tNpcGossip[18714]["tOption1-1"] = {1}
tNpcGossip[18714]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tActivity2015TheBestHero_Cont["BeforeActivity"])
end
--活动后对白
tNpcGossip[18714]["Text1-2"] = {121}
tNpcGossip[18714]["Text121"] = tActivity2015TheBestHero_Text[18714]["Text121"]
tNpcGossip[18714]["tOption1-2"] = {2}
tNpcGossip[18714]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tActivity2015TheBestHero_Cont["AfterActivity"])
end
--活动中对白
tNpcGossip[18714]["Text1-3"] = {131}
tNpcGossip[18714]["Text131"] = tActivity2015TheBestHero_Text[18714]["Text131"]
tNpcGossip[18714]["tOption1-3"] = {3}
tNpcGossip[18714]["ChkFunc1-3"] = function ()
	return Sys_ChkFullTime(tActivity2015TheBestHero_Cont["Activity"]) and (not Activity2015TheBestHero_LevelJudgement())
end
--等级满足条件
tNpcGossip[18714]["Text1-4"] = {141,142}
tNpcGossip[18714]["Text141"] = tActivity2015TheBestHero_Text[18714]["Text141"]
tNpcGossip[18714]["Text142"] = tActivity2015TheBestHero_Text[18714]["Text142"]
tNpcGossip[18714]["tOption1-4"] = {4,5,6,7,8,9}
tNpcGossip[18714]["ChkFunc1-4"] = function ()
	return Sys_ChkFullTime(tActivity2015TheBestHero_Cont["Activity"]) and Activity2015TheBestHero_LevelJudgement()
end
--接Option4：送我入场。
tNpcGossip[18714]["Text4-1"] = {411}
tNpcGossip[18714]["Text411"] = tActivity2015TheBestHero_Text[18714]["Text411"]
tNpcGossip[18714]["tOption4-1"] = {9}
--接Option5：领取活动奖励。 --此项请在当天擂台结束，且0点前显示
tNpcGossip[18714]["Text5-1"] = {511}
tNpcGossip[18714]["Text511"] = tActivity2015TheBestHero_Text[18714]["Text511"]
tNpcGossip[18714]["tOption5-1"] = {10,11,12,13}
tNpcGossip[18714]["ChkFunc5-1"] = function ()
	local nEvent = tActivity2015TheBestHero_Stc[2]["EventType"]
	local nType = tActivity2015TheBestHero_Stc[2]["DataType"]
	local nFloor = Get_UserStatisticValue(nEvent,nType)
	tNpcGossip[18714]["Text511"]= string.format(tActivity2015TheBestHero_Text[18714]["Text511"],nFloor)
	return true
end
--接10：X分钟经验。
tNpcGossip[18714]["Text10-1"] = {1011}
tNpcGossip[18714]["Text1011"] = tActivity2015TheBestHero_Text[18714]["Text1011"]
tNpcGossip[18714]["tOption10-1"] = {14}
--接12：获得XX物品
tNpcGossip[18714]["Text12-1"] = {1211}
tNpcGossip[18714]["Text1211"] = tActivity2015TheBestHero_Text[18714]["Text1211"]
tNpcGossip[18714]["tOption12-1"] = {15}
tNpcGossip[18714]["Text5-2"] = {521}
tNpcGossip[18714]["Text521"] = tActivity2015TheBestHero_Text[18714]["Text521"]
tNpcGossip[18714]["tOption5-2"] = {16,17,18,19}
--接16：360分钟经验。
tNpcGossip[18714]["Text16-1"] = {1611}
tNpcGossip[18714]["Text1611"] = tActivity2015TheBestHero_Text[18714]["Text1611"]
tNpcGossip[18714]["tOption16-1"] = {20}
--接18：1颗究极通神丹（赠）。
tNpcGossip[18714]["Text18-1"] = {1811}
tNpcGossip[18714]["Text1811"] = tActivity2015TheBestHero_Text[18714]["Text1811"]
tNpcGossip[18714]["tOption18-1"] = {21}
tNpcGossip[18714]["Text5-3"] = {531}
tNpcGossip[18714]["Text531"] = tActivity2015TheBestHero_Text[18714]["Text531"]
tNpcGossip[18714]["tOption5-3"] = {21}
tNpcGossip[18714]["Text5-4"] = {541}
tNpcGossip[18714]["Text541"] = tActivity2015TheBestHero_Text[18714]["Text541"]
tNpcGossip[18714]["tOption5-4"] = {21}
--接Option6：领取活动奖励。  --此项请在当天擂台结束，且0点前显示
tNpcGossip[18714]["Text6-1"] = {611,612,613,614,615,616,617,618,619,620,621}
tNpcGossip[18714]["Text611"] = tActivity2015TheBestHero_Text[18714]["Text611"]
tNpcGossip[18714]["Text612"] = tActivity2015TheBestHero_Text[18714]["Text612"]
tNpcGossip[18714]["Text613"] = tActivity2015TheBestHero_Text[18714]["Text613"]
tNpcGossip[18714]["Text614"] = tActivity2015TheBestHero_Text[18714]["Text614"]
tNpcGossip[18714]["Text615"] = tActivity2015TheBestHero_Text[18714]["Text615"]
tNpcGossip[18714]["Text616"] = tActivity2015TheBestHero_Text[18714]["Text616"]
tNpcGossip[18714]["Text617"] = tActivity2015TheBestHero_Text[18714]["Text617"]
tNpcGossip[18714]["Text618"] = tActivity2015TheBestHero_Text[18714]["Text618"]
tNpcGossip[18714]["Text619"] = tActivity2015TheBestHero_Text[18714]["Text619"]
tNpcGossip[18714]["Text620"] = tActivity2015TheBestHero_Text[18714]["Text620"]
tNpcGossip[18714]["Text621"] = tActivity2015TheBestHero_Text[18714]["Text621"]
tNpcGossip[18714]["tOption6-1"] = {22,23}
tNpcGossip[18714]["ChkFunc6-1"] = function ()
	local s0 = tActivity2015TheBestHero_Text[18714]["Null"]
	local s1 = Get_SysDynaGlobalDataStr0(tActivity2015TheBestHero_List[1]["GlobalId"])
	local s2 = Get_SysDynaGlobalDataStr1(tActivity2015TheBestHero_List[2]["GlobalId"])
	local s3 = Get_SysDynaGlobalDataStr2(tActivity2015TheBestHero_List[3]["GlobalId"])
	local s4 = Get_SysDynaGlobalDataStr3(tActivity2015TheBestHero_List[4]["GlobalId"])
	local s5 = Get_SysDynaGlobalDataStr4(tActivity2015TheBestHero_List[5]["GlobalId"])
	local s6 = Get_SysDynaGlobalDataStr5(tActivity2015TheBestHero_List[6]["GlobalId"])
	local s7 = Get_SysDynaGlobalDataStr0(tActivity2015TheBestHero_List[7]["GlobalId"])
	local s8 = Get_SysDynaGlobalDataStr1(tActivity2015TheBestHero_List[8]["GlobalId"])
	local s9 = Get_SysDynaGlobalDataStr2(tActivity2015TheBestHero_List[9]["GlobalId"])
	local s10 = Get_SysDynaGlobalDataStr3(tActivity2015TheBestHero_List[10]["GlobalId"])
	if string.len(s1) ~= 0  then
		tNpcGossip[18714]["Text612"] = string.format(tActivity2015TheBestHero_Text[18714]["Text612"],s1)
	else
		tNpcGossip[18714]["Text612"] = string.format(tActivity2015TheBestHero_Text[18714]["Text612"],s0)
	end	
	if string.len(s2) ~= 0  then
		tNpcGossip[18714]["Text613"] = string.format(tActivity2015TheBestHero_Text[18714]["Text613"],s2)
	else
		tNpcGossip[18714]["Text613"] = string.format(tActivity2015TheBestHero_Text[18714]["Text613"],s0)
	end
	if string.len(s3) ~= 0  then
		tNpcGossip[18714]["Text614"] = string.format(tActivity2015TheBestHero_Text[18714]["Text614"],s3)
	else
		tNpcGossip[18714]["Text614"] = string.format(tActivity2015TheBestHero_Text[18714]["Text614"],s0)
	end
	if string.len(s4) ~= 0  then
		tNpcGossip[18714]["Text615"] = string.format(tActivity2015TheBestHero_Text[18714]["Text615"],s4)
	else
		tNpcGossip[18714]["Text615"] = string.format(tActivity2015TheBestHero_Text[18714]["Text615"],s0)
	end
	if string.len(s5) ~= 0  then
		tNpcGossip[18714]["Text616"] = string.format(tActivity2015TheBestHero_Text[18714]["Text616"],s5)
	else
		tNpcGossip[18714]["Text616"] = string.format(tActivity2015TheBestHero_Text[18714]["Text616"],s0)
	end
	if string.len(s6) ~= 0  then
		tNpcGossip[18714]["Text617"] = string.format(tActivity2015TheBestHero_Text[18714]["Text617"],s6)
	else
		tNpcGossip[18714]["Text617"] = string.format(tActivity2015TheBestHero_Text[18714]["Text617"],s0)
	end
	if string.len(s7) ~= 0  then
		tNpcGossip[18714]["Text618"] = string.format(tActivity2015TheBestHero_Text[18714]["Text618"],s7)
	else
		tNpcGossip[18714]["Text618"] = string.format(tActivity2015TheBestHero_Text[18714]["Text618"],s0)
	end
	if string.len(s8) ~= 0  then
		tNpcGossip[18714]["Text619"] = string.format(tActivity2015TheBestHero_Text[18714]["Text619"],s8)
	else
		tNpcGossip[18714]["Text619"] = string.format(tActivity2015TheBestHero_Text[18714]["Text619"],s0)
	end
	if string.len(s9) ~= 0  then
		tNpcGossip[18714]["Text620"] = string.format(tActivity2015TheBestHero_Text[18714]["Text620"],s9)
	else
		tNpcGossip[18714]["Text620"] = string.format(tActivity2015TheBestHero_Text[18714]["Text620"],s0)
	end
	if string.len(s10) ~= 0  then
		tNpcGossip[18714]["Text621"] = string.format(tActivity2015TheBestHero_Text[18714]["Text621"],s10)
	else
		tNpcGossip[18714]["Text621"] = string.format(tActivity2015TheBestHero_Text[18714]["Text621"],s0)
	end
	return true
end
--接Option6：领取排行奖励。   未参加活动
tNpcGossip[18714]["Text6-3"] = {631}
tNpcGossip[18714]["Text631"] = tActivity2015TheBestHero_Text[18714]["Text631"]
tNpcGossip[18714]["tOption6-3"] = {21}
--接22：领取排行奖励。
tNpcGossip[18714]["Text22-1"] = {2211}
tNpcGossip[18714]["Text2211"] = tActivity2015TheBestHero_Text[18714]["Text2211"]
tNpcGossip[18714]["tOption22-1"] = {21}
tNpcGossip[18714]["Text22-2"] = {2221}
tNpcGossip[18714]["Text2221"] = tActivity2015TheBestHero_Text[18714]["Text2221"]
tNpcGossip[18714]["tOption22-2"] = {21}
tNpcGossip[18714]["Text22-3"] = {2231}
tNpcGossip[18714]["Text2231"] = tActivity2015TheBestHero_Text[18714]["Text2231"]
tNpcGossip[18714]["tOption22-3"] = {21}	
--接Option7：了解活动详情
tNpcGossip[18714]["Text7-1"] = {711,712,713}
tNpcGossip[18714]["Text711"] = tActivity2015TheBestHero_Text[18714]["Text711"]
tNpcGossip[18714]["Text712"] = tActivity2015TheBestHero_Text[18714]["Text712"]
tNpcGossip[18714]["Text713"] = tActivity2015TheBestHero_Text[18714]["Text713"]
tNpcGossip[18714]["tOption7-1"] = {25,26}
--接25：了解注意事项。
tNpcGossip[18714]["Text25-1"] = {2511,2512}
tNpcGossip[18714]["Text2511"] = tActivity2015TheBestHero_Text[18714]["Text2511"]
tNpcGossip[18714]["Text2512"] = tActivity2015TheBestHero_Text[18714]["Text2512"]
tNpcGossip[18714]["tOption25-1"] = {28,29}
--接Option8：了解奖励详情
tNpcGossip[18714]["Text8-1"] = {811,812,813,814}
tNpcGossip[18714]["Text811"] = tActivity2015TheBestHero_Text[18714]["Text811"]
tNpcGossip[18714]["Text812"] = tActivity2015TheBestHero_Text[18714]["Text812"]
tNpcGossip[18714]["Text813"] = tActivity2015TheBestHero_Text[18714]["Text813"]
tNpcGossip[18714]["Text814"] = tActivity2015TheBestHero_Text[18714]["Text814"]
tNpcGossip[18714]["tOption8-1"] = {32,31,30,34,33,35}
--接30：活动结束奖励。--上一页。离开。
tNpcGossip[18714]["Text30-1"] = {3011,3012,3013,3014,3015,3016,3017,3018,3019,3020,3021}
tNpcGossip[18714]["Text3011"] = tActivity2015TheBestHero_Text[18714]["Text3011"]
tNpcGossip[18714]["Text3012"] = tActivity2015TheBestHero_Text[18714]["Text3012"]
tNpcGossip[18714]["Text3013"] = tActivity2015TheBestHero_Text[18714]["Text3013"]
tNpcGossip[18714]["Text3014"] = tActivity2015TheBestHero_Text[18714]["Text3014"]
tNpcGossip[18714]["Text3015"] = tActivity2015TheBestHero_Text[18714]["Text3015"]
tNpcGossip[18714]["Text3016"] = tActivity2015TheBestHero_Text[18714]["Text3016"]
tNpcGossip[18714]["Text3017"] = tActivity2015TheBestHero_Text[18714]["Text3017"]
tNpcGossip[18714]["Text3018"] = tActivity2015TheBestHero_Text[18714]["Text3018"]
tNpcGossip[18714]["Text3019"] = tActivity2015TheBestHero_Text[18714]["Text3019"]
tNpcGossip[18714]["Text3020"] = tActivity2015TheBestHero_Text[18714]["Text3020"]
tNpcGossip[18714]["Text3021"] = tActivity2015TheBestHero_Text[18714]["Text3021"]
tNpcGossip[18714]["tOption30-1"] = {39,36}
--接31：9分钟内通关奖励。--上一页。离开。
tNpcGossip[18714]["Text31-1"] = {3111,3112,3113,3114,3115}
tNpcGossip[18714]["Text3111"] = tActivity2015TheBestHero_Text[18714]["Text3111"]
tNpcGossip[18714]["Text3112"] = tActivity2015TheBestHero_Text[18714]["Text3112"]
tNpcGossip[18714]["Text3113"] = tActivity2015TheBestHero_Text[18714]["Text3113"]
tNpcGossip[18714]["Text3114"] = tActivity2015TheBestHero_Text[18714]["Text3114"]
tNpcGossip[18714]["Text3115"] = tActivity2015TheBestHero_Text[18714]["Text3115"]
tNpcGossip[18714]["tOption31-1"] = {39,36}
--接32：升层奖励。--上一页。离开。
tNpcGossip[18714]["Text32-1"] = {3211,3212,3213,3214,3215,3216,3217,3218,3219,3220,3221,3222}
tNpcGossip[18714]["Text3211"] = tActivity2015TheBestHero_Text[18714]["Text3211"]
tNpcGossip[18714]["Text3212"] = tActivity2015TheBestHero_Text[18714]["Text3212"]
tNpcGossip[18714]["Text3213"] = tActivity2015TheBestHero_Text[18714]["Text3213"]
tNpcGossip[18714]["Text3214"] = tActivity2015TheBestHero_Text[18714]["Text3214"]
tNpcGossip[18714]["Text3215"] = tActivity2015TheBestHero_Text[18714]["Text3215"]
tNpcGossip[18714]["Text3216"] = tActivity2015TheBestHero_Text[18714]["Text3216"]
tNpcGossip[18714]["Text3217"] = tActivity2015TheBestHero_Text[18714]["Text3217"]
tNpcGossip[18714]["Text3218"] = tActivity2015TheBestHero_Text[18714]["Text3218"]
tNpcGossip[18714]["Text3219"] = tActivity2015TheBestHero_Text[18714]["Text3219"]
tNpcGossip[18714]["Text3220"] = tActivity2015TheBestHero_Text[18714]["Text3220"]
tNpcGossip[18714]["Text3221"] = tActivity2015TheBestHero_Text[18714]["Text3221"]
tNpcGossip[18714]["Text3222"] = tActivity2015TheBestHero_Text[18714]["Text3222"]
tNpcGossip[18714]["tOption32-1"] = {37,39}
--接37：查询礼包奖励--上一页。离开。
tNpcGossip[18714]["Text37-1"] = {3711,3712}
tNpcGossip[18714]["Text3711"] = tActivity2015TheBestHero_Text[18714]["Text3711"]
tNpcGossip[18714]["Text3712"] = tActivity2015TheBestHero_Text[18714]["Text3712"]
tNpcGossip[18714]["tOption37-1"] = {40,36}
--接33：擂主奖励。--上一页。离开。
tNpcGossip[18714]["Text33-1"] = {3311,3312,3313,3314}
tNpcGossip[18714]["Text3311"] = tActivity2015TheBestHero_Text[18714]["Text3311"]
tNpcGossip[18714]["Text3312"] = tActivity2015TheBestHero_Text[18714]["Text3312"]
tNpcGossip[18714]["Text3313"] = tActivity2015TheBestHero_Text[18714]["Text3313"]
tNpcGossip[18714]["Text3314"] = tActivity2015TheBestHero_Text[18714]["Text3314"]
tNpcGossip[18714]["tOption33-1"] = {39,36}
--接34：排行奖励。--上一页。离开。
tNpcGossip[18714]["Text34-1"] = {3411,3412,3413,3414,3415,3416}
tNpcGossip[18714]["Text3411"] = tActivity2015TheBestHero_Text[18714]["Text3411"]
tNpcGossip[18714]["Text3412"] = tActivity2015TheBestHero_Text[18714]["Text3412"]
tNpcGossip[18714]["Text3413"] = tActivity2015TheBestHero_Text[18714]["Text3413"]
tNpcGossip[18714]["Text3414"] = tActivity2015TheBestHero_Text[18714]["Text3414"]
tNpcGossip[18714]["Text3415"] = tActivity2015TheBestHero_Text[18714]["Text3415"]
tNpcGossip[18714]["Text3416"] = tActivity2015TheBestHero_Text[18714]["Text3416"]
tNpcGossip[18714]["tOption34-1"] = {38,39}
--接38：了解FlameDragon碎片。--上一页。离开。
tNpcGossip[18714]["Text38-1"] = {3811,3812,3813,3814,3815}
tNpcGossip[18714]["Text3811"] = tActivity2015TheBestHero_Text[18714]["Text3811"]
tNpcGossip[18714]["Text3812"] = tActivity2015TheBestHero_Text[18714]["Text3812"]
tNpcGossip[18714]["Text3813"] = tActivity2015TheBestHero_Text[18714]["Text3813"]
tNpcGossip[18714]["Text3814"] = tActivity2015TheBestHero_Text[18714]["Text3814"]
tNpcGossip[18714]["Text3815"] = tActivity2015TheBestHero_Text[18714]["Text3815"]
tNpcGossip[18714]["tOption38-1"] = {41,36}

--选项
tNpcGossip[18714]["Option1"] = tActivity2015TheBestHero_Text[18714]["Option1"]
tNpcGossip[18714]["Option2"] = tActivity2015TheBestHero_Text[18714]["Option2"]
tNpcGossip[18714]["Option3"] = tActivity2015TheBestHero_Text[18714]["Option3"]
--送我入场。此项请在活动时间内显示
tNpcGossip[18714]["Option4"] = tActivity2015TheBestHero_Text[18714]["Option4"]
tNpcGossip[18714]["OptionFunc4"] = "Activity2015TheBestHero_NPCSendIn</N>18714"
tNpcGossip[18714]["OptionChkFunc4"] = function ()
	if Sys_ChkFullTime(tActivity2015TheBestHero_Cont["Activity"]) then
		if Sys_ChkDayTime(tActivity2015TheBestHero_Cont["ActivityTime"]) then
			return true
		else
			return false
		end
	else
		return false
	end
end
--领取活动奖励。此项请在当天擂台结束，且0点前显示
tNpcGossip[18714]["Option5"] = tActivity2015TheBestHero_Text[18714]["Option5"]
tNpcGossip[18714]["OptionFunc5"] = "Activity2015TheBestHero_GetActiveRewards</N>18714"
tNpcGossip[18714]["OptionChkFunc5"] = function ()
	if Sys_ChkFullTime(tActivity2015TheBestHero_Cont["Activity"]) then
		if Sys_ChkDayTime(tActivity2015TheBestHero_Cont["EndingTime"]) then
			return true
		else
			return false
		end
	else
		return false
	end
end
--领取排行奖励。此项请在当天擂台开始，且0点前显示
tNpcGossip[18714]["Option6"] = tActivity2015TheBestHero_Text[18714]["Option6"]
tNpcGossip[18714]["OptionFunc6"] = "Activity2015TheBestHero_GetRankingDetail</N>18714"
tNpcGossip[18714]["OptionChkFunc6"] = function ()
	if Sys_ChkFullTime(tActivity2015TheBestHero_Cont["Activity"]) then
		if Sys_ChkDayTime(tActivity2015TheBestHero_Cont["RankingTime"]) then
			return true
		else
			return false
		end
	else
		return false
	end
end
--了解活动详情。
tNpcGossip[18714]["Option7"] = tActivity2015TheBestHero_Text[18714]["Option7"]
tNpcGossip[18714]["OptionPoint7"] = "7-1"
--了解奖励详情。
tNpcGossip[18714]["Option8"] = tActivity2015TheBestHero_Text[18714]["Option8"]
tNpcGossip[18714]["OptionPoint8"] = "8-1"
tNpcGossip[18714]["Option9"] = tActivity2015TheBestHero_Text[18714]["Option9"]
tNpcGossip[18714]["Option10"] = tActivity2015TheBestHero_Text[18714]["Option10"]
tNpcGossip[18714]["OptionFunc10"] = "Activity2015TheBestHero_GetFloorRewards</N>18714</N>1"
tNpcGossip[18714]["OptionChkFunc10"] = function ()
	--判断活动结束时玩家所在层数
	local nEvent = tActivity2015TheBestHero_Stc[2]["EventType"]
	local nType = tActivity2015TheBestHero_Stc[2]["DataType"]
	local nFloor = Get_UserStatisticValue(nEvent,nType)
	tNpcGossip[18714]["Option10"] = string.format(tActivity2015TheBestHero_Text[18714]["Option10"],tActivity2015TheBestHero_Reward["EachFloor"][nFloor]["EXP"])
	return true
end
tNpcGossip[18714]["Option11"] = tActivity2015TheBestHero_Text[18714]["Option11"]
tNpcGossip[18714]["OptionFunc11"] = "Activity2015TheBestHero_GetFloorRewards</N>18714</N>2"
tNpcGossip[18714]["OptionChkFunc11"] = function ()
	local nEvent = tActivity2015TheBestHero_Stc[2]["EventType"]
	local nType = tActivity2015TheBestHero_Stc[2]["DataType"]
	local nFloor = Get_UserStatisticValue(nEvent,nType)
	tNpcGossip[18714]["Option11"] = string.format(tActivity2015TheBestHero_Text[18714]["Option11"],tActivity2015TheBestHero_Reward["EachFloor"][nFloor]["Strength"])
	return true
end
tNpcGossip[18714]["Option12"] = tActivity2015TheBestHero_Text[18714]["Option12"]
tNpcGossip[18714]["OptionFunc12"] = "Activity2015TheBestHero_GetFloorRewards</N>18714</N>3"
tNpcGossip[18714]["OptionChkFunc12"] = function ()
	local nEvent = tActivity2015TheBestHero_Stc[2]["EventType"]
	local nType = tActivity2015TheBestHero_Stc[2]["DataType"]
	local nFloor = Get_UserStatisticValue(nEvent,nType)
	if nFloor >= 8 and nFloor <= 10 then
		tNpcGossip[18714]["Option12"] = string.format(tActivity2015TheBestHero_Text[18714]["Option12"],tActivity2015TheBestHero_Text["OptionStr"][nFloor])
		return true
	else
		return false
	end
end
tNpcGossip[18714]["Option13"] = tActivity2015TheBestHero_Text[18714]["Option13"]
tNpcGossip[18714]["Option14"] = tActivity2015TheBestHero_Text[18714]["Option14"]
tNpcGossip[18714]["OptionPoint14"] = "5-1"
tNpcGossip[18714]["Option15"] = tActivity2015TheBestHero_Text[18714]["Option15"]
tNpcGossip[18714]["Option16"] = tActivity2015TheBestHero_Text[18714]["Option16"]
tNpcGossip[18714]["OptionFunc16"] = "Activity2015TheBestHero_GetSuccessRewards</N>18714</N>1"
tNpcGossip[18714]["Option17"] = tActivity2015TheBestHero_Text[18714]["Option17"]
tNpcGossip[18714]["OptionFunc17"] = "Activity2015TheBestHero_GetSuccessRewards</N>18714</N>2"
tNpcGossip[18714]["Option18"] = tActivity2015TheBestHero_Text[18714]["Option18"]
tNpcGossip[18714]["OptionFunc18"] = "Activity2015TheBestHero_GetSuccessRewards</N>18714</N>3"
tNpcGossip[18714]["Option19"] = tActivity2015TheBestHero_Text[18714]["Option19"]
tNpcGossip[18714]["Option20"] = tActivity2015TheBestHero_Text[18714]["Option20"]
tNpcGossip[18714]["OptionPoint20"] = "5-2"
tNpcGossip[18714]["Option21"] = tActivity2015TheBestHero_Text[18714]["Option21"]
--领取排行奖励。
tNpcGossip[18714]["Option22"] = tActivity2015TheBestHero_Text[18714]["Option22"]
tNpcGossip[18714]["OptionFunc22"] = "Activity2015TheBestHero_GetRankingRewards</N>18714"
tNpcGossip[18714]["Option23"] = tActivity2015TheBestHero_Text[18714]["Option23"]
tNpcGossip[18714]["OptionPoint23"] = "1-4"
tNpcGossip[18714]["Option24"] = tActivity2015TheBestHero_Text[18714]["Option24"]
--了解注意事项。
tNpcGossip[18714]["Option25"] = tActivity2015TheBestHero_Text[18714]["Option25"]
tNpcGossip[18714]["OptionPoint25"] = "25-1"
tNpcGossip[18714]["Option26"] = tActivity2015TheBestHero_Text[18714]["Option26"]
tNpcGossip[18714]["OptionPoint26"] = "1-4"
tNpcGossip[18714]["Option27"] = tActivity2015TheBestHero_Text[18714]["Option27"]
tNpcGossip[18714]["Option28"] = tActivity2015TheBestHero_Text[18714]["Option28"]
tNpcGossip[18714]["OptionPoint28"] = "1-4"
tNpcGossip[18714]["Option29"] = tActivity2015TheBestHero_Text[18714]["Option29"]
--活动结束奖励。
tNpcGossip[18714]["Option30"] = tActivity2015TheBestHero_Text[18714]["Option30"]
tNpcGossip[18714]["OptionPoint30"] = "30-1"
--9分钟内通关奖励。
tNpcGossip[18714]["Option31"] = tActivity2015TheBestHero_Text[18714]["Option31"]
tNpcGossip[18714]["OptionPoint31"] = "31-1"
--升层奖励。
tNpcGossip[18714]["Option32"] = tActivity2015TheBestHero_Text[18714]["Option32"]
tNpcGossip[18714]["OptionPoint32"] = "32-1"
--擂主奖励。
tNpcGossip[18714]["Option33"] = tActivity2015TheBestHero_Text[18714]["Option33"]
tNpcGossip[18714]["OptionPoint33"] = "33-1"
--排行奖励。
tNpcGossip[18714]["Option34"] = tActivity2015TheBestHero_Text[18714]["Option34"]
tNpcGossip[18714]["OptionPoint34"] = "34-1"
tNpcGossip[18714]["Option35"] = tActivity2015TheBestHero_Text[18714]["Option35"]
tNpcGossip[18714]["OptionPoint35"] = "1-4"
tNpcGossip[18714]["Option36"] = tActivity2015TheBestHero_Text[18714]["Option36"]
--查询礼包奖励。
tNpcGossip[18714]["Option37"] = tActivity2015TheBestHero_Text[18714]["Option37"]
tNpcGossip[18714]["OptionPoint37"] = "37-1"
--了解FlameDragon碎片。
tNpcGossip[18714]["Option38"] = tActivity2015TheBestHero_Text[18714]["Option38"]
tNpcGossip[18714]["OptionPoint38"] = "38-1"
tNpcGossip[18714]["Option39"] = tActivity2015TheBestHero_Text[18714]["Option39"]
tNpcGossip[18714]["OptionPoint39"] = "8-1"
tNpcGossip[18714]["Option40"] = tActivity2015TheBestHero_Text[18714]["Option40"]
tNpcGossip[18714]["OptionPoint40"] = "32-1"
tNpcGossip[18714]["Option41"] = tActivity2015TheBestHero_Text[18714]["Option41"]
tNpcGossip[18714]["OptionPoint41"] = "34-1"


-- 18715  行脚商人(第一层)
tNpcFace[3744] = 22
tNpcGossip[18715] = tNpcGossip[18715] or DefaultNpc:new{}
tNpcGossip[18715]["OptionHidden"] = 1
--活动中对白
tNpcGossip[18715]["Text1-1"] = {111}
tNpcGossip[18715]["Text111"] = tActivity2015TheBestHero_Text[18715]["Text111"]
tNpcGossip[18715]["tOption1-1"] = {1,2,3,4}
--接1：购买万能金牌（40点天石）。
tNpcGossip[18715]["Text2-1"] = {211}
tNpcGossip[18715]["Text211"] = tActivity2015TheBestHero_Text[18715]["Text211"]
tNpcGossip[18715]["tOption2-1"] = {5}
tNpcGossip[18715]["Text2-2"] = {221}
tNpcGossip[18715]["Text221"] = tActivity2015TheBestHero_Text[18715]["Text221"]
tNpcGossip[18715]["tOption2-2"] = {5}
tNpcGossip[18715]["Text2-3"] = {231}
tNpcGossip[18715]["Text231"] = tActivity2015TheBestHero_Text[18715]["Text231"]
tNpcGossip[18715]["tOption2-3"] = {6,7}
--接2：购买增益符（20点天石）。
tNpcGossip[18715]["Text2-4"] = {241}
tNpcGossip[18715]["Text241"] = tActivity2015TheBestHero_Text[18715]["Text241"]
tNpcGossip[18715]["tOption2-4"] = {5}
tNpcGossip[18715]["Text2-5"] = {251}
tNpcGossip[18715]["Text251"] = tActivity2015TheBestHero_Text[18715]["Text251"]
tNpcGossip[18715]["tOption2-5"] = {5}
tNpcGossip[18715]["Text2-6"] = {261}
tNpcGossip[18715]["Text261"] = tActivity2015TheBestHero_Text[18715]["Text261"]
tNpcGossip[18715]["tOption2-6"] = {8,7}
--接3：送我回双龙城。
tNpcGossip[18715]["Text3-1"] = {311}
tNpcGossip[18715]["Text311"] = tActivity2015TheBestHero_Text[18715]["Text311"]
tNpcGossip[18715]["tOption3-1"] = {9,7}

tNpcGossip[18715]["Option1"] = tActivity2015TheBestHero_Text[18715]["Option1"]
tNpcGossip[18715]["OptionFunc1"] = "Activity2015TheBestHero_BuyPowerCard"
tNpcGossip[18715]["OptionChkFunc1"] = function ()
	local nNpcId = Get_NpcId()
	if nNpcId == 18780 then
		return false
	else
		return true
	end
end
tNpcGossip[18715]["Option2"] = tActivity2015TheBestHero_Text[18715]["Option2"]
tNpcGossip[18715]["OptionFunc2"] = "Activity2015TheBestHero_BuyTool"
tNpcGossip[18715]["Option3"] = tActivity2015TheBestHero_Text[18715]["Option3"]
tNpcGossip[18715]["OptionPoint3"] = "3-1"
tNpcGossip[18715]["Option4"] = tActivity2015TheBestHero_Text[18715]["Option4"]
tNpcGossip[18715]["Option5"] = tActivity2015TheBestHero_Text[18715]["Option5"]
tNpcGossip[18715]["Option6"] = tActivity2015TheBestHero_Text[18715]["Option6"]
tNpcGossip[18715]["OptionFunc6"] = "Activity2015TheBestHero_SureToBuyCard"
tNpcGossip[18715]["Option7"] = tActivity2015TheBestHero_Text[18715]["Option7"]
tNpcGossip[18715]["Option8"] = tActivity2015TheBestHero_Text[18715]["Option8"]
tNpcGossip[18715]["OptionFunc8"] = "Activity2015TheBestHero_SureToBuyTool"
tNpcGossip[18715]["Option9"] = tActivity2015TheBestHero_Text[18715]["Option9"]
tNpcGossip[18715]["OptionFunc9"] = "Activity2015TheBestHero_BackToTown"

tNpcGossip[18772] = tNpcGossip[18715]		-- 18772  行脚商人(第二层)
tNpcGossip[18773] = tNpcGossip[18715]		-- 18773  行脚商人(第三层)
tNpcGossip[18774] = tNpcGossip[18715]		-- 18774  行脚商人(第四层)
tNpcGossip[18775] = tNpcGossip[18715]		-- 18775  行脚商人(第五层)
tNpcGossip[18776] = tNpcGossip[18715]		-- 18776  行脚商人(第六层)
tNpcGossip[18777] = tNpcGossip[18715]		-- 18777  行脚商人(第七层)
tNpcGossip[18778] = tNpcGossip[18715]		-- 18778  行脚商人(第八层)
tNpcGossip[18779] = tNpcGossip[18715]		-- 18779  行脚商人(第九层)
tNpcGossip[18780] = tNpcGossip[18715]		-- 18780  行脚商人(第十层)

----------------------------------------玩家死亡触发----------------------------------------------------------
-- tUserKilled["tFunction"] = tUserKilled["tFunction"] or {}
-- table.insert(tUserKilled["tFunction"],Activity2015TheBestHero_PlayerDead)

------------------------------------------------itemtype模块--------------------------------------------------
--背包信
tItem[3007030] = tItem[3007030] or {}
tItem[3007030]["Text1-1"] = {111,112}
tItem[3007030]["Text111"] = tActivity2015TheBestHero_Text[3007030]["Text111"]
tItem[3007030]["Text112"] = tActivity2015TheBestHero_Text[3007030]["Text112"]
tItem[3007030]["tOption1-1"] = {1}
tItem[3007030]["Option1"] = tActivity2015TheBestHero_Text[3007030]["Option1"]
tItem[3007030]["OptionFunc1"]="Activity2015TheBestHero_UseLetter</N>3007030"

--万能金牌
tItem[3006970] = tItem[3006970] or {}
tItem[3006970]["Function"] = function(nItemId,sItemName)
	local nItemId = tActivity2015TheBestHero_Item["Item3006970"]
	Activity2015TheBestHero_UseItem_3006970(nItemId)
end

--侠客令牌
tItem[3006971] = tItem[3006971] or {}
tItem[3006971]["Function"] = function(nItemId,sItemName)
	local nItemId = tActivity2015TheBestHero_Item["Item3006971"]
	local nNum = tActivity2015TheBestHero_Item["Item_num1"]
	Activity2015TheBestHero_UseCard(nItemId,nNum)
end

--精英令牌
tItem[3006972] = tItem[3006972] or {}
tItem[3006972]["Function"] = function(nItemId,sItemName)
	local nItemId = tActivity2015TheBestHero_Item["Item3006972"]
	local nNum = tActivity2015TheBestHero_Item["Item_num2"]
	Activity2015TheBestHero_UseCard(nItemId,nNum)
end

--豪杰令牌
tItem[3006973] = tItem[3006973] or {}
tItem[3006973]["Function"] = function(nItemId,sItemName)
	local nItemId = tActivity2015TheBestHero_Item["Item3006973"]
	local nNum = tActivity2015TheBestHero_Item["Item_num3"]
	Activity2015TheBestHero_UseCard(nItemId,nNum)
end

--霸主令牌
tItem[3006974] = tItem[3006974] or {}
tItem[3006974]["Function"] = function(nItemId,sItemName)
	local nItemId = tActivity2015TheBestHero_Item["Item3006974"]
	local nNum = tActivity2015TheBestHero_Item["Item_num3"]
	Activity2015TheBestHero_UseCard(nItemId,nNum)
end

--增益属性丹
tItem[3006975] = tItem[3006975] or {}
tItem[3006975]["Function"] = function(nItemId,sItemName)
	local nItemId = tActivity2015TheBestHero_Item["Item3006975"]
	Activity2015TheBestHero_UseTools(nItemId)
end

--增益属性符
tItem[3006976] = tItem[3006976] or {}
tItem[3006976]["Function"] = function(nItemId,sItemName)
	local nItemId = tActivity2015TheBestHero_Item["Item3006976"]
	Activity2015TheBestHero_UseTools(nItemId)
end

--礼包碎片
tItem[3006977] = tItem[3006977] or {}
tItem[3006977]["Function"] = function(nItemId,sItemName)
	local nItemId = tActivity2015TheBestHero_Item["Item3006977"]
	Activity2015TheBestHero_UseItem_3006977(nItemId)
end

--小礼包  武艺超群礼包
tItem[3006978] = tItem[3006978] or {}
tItem[3006978]["Text1-1"] = {111,112}
tItem[3006978]["Text111"] = tActivity2015TheBestHero_Text[3006978]["111"]
tItem[3006978]["Text112"] = tActivity2015TheBestHero_Text[3006978]["112"]
tItem[3006978]["tOption1-1"] = {1,2}
--接1：直接打开。
tItem[3006978]["Text2-1"] = {211}
tItem[3006978]["Text211"] = tActivity2015TheBestHero_Text[3006978]["211"]
tItem[3006978]["tOption2-1"] = {3}
--接2：合成盖世无双礼包。
tItem[3006978]["Text2-2"] = {221}
tItem[3006978]["Text221"] = tActivity2015TheBestHero_Text[3006978]["221"]
tItem[3006978]["tOption2-2"] = {3}
tItem[3006978]["Text2-3"] = {231}
tItem[3006978]["Text231"] = tActivity2015TheBestHero_Text[3006978]["231"]
tItem[3006978]["tOption2-3"] = {3}
tItem[3006978]["Option1"] = tActivity2015TheBestHero_Text[3006978]["Option1"]
tItem[3006978]["OptionFunc1"]="Activity2015TheBestHero_UseItem_3006978</N>3006978</N>1"
tItem[3006978]["Option2"] = tActivity2015TheBestHero_Text[3006978]["Option2"]
tItem[3006978]["OptionFunc2"]="Activity2015TheBestHero_UseItem_3006978</N>3006978</N>2"
tItem[3006978]["Option3"] = tActivity2015TheBestHero_Text[3006978]["Option3"]

--超级礼包
tItem[3006979] = tItem[3006979] or {}
tItem[3006979]["Function"] = function(nItemId,sItemName)
	local nItemId = tActivity2015TheBestHero_Item["Item3006979"]
	Activity2015TheBestHero_UseItem_3006979(nItemId)
end

--外套碎片
tItem[3006980] = tItem[3006980] or {}
tItem[3006980]["Text1-1"] = {111}
tItem[3006980]["Text111"] = tActivity2015TheBestHero_Text[3006980]["111"]
tItem[3006980]["tOption1-1"] = {1,2,3,4}
tItem[3006980]["Text2-1"] = {211}
tItem[3006980]["Text211"] = tActivity2015TheBestHero_Text[3006980]["211"]
tItem[3006980]["tOption2-1"] = {5,6}
tItem[3006980]["Text2-2"] = {221}
tItem[3006980]["Text221"] = tActivity2015TheBestHero_Text[3006980]["221"]
tItem[3006980]["tOption2-2"] = {7,6}
tItem[3006980]["Text2-3"] = {231}
tItem[3006980]["Text231"] = tActivity2015TheBestHero_Text[3006980]["231"]
tItem[3006980]["tOption2-3"] = {8,6}
tItem[3006980]["Text2-4"] = {241}
tItem[3006980]["Text241"] = tActivity2015TheBestHero_Text[3006980]["241"]
tItem[3006980]["tOption2-4"] = {9,6}
tItem[3006980]["Text2-5"] = {251}
tItem[3006980]["Text251"] = tActivity2015TheBestHero_Text[3006980]["251"]
tItem[3006980]["tOption2-5"] = {10}
tItem[3006980]["Text2-6"] = {261}
tItem[3006980]["Text261"] = tActivity2015TheBestHero_Text[3006980]["261"]
tItem[3006980]["tOption2-6"] = {10}
tItem[3006980]["Option1"] = tActivity2015TheBestHero_Text[3006980]["Option1"]
tItem[3006980]["OptionPoint1"]="2-1"
tItem[3006980]["Option2"] = tActivity2015TheBestHero_Text[3006980]["Option2"]
tItem[3006980]["OptionPoint2"]="2-2"
tItem[3006980]["Option3"] = tActivity2015TheBestHero_Text[3006980]["Option3"]
tItem[3006980]["OptionPoint3"]="2-3"
tItem[3006980]["Option4"] = tActivity2015TheBestHero_Text[3006980]["Option4"]
tItem[3006980]["OptionPoint4"]="2-4"
tItem[3006980]["Option5"] = tActivity2015TheBestHero_Text[3006980]["Option5"]
tItem[3006980]["OptionFunc5"]="Activity2015TheBestHero_UseItem_3006980</N>3006980</N>1"
tItem[3006980]["Option6"] = tActivity2015TheBestHero_Text[3006980]["Option6"]
tItem[3006980]["Option7"] = tActivity2015TheBestHero_Text[3006980]["Option7"]
tItem[3006980]["OptionFunc7"]="Activity2015TheBestHero_UseItem_3006980</N>3006980</N>2"
tItem[3006980]["Option8"] = tActivity2015TheBestHero_Text[3006980]["Option8"]
tItem[3006980]["OptionFunc8"]="Activity2015TheBestHero_UseItem_3006980</N>3006980</N>3"
tItem[3006980]["Option9"] = tActivity2015TheBestHero_Text[3006980]["Option9"]
tItem[3006980]["OptionFunc9"]="Activity2015TheBestHero_UseItem_3006980</N>3006980</N>4"
tItem[3006980]["Option10"] = tActivity2015TheBestHero_Text[3006980]["Option10"]

------------------------------------------------Monster模块--------------------------------------------------
--江湖侠客  第1层
tMonster[7841] = tMonster[7841] or {}
tMonster[7841]["tFunction"] = tMonster[7841]["tFunction"] or {}
table.insert(tMonster[7841]["tFunction"],Activity2015TheBestHero_KillNormalMonster)
--江湖侠客  第2层
tMonster[7842] = tMonster[7842] or {}
tMonster[7842]["tFunction"] = tMonster[7842]["tFunction"] or {}
table.insert(tMonster[7842]["tFunction"],Activity2015TheBestHero_KillNormalMonster)
--江湖侠客  第3层
tMonster[7843] = tMonster[7843] or {}
tMonster[7843]["tFunction"] = tMonster[7843]["tFunction"] or {}
table.insert(tMonster[7843]["tFunction"],Activity2015TheBestHero_KillNormalMonster)
-- 第3层擂主
tMonster[7851] = tMonster[7851] or {}
tMonster[7851]["tFunction"] = tMonster[7851]["tFunction"] or {}
table.insert(tMonster[7851]["tFunction"],Activity2015TheBestHero_KillBOSS)

-- 江湖精英  第4层
tMonster[7844] = tMonster[7844] or {}
tMonster[7844]["tFunction"] = tMonster[7844]["tFunction"] or {}
table.insert(tMonster[7844]["tFunction"],Activity2015TheBestHero_KillNormalMonster)
-- 江湖精英  第5层
tMonster[7845] = tMonster[7845] or {}
tMonster[7845]["tFunction"] = tMonster[7845]["tFunction"] or {}
table.insert(tMonster[7845]["tFunction"],Activity2015TheBestHero_KillNormalMonster)
-- 江湖精英  第6层
tMonster[7846] = tMonster[7846] or {}
tMonster[7846]["tFunction"] = tMonster[7846]["tFunction"] or {}
table.insert(tMonster[7846]["tFunction"],Activity2015TheBestHero_KillNormalMonster)
-- 第6层擂主
tMonster[7852] = tMonster[7852] or {}
tMonster[7852]["tFunction"] = tMonster[7852]["tFunction"] or {}
table.insert(tMonster[7852]["tFunction"],Activity2015TheBestHero_KillBOSS)

-- 江湖豪杰 第7层
tMonster[7847] = tMonster[7847] or {}
tMonster[7847]["tFunction"] = tMonster[7847]["tFunction"] or {}
table.insert(tMonster[7847]["tFunction"],Activity2015TheBestHero_KillNormalMonster)
-- 江湖豪杰 第8层
tMonster[7848] = tMonster[7848] or {}
tMonster[7848]["tFunction"] = tMonster[7848]["tFunction"] or {}
table.insert(tMonster[7848]["tFunction"],Activity2015TheBestHero_KillNormalMonster)
-- 江湖豪杰 第9层
tMonster[7849] = tMonster[7849] or {}
tMonster[7849]["tFunction"] = tMonster[7849]["tFunction"] or {}
table.insert(tMonster[7849]["tFunction"],Activity2015TheBestHero_KillNormalMonster)
-- 第9层擂主
tMonster[7853] = tMonster[7853] or {}
tMonster[7853]["tFunction"] = tMonster[7853]["tFunction"] or {}
table.insert(tMonster[7853]["tFunction"],Activity2015TheBestHero_KillBOSS)

-- 江湖霸主 第10层
tMonster[7850] = tMonster[7850] or {}
tMonster[7850]["tFunction"] = tMonster[7850]["tFunction"] or {}
table.insert(tMonster[7850]["tFunction"],Activity2015TheBestHero_KillNormalMonster)

-- 7863 宝箱（第1层）
tMonster[7863] = tMonster[7863] or {}
tMonster[7863]["tFunction"] = tMonster[7863]["tFunction"] or {}
table.insert(tMonster[7863]["tFunction"],Activity2015TheBestHero_KillBox)
-- 7864 宝箱（第2层）
tMonster[7864] = tMonster[7864] or {}
tMonster[7864]["tFunction"] = tMonster[7864]["tFunction"] or {}
table.insert(tMonster[7864]["tFunction"],Activity2015TheBestHero_KillBox)
-- 7865 宝箱（第3层）
tMonster[7865] = tMonster[7865] or {}
tMonster[7865]["tFunction"] = tMonster[7865]["tFunction"] or {}
table.insert(tMonster[7865]["tFunction"],Activity2015TheBestHero_KillBox)
-- 7866 宝箱（第4层）
tMonster[7866] = tMonster[7866] or {}
tMonster[7866]["tFunction"] = tMonster[7866]["tFunction"] or {}
table.insert(tMonster[7866]["tFunction"],Activity2015TheBestHero_KillBox)
-- 7867 宝箱（第5层）
tMonster[7867] = tMonster[7867] or {}
tMonster[7867]["tFunction"] = tMonster[7867]["tFunction"] or {}
table.insert(tMonster[7867]["tFunction"],Activity2015TheBestHero_KillBox)
-- 7868 宝箱（第6层）
tMonster[7868] = tMonster[7868] or {}
tMonster[7868]["tFunction"] = tMonster[7868]["tFunction"] or {}
table.insert(tMonster[7868]["tFunction"],Activity2015TheBestHero_KillBox)
-- 7869 宝箱（第7层）
tMonster[7869] = tMonster[7869] or {}
tMonster[7869]["tFunction"] = tMonster[7869]["tFunction"] or {}
table.insert(tMonster[7869]["tFunction"],Activity2015TheBestHero_KillBox)
-- 7870 宝箱（第8层）
tMonster[7870] = tMonster[7870] or {}
tMonster[7870]["tFunction"] = tMonster[7870]["tFunction"] or {}
table.insert(tMonster[7870]["tFunction"],Activity2015TheBestHero_KillBox)
-- 7871 宝箱（第9层）
tMonster[7871] = tMonster[7871] or {}
tMonster[7871]["tFunction"] = tMonster[7871]["tFunction"] or {}
table.insert(tMonster[7871]["tFunction"],Activity2015TheBestHero_KillBox)
-- 7872 宝箱（第10层）
tMonster[7872] = tMonster[7872] or {}
tMonster[7872]["tFunction"] = tMonster[7872]["tFunction"] or {}
table.insert(tMonster[7872]["tFunction"],Activity2015TheBestHero_KillBox)

