------------------------------------------------------------------------------------
--Name:			[征服][活动脚本]2015情人节花魁活动(2.11-2.28).lua
--Purpose:		2015情人节花魁活动(2.11-2.28)
--Creator: 		张世超
--Created:		2015/02/02
------------------------------------------------------------------------------------

-- 命名前缀
-- Huakui2015

-- 掩码说明
-- 掩码13280记录玩家报名编号
-- 掩码13281记录玩家积分           


-- logID 12000028


-- 常量表配置
local tHuakui2015_Cont = {}
	tHuakui2015_Cont["WebSite"] = "http://event.co.99.com/beauty/"
	tHuakui2015_Cont["AcceptLen"] = 2
	tHuakui2015_Cont["TextFormatNum"] = {}
	tHuakui2015_Cont["TextFormatNum"][1]   = {10,15}
	tHuakui2015_Cont["TextFormatNum"][3]   = {30,45}
	tHuakui2015_Cont["TextFormatNum"][9]   = {90,135}
	tHuakui2015_Cont["TextFormatNum"][99]  = {990,1485}
	tHuakui2015_Cont["TextFormatNum"][999] = {9990,14985}
	
	tHuakui2015_Cont["TextFormatType"] = {}
	tHuakui2015_Cont["TextFormatType"][18222] = {}
	tHuakui2015_Cont["TextFormatType"][18222][1] = "Beer"
	tHuakui2015_Cont["TextFormatType"][18222][2] = "LoveLetter"
	tHuakui2015_Cont["TextFormatType"][18222][3] = "Kiss"
	tHuakui2015_Cont["TextFormatType"][18222][4] = "Jade"
	
	tHuakui2015_Cont["TextFormatType"][18223] = {}
	tHuakui2015_Cont["TextFormatType"][18223][1] = "Lily"
	tHuakui2015_Cont["TextFormatType"][18223][2] = "Orchid"
	tHuakui2015_Cont["TextFormatType"][18223][3] = "Rose"
	tHuakui2015_Cont["TextFormatType"][18223][4] = "Tulip"

	tHuakui2015_Cont["ItemAndPoint"] = {}
	tHuakui2015_Cont["ItemAndPoint"][18222] = {}
	tHuakui2015_Cont["ItemAndPoint"][18222][1] = {}
	tHuakui2015_Cont["ItemAndPoint"][18222][1][1]   = {757001,10}
	tHuakui2015_Cont["ItemAndPoint"][18222][1][3]   = {757003,30}
	tHuakui2015_Cont["ItemAndPoint"][18222][1][9]   = {757009,90}
	tHuakui2015_Cont["ItemAndPoint"][18222][1][99]  = {757099,990}
	tHuakui2015_Cont["ItemAndPoint"][18222][1][999] = {757999,9990}
	
	tHuakui2015_Cont["ItemAndPoint"][18222][2] = {}
	tHuakui2015_Cont["ItemAndPoint"][18222][2][1]   = {756001,10}
	tHuakui2015_Cont["ItemAndPoint"][18222][2][3]   = {756003,30}
	tHuakui2015_Cont["ItemAndPoint"][18222][2][9]   = {756009,90}
	tHuakui2015_Cont["ItemAndPoint"][18222][2][99]  = {756099,990}
	tHuakui2015_Cont["ItemAndPoint"][18222][2][999] = {756999,9990}
	
	tHuakui2015_Cont["ItemAndPoint"][18222][3] = {}
	tHuakui2015_Cont["ItemAndPoint"][18222][3][1]   = {755001,10}
	tHuakui2015_Cont["ItemAndPoint"][18222][3][3]   = {755003,30}
	tHuakui2015_Cont["ItemAndPoint"][18222][3][9]   = {755009,90}
	tHuakui2015_Cont["ItemAndPoint"][18222][3][99]  = {755099,990}
	tHuakui2015_Cont["ItemAndPoint"][18222][3][999] = {755999,9990}
	
	tHuakui2015_Cont["ItemAndPoint"][18222][4] = {}
	tHuakui2015_Cont["ItemAndPoint"][18222][4][1]   = {758001,15}
	tHuakui2015_Cont["ItemAndPoint"][18222][4][3]   = {758003,45}
	tHuakui2015_Cont["ItemAndPoint"][18222][4][9]   = {758009,135}
	tHuakui2015_Cont["ItemAndPoint"][18222][4][99]  = {758099,1485}
	tHuakui2015_Cont["ItemAndPoint"][18222][4][999] = {758999,14985}

	tHuakui2015_Cont["ItemAndPoint"][18223] = {}
	tHuakui2015_Cont["ItemAndPoint"][18223][1] = {}
	tHuakui2015_Cont["ItemAndPoint"][18223][1][1]   = {752001,10}
	tHuakui2015_Cont["ItemAndPoint"][18223][1][3]   = {752003,30}
	tHuakui2015_Cont["ItemAndPoint"][18223][1][9]   = {752009,90}
	tHuakui2015_Cont["ItemAndPoint"][18223][1][99]  = {752099,990}
	tHuakui2015_Cont["ItemAndPoint"][18223][1][999] = {752999,9990}
	
	tHuakui2015_Cont["ItemAndPoint"][18223][2] = {}
	tHuakui2015_Cont["ItemAndPoint"][18223][2][1]   = {753001,10}
	tHuakui2015_Cont["ItemAndPoint"][18223][2][3]   = {753003,30}
	tHuakui2015_Cont["ItemAndPoint"][18223][2][9]   = {753009,90}
	tHuakui2015_Cont["ItemAndPoint"][18223][2][99]  = {753099,990}
	tHuakui2015_Cont["ItemAndPoint"][18223][2][999] = {753999,9990}
	
	tHuakui2015_Cont["ItemAndPoint"][18223][3] = {}
	tHuakui2015_Cont["ItemAndPoint"][18223][3][1]   = {751001,10}
	tHuakui2015_Cont["ItemAndPoint"][18223][3][3]   = {751003,30}
	tHuakui2015_Cont["ItemAndPoint"][18223][3][9]   = {751009,90}
	tHuakui2015_Cont["ItemAndPoint"][18223][3][99]  = {751099,990}
	tHuakui2015_Cont["ItemAndPoint"][18223][3][999] = {751999,9990}
	
	tHuakui2015_Cont["ItemAndPoint"][18223][4] = {}
	tHuakui2015_Cont["ItemAndPoint"][18223][4][1]   = {754001,15}
	tHuakui2015_Cont["ItemAndPoint"][18223][4][3]   = {754003,45}
	tHuakui2015_Cont["ItemAndPoint"][18223][4][9]   = {754009,135}
	tHuakui2015_Cont["ItemAndPoint"][18223][4][99]  = {754099,1485}
	tHuakui2015_Cont["ItemAndPoint"][18223][4][999] = {754999,14985}	
	
	--兑换配置
	tHuakui2015_Cont["Change"] = {}
	
	--Lily花换取啤酒
	tHuakui2015_Cont["Change"][1] = {}
	tHuakui2015_Cont["Change"][1][1]   = {752001,757001}
	tHuakui2015_Cont["Change"][1][3]   = {752003,757003}
	tHuakui2015_Cont["Change"][1][9]   = {752009,757009}
	tHuakui2015_Cont["Change"][1][99]  = {752099,757099}
	tHuakui2015_Cont["Change"][1][999] = {752999,757999}
	
	--Orchid换取情书
	tHuakui2015_Cont["Change"][2] = {}
	tHuakui2015_Cont["Change"][2][1]   = {753001,756001}
	tHuakui2015_Cont["Change"][2][3]   = {753003,756003}
	tHuakui2015_Cont["Change"][2][9]   = {753009,756009}
	tHuakui2015_Cont["Change"][2][99]  = {753099,756099}
	tHuakui2015_Cont["Change"][2][999] = {753999,756999}
	
	--Rose换取飞吻
	tHuakui2015_Cont["Change"][3] = {}
	tHuakui2015_Cont["Change"][3][1]   = {751001,755001}
	tHuakui2015_Cont["Change"][3][3]   = {751003,755003}
	tHuakui2015_Cont["Change"][3][9]   = {751009,755009}
	tHuakui2015_Cont["Change"][3][99]  = {751099,755099}
	tHuakui2015_Cont["Change"][3][999] = {751999,755999}
	
	--Tulip换取玉佩
	tHuakui2015_Cont["Change"][4] = {}
	tHuakui2015_Cont["Change"][4][1]   = {754001,758001}
	tHuakui2015_Cont["Change"][4][3]   = {754003,758003}
	tHuakui2015_Cont["Change"][4][9]   = {754009,758009}
	tHuakui2015_Cont["Change"][4][99]  = {754099,758099}
	tHuakui2015_Cont["Change"][4][999] = {754999,758999}


	
	tHuakui2015_Cont["Award02000Point"] = 2000
	tHuakui2015_Cont["Award10000Point"] = 10000
	tHuakui2015_Cont["Award30000Point"] = 30000
	tHuakui2015_Cont["Award02000Gift"] = 3005825
	tHuakui2015_Cont["Award10000Gift"] = 3005826
	tHuakui2015_Cont["Award30000Gift"] = 3005827
	
	-- 活动时间
	tHuakui2015_Cont["ActivityTime"] = "2015-02-11 00:00 2015-02-28 23:59"
	tHuakui2015_Cont["BeforeActivityTime"] = "2014-02-11 00:00 2015-02-10 23:59"

	-- 等级要求
	tHuakui2015_Cont["Metempsychosis"] = 0
	tHuakui2015_Cont["Level"] = 100
	
	
	-- 掩码
	tHuakui2015_Cont["StcEventRegist"] = 132
	tHuakui2015_Cont["StcTypeRegist"] = 80
	
	tHuakui2015_Cont["StcEventPoint"] = 132
	tHuakui2015_Cont["StcTypePoint"] = 81
	--用来记录玩家所选道具数量
	tHuakui2015_Cont["StcEventItemNum"] = 132
	tHuakui2015_Cont["StcTypeItemNum"] = 89
	--用来记录玩家所选道具类型
	tHuakui2015_Cont["StcEventItemType"] = 132
	tHuakui2015_Cont["StcTypeItemType"] = 90
	
	--用来记录玩家选的玩家编号
	tHuakui2015_Cont["StcEventHandInNum"] = 132
	tHuakui2015_Cont["StcTypeHandInNum"] = 91
	-- 报名条件
	tHuakui2015_Cont["RegistSex"] = {}
	tHuakui2015_Cont["RegistSex"][18222] = 1
	tHuakui2015_Cont["RegistSex"][18223] = 2

	tHuakui2015_Cont["RegistItem1"] = 754099
	tHuakui2015_Cont["RegistItem1Num"] = 1
	tHuakui2015_Cont["RegistItem2"] = 3005824
	tHuakui2015_Cont["RegistItem2Num"] = 42
	tHuakui2015_Cont["RegistEmoney"] = 299
	tHuakui2015_Cont["RegistMoney"] = 30000000
	tHuakui2015_Cont["RegistCount"] = 50
	tHuakui2015_Cont["RegistCount1"] = 40
	tHuakui2015_Cont["RegistCount2"] = 10

	local tHuakui2015_Log = {}
	tHuakui2015_Log["Regist"] = {}
	tHuakui2015_Log["Regist"]["Money"] = "0,0,1,30000000,12000028,1,0,0"
	tHuakui2015_Log["Regist"]["Emoney"] = "299,0,0,0,12000028,1,0,0"
	tHuakui2015_Log["Regist"]["RegistItem1"] = "0,0,754099,1,12000028,1,0,0"
	tHuakui2015_Log["Regist"]["RegistItem2"] = "0,0,3005824,42,12000028,1,0,0"
	--上交log
	tHuakui2015_Log["HandIn"] = "0,0,%s,1,12000028,3,0,0"
	--兑换log
	tHuakui2015_Log["Award02000"] = "0,0,0,0,12000028,2,3005825,1"
	tHuakui2015_Log["Award10000"] = "0,0,0,0,12000028,2,3005826,1"
	tHuakui2015_Log["Award30000"] = "0,0,0,0,12000028,2,3005827,1"
	tHuakui2015_Log["Huakui2015_Change"] = "0,0,%s,1,12000028,2,%s,1"


local tHuakui2015_DynaGlobalData = {}
	tHuakui2015_DynaGlobalData["Count"] = 50846
	
	tHuakui2015_DynaGlobalData["Regist"] = {}
	tHuakui2015_DynaGlobalData["Regist"][1] = 50694
	tHuakui2015_DynaGlobalData["Regist"][2] = 50695
	tHuakui2015_DynaGlobalData["Regist"][3] = 50696
	tHuakui2015_DynaGlobalData["Regist"][4] = 50697
	tHuakui2015_DynaGlobalData["Regist"][5] = 50698
	tHuakui2015_DynaGlobalData["Regist"][6] = 50699
	tHuakui2015_DynaGlobalData["Regist"][7] = 50700
	tHuakui2015_DynaGlobalData["Regist"][8] = 50701
	tHuakui2015_DynaGlobalData["Regist"][9] = 50702
	tHuakui2015_DynaGlobalData["Regist"][10] = 50703
	tHuakui2015_DynaGlobalData["Regist"][11] = 50704
	tHuakui2015_DynaGlobalData["Regist"][12] = 50705
	tHuakui2015_DynaGlobalData["Regist"][13] = 50706
	tHuakui2015_DynaGlobalData["Regist"][14] = 50707
	tHuakui2015_DynaGlobalData["Regist"][15] = 50708
	tHuakui2015_DynaGlobalData["Regist"][16] = 50709
	tHuakui2015_DynaGlobalData["Regist"][17] = 50710
	tHuakui2015_DynaGlobalData["Regist"][18] = 50711
	tHuakui2015_DynaGlobalData["Regist"][19] = 50712
	tHuakui2015_DynaGlobalData["Regist"][20] = 50713
	tHuakui2015_DynaGlobalData["Regist"][21] = 50714
	tHuakui2015_DynaGlobalData["Regist"][22] = 50715
	tHuakui2015_DynaGlobalData["Regist"][23] = 50716
	tHuakui2015_DynaGlobalData["Regist"][24] = 50717
	tHuakui2015_DynaGlobalData["Regist"][25] = 50718
	tHuakui2015_DynaGlobalData["Regist"][26] = 50719
	tHuakui2015_DynaGlobalData["Regist"][27] = 50720
	tHuakui2015_DynaGlobalData["Regist"][28] = 50721
	tHuakui2015_DynaGlobalData["Regist"][29] = 50722
	tHuakui2015_DynaGlobalData["Regist"][30] = 50723
	tHuakui2015_DynaGlobalData["Regist"][31] = 50724
	tHuakui2015_DynaGlobalData["Regist"][32] = 50725
	tHuakui2015_DynaGlobalData["Regist"][33] = 50726
	tHuakui2015_DynaGlobalData["Regist"][34] = 50727
	tHuakui2015_DynaGlobalData["Regist"][35] = 50728
	tHuakui2015_DynaGlobalData["Regist"][36] = 50729
	tHuakui2015_DynaGlobalData["Regist"][37] = 50730
	tHuakui2015_DynaGlobalData["Regist"][38] = 50731
	tHuakui2015_DynaGlobalData["Regist"][39] = 50732
	tHuakui2015_DynaGlobalData["Regist"][40] = 50733
	tHuakui2015_DynaGlobalData["Regist"][41] = 50734
	tHuakui2015_DynaGlobalData["Regist"][42] = 50735
	tHuakui2015_DynaGlobalData["Regist"][43] = 50736
	tHuakui2015_DynaGlobalData["Regist"][44] = 50737
	tHuakui2015_DynaGlobalData["Regist"][45] = 50738
	tHuakui2015_DynaGlobalData["Regist"][46] = 50739
	tHuakui2015_DynaGlobalData["Regist"][47] = 50740
	tHuakui2015_DynaGlobalData["Regist"][48] = 50741
	tHuakui2015_DynaGlobalData["Regist"][49] = 50742
	tHuakui2015_DynaGlobalData["Regist"][50] = 50743

	tHuakui2015_DynaGlobalData["Flower"] = {}
	tHuakui2015_DynaGlobalData["Flower"][18222] = {}
	tHuakui2015_DynaGlobalData["Flower"][18223] = {}
	
	
	tHuakui2015_DynaGlobalData["Flower"][18222][1] = 50746
	tHuakui2015_DynaGlobalData["Flower"][18222][2] = 50747
	tHuakui2015_DynaGlobalData["Flower"][18222][3] = 50748
	tHuakui2015_DynaGlobalData["Flower"][18222][4] = 50749
	tHuakui2015_DynaGlobalData["Flower"][18222][5] = 50750
	tHuakui2015_DynaGlobalData["Flower"][18222][6] = 50751
	tHuakui2015_DynaGlobalData["Flower"][18222][7] = 50752
	tHuakui2015_DynaGlobalData["Flower"][18222][8] = 50753
	tHuakui2015_DynaGlobalData["Flower"][18222][9] = 50754
	tHuakui2015_DynaGlobalData["Flower"][18222][10] = 50755
	tHuakui2015_DynaGlobalData["Flower"][18222][11] = 50756
	tHuakui2015_DynaGlobalData["Flower"][18222][12] = 50757
	tHuakui2015_DynaGlobalData["Flower"][18222][13] = 50758
	tHuakui2015_DynaGlobalData["Flower"][18222][14] = 50759
	tHuakui2015_DynaGlobalData["Flower"][18222][15] = 50760
	tHuakui2015_DynaGlobalData["Flower"][18222][16] = 50761
	tHuakui2015_DynaGlobalData["Flower"][18222][17] = 50762
	tHuakui2015_DynaGlobalData["Flower"][18222][18] = 50763
	tHuakui2015_DynaGlobalData["Flower"][18222][19] = 50764
	tHuakui2015_DynaGlobalData["Flower"][18222][20] = 50765
	tHuakui2015_DynaGlobalData["Flower"][18222][21] = 50766
	tHuakui2015_DynaGlobalData["Flower"][18222][22] = 50767
	tHuakui2015_DynaGlobalData["Flower"][18222][23] = 50768
	tHuakui2015_DynaGlobalData["Flower"][18222][24] = 50769
	tHuakui2015_DynaGlobalData["Flower"][18222][25] = 50770
	tHuakui2015_DynaGlobalData["Flower"][18222][26] = 50771
	tHuakui2015_DynaGlobalData["Flower"][18222][27] = 50772
	tHuakui2015_DynaGlobalData["Flower"][18222][28] = 50773
	tHuakui2015_DynaGlobalData["Flower"][18222][29] = 50774
	tHuakui2015_DynaGlobalData["Flower"][18222][30] = 50775
	tHuakui2015_DynaGlobalData["Flower"][18222][31] = 50776
	tHuakui2015_DynaGlobalData["Flower"][18222][32] = 50777
	tHuakui2015_DynaGlobalData["Flower"][18222][33] = 50778
	tHuakui2015_DynaGlobalData["Flower"][18222][34] = 50779
	tHuakui2015_DynaGlobalData["Flower"][18222][35] = 50780
	tHuakui2015_DynaGlobalData["Flower"][18222][36] = 50781
	tHuakui2015_DynaGlobalData["Flower"][18222][37] = 50782
	tHuakui2015_DynaGlobalData["Flower"][18222][38] = 50783
	tHuakui2015_DynaGlobalData["Flower"][18222][39] = 50784
	tHuakui2015_DynaGlobalData["Flower"][18222][40] = 50785
	tHuakui2015_DynaGlobalData["Flower"][18222][41] = 50786
	tHuakui2015_DynaGlobalData["Flower"][18222][42] = 50787
	tHuakui2015_DynaGlobalData["Flower"][18222][43] = 50788
	tHuakui2015_DynaGlobalData["Flower"][18222][44] = 50789
	tHuakui2015_DynaGlobalData["Flower"][18222][45] = 50790
	tHuakui2015_DynaGlobalData["Flower"][18222][46] = 50791
	tHuakui2015_DynaGlobalData["Flower"][18222][47] = 50792
	tHuakui2015_DynaGlobalData["Flower"][18222][48] = 50793
	tHuakui2015_DynaGlobalData["Flower"][18222][49] = 50794
	tHuakui2015_DynaGlobalData["Flower"][18222][50] = 50795
	
	tHuakui2015_DynaGlobalData["Flower"][18223][1] = 50796
	tHuakui2015_DynaGlobalData["Flower"][18223][2] = 50797
	tHuakui2015_DynaGlobalData["Flower"][18223][3] = 50798
	tHuakui2015_DynaGlobalData["Flower"][18223][4] = 50799
	tHuakui2015_DynaGlobalData["Flower"][18223][5] = 50800
	tHuakui2015_DynaGlobalData["Flower"][18223][6] = 50801
	tHuakui2015_DynaGlobalData["Flower"][18223][7] = 50802
	tHuakui2015_DynaGlobalData["Flower"][18223][8] = 50803
	tHuakui2015_DynaGlobalData["Flower"][18223][9] = 50804
	tHuakui2015_DynaGlobalData["Flower"][18223][10] = 50805
	tHuakui2015_DynaGlobalData["Flower"][18223][11] = 50806
	tHuakui2015_DynaGlobalData["Flower"][18223][12] = 50807
	tHuakui2015_DynaGlobalData["Flower"][18223][13] = 50808
	tHuakui2015_DynaGlobalData["Flower"][18223][14] = 50809
	tHuakui2015_DynaGlobalData["Flower"][18223][15] = 50810
	tHuakui2015_DynaGlobalData["Flower"][18223][16] = 50811
	tHuakui2015_DynaGlobalData["Flower"][18223][17] = 50812
	tHuakui2015_DynaGlobalData["Flower"][18223][18] = 50813
	tHuakui2015_DynaGlobalData["Flower"][18223][19] = 50814
	tHuakui2015_DynaGlobalData["Flower"][18223][20] = 50815
	tHuakui2015_DynaGlobalData["Flower"][18223][21] = 50816
	tHuakui2015_DynaGlobalData["Flower"][18223][22] = 50817
	tHuakui2015_DynaGlobalData["Flower"][18223][23] = 50818
	tHuakui2015_DynaGlobalData["Flower"][18223][24] = 50819
	tHuakui2015_DynaGlobalData["Flower"][18223][25] = 50820
	tHuakui2015_DynaGlobalData["Flower"][18223][26] = 50821
	tHuakui2015_DynaGlobalData["Flower"][18223][27] = 50822
	tHuakui2015_DynaGlobalData["Flower"][18223][28] = 50823
	tHuakui2015_DynaGlobalData["Flower"][18223][29] = 50824
	tHuakui2015_DynaGlobalData["Flower"][18223][30] = 50825
	tHuakui2015_DynaGlobalData["Flower"][18223][31] = 50826
	tHuakui2015_DynaGlobalData["Flower"][18223][32] = 50827
	tHuakui2015_DynaGlobalData["Flower"][18223][33] = 50828
	tHuakui2015_DynaGlobalData["Flower"][18223][34] = 50829
	tHuakui2015_DynaGlobalData["Flower"][18223][35] = 50830
	tHuakui2015_DynaGlobalData["Flower"][18223][36] = 50831
	tHuakui2015_DynaGlobalData["Flower"][18223][37] = 50832
	tHuakui2015_DynaGlobalData["Flower"][18223][38] = 50833
	tHuakui2015_DynaGlobalData["Flower"][18223][39] = 50834
	tHuakui2015_DynaGlobalData["Flower"][18223][40] = 50835
	tHuakui2015_DynaGlobalData["Flower"][18223][41] = 50836
	tHuakui2015_DynaGlobalData["Flower"][18223][42] = 50837
	tHuakui2015_DynaGlobalData["Flower"][18223][43] = 50838
	tHuakui2015_DynaGlobalData["Flower"][18223][44] = 50839
	tHuakui2015_DynaGlobalData["Flower"][18223][45] = 50840
	tHuakui2015_DynaGlobalData["Flower"][18223][46] = 50841
	tHuakui2015_DynaGlobalData["Flower"][18223][47] = 50842
	tHuakui2015_DynaGlobalData["Flower"][18223][48] = 50843
	tHuakui2015_DynaGlobalData["Flower"][18223][49] = 50844
	tHuakui2015_DynaGlobalData["Flower"][18223][50] = 50845





local tHuakui2015_Text = {}
	tHuakui2015_Text[18222] = {}

	-- 活动前对白
	tHuakui2015_Text[18222]["Text111"] = "Ladies and gentlemen, the Mr. & Ms. Conquer contest will be held in Twin City from Feb. 11th to 28th."
	tHuakui2015_Text[18222]["Text112"] = "~We`ll accept up to 50 candidates respectively for Mr. Conquer and Ms. Conquer. I`m the host of Mr. Conquer."
	tHuakui2015_Text[18222]["Text113"] = "~If you`re above Level 100 and you want to be Mr. Conquer, find me!"
	tHuakui2015_Text[18222]["Option1"] = "I~can`t~wait~to~see."

	-- 活动后对白
	tHuakui2015_Text[18222]["Text121"] = "What do you think Mr. Conquer is like? Handsome? Powerful? Or stylish? We`re going to find the answer"
	tHuakui2015_Text[18222]["Text122"] = "~in Mr. Conquer contest from Feb. 11th to 28th. Gentlemen, if you`re above Level 100, come and sign up"
	tHuakui2015_Text[18222]["Text123"] = "~for the event! We also welcome people to donate and support the `Mr. Conquer` in your mind."
	tHuakui2015_Text[18222]["Text124"] = ""
	tHuakui2015_Text[18222]["Option2"] = "I~want~to~sign~up."
	tHuakui2015_Text[18222]["Option3"] = "View~candidates`~score."
	tHuakui2015_Text[18222]["Option4"] = "Donate~for~my~`Mr.~Conquer`."
	tHuakui2015_Text[18222]["Option5"] = "View~my~Fan~Points?"
	tHuakui2015_Text[18222]["Option6"] = "Claim~fan`s~reward."
	tHuakui2015_Text[18222]["Option7"] = "Swap~for~donate~items."
	tHuakui2015_Text[18222]["Option8"] = "Head~to~the~event~page."
	tHuakui2015_Text[18222]["Option9"] = "What`re~the~rules?"

	tHuakui2015_Text[18222]["Text211"] = "Come on, you should reach at least Level 100 to sign up for the event."
	tHuakui2015_Text[18222]["Text212"] = ""
	tHuakui2015_Text[18222]["Option10"] = "Alright."

	tHuakui2015_Text[18222]["Text221"] = "Sorry, you`re late. There are enough candidates for Mr. Conquer contest."
	tHuakui2015_Text[18222]["Text222"] = "~Be earlier next time!"
	tHuakui2015_Text[18222]["Option11"] = "What~a~pity."

	tHuakui2015_Text[18222]["Text231"] = "Hey, you`ve already signed up for the contest, haven`t you? You number is %s."
	tHuakui2015_Text[18222]["Option12"] = "Sorry,~I~forgot."

	tHuakui2015_Text[18222]["Text241"] = "My lady, I`m afraid you got the wrong person. If you want to sign up for Ms. Conquer contest, talk to Ms. Conquer Hostess."
	tHuakui2015_Text[18222]["Text242"] = ""
	tHuakui2015_Text[18222]["Option13"] = "Okay."

	tHuakui2015_Text[18222]["Text251"] = "My hero, you can submit 99 Tulips, or pay 299 CPs, or 30000000 Silver, or 42 Dark Horse Tokens"
	tHuakui2015_Text[18222]["Text252"] = "~to sign up for the contest. As I know, the Spring Festival celebration and Valentine`s Day celebration held in Twin City (288,374)"
	tHuakui2015_Text[18222]["Text253"] = "~give participants up to 6 Dark Horse Tokens in a day. If you`re thinking of that, hurry up! We only"
	tHuakui2015_Text[18222]["Text254"] = "~accept 10 candidates who sign up with the Dark Horse Tokens. So, which way would you like to take?"
	tHuakui2015_Text[18222]["Option14"] = "Submit~99~Tulips."
	tHuakui2015_Text[18222]["Option15"] = "Pay~299~CPs."
	tHuakui2015_Text[18222]["Option16"] = "Pay~30000000~Silver."
	tHuakui2015_Text[18222]["Option17"] = "Submit~42~Dark~Horse~Tokens."
	tHuakui2015_Text[18222]["Option18"] = "I~need~to~think~about~it."

	tHuakui2015_Text[18222]["Text311"] = "Are you sure you want to sign up for Mr. Conquer contest with 99 Tulips?"
	tHuakui2015_Text[18222]["Option19"] = "Yes."
	tHuakui2015_Text[18222]["Option20"] = "I~haven`t~decided,~yet."
	
	tHuakui2015_Text[18222]["Text321"] = "Sorry, you don`t have 99 Tulips. You must be too nervous to check it."
	tHuakui2015_Text[18222]["Text322"] = ""
	tHuakui2015_Text[18222]["Option24"] = "I~see."

	tHuakui2015_Text[18222]["Text331"] = "Great! You`ve successfully signed up for Mr. Conquer contest. You number is [%s]."
	tHuakui2015_Text[18222]["Text332"] = "~Don`t forget to upload a photo of yourself to the event page, and submit your information."
	tHuakui2015_Text[18222]["Text333"] = ""
	tHuakui2015_Text[18222]["Option25"] = "Okay."

	tHuakui2015_Text[18222]["Text341"] = "Sorry, we have recruited enough candidates who signed up in this way. You can consider to sign up with 42 Dark Horse Tokens."
	tHuakui2015_Text[18222]["Text342"] = ""

	tHuakui2015_Text[18222]["Text351"] = "Sorry, we have recruited enough candidates who signed up with the Dark Horse Tokens. You can consider other ways to sign up."
	tHuakui2015_Text[18222]["Text352"] = ""


	tHuakui2015_Text[18222]["Text411"] = "Are you sure you want to sign up for Mr. Conquer contest with 299 CPs?"
	tHuakui2015_Text[18222]["Text511"] = "Are you sure you want to sign up for Mr. Conquer contest with 30000000 Silver?"
	tHuakui2015_Text[18222]["Text611"] = "Are you sure you want to sign up for Mr. Conquer contest with 42 Dark Horse Tokens?"
	tHuakui2015_Text[18222]["Option21"] = "Yes."
	tHuakui2015_Text[18222]["Option22"] = "Yes."
	tHuakui2015_Text[18222]["Option23"] = "Yes."

	tHuakui2015_Text[18222]["Text421"] = "Sorry, you don`t have 299 CPs. You must be too nervous to check it."
	tHuakui2015_Text[18222]["Text422"] = ""

	tHuakui2015_Text[18222]["Text521"] = "Sorry, you don`t have 30000000 Silver. You must be too nervous to check it."
	tHuakui2015_Text[18222]["Text522"] = ""

	tHuakui2015_Text[18222]["Text621"] = "Sorry, you don`t have 42 Dark Horse Tokens. You must be too nervous to check it."
	tHuakui2015_Text[18222]["Text622"] = ""

	tHuakui2015_Text[18222]["Text721"] = "I`m afraid you`re still too green to understand the contest. When you reach Level 100, you can donate and support for your `Mr. Conquer`."
	tHuakui2015_Text[18222]["Text722"] = ""
	tHuakui2015_Text[18222]["Option26"] = "I~see."
	
	
	--上交点赞品
	tHuakui2015_Text[18222]["Text711"] = "You can donate items to support your `Mr. Conquer`. When you increase his score, you`ll also receive a certain amount of Fan Points."
	tHuakui2015_Text[18222]["Text712"] = "~The donate items include Beer, Love Letter, Kiss and Jade. Donating 1/3/9/99/999 piece(s) of Beer, Love Letter, or Kiss will bring you"
	tHuakui2015_Text[18222]["Text713"] = "~10/30/90/990/9990 Fan Points. While donating 1/3/9/99/999 piece(s) of Jade will earn yourself 15/45/135/1485/14985 Fan Points."
	tHuakui2015_Text[18222]["Text714"] = "~First, tell me how many pieces of donate items would you like to submit?"
	tHuakui2015_Text[18222]["Option27"] = "Submit~1~piece."
	tHuakui2015_Text[18222]["Option28"] = "Submit~3~pieces."
	tHuakui2015_Text[18222]["Option29"] = "Submit~9~pieces."
	tHuakui2015_Text[18222]["Option30"] = "Submit~99~pieces."
	tHuakui2015_Text[18222]["Option31"] = "Submit~999~pieces."
	tHuakui2015_Text[18222]["Option32"] = "I~haven`t~decided,~yet."
	
	tHuakui2015_Text[18222]["Text811"] = "Every time you donate %s piece(s) of Beer, Love Letter, or Kiss, you`ll receive %s Fan Points, and the `Mr. Conquer`"
	tHuakui2015_Text[18222]["Text812"] = "~you support will receive %s points. While for %s piece(s) of Jade, you`ll receive %s Fan Points,"
	tHuakui2015_Text[18222]["Text813"] = "~and your `Mr. Conquer` will receive %s points. So, what item of %s piece(s) do you want to submit?"
	tHuakui2015_Text[18222]["Option33"] = "Beer."
	tHuakui2015_Text[18222]["Option34"] = "Love~Letter."
	tHuakui2015_Text[18222]["Option35"] = "Kiss."
	tHuakui2015_Text[18222]["Option36"] = "Jade."
	tHuakui2015_Text[18222]["Option37"] = "I~changed~my~mind."

	tHuakui2015_Text[18222]["Text1311"] = "Are you sure you want to donate %s piece(s) of %s to support your `Mr. Conquer`? (Please enter the candidate`s number to support.)"
	tHuakui2015_Text[18222]["Text1312"] = ""
	tHuakui2015_Text[18222]["Option54"] = "1-50"

	tHuakui2015_Text[18222]["Text1411"] = "Sorry, the candidate`s number does not exist. You need to check it again."
	tHuakui2015_Text[18222]["Option55"] = "Okay."
	tHuakui2015_Text[18222]["Text1421"] = "Sorry, you don`t have the item to donate."
	tHuakui2015_Text[18222]["Option56"] = "I`ll~bring~some."
	
	tHuakui2015_Text[18222]["Text1431"] = "Are you sure you want to support No.%s candidate, [%s]?"
	tHuakui2015_Text[18222]["Option57"] = "Yes."
	tHuakui2015_Text[18222]["Option58"] = "No."

	tHuakui2015_Text[18222]["Text1441"] = "You successfully supported No.%s candidate of Mr. Conquer, [%s]! Currently, his score"
	tHuakui2015_Text[18222]["Text1442"] = "~is %s, and your Fan score is %s."
	tHuakui2015_Text[18222]["Option59"] = "Good."
	
	tHuakui2015_Text[18222]["Text1451"] = "Sorry, you can`t support yourself."

	--查询积分
	tHuakui2015_Text[18222]["Text3711"] = "You can`t see your Fan score, since you are not a fan to any Mr. Conquer."
	tHuakui2015_Text[18222]["Option79"] = "I~see."

	tHuakui2015_Text[18222]["Text3721"] = "You`ve accumulated %s Fan Points."
	tHuakui2015_Text[18222]["Option80"] = "I~see."
	
	--兑换积分
	tHuakui2015_Text[18222]["Text3811"] = "When you accumulate 2000, 10000, or 30000 Fan Points by donating items in Mr. & Ms. Conquer contest,"
	tHuakui2015_Text[18222]["Text3812"] = "~you can exchange them for Fans Like Pack, Fans Love Pack or Fans Fever Pack. No limit on exchange times."
	tHuakui2015_Text[18222]["Text3813"] = "~Which gift pack would you like to claim?"
	tHuakui2015_Text[18222]["Option81"] = "Fans~Like~Pack."
	tHuakui2015_Text[18222]["Option82"] = "Fans~Love~Pack."
	tHuakui2015_Text[18222]["Option83"] = "Fans~Fever~Pack."
	tHuakui2015_Text[18222]["Option84"] = "I~haven`t~decided,~yet."

	tHuakui2015_Text[18222]["Text3911"] = "Sorry, you don`t have %s Fan Points to exchange for this reward."
	tHuakui2015_Text[18222]["Text3912"] = ""
	tHuakui2015_Text[18222]["Option85"] = "I~see."
	
	tHuakui2015_Text[18222]["Text4011"] = "When you open Fans Like Pack, you`ll have a chance to get Flame Dance Scrap, a random 7-day weapon"
	tHuakui2015_Text[18222]["Text4012"] = "~accessory, a Justice Scroll, or other gifts. So, are you sure you want to exchange 2000 Fan Points for the pack?"
	tHuakui2015_Text[18222]["Text4013"] = ""
	tHuakui2015_Text[18222]["Option86"] = "Yes."

	tHuakui2015_Text[18222]["Text4111"] = "You received a %s!"
	tHuakui2015_Text[18222]["Option87"] = "Good."

	tHuakui2015_Text[18222]["Text4121"] = "Your inventory is full. You need to make some room, first."

	tHuakui2015_Text[18222]["Text4211"] = "When you open Fans Love Pack, you`ll have a chance to get Flame Dance Scrap, Valentine`s Day hairstyle,"
	tHuakui2015_Text[18222]["Text4212"] = "~or an Endeavor Scroll, or other gifts. So, are you sure you want to exchange 10000 Fan Points for this pack?"
	tHuakui2015_Text[18222]["Text4213"] = ""
	tHuakui2015_Text[18222]["Option89"] = "Yes."

	tHuakui2015_Text[18222]["Text4311"] = "When you open Fans Fever Pack, you`ll have a chance to get a garment, 2 Flame Dance Scraps, an Endeavor Scroll,"
	tHuakui2015_Text[18222]["Text4312"] = "~a Justice Scroll or other gifts. So, are you sure you want to exchange 30000 Fan Points for this pack?"
	tHuakui2015_Text[18222]["Text4313"] = ""
	tHuakui2015_Text[18222]["Option90"] = "Yes."

	tHuakui2015_Text[18222]["Text4411"] = "The donate items for Mr. Conquer contains Beer, Kiss, Love Letter and Jade. If you happen to have"
	tHuakui2015_Text[18222]["Text4412"] = "~some donate items for Ms. Conquer, you can swap them for the items above for Mr. Conquer with me."
	tHuakui2015_Text[18222]["Text4413"] = "~For example, swap Rose for Kiss, Orchid for Love Letter, and Tulip for Jade. How many pieces of donate items do you want to swap for?"
	tHuakui2015_Text[18222]["Option91"] = "1~piece."
	tHuakui2015_Text[18222]["Option92"] = "3~pieces."
	tHuakui2015_Text[18222]["Option93"] = "9~pieces."
	tHuakui2015_Text[18222]["Option94"] = "99~pieces."
	tHuakui2015_Text[18222]["Option95"] = "999~pieces."
	
	--兑换点赞品
	tHuakui2015_Text[18222]["Text4511"] = "What item of %s piece(s) would you like to swap for?"
	tHuakui2015_Text[18222]["Option96"] = "Swap~Lily~for~Beer."
	tHuakui2015_Text[18222]["Option97"] = "Swap~Orchid~for~Love~Letter."
	tHuakui2015_Text[18222]["Option98"] = "Swap~Rose~for~Kiss."
	tHuakui2015_Text[18222]["Option99"] = "Swap~Tulip~for~Jade."

	tHuakui2015_Text[18222]["Text4611"] = "You don`t have the donate item to swap."
	tHuakui2015_Text[18222]["Option100"] = "Alright."
	
	tHuakui2015_Text[18222]["Text4621"] = "You successfully swapped for %s! Hurry and donate it to your Mr. Conquer!"
	

	


	--报名规则和投票规则
	tHuakui2015_Text[18222]["Text4711"] = "The contest is divided into two parts for Mr. Conquer and Ms. Conquer, taking 50 candidates for each part."
	tHuakui2015_Text[18222]["Text4712"] = "~I`m the host of Mr. Conquer. To sign up or vote for Mr. Conquer, you should reach at least Level 100."
	tHuakui2015_Text[18222]["Text4713"] = "~For gentlemen, you can submit 99 Tulips, or pay 299 CPs, or 30000000 Silver, or 42 Dark Horse Tokens"
	tHuakui2015_Text[18222]["Text4714"] = "~to sign up for the contest. As I know, the Spring Festival celebration and Valentine`s Day celebration held in Twin City (288,374)"
	tHuakui2015_Text[18222]["Text4715"] = "~give participants up to 6 Dark Horse Tokens in a day. Remember, we only accept 10 candidates who sign up with the tokens. So, be quick!"
	tHuakui2015_Text[18222]["Option101"]="What~else?"
	tHuakui2015_Text[18222]["Option102"]="I~see."

	tHuakui2015_Text[18222]["Text4811"] = "For fans, you can donate items to support your `Mr. Conquer` or `Ms. Conquer`. When you increase his/her score,"
	tHuakui2015_Text[18222]["Text4812"] = "~you`ll also receive a certain amount of Fan Points. The donate items for Mr. Conquer include Beer, Love Letter, Kiss and Jade."
	tHuakui2015_Text[18222]["Text4813"] = "~Different items give different amount of points. If you have some donate items for Ms. Conquer, you can talk to me to exchange"
	tHuakui2015_Text[18222]["Text4814"] = "~them for the items for Mr. Conquer."
	tHuakui2015_Text[18222]["Option103"]="Anything~else?"
	tHuakui2015_Text[18222]["Option104"]="Learn~about~other~things."
	
	tHuakui2015_Text[18222]["Text4911"] = "When your Fan Points reach 2000, 10000, or 30000 (accumulated from Mr. Conquer and Ms. Conquer),"
	tHuakui2015_Text[18222]["Text4912"] = "~you can exchange them for corresponding fan`s pack. The top 3 gentlemen of Mr. Conquer are able to"
	tHuakui2015_Text[18222]["Text4913"] = "~claim their prizes on the event page on and after March 1st. By the way, you can check the candidates` score"
	tHuakui2015_Text[18222]["Text4914"] = "~and your Fan score at me."
	tHuakui2015_Text[18222]["Option105"]="Learn~about~other~things."

	tHuakui2015_Text[18222]["Text131"] = "Mr. Conquer contest has ended, and the top 3 gentlemen have come out. If you`re one of the winners, go claim"
	tHuakui2015_Text[18222]["Text132"] = "~your prize on the event page. For supporters, we`ve prepared wonderful fans` packs. Don`t forget to claim your rewards!"
	tHuakui2015_Text[18222]["Text133"] = ""
	tHuakui2015_Text[18222]["Option106"]="Great!"	





	tHuakui2015_Text[18223] = {}

	-- 活动前对白
	tHuakui2015_Text[18223]["Text111"] = "Ladies and gentlemen, the Mr. & Ms. Conquer contest will be held in Twin City from Feb. 11th to 28th."
	tHuakui2015_Text[18223]["Text112"] = "~We`ll accept up to 50 candidates respectively for Mr. Conquer and Ms. Conquer. I`m the host of Mr. Conquer."
	tHuakui2015_Text[18223]["Text113"] = "~If you`re above Level 100 and you want to be Mr. Conquer, find me!"
	tHuakui2015_Text[18223]["Option1"] = "I~can`t~wait~to~see."

	-- 活动中对白
	tHuakui2015_Text[18223]["Text121"] = "What do you think Ms. Conquer is like? Pretty? Very pretty? Or stunningly pretty? We`re going to find the answer"
	tHuakui2015_Text[18223]["Text122"] = "~in Ms. Conquer contest from Feb. 11th to 28th. Gentlemen, if you`re above Level 100, come and sign up"
	tHuakui2015_Text[18223]["Text123"] = "~for the event! We also welcome people to donate and support the `Ms. Conquer` in your mind."
	tHuakui2015_Text[18223]["Text124"] = ""
	tHuakui2015_Text[18223]["Option2"] = "I~want~to~sign~up."
	tHuakui2015_Text[18223]["Option3"] = "View~candidates`~score."
	tHuakui2015_Text[18223]["Option4"] = "Donate~for~my~`Ms.~Conquer`."
	tHuakui2015_Text[18223]["Option5"] = "View~my~Fan~Points?"
	tHuakui2015_Text[18223]["Option6"] = "Claim~fan`s~reward."
	tHuakui2015_Text[18223]["Option7"] = "Swap~for~donate~items."
	tHuakui2015_Text[18223]["Option8"] = "Head~to~the~event~page."
	tHuakui2015_Text[18223]["Option9"] = "What`re~the~rules?"


	tHuakui2015_Text[18223]["Text211"] = "Come on, you should reach at least Level 100 to sign up for the event."
	tHuakui2015_Text[18223]["Text212"] = ""
	tHuakui2015_Text[18223]["Option10"] = "Alright."

	tHuakui2015_Text[18223]["Text221"] = "Sorry, you`re late. There are enough candidates for Ms. Conquer contest."
	tHuakui2015_Text[18223]["Text222"] = "~Be earlier next time!"
	tHuakui2015_Text[18223]["Option11"] = "What~a~pity."

	tHuakui2015_Text[18223]["Text231"] = "Hey, you`ve already signed up for the contest, haven`t you? You number is %s."
	tHuakui2015_Text[18223]["Option12"] = "Sorry,~I~forgot."

	tHuakui2015_Text[18223]["Text241"] = "My hero, I`m afraid you got the wrong person. If you want to sign up for Mr. Conquer contest, talk to Mr. Conquer Host."
	tHuakui2015_Text[18223]["Text242"] = ""
	tHuakui2015_Text[18223]["Option13"] = "Okay."

	tHuakui2015_Text[18223]["Text251"] = "My lady, you can submit 99 Tulips, or pay 299 CPs, or 30000000 Silver, or 42 Dark Horse Tokens"
	tHuakui2015_Text[18223]["Text252"] = "~to sign up for the contest. As I know, the Spring Festival celebration and Valentine`s Day celebration held in Twin City (288,374)"
	tHuakui2015_Text[18223]["Text253"] = "~give participants up to 6 Dark Horse Tokens in a day. If you`re thinking of that, hurry up! We only"
	tHuakui2015_Text[18223]["Text254"] = "~accept 10 candidates who sign up with the Dark Horse Tokens. So, which way would you like to take?"
	tHuakui2015_Text[18223]["Option14"] = "Submit~99~Tulips."
	tHuakui2015_Text[18223]["Option15"] = "Pay~299~CPs."
	tHuakui2015_Text[18223]["Option16"] = "Pay~30000000~Silver."
	tHuakui2015_Text[18223]["Option17"] = "Submit~42~Dark~Horse~Tokens."
	tHuakui2015_Text[18223]["Option18"] = "I~haven`t~decided,~yet."

	tHuakui2015_Text[18223]["Text311"] = "Are you sure you want to sign up for Mr. Conquer contest with 99 Tulips?"
	tHuakui2015_Text[18223]["Option19"] = "Yes."
	tHuakui2015_Text[18223]["Option20"] = "I~haven`t~decided,~yet."
	
	tHuakui2015_Text[18223]["Text321"] = "Sorry, you don`t have 99 Tulips. You must be too nervous to check it."
	tHuakui2015_Text[18223]["Text322"] = ""
	tHuakui2015_Text[18223]["Option24"] = "I~see."

	tHuakui2015_Text[18223]["Text331"] = "Great! You`ve successfully signed up for Ms. Conquer contest. You number is [%s]."
	tHuakui2015_Text[18223]["Text332"] = "~Don`t forget to upload a photo of yourself to the event page, and submit your information."
	tHuakui2015_Text[18223]["Text333"] = ""
	tHuakui2015_Text[18223]["Option25"] = "Okay."

	tHuakui2015_Text[18223]["Text341"] = "Sorry, we have recruited enough candidates who signed up in this way. You can consider to sign up with 42 Dark Horse Tokens."
	tHuakui2015_Text[18223]["Text342"] = ""

	tHuakui2015_Text[18223]["Text351"] = "Sorry, we have recruited enough candidates who signed up with the Dark Horse Tokens. You can consider other ways to sign up."
	tHuakui2015_Text[18223]["Text352"] = ""


	tHuakui2015_Text[18223]["Text411"] = "Are you sure you want to sign up for Ms. Conquer contest with 299 CPs?"
	tHuakui2015_Text[18223]["Text511"] = "Are you sure you want to sign up for Ms. Conquer contest with 30000000 Silver?"
	tHuakui2015_Text[18223]["Text611"] = "Are you sure you want to sign up for Ms. Conquer contest with 42 Dark Horse Tokens?"
	tHuakui2015_Text[18223]["Option21"] = "Yes."
	tHuakui2015_Text[18223]["Option22"] = "Yes."
	tHuakui2015_Text[18223]["Option23"] = "Yes."

	tHuakui2015_Text[18223]["Text421"] = "Sorry, you don`t have 299 CPs. You must be too nervous to check it."
	tHuakui2015_Text[18223]["Text422"] = ""

	tHuakui2015_Text[18223]["Text521"] = "Sorry, you don`t have 30000000 Silver. You must be too nervous to check it."
	tHuakui2015_Text[18223]["Text522"] = ""

	tHuakui2015_Text[18223]["Text621"] = "Sorry, you don`t have 42 Dark Horse Tokens. You must be too nervous to check it."
	tHuakui2015_Text[18223]["Text622"] = ""

	tHuakui2015_Text[18223]["Text721"] = "I`m afraid you`re still too green to understand the contest. When you reach Level 100, you can donate and support for your `Ms. Conquer`."
	tHuakui2015_Text[18223]["Text722"] = ""
	tHuakui2015_Text[18223]["Option26"] = "I~see."

	tHuakui2015_Text[18223]["Text711"] = "You can donate items to support your `Ms. Conquer`. When you increase her score, you`ll also receive a certain amount of Fan Points."
	tHuakui2015_Text[18223]["Text712"] = "~The donate items include Rose, Lily, Orchid and Tulip. Donating 1/3/9/99/999 Roses, Lilies, Orchids will bring you"
	tHuakui2015_Text[18223]["Text713"] = "~10/30/90/990/9990 Fan Points. While donating 1/3/9/99/999 Tulips will earn yourself 15/45/135/1485/14985 Fan Points."
	tHuakui2015_Text[18223]["Text714"] = "~First, tell me how many flowers would you like to submit?"
	tHuakui2015_Text[18223]["Option27"] = "Submit~1~flower."
	tHuakui2015_Text[18223]["Option28"] = "Submit~3~flowers."
	tHuakui2015_Text[18223]["Option29"] = "Submit~9~flowers."
	tHuakui2015_Text[18223]["Option30"] = "Submit~99~flowers."
	tHuakui2015_Text[18223]["Option31"] = "Submit~999~flowers."
	tHuakui2015_Text[18223]["Option32"] = "I~haven`t~decided,~yet."
	
	tHuakui2015_Text[18223]["Text811"] = "Every time you donate 1 Lily, Orchid or Rose, you`ll receive 10 Fan Points, and the `Ms. Conquer`"
	tHuakui2015_Text[18223]["Text812"] = "~you support will receive 10 points. While for 1 Tulip, you`ll receive 15 Fan Points,"
	tHuakui2015_Text[18223]["Text813"] = "~and your `Ms. Conquer` will receive 15 points. So, what flower do you want to submit?"
	tHuakui2015_Text[18223]["Option33"] = "Lily."
	tHuakui2015_Text[18223]["Option34"] = "Orchid."
	tHuakui2015_Text[18223]["Option35"] = "Rose."
	tHuakui2015_Text[18223]["Option36"] = "Tulip."
	tHuakui2015_Text[18223]["Option37"] = "I~changed~my~mind."


	tHuakui2015_Text[18223]["Text1311"] = "Are you sure you want to donate %s %s(s) to support your `Ms. Conquer`? (Please enter the candidate`s number to support.)"
	tHuakui2015_Text[18223]["Text1312"] = ""
	tHuakui2015_Text[18223]["Option54"] = "1-50"
	
	tHuakui2015_Text[18223]["Text1411"] = "Sorry, the candidate`s number does not exist. You need to check it again."
	tHuakui2015_Text[18223]["Option55"] = "Okay."
	tHuakui2015_Text[18223]["Text1421"] = "Sorry, you don`t have the flower to donate."
	tHuakui2015_Text[18223]["Option56"] = "I`ll~bring~some."
	
	tHuakui2015_Text[18223]["Text1431"] = "Are you sure you want to support No.%s candidate, [%s]?"
	tHuakui2015_Text[18223]["Option57"] = "Yes."
	tHuakui2015_Text[18223]["Option58"] = "No."

	tHuakui2015_Text[18223]["Text1441"] = "You successfully supported No.%s candidate of Ms. Conquer, [%s]! Currently, her score"
	tHuakui2015_Text[18223]["Text1442"] = "~is %s, and your Fan score is %s."
	tHuakui2015_Text[18223]["Option59"] = "Good."
	
	tHuakui2015_Text[18223]["Text1451"] = "Sorry, you can`t support yourself."
	

	tHuakui2015_Text[18223]["Text3711"] = "You can`t see your Fan Points, since you are not a fan to any Mr. Conquer."
	tHuakui2015_Text[18223]["Option79"] = "I~see."

	tHuakui2015_Text[18223]["Text3721"] = "You`ve accumulated %s Fan Point(s)!"
	tHuakui2015_Text[18223]["Option80"] = "I~see."

	tHuakui2015_Text[18223]["Text3811"] = "When you accumulate 2000, 10000, or 30000 Fan Points by donating items in Mr. & Ms. Conquer contest,"
	tHuakui2015_Text[18223]["Text3812"] = "~you can exchange them for Fans Like Pack, Fans Love Pack or Fans Fever Pack. No limit on exchange times."
	tHuakui2015_Text[18223]["Text3813"] = "~Which gift pack would you like to claim?"
	tHuakui2015_Text[18223]["Option81"] = "Fans~Like~Pack."
	tHuakui2015_Text[18223]["Option82"] = "Fans~Love~Pack."
	tHuakui2015_Text[18223]["Option83"] = "Fans~Fever~Pack."
	tHuakui2015_Text[18223]["Option84"] = "I~haven`t~decided,~yet."

	tHuakui2015_Text[18223]["Text3911"] = "Sorry, you don`t have %s Fan Points to exchange for this reward."
	tHuakui2015_Text[18223]["Text3912"] = ""
	tHuakui2015_Text[18223]["Option85"] = "I~see."
	
	tHuakui2015_Text[18223]["Text4011"] = "When you open Fans Like Pack, you`ll have a chance to get Flame Dance Scrap, a random 7-day weapon"
	tHuakui2015_Text[18223]["Text4012"] = "~accessory, a Justice Scroll, or other gifts. So, are you sure you want to exchange 2000 Fan Points for the pack?"
	tHuakui2015_Text[18223]["Text4013"] = ""
	tHuakui2015_Text[18223]["Option86"] = "Yes."

	tHuakui2015_Text[18223]["Text4111"] = "You received a %s!"
	tHuakui2015_Text[18223]["Option87"] = "Good."

	tHuakui2015_Text[18223]["Text4121"] = "Your inventory is full. You need to make some room, first."

	tHuakui2015_Text[18223]["Text4211"] = "When you open Fans Love Pack, you`ll have a chance to get Flame Dance Scrap, Valentine`s Day hairstyle,"
	tHuakui2015_Text[18223]["Text4212"] = "~or an Endeavor Scroll, or other gifts. So, are you sure you want to exchange 10000 Fan Points for this pack?"
	tHuakui2015_Text[18223]["Text4213"] = ""
	tHuakui2015_Text[18223]["Option89"] = "Yes."

	tHuakui2015_Text[18223]["Text4311"] = "When you open Fans Fever Pack, you`ll have a chance to get a garment, 2 Flame Dance Scraps, an Endeavor Scroll,"
	tHuakui2015_Text[18223]["Text4312"] = "~a Justice Scroll or other gifts. So, are you sure you want to exchange 30000 Fan Points for this pack?"
	tHuakui2015_Text[18223]["Text4313"] = ""
	tHuakui2015_Text[18223]["Option90"] = "Yes."

	tHuakui2015_Text[18223]["Text4411"] = "The donate items for Ms. Conquer contains Lily, Orchid, Rose and Tulip. If you happen to have"
	tHuakui2015_Text[18223]["Text4412"] = "~some donate items for Mr. Conquer, you can swap them for the items above for Ms. Conquer with me."
	tHuakui2015_Text[18223]["Text4413"] = "~For example, swap Beer for Lily, Kiss for Rose, and Jade for Tulip. How many pieces of donate items do you want to swap for?"
	tHuakui2015_Text[18223]["Option91"] = "1~piece."
	tHuakui2015_Text[18223]["Option92"] = "3~pieces."
	tHuakui2015_Text[18223]["Option93"] = "9~pieces."
	tHuakui2015_Text[18223]["Option94"] = "99~pieces."
	tHuakui2015_Text[18223]["Option95"] = "999~pieces."

	tHuakui2015_Text[18223]["Text4511"] = "What item of %s piece(s) would you like to swap for?"
	tHuakui2015_Text[18223]["Option96"] = "Swap~Beer~for~Lily."
	tHuakui2015_Text[18223]["Option97"] = "Swap~Love~Letter~for~Orchid."
	tHuakui2015_Text[18223]["Option98"] = "Swap~Kiss~for~Rose."
	tHuakui2015_Text[18223]["Option99"] = "Swap~Jade~for~Tulip."

	tHuakui2015_Text[18223]["Text4611"] = "You don`t have the donate item to swap."
	tHuakui2015_Text[18223]["Option100"] = "Alright."
	tHuakui2015_Text[18223]["Text4621"] = "You successfully swapped for %s! Hurry and donate it to your Ms. Conquer!"


	--报名规则和投票规则
	tHuakui2015_Text[18223]["Text4711"] = "The contest is divided into two parts for Mr. Conquer and Ms. Conquer, taking 50 candidates for each part."
	tHuakui2015_Text[18223]["Text4712"] = "~I`m the hostess of Ms. Conquer. To sign up or vote for Ms. Conquer, you should reach at least Level 100."
	tHuakui2015_Text[18223]["Text4713"] = "~For ladies, you can submit 99 Tulips, or pay 299 CPs, or 30000000 Silver, or 42 Dark Horse Tokens"
	tHuakui2015_Text[18223]["Text4714"] = "~to sign up for the contest. As I know, the Spring Festival celebration and Valentine`s Day celebration held in Twin City (288,374)"
	tHuakui2015_Text[18223]["Text4715"] = "~give participants up to 6 Dark Horse Tokens in a day. Remember, we only accept 10 candidates who sign up with the tokens. So, be quick!"
	tHuakui2015_Text[18223]["Option101"]="What~else?"
	tHuakui2015_Text[18223]["Option102"]="I~see."

	tHuakui2015_Text[18223]["Text4811"] = "For fans, you can donate items to support your `Mr. Conquer` or `Ms. Conquer`. When you increase his/her score,"
	tHuakui2015_Text[18223]["Text4812"] = "~you`ll also receive a certain amount of Fan Points. The donate items for Ms. Conquer include Lily, Rose, Orchid and Tulip."
	tHuakui2015_Text[18223]["Text4813"] = "~Different items give different amount of points. If you have some donate items for Mr. Conquer, you can talk to me to exchange"
	tHuakui2015_Text[18223]["Text4814"] = "~them for the items for Ms. Conquer."
	tHuakui2015_Text[18223]["Option103"]="Anything~else?"
	tHuakui2015_Text[18223]["Option104"]="Learn~about~other~things."
	
	tHuakui2015_Text[18223]["Text4911"] = "When your Fan Points reach 2000, 10000, or 30000 (accumulated from Mr. Conquer and Ms. Conquer),"
	tHuakui2015_Text[18223]["Text4912"] = "~you can exchange them for corresponding fan`s pack. The top 3 ladies of Ms. Conquer are able to"
	tHuakui2015_Text[18223]["Text4913"] = "~claim their prizes on the event page on and after March 1st. By the way, you can check the candidates` score"
	tHuakui2015_Text[18223]["Text4914"] = "~and your Fan score at me."
	tHuakui2015_Text[18223]["Option105"]="Learn~about~other~things."

	tHuakui2015_Text[18223]["Text5011"] = "Ms. Conquer contest has ended, and the top 3 ladies have come out. If you`re one of the winners, go claim"
	tHuakui2015_Text[18223]["Text5012"] = "~your prize on the event page. For supporters, we`ve prepared wonderful fans` packs. Don`t forget to claim your rewards!"
	tHuakui2015_Text[18223]["Text5013"] = ""
	tHuakui2015_Text[18223]["Option106"]="Great!"
	
	

	
	


--------------------------------------逻辑部分-----------------------------------------
-- 男神报名
-- 报名条件
function Huakui2015_RegistConditions(nNpcId)
	-- 判断活动时间（待定）
	if not Sys_ChkFullTime(tHuakui2015_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end

	--判断玩家性别
	local nSex = Get_UserSex()
	
	if not (nSex == tHuakui2015_Cont["RegistSex"][nNpcId] ) then
		LinkNpcGossipFunc_New(nNpcId,"2-4")
		return
	end
	
	-- 判断玩家等级
	if not User_JudgeLevelAndMetempsychosis(tHuakui2015_Cont["Level"],tHuakui2015_Cont["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end

	local nEvent = tHuakui2015_Cont["StcEventRegist"]
	local nType = tHuakui2015_Cont["StcTypeRegist"]
    local nRegistNo = Get_UserStatisticValue(tHuakui2015_Cont["StcEventRegist"],tHuakui2015_Cont["StcTypeRegist"])

	-- 是否报名
	if not Task_ChkStcValue(nEvent,nType,"==",0) then
		tNpcGossip[nNpcId]["Text231"] = string.format(tHuakui2015_Text[nNpcId]["Text231"],nRegistNo)
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end

	--判断报名上限
	local nSex = Get_UserSex()
	local nCount = 0
	if ( nSex == 1 ) then
		nCount = Get_SysDynaGlobalData0(tHuakui2015_DynaGlobalData["Count"])
	else
		nCount = Get_SysDynaGlobalData3(tHuakui2015_DynaGlobalData["Count"])
	end

	if (nCount >= tHuakui2015_Cont["RegistCount"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end

	--条件满足，进入下一级选项
	LinkNpcGossipFunc_New(nNpcId,"2-5")
end

-- 金币报名
function Huakui2015_MaleRegistMoney(nNpcId)
	local nMoney = Get_UserMoney()

	--判断金钱数
	if not (nMoney >= tHuakui2015_Cont["RegistMoney"]) then
		LinkNpcGossipFunc_New(nNpcId,"5-2")
		return
	end
	if Huakui2015_MaleRegistCount1(nNpcId) then
		return
	end
	
	User_AddMoney(-tHuakui2015_Cont["RegistMoney"])
	Huakui2015_MaleRegistSuccess1(nNpcId)
	Sys_SaveActionFestivalLog(tHuakui2015_Log["Regist"]["Money"])
end

-- 天石报名
function Huakui2015_MaleRegistEmoney(nNpcId)
	local nEmoney = Get_UserEMoney()

	--判断天石数
	if not (nEmoney >= tHuakui2015_Cont["RegistEmoney"]) then
		LinkNpcGossipFunc_New(nNpcId,"4-2")
		return
	end

	if Huakui2015_MaleRegistCount1(nNpcId) then
		return
	end	
	User_AddEMoney(-tHuakui2015_Cont["RegistEmoney"])
	Huakui2015_MaleRegistSuccess1(nNpcId)
	Sys_SaveActionFestivalLog(tHuakui2015_Log["Regist"]["Emoney"])
end

-- Tulip报名
function Huakui2015_MaleRegistItem1(nNpcId)
	--判断物品数量
	if not Item_ChkItem(tHuakui2015_Cont["RegistItem1"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end

	if Huakui2015_MaleRegistCount1(nNpcId) then
		return
	end
	
	if Item_DelItem(tHuakui2015_Cont["RegistItem1"]) then
		Huakui2015_MaleRegistSuccess1(nNpcId)
		Sys_SaveActionFestivalLog(tHuakui2015_Log["Regist"]["RegistItem1"])
	end
end

--令牌报名
function Huakui2015_MaleRegistItem2(nNpcId)
	--判断物品数量
	if not Item_ChkMulItem(tHuakui2015_Cont["RegistItem2"],tHuakui2015_Cont["RegistItem2"],tHuakui2015_Cont["RegistItem2Num"]) then
		LinkNpcGossipFunc_New(nNpcId,"6-2")
		return
	end

	if Huakui2015_MaleRegistCount2(nNpcId) then
		return
	end
	
	Item_DelMulItem(tHuakui2015_Cont["RegistItem2"],tHuakui2015_Cont["RegistItem2"],tHuakui2015_Cont["RegistItem2Num"])
	Huakui2015_MaleRegistSuccess2(nNpcId)
	Sys_SaveActionFestivalLog(tHuakui2015_Log["Regist"]["RegistItem2"])
end


--判断报名上限
function Huakui2015_MaleRegistCount1(nNpcId)
	local nSex = Get_UserSex()
	local nCount = 0
	if ( nSex == 1 ) then
		nCount = Get_SysDynaGlobalData1(tHuakui2015_DynaGlobalData["Count"])
	else
		nCount = Get_SysDynaGlobalData4(tHuakui2015_DynaGlobalData["Count"])
	end

	if (nCount >= tHuakui2015_Cont["RegistCount1"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-4")
		return true
	end
end

function Huakui2015_MaleRegistCount2(nNpcId)
	local nSex = Get_UserSex()
	local nCount = 0
	if ( nSex == 1 ) then
		nCount = Get_SysDynaGlobalData2(tHuakui2015_DynaGlobalData["Count"])
	else
		nCount = Get_SysDynaGlobalData5(tHuakui2015_DynaGlobalData["Count"])
	end
	
	if (nCount >= tHuakui2015_Cont["RegistCount2"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-5")
		return true
	end
end

-- 报名成功
function Huakui2015_MaleRegistSuccess1(nNpcId)
	local nUserId = Get_UserId()
	local sUserName = Get_UserName()
	local nSex = Get_UserSex()
	if ( nSex == 1 ) then
		local nCount = Get_SysDynaGlobalData0(tHuakui2015_DynaGlobalData["Count"])
		local nCount1 = Get_SysDynaGlobalData1(tHuakui2015_DynaGlobalData["Count"])
		
		nCount=nCount+1
		nCount1=nCount1+1
		Sys_SetSynaGlobalData0(tHuakui2015_DynaGlobalData["Count"],nCount)
		Sys_SetSynaGlobalData1(tHuakui2015_DynaGlobalData["Count"],nCount1)
		Sys_SetSynaGlobalData1(tHuakui2015_DynaGlobalData["Regist"][nCount],nUserId)
		Sys_SetSynaGlobalDataStr0(tHuakui2015_DynaGlobalData["Regist"][nCount],sUserName)
		Task_SetStatistic(tHuakui2015_Cont["StcEventRegist"],tHuakui2015_Cont["StcTypeRegist"],nCount,1)
		tNpcGossip[nNpcId]["Text331"] = string.format(tHuakui2015_Text[nNpcId]["Text331"],nCount) 
		LinkNpcGossipFunc_New(nNpcId,"3-3")

	else
		local nCount = Get_SysDynaGlobalData3(tHuakui2015_DynaGlobalData["Count"])
		local nCount1 = Get_SysDynaGlobalData4(tHuakui2015_DynaGlobalData["Count"])
		nCount=nCount+1
		nCount1=nCount1+1
		Sys_SetSynaGlobalData3(tHuakui2015_DynaGlobalData["Count"],nCount)
		Sys_SetSynaGlobalData4(tHuakui2015_DynaGlobalData["Count"],nCount1)
		Sys_SetSynaGlobalData4(tHuakui2015_DynaGlobalData["Regist"][nCount],nUserId)
		Sys_SetSynaGlobalDataStr1(tHuakui2015_DynaGlobalData["Regist"][nCount],sUserName)
		Task_SetStatistic(tHuakui2015_Cont["StcEventRegist"],tHuakui2015_Cont["StcTypeRegist"],nCount,1)
		tNpcGossip[nNpcId]["Text331"] = string.format(tHuakui2015_Text[nNpcId]["Text331"],nCount) 
		LinkNpcGossipFunc_New(nNpcId,"3-3")

	end
	
end

function Huakui2015_MaleRegistSuccess2(nNpcId)
	local nUserId = Get_UserId()
	local sUserName = Get_UserName()
	local nSex = Get_UserSex()
	local nCount = 0
	local nCount2 = 0

	if (nSex == 1 ) then
		nCount = Get_SysDynaGlobalData0(tHuakui2015_DynaGlobalData["Count"])
		nCount2 = Get_SysDynaGlobalData2(tHuakui2015_DynaGlobalData["Count"])
		nCount=nCount+1
		nCount2=nCount2+1
		Sys_SetSynaGlobalData0(tHuakui2015_DynaGlobalData["Count"],nCount)
		Sys_SetSynaGlobalData2(tHuakui2015_DynaGlobalData["Count"],nCount2)
		Sys_SetSynaGlobalData1(tHuakui2015_DynaGlobalData["Regist"][nCount],nUserId)
		Sys_SetSynaGlobalDataStr0(tHuakui2015_DynaGlobalData["Regist"][nCount],sUserName)

	else
		nCount = Get_SysDynaGlobalData3(tHuakui2015_DynaGlobalData["Count"])
		nCount2 = Get_SysDynaGlobalData5(tHuakui2015_DynaGlobalData["Count"])
		nCount=nCount+1
		nCount2=nCount2+1
		Sys_SetSynaGlobalData3(tHuakui2015_DynaGlobalData["Count"],nCount)
		Sys_SetSynaGlobalData5(tHuakui2015_DynaGlobalData["Count"],nCount2)
		Sys_SetSynaGlobalData4(tHuakui2015_DynaGlobalData["Regist"][nCount],nUserId)
		Sys_SetSynaGlobalDataStr1(tHuakui2015_DynaGlobalData["Regist"][nCount],sUserName)
	end
	
	Task_SetStatistic(tHuakui2015_Cont["StcEventRegist"],tHuakui2015_Cont["StcTypeRegist"],nCount,1)
	tNpcGossip[nNpcId]["Text331"] = string.format(tHuakui2015_Text[nNpcId]["Text331"],nCount) 
	LinkNpcGossipFunc_New(nNpcId,"3-3")
end

function Huakui2015_OpenWebSite(nNpcId)
	User_SendWebPage(tHuakui2015_Cont["WebSite"])
end

--上交条件
function Huakui2015_HandInConditions(nNpcId)
	-- 判断活动时间（待定）
	if not Sys_ChkFullTime(tHuakui2015_Cont["ActivityTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	-- 判断玩家等级
	if not User_JudgeLevelAndMetempsychosis(tHuakui2015_Cont["Level"],tHuakui2015_Cont["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"7-2")
		return
	end
	
	--条件满足，进入下一级选项
	LinkNpcGossipFunc_New(nNpcId,"7-1")
end
----------------------------------------------------------jiangwen
function Huakui2015_HandInType(nNpcId,nNum)
	local nEvent = tHuakui2015_Cont["StcEventItemNum"]
	local nEventType = tHuakui2015_Cont["StcTypeItemNum"]
	Task_SetStatistic(nEvent,nEventType,nNum,1)
	tNpcGossip[nNpcId]["Text811"] = string.format(tHuakui2015_Text[nNpcId]["Text811"],nNum,tHuakui2015_Cont["TextFormatNum"][nNum][1])
	tNpcGossip[nNpcId]["Text812"] = string.format(tHuakui2015_Text[nNpcId]["Text812"],tHuakui2015_Cont["TextFormatNum"][nNum][1],nNum,tHuakui2015_Cont["TextFormatNum"][nNum][2])
	tNpcGossip[nNpcId]["Text813"] = string.format(tHuakui2015_Text[nNpcId]["Text813"],tHuakui2015_Cont["TextFormatNum"][nNum][2],nNum)
	LinkNpcGossipFunc_New(nNpcId,"8-1")
end

function Huakui2015_HandIn(nNpcId,nType)
	local nNumEvent = tHuakui2015_Cont["StcEventItemNum"]
	local nNumEventType = tHuakui2015_Cont["StcTypeItemNum"]
	local nTypeEvent = tHuakui2015_Cont["StcEventItemType"]
	local nTypeEventType = tHuakui2015_Cont["StcTypeItemType"]
	local nNum = Get_UserStatisticValue(nNumEvent,nNumEventType)
	Task_SetStatistic(nTypeEvent,nTypeEventType,nType,1)
	
	Sys_DialogText(string.format(tHuakui2015_Text[nNpcId]["Text1311"],nNum,tHuakui2015_Cont["TextFormatType"][nNpcId][nType]))
	Sys_DialogText(tHuakui2015_Text[nNpcId]["Text1312"])
	Sys_DialogOptEdit(tHuakui2015_Text[nNpcId]["Option54"],tHuakui2015_Cont["AcceptLen"],"Huakui2015_HandInTypeIn</N>"..nNpcId)
	Sys_DialogFace()
	Sys_DialogEnd()
end

function Huakui2015_HandInTypeIn(nNpcId)
	local nRegistNo = tonumber(Get_SysAcceptStr())
	local nEvent = tHuakui2015_Cont["StcEventHandInNum"]
	local nType = tHuakui2015_Cont["StcTypeHandInNum"]
	if not Huakui2015_CheckRegistNo(nRegistNo,nNpcId) then
		return
	end
	
	Task_SetStatistic(nEvent,nType,nRegistNo,1)

	local sName = ""
	if ( nNpcId == 18222 )  then
		sName = Get_SysDynaGlobalDataStr0(tHuakui2015_DynaGlobalData["Regist"][nRegistNo])
	else
		sName = Get_SysDynaGlobalDataStr1(tHuakui2015_DynaGlobalData["Regist"][nRegistNo])
	end

	tNpcGossip[nNpcId]["Text1431"] = string.format(tHuakui2015_Text[nNpcId]["Text1431"],nRegistNo,sName) 
	LinkNpcGossipFunc_New(nNpcId,"14-3")
end

function Huakui2015_HandInConfirm(nNpcId)
	local nNumEvent = tHuakui2015_Cont["StcEventItemNum"]
	local nNumEventType = tHuakui2015_Cont["StcTypeItemNum"]
	local nTypeEvent = tHuakui2015_Cont["StcEventItemType"]
	local nTypeEventType = tHuakui2015_Cont["StcTypeItemType"]
	local nRegistNoEvent = tHuakui2015_Cont["StcEventHandInNum"]
	local nRegistNoType = tHuakui2015_Cont["StcTypeHandInNum"]
	local nNum = Get_UserStatisticValue(nNumEvent,nNumEventType)
	local nType = Get_UserStatisticValue(nTypeEvent,nTypeEventType)
	local nRegistNo = Get_UserStatisticValue(nRegistNoEvent,nRegistNoType)
	
	local nHandinItem = tHuakui2015_Cont["ItemAndPoint"][nNpcId][nType][nNum][1]

	if not Item_ChkItem(nHandinItem,1) then
		LinkNpcGossipFunc_New(nNpcId,"14-2")
		return
	end
	
	if Item_DelItem(nHandinItem,1) then
		local nPoint = tHuakui2015_Cont["ItemAndPoint"][nNpcId][nType][nNum][2]
		Huakui2015_HandInSuccess(nRegistNo,nPoint,nNum,nType,nNpcId)
		Sys_SaveActionFestivalLog(string.format(tHuakui2015_Log["HandIn"],nHandinItem))
	end
end

function Huakui2015_HandInSuccess(nRegistNo,nPoint,nNum,nType,nNpcId)
	local nSumPoint = 0
	if ( nNpcId == 18222 ) then
		nSumPoint = Get_SysDynaGlobalData2(tHuakui2015_DynaGlobalData["Regist"][nRegistNo])
		nSumPoint = nSumPoint+nPoint
		Sys_SetSynaGlobalData2(tHuakui2015_DynaGlobalData["Regist"][nRegistNo],nSumPoint)

	else
		nSumPoint = Get_SysDynaGlobalData5(tHuakui2015_DynaGlobalData["Regist"][nRegistNo])
		nSumPoint = nSumPoint+nPoint
		Sys_SetSynaGlobalData5(tHuakui2015_DynaGlobalData["Regist"][nRegistNo],nSumPoint)
	end

	local nFlowerPoint = 0
	if (nType == 1) then
		nFlowerPoint = Get_SysDynaGlobalData0(tHuakui2015_DynaGlobalData["Flower"][nNpcId][nRegistNo])
		nFlowerPoint = nFlowerPoint+nNum
		Sys_SetSynaGlobalData0(tHuakui2015_DynaGlobalData["Flower"][nNpcId][nRegistNo],nFlowerPoint)
	elseif (nType == 2) then
		nFlowerPoint = Get_SysDynaGlobalData1(tHuakui2015_DynaGlobalData["Flower"][nNpcId][nRegistNo])
		nFlowerPoint = nFlowerPoint+nNum
		Sys_SetSynaGlobalData1(tHuakui2015_DynaGlobalData["Flower"][nNpcId][nRegistNo],nFlowerPoint)
	elseif (nType == 3) then
		nFlowerPoint = Get_SysDynaGlobalData2(tHuakui2015_DynaGlobalData["Flower"][nNpcId][nRegistNo])
		nFlowerPoint = nFlowerPoint+nNum
		Sys_SetSynaGlobalData2(tHuakui2015_DynaGlobalData["Flower"][nNpcId][nRegistNo],nFlowerPoint)
	elseif (nType == 4) then
		nFlowerPoint = Get_SysDynaGlobalData3(tHuakui2015_DynaGlobalData["Flower"][nNpcId][nRegistNo])
		nFlowerPoint = nFlowerPoint+nNum
		Sys_SetSynaGlobalData3(tHuakui2015_DynaGlobalData["Flower"][nNpcId][nRegistNo],nFlowerPoint)
	end


	local nFanPoint = Get_UserStatisticValue(tHuakui2015_Cont["StcEventPoint"],tHuakui2015_Cont["StcTypePoint"])
	nFanPoint = nFanPoint+nPoint
	Task_SetStatistic(tHuakui2015_Cont["StcEventPoint"],tHuakui2015_Cont["StcTypePoint"],nFanPoint,1)
	local sName = ""
	if ( nNpcId == 18222 )  then
		sName = Get_SysDynaGlobalDataStr0(tHuakui2015_DynaGlobalData["Regist"][nRegistNo])
	else
		sName = Get_SysDynaGlobalDataStr1(tHuakui2015_DynaGlobalData["Regist"][nRegistNo])
	end
	tNpcGossip[nNpcId]["Text1441"] = string.format(tHuakui2015_Text[nNpcId]["Text1441"],nRegistNo,sName) 
	tNpcGossip[nNpcId]["Text1442"] = string.format(tHuakui2015_Text[nNpcId]["Text1442"],nSumPoint,nFanPoint) 
	LinkNpcGossipFunc_New(nNpcId,"14-4")
end
-----------------------------------534523432423

function Huakui2015_CheckRegistNo(nRegistNo,nNpcId)
	local nCount = 0
	if (nNpcId == 18222) then
		nCount = Get_SysDynaGlobalData0(tHuakui2015_DynaGlobalData["Count"])
	else
		nCount = Get_SysDynaGlobalData3(tHuakui2015_DynaGlobalData["Count"])
	end
	
	local nSelfRegistNo = Get_UserStatisticValue(tHuakui2015_Cont["StcEventRegist"],tHuakui2015_Cont["StcTypeRegist"])
	if not ((nRegistNo > 0) and (nRegistNo <= nCount)) then
		LinkNpcGossipFunc_New(nNpcId,"14-1")
		return false
	end
	
	if (nRegistNo == nSelfRegistNo) then
		LinkNpcGossipFunc_New(nNpcId,"14-5")
		return false
	end
	
	return true
end


---查询积分
function Huakui2015_FanPoint(nNpcId)
	local nFanPoint = Get_UserStatisticValue(tHuakui2015_Cont["StcEventPoint"],tHuakui2015_Cont["StcTypePoint"])
	
	if (nFanPoint == 0) then
		LinkNpcGossipFunc_New(nNpcId,"37-1")
	else
		tNpcGossip[nNpcId]["Text3721"] = string.format(tHuakui2015_Text[nNpcId]["Text3721"],nFanPoint) 
		LinkNpcGossipFunc_New(nNpcId,"37-2")
	end
end

--积分兑换
function Huakui2015_Award02000(nNpcId)
	local nAwardPoint = tHuakui2015_Cont["Award02000Point"]
	local nFanPoint = Get_UserStatisticValue(tHuakui2015_Cont["StcEventPoint"],tHuakui2015_Cont["StcTypePoint"])
	if (nFanPoint < nAwardPoint) then
		tNpcGossip[nNpcId]["Text3911"] = string.format(tHuakui2015_Text[nNpcId]["Text3911"],nAwardPoint) 
		LinkNpcGossipFunc_New(nNpcId,"39-1")
		return
	end
	LinkNpcGossipFunc_New(nNpcId,"40-1")
end

function Huakui2015_Award02000Confirm(nNpcId)
	local nAwardPoint = tHuakui2015_Cont["Award02000Point"]
	local nAwardGift = tHuakui2015_Cont["Award02000Gift"]
	Huakui2015_Award(nAwardPoint,nAwardGift,nNpcId)
	Sys_SaveActionFestivalLog(tHuakui2015_Log["Award02000"])
end

function Huakui2015_Award10000(nNpcId)
	local nAwardPoint = tHuakui2015_Cont["Award10000Point"]
	local nFanPoint = Get_UserStatisticValue(tHuakui2015_Cont["StcEventPoint"],tHuakui2015_Cont["StcTypePoint"])
	if (nFanPoint < nAwardPoint) then
		tNpcGossip[nNpcId]["Text3911"] = string.format(tHuakui2015_Text[nNpcId]["Text3911"],nAwardPoint) 
		LinkNpcGossipFunc_New(nNpcId,"39-1")
		return
	end

	LinkNpcGossipFunc_New(nNpcId,"42-1")
end

function Huakui2015_Award10000Confirm(nNpcId)
	local nAwardPoint = tHuakui2015_Cont["Award10000Point"]
	local nAwardGift = tHuakui2015_Cont["Award10000Gift"]
	Huakui2015_Award(nAwardPoint,nAwardGift,nNpcId)
	Sys_SaveActionFestivalLog(tHuakui2015_Log["Award10000"])
end

function Huakui2015_Award30000(nNpcId)
	local nAwardPoint = tHuakui2015_Cont["Award30000Point"]
	local nFanPoint = Get_UserStatisticValue(tHuakui2015_Cont["StcEventPoint"],tHuakui2015_Cont["StcTypePoint"])
	if (nFanPoint < nAwardPoint) then
		tNpcGossip[nNpcId]["Text3911"] = string.format(tHuakui2015_Text[nNpcId]["Text3911"],nAwardPoint) 
		LinkNpcGossipFunc_New(nNpcId,"39-1")
		return
	end
	LinkNpcGossipFunc_New(nNpcId,"43-1")
end

function Huakui2015_Award30000Confirm(nNpcId)
	local nAwardPoint = tHuakui2015_Cont["Award30000Point"]
	local nAwardGift = tHuakui2015_Cont["Award30000Gift"]
	Huakui2015_Award(nAwardPoint,nAwardGift,nNpcId)
	Sys_SaveActionFestivalLog(tHuakui2015_Log["Award30000"])
end



function Huakui2015_Award(nAwardPoint,nAwardGift,nNpcId)
	local nFanPoint = Get_UserStatisticValue(tHuakui2015_Cont["StcEventPoint"],tHuakui2015_Cont["StcTypePoint"])
	if (nFanPoint < nAwardPoint) then
		tNpcGossip[nNpcId]["Text3911"] = string.format(tHuakui2015_Text[nNpcId]["Text3911"],nAwardPoint) 
		LinkNpcGossipFunc_New(nNpcId,"39-1")
		return
	end
	
	if not User_CheckLeftSpace(1) then
		LinkNpcGossipFunc_New(nNpcId,"41-2")
		return
	end
	
	local nFanPoint = Get_UserStatisticValue(tHuakui2015_Cont["StcEventPoint"],tHuakui2015_Cont["StcTypePoint"])
	local sGiftName = Get_ItemtypeName(nAwardGift)
	nFanPoint = nFanPoint-nAwardPoint
	Task_SetStatistic(tHuakui2015_Cont["StcEventPoint"],tHuakui2015_Cont["StcTypePoint"],nFanPoint,1)
	Item_AddItem(nAwardGift)
	tNpcGossip[nNpcId]["Text4111"] = string.format(tHuakui2015_Text[nNpcId]["Text4111"],sGiftName) 
	LinkNpcGossipFunc_New(nNpcId,"41-1")
end

function Huakui2015_ChangeCheck(nNpcId)
	if not User_JudgeLevelAndMetempsychosis(tHuakui2015_Cont["Level"],tHuakui2015_Cont["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	LinkNpcGossipFunc_New(nNpcId,"44-1")
end

function Huakui2015_ChangeType(nNpcId,nNum)
	local nEvent = tHuakui2015_Cont["StcEventItemNum"]
	local nEventType = tHuakui2015_Cont["StcTypeItemNum"]
	
	Task_SetStatistic(nEvent,nEventType,nNum,1)
	tNpcGossip[nNpcId]["Text4511"] = string.format(tHuakui2015_Text[nNpcId]["Text4511"],nNum)
	LinkNpcGossipFunc_New(nNpcId,"45-1")
end



function Huakui2015_Change(nNpcId,nType)
	local nEvent = tHuakui2015_Cont["StcEventItemNum"]
	local nEventType = tHuakui2015_Cont["StcTypeItemNum"]
	local nNum = Get_UserStatisticValue(nEvent,nEventType)
	local nItem
	local nChangeItem
	
	if (nNpcId == 18222) then
		nItem = tHuakui2015_Cont["Change"][nType][nNum][2]
		nChangeItem = tHuakui2015_Cont["Change"][nType][nNum][1]
	else
		nChangeItem = tHuakui2015_Cont["Change"][nType][nNum][2]
		nItem = tHuakui2015_Cont["Change"][nType][nNum][1]
	end

	local sItemName = Get_ItemtypeName(nItem)
	local sChangeItemName = Get_ItemtypeName(nChangeItem)
	if not Item_ChkItem(nChangeItem) then
		LinkNpcGossipFunc_New(nNpcId,"46-1")
		return
	end
	if Item_DelItem(nChangeItem) then
		Item_AddItem(nItem)
		tNpcGossip[nNpcId]["Text4621"] = string.format(tHuakui2015_Text[nNpcId]["Text4621"],sItemName)
		LinkNpcGossipFunc_New(nNpcId,"46-2")

		Sys_SaveActionFestivalLog(string.format(tHuakui2015_Log["Huakui2015_Change"],nChangeItem,nItem))
	end
end



--------------------------------------------------------------------------



--------------------------------------NPC模块-------------------------------------------
-- NPC头像
tNpcFace[3563] = 7
tNpcFace[3564] = 123

-- 男神报名
tNpcGossip[18222] = tNpcGossip[18222] or DefaultNpc:new{}
tNpcGossip[18222]["OptionHidden"] = 1
tNpcGossip[18223] = tNpcGossip[18223] or DefaultNpc:new{}
tNpcGossip[18223]["OptionHidden"] = 1

-- 活动前对白
tNpcGossip[18222]["Text1-1"] = {111,112,113}
tNpcGossip[18222]["Text111"] = tHuakui2015_Text[18222]["Text111"]
tNpcGossip[18222]["Text112"] = tHuakui2015_Text[18222]["Text112"]
tNpcGossip[18222]["Text113"] = tHuakui2015_Text[18222]["Text113"]
tNpcGossip[18222]["tOption1-1"] = {1}
tNpcGossip[18222]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tHuakui2015_Cont["BeforeActivityTime"])
end

tNpcGossip[18222]["Option1"] = tHuakui2015_Text[18222]["Option1"]

-- 活动中对白
tNpcGossip[18222]["Text1-2"] = {121,122,123,124}
tNpcGossip[18222]["Text121"] = tHuakui2015_Text[18222]["Text121"]
tNpcGossip[18222]["Text122"] = tHuakui2015_Text[18222]["Text122"]
tNpcGossip[18222]["Text123"] = tHuakui2015_Text[18222]["Text123"]
tNpcGossip[18222]["Text124"] = tHuakui2015_Text[18222]["Text124"]
tNpcGossip[18222]["tOption1-2"] = {2,3,4,5,6,8,9}
tNpcGossip[18222]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tHuakui2015_Cont["ActivityTime"])
end
-- 快让我报名！我要当男神！
tNpcGossip[18222]["Option2"] = tHuakui2015_Text[18222]["Option2"]
tNpcGossip[18222]["OptionFunc2"]="Huakui2015_RegistConditions</N>18222"
-- 查看男神参赛者积分。
tNpcGossip[18222]["Option3"] = tHuakui2015_Text[18222]["Option3"]
tNpcGossip[18222]["OptionFunc3"]="Huakui2015_OpenWebSite</N>18222"
--为我心爱的男神投票点赞。
tNpcGossip[18222]["Option4"] = tHuakui2015_Text[18222]["Option4"]
tNpcGossip[18222]["OptionFunc4"]="Huakui2015_HandInConditions</N>18222"
--查看自身的粉丝爱心积分。
tNpcGossip[18222]["Option5"] = tHuakui2015_Text[18222]["Option5"]
tNpcGossip[18222]["OptionFunc5"]="Huakui2015_FanPoint</N>18222"
--领取粉丝爱心礼包。
tNpcGossip[18222]["Option6"] = tHuakui2015_Text[18222]["Option6"]
tNpcGossip[18222]["OptionPoint6"]="38"
--兑换投票点赞品
tNpcGossip[18222]["Option7"] = tHuakui2015_Text[18222]["Option7"]
tNpcGossip[18222]["OptionFunc7"]="Huakui2015_ChangeCheck</N>18222"

--前往活动页面查看详情。
tNpcGossip[18222]["Option8"] = tHuakui2015_Text[18222]["Option8"]
tNpcGossip[18222]["OptionFunc8"]="Huakui2015_OpenWebSite</N>18222"
--报名规则和投票规则。
tNpcGossip[18222]["Option9"] = tHuakui2015_Text[18222]["Option9"]
tNpcGossip[18222]["OptionPoint9"]="47"


tNpcGossip[18222]["Text2-1"] = {211,212}
tNpcGossip[18222]["Text211"] = tHuakui2015_Text[18222]["Text211"]
tNpcGossip[18222]["Text212"] = tHuakui2015_Text[18222]["Text212"]
tNpcGossip[18222]["tOption2-1"] = {10}

tNpcGossip[18222]["Text2-2"] = {221,222}
tNpcGossip[18222]["Text221"] = tHuakui2015_Text[18222]["Text221"]
tNpcGossip[18222]["Text222"] = tHuakui2015_Text[18222]["Text222"]
tNpcGossip[18222]["tOption2-2"] = {11}

tNpcGossip[18222]["Text2-3"] = {231}
tNpcGossip[18222]["Text231"] = ""
tNpcGossip[18222]["tOption2-3"] = {12}

tNpcGossip[18222]["Text2-4"] = {241,242}
tNpcGossip[18222]["Text241"] = tHuakui2015_Text[18222]["Text241"]
tNpcGossip[18222]["Text242"] = tHuakui2015_Text[18222]["Text242"]
tNpcGossip[18222]["tOption2-4"] = {13}

tNpcGossip[18222]["Text2-5"] = {251,252,253,254}
tNpcGossip[18222]["Text251"] = tHuakui2015_Text[18222]["Text251"]
tNpcGossip[18222]["Text252"] = tHuakui2015_Text[18222]["Text252"]
tNpcGossip[18222]["Text253"] = tHuakui2015_Text[18222]["Text253"]
tNpcGossip[18222]["Text254"] = tHuakui2015_Text[18222]["Text254"]
tNpcGossip[18222]["tOption2-5"] = {14,15,16,17,18}
tNpcGossip[18222]["ChkFunc2-5"] = function ()
	return Sys_ChkFullTime(tHuakui2015_Cont["ActivityTime"])
end

tNpcGossip[18222]["Option14"] = tHuakui2015_Text[18222]["Option14"]
tNpcGossip[18222]["Option15"] = tHuakui2015_Text[18222]["Option15"]
tNpcGossip[18222]["Option16"] = tHuakui2015_Text[18222]["Option16"]
tNpcGossip[18222]["Option17"] = tHuakui2015_Text[18222]["Option17"]
tNpcGossip[18222]["Option18"] = tHuakui2015_Text[18222]["Option18"]
tNpcGossip[18222]["OptionPoint14"]="3"
tNpcGossip[18222]["OptionPoint15"]="4"
tNpcGossip[18222]["OptionPoint16"]="5"
tNpcGossip[18222]["OptionPoint17"]="6"

tNpcGossip[18222]["Text3-1"] = {311}
tNpcGossip[18222]["Text311"] = tHuakui2015_Text[18222]["Text311"]
tNpcGossip[18222]["tOption3-1"] = {19,20}

tNpcGossip[18222]["Option19"] = tHuakui2015_Text[18222]["Option19"]
tNpcGossip[18222]["Option20"] = tHuakui2015_Text[18222]["Option20"]
tNpcGossip[18222]["OptionFunc19"]="Huakui2015_MaleRegistItem1</N>18222"

tNpcGossip[18222]["Text3-2"] = {321,322}
tNpcGossip[18222]["Text321"] = tHuakui2015_Text[18222]["Text321"]
tNpcGossip[18222]["Text322"] = tHuakui2015_Text[18222]["Text322"]
tNpcGossip[18222]["tOption3-2"] = {24}
tNpcGossip[18222]["Option24"] = tHuakui2015_Text[18222]["Option24"]

tNpcGossip[18222]["Text3-3"] = {331,332,333}
tNpcGossip[18222]["Text331"] = tHuakui2015_Text[18222]["Text331"]
tNpcGossip[18222]["Text332"] = tHuakui2015_Text[18222]["Text332"]
tNpcGossip[18222]["Text333"] = tHuakui2015_Text[18222]["Text333"]
tNpcGossip[18222]["tOption3-3"] = {25}
tNpcGossip[18222]["Option25"] = tHuakui2015_Text[18222]["Option25"]
tNpcGossip[18222]["OptionFunc25"]="Huakui2015_OpenWebSite</N>18222"

tNpcGossip[18222]["Text3-4"] = {341,342}
tNpcGossip[18222]["Text341"] = tHuakui2015_Text[18222]["Text341"]
tNpcGossip[18222]["Text342"] = tHuakui2015_Text[18222]["Text342"]
tNpcGossip[18222]["tOption3-4"] = {24}

tNpcGossip[18222]["Text3-5"] = {351,352}
tNpcGossip[18222]["Text351"] = tHuakui2015_Text[18222]["Text351"]
tNpcGossip[18222]["Text352"] = tHuakui2015_Text[18222]["Text352"]
tNpcGossip[18222]["tOption3-5"] = {24}

tNpcGossip[18222]["Text4-1"] = {411}
tNpcGossip[18222]["Text411"] = tHuakui2015_Text[18222]["Text411"]
tNpcGossip[18222]["tOption4-1"] = {21,20}
tNpcGossip[18222]["Option21"] = tHuakui2015_Text[18222]["Option21"]
tNpcGossip[18222]["OptionFunc21"]="Huakui2015_MaleRegistEmoney</N>18222"

tNpcGossip[18222]["Text4-2"] = {421,422}
tNpcGossip[18222]["Text421"] = tHuakui2015_Text[18222]["Text421"]
tNpcGossip[18222]["Text422"] = tHuakui2015_Text[18222]["Text422"]
tNpcGossip[18222]["tOption4-2"] = {24}

tNpcGossip[18222]["Text5-1"] = {511}
tNpcGossip[18222]["Text511"] = tHuakui2015_Text[18222]["Text511"]
tNpcGossip[18222]["tOption5-1"] = {22,20}
tNpcGossip[18222]["Option22"] = tHuakui2015_Text[18222]["Option22"]
tNpcGossip[18222]["OptionFunc22"]="Huakui2015_MaleRegistMoney</N>18222"

tNpcGossip[18222]["Text5-2"] = {521,522}
tNpcGossip[18222]["Text521"] = tHuakui2015_Text[18222]["Text521"]
tNpcGossip[18222]["Text522"] = tHuakui2015_Text[18222]["Text522"]
tNpcGossip[18222]["tOption5-2"] = {24}

tNpcGossip[18222]["Text6-1"] = {611}
tNpcGossip[18222]["Text611"] = tHuakui2015_Text[18222]["Text611"]
tNpcGossip[18222]["tOption6-1"] = {23,20}
tNpcGossip[18222]["Option23"] = tHuakui2015_Text[18222]["Option23"]
tNpcGossip[18222]["OptionFunc23"]="Huakui2015_MaleRegistItem2</N>18222"

tNpcGossip[18222]["Text6-2"] = {621,622}
tNpcGossip[18222]["Text621"] = tHuakui2015_Text[18222]["Text621"]
tNpcGossip[18222]["Text622"] = tHuakui2015_Text[18222]["Text622"]
tNpcGossip[18222]["tOption6-2"] = {24}

tNpcGossip[18222]["Text7-2"] = {721,722}
tNpcGossip[18222]["Text721"] = tHuakui2015_Text[18222]["Text721"]
tNpcGossip[18222]["Text722"] = tHuakui2015_Text[18222]["Text722"]
tNpcGossip[18222]["tOption7-2"] = {26}
tNpcGossip[18222]["Option26"] = tHuakui2015_Text[18222]["Option26"]

tNpcGossip[18222]["Text7-1"] = {711,712,713,714}
tNpcGossip[18222]["Text711"] = tHuakui2015_Text[18222]["Text711"]
tNpcGossip[18222]["Text712"] = tHuakui2015_Text[18222]["Text712"]
tNpcGossip[18222]["Text713"] = tHuakui2015_Text[18222]["Text713"]
tNpcGossip[18222]["Text714"] = tHuakui2015_Text[18222]["Text714"]
tNpcGossip[18222]["tOption7-1"] = {27,28,29,30,31,32}
tNpcGossip[18222]["Option27"] = tHuakui2015_Text[18222]["Option27"]
tNpcGossip[18222]["Option28"] = tHuakui2015_Text[18222]["Option28"]
tNpcGossip[18222]["Option29"] = tHuakui2015_Text[18222]["Option29"]
tNpcGossip[18222]["Option30"] = tHuakui2015_Text[18222]["Option30"]
tNpcGossip[18222]["Option31"] = tHuakui2015_Text[18222]["Option31"]
tNpcGossip[18222]["Option32"] = tHuakui2015_Text[18222]["Option32"]
tNpcGossip[18222]["OptionFunc27"]="Huakui2015_HandInType</N>18222</N>1"
tNpcGossip[18222]["OptionFunc28"]="Huakui2015_HandInType</N>18222</N>3"
tNpcGossip[18222]["OptionFunc29"]="Huakui2015_HandInType</N>18222</N>9"
tNpcGossip[18222]["OptionFunc30"]="Huakui2015_HandInType</N>18222</N>99"
tNpcGossip[18222]["OptionFunc31"]="Huakui2015_HandInType</N>18222</N>999"



tNpcGossip[18222]["Text8-1"] = {811,812,813}
tNpcGossip[18222]["Text811"] = tHuakui2015_Text[18222]["Text811"]
tNpcGossip[18222]["Text812"] = tHuakui2015_Text[18222]["Text812"]
tNpcGossip[18222]["Text813"] = tHuakui2015_Text[18222]["Text813"]
tNpcGossip[18222]["tOption8-1"] = {33,34,35,36,37}
tNpcGossip[18222]["Option33"] = tHuakui2015_Text[18222]["Option33"]
tNpcGossip[18222]["Option34"] = tHuakui2015_Text[18222]["Option34"]
tNpcGossip[18222]["Option35"] = tHuakui2015_Text[18222]["Option35"]
tNpcGossip[18222]["Option36"] = tHuakui2015_Text[18222]["Option36"]
tNpcGossip[18222]["Option37"] = tHuakui2015_Text[18222]["Option37"]
tNpcGossip[18222]["OptionFunc33"]="Huakui2015_HandIn</N>18222</N>1"
tNpcGossip[18222]["OptionFunc34"]="Huakui2015_HandIn</N>18222</N>2"
tNpcGossip[18222]["OptionFunc35"]="Huakui2015_HandIn</N>18222</N>3"
tNpcGossip[18222]["OptionFunc36"]="Huakui2015_HandIn</N>18222</N>4"
tNpcGossip[18222]["OptionPoint37"]="7"


tNpcGossip[18222]["Text14-1"] = {1411}
tNpcGossip[18222]["Text1411"] = tHuakui2015_Text[18222]["Text1411"]
tNpcGossip[18222]["tOption14-1"] = {55}
tNpcGossip[18222]["Option55"] = tHuakui2015_Text[18222]["Option55"]

tNpcGossip[18222]["Text14-2"] = {1421}
tNpcGossip[18222]["Text1421"] = tHuakui2015_Text[18222]["Text1421"]
tNpcGossip[18222]["tOption14-2"] = {56}
tNpcGossip[18222]["Option56"] = tHuakui2015_Text[18222]["Option56"]

tNpcGossip[18222]["Text14-3"] = {1431,1432}
tNpcGossip[18222]["Text1431"] = tHuakui2015_Text[18222]["Text1431"]
tNpcGossip[18222]["tOption14-3"] = {57,58}
tNpcGossip[18222]["Option57"] = tHuakui2015_Text[18222]["Option57"]
tNpcGossip[18222]["Option58"] = tHuakui2015_Text[18222]["Option58"]
tNpcGossip[18222]["OptionFunc57"]="Huakui2015_HandInConfirm</N>18222"

tNpcGossip[18222]["Text14-4"] = {1441,1442}
tNpcGossip[18222]["Text1441"] = tHuakui2015_Text[18222]["Text1441"]
tNpcGossip[18222]["Text1442"] = tHuakui2015_Text[18222]["Text1442"]
tNpcGossip[18222]["tOption14-4"] = {59}
tNpcGossip[18222]["Option59"] = tHuakui2015_Text[18222]["Option59"]

tNpcGossip[18222]["Text14-5"] = {1451}
tNpcGossip[18222]["Text1451"] = tHuakui2015_Text[18222]["Text1451"]
tNpcGossip[18222]["tOption14-5"] = {55}



tNpcGossip[18222]["Text37-1"] = {3711}
tNpcGossip[18222]["Text3711"] = tHuakui2015_Text[18222]["Text3711"]
tNpcGossip[18222]["tOption37-1"] = {79}
tNpcGossip[18222]["Option79"] = tHuakui2015_Text[18222]["Option79"]

tNpcGossip[18222]["Text37-2"] = {3721}
tNpcGossip[18222]["Text3721"] = tHuakui2015_Text[18222]["Text3721"]
tNpcGossip[18222]["tOption37-2"] = {80}
tNpcGossip[18222]["Option80"] = tHuakui2015_Text[18222]["Option80"]

tNpcGossip[18222]["Text38-1"] = {3811,3812,3813}
tNpcGossip[18222]["Text3811"] = tHuakui2015_Text[18222]["Text3811"]
tNpcGossip[18222]["Text3812"] = tHuakui2015_Text[18222]["Text3812"]
tNpcGossip[18222]["Text3813"] = tHuakui2015_Text[18222]["Text3813"]
tNpcGossip[18222]["tOption38-1"] = {81,82,83,84}
tNpcGossip[18222]["Option81"] = tHuakui2015_Text[18222]["Option81"]
tNpcGossip[18222]["Option82"] = tHuakui2015_Text[18222]["Option82"]
tNpcGossip[18222]["Option83"] = tHuakui2015_Text[18222]["Option83"]
tNpcGossip[18222]["Option84"] = tHuakui2015_Text[18222]["Option84"]
tNpcGossip[18222]["OptionFunc81"]="Huakui2015_Award02000</N>18222"
tNpcGossip[18222]["OptionFunc82"]="Huakui2015_Award10000</N>18222"
tNpcGossip[18222]["OptionFunc83"]="Huakui2015_Award30000</N>18222"

tNpcGossip[18222]["Text38-1"] = {3811,3812,3813}
tNpcGossip[18222]["Text3811"] = tHuakui2015_Text[18222]["Text3811"]
tNpcGossip[18222]["Text3812"] = tHuakui2015_Text[18222]["Text3812"]
tNpcGossip[18222]["Text3813"] = tHuakui2015_Text[18222]["Text3813"]
tNpcGossip[18222]["tOption38-1"] = {81,82,83,84}
tNpcGossip[18222]["Option81"] = tHuakui2015_Text[18222]["Option81"]
tNpcGossip[18222]["Option82"] = tHuakui2015_Text[18222]["Option82"]
tNpcGossip[18222]["Option83"] = tHuakui2015_Text[18222]["Option83"]
tNpcGossip[18222]["Option84"] = tHuakui2015_Text[18222]["Option84"]
tNpcGossip[18222]["OptionFunc81"]="Huakui2015_Award02000</N>18222"
tNpcGossip[18222]["OptionFunc82"]="Huakui2015_Award10000</N>18222"
tNpcGossip[18222]["OptionFunc83"]="Huakui2015_Award30000</N>18222"


tNpcGossip[18222]["Text39-1"] = {3911,3912}
tNpcGossip[18222]["Text3911"] = tHuakui2015_Text[18222]["Text3911"]
tNpcGossip[18222]["Text3912"] = tHuakui2015_Text[18222]["Text3912"]
tNpcGossip[18222]["Text3913"] = tHuakui2015_Text[18222]["Text3913"]
tNpcGossip[18222]["tOption39-1"] = {85}
tNpcGossip[18222]["Option85"] = tHuakui2015_Text[18222]["Option85"]

tNpcGossip[18222]["Text40-1"] = {4011,4012,4013}
tNpcGossip[18222]["Text4011"] = tHuakui2015_Text[18222]["Text4011"]
tNpcGossip[18222]["Text4012"] = tHuakui2015_Text[18222]["Text4012"]
tNpcGossip[18222]["Text4013"] = tHuakui2015_Text[18222]["Text4013"]
tNpcGossip[18222]["tOption40-1"] = {86,84}
tNpcGossip[18222]["Option86"] = tHuakui2015_Text[18222]["Option86"]
tNpcGossip[18222]["OptionFunc86"]="Huakui2015_Award02000Confirm</N>18222"


tNpcGossip[18222]["Text41-1"] = {4111}
tNpcGossip[18222]["Text4111"] = tHuakui2015_Text[18222]["Text4111"]
tNpcGossip[18222]["tOption41-1"] = {87}
tNpcGossip[18222]["Option87"] = tHuakui2015_Text[18222]["Option87"]

tNpcGossip[18222]["Text41-2"] = {4121}
tNpcGossip[18222]["Text4121"] = tHuakui2015_Text[18222]["Text4121"]
tNpcGossip[18222]["tOption40-2"] = {87}

tNpcGossip[18222]["Text42-1"] = {4211,4212,4213}
tNpcGossip[18222]["Text4211"] = tHuakui2015_Text[18222]["Text4211"]
tNpcGossip[18222]["Text4212"] = tHuakui2015_Text[18222]["Text4212"]
tNpcGossip[18222]["Text4213"] = tHuakui2015_Text[18222]["Text4213"]
tNpcGossip[18222]["tOption42-1"] = {89,84}
tNpcGossip[18222]["Option89"] = tHuakui2015_Text[18222]["Option89"]
tNpcGossip[18222]["OptionFunc89"]="Huakui2015_Award10000Confirm</N>18222"

tNpcGossip[18222]["Text43-1"] = {4311,4312,4313}
tNpcGossip[18222]["Text4311"] = tHuakui2015_Text[18222]["Text4311"]
tNpcGossip[18222]["Text4312"] = tHuakui2015_Text[18222]["Text4312"]
tNpcGossip[18222]["Text4313"] = tHuakui2015_Text[18222]["Text4313"]
tNpcGossip[18222]["tOption43-1"] = {90,84}
tNpcGossip[18222]["Option90"] = tHuakui2015_Text[18222]["Option90"]
tNpcGossip[18222]["OptionFunc90"]="Huakui2015_Award30000Confirm</N>18222"

tNpcGossip[18222]["Text44-1"] = {4411,4412,4413}
tNpcGossip[18222]["Text4411"] = tHuakui2015_Text[18222]["Text4411"]
tNpcGossip[18222]["Text4412"] = tHuakui2015_Text[18222]["Text4412"]
tNpcGossip[18222]["Text4413"] = tHuakui2015_Text[18222]["Text4413"]
tNpcGossip[18222]["tOption44-1"] = {91,92,93,94,95,84}
tNpcGossip[18222]["Option91"] = tHuakui2015_Text[18222]["Option91"]
tNpcGossip[18222]["Option92"] = tHuakui2015_Text[18222]["Option92"]
tNpcGossip[18222]["Option93"] = tHuakui2015_Text[18222]["Option93"]
tNpcGossip[18222]["Option94"] = tHuakui2015_Text[18222]["Option94"]
tNpcGossip[18222]["Option95"] = tHuakui2015_Text[18222]["Option95"]
tNpcGossip[18222]["OptionFunc91"]="Huakui2015_ChangeType</N>18222</N>1"
tNpcGossip[18222]["OptionFunc92"]="Huakui2015_ChangeType</N>18222</N>3"
tNpcGossip[18222]["OptionFunc93"]="Huakui2015_ChangeType</N>18222</N>9"
tNpcGossip[18222]["OptionFunc94"]="Huakui2015_ChangeType</N>18222</N>99"
tNpcGossip[18222]["OptionFunc95"]="Huakui2015_ChangeType</N>18222</N>999"

tNpcGossip[18222]["Text45-1"] = {4511}
tNpcGossip[18222]["Text4511"] = tHuakui2015_Text[18222]["Text4511"]
tNpcGossip[18222]["tOption45-1"] = {96,97,98,99,84}
tNpcGossip[18222]["Option96"] = tHuakui2015_Text[18222]["Option96"]
tNpcGossip[18222]["Option97"] = tHuakui2015_Text[18222]["Option97"]
tNpcGossip[18222]["Option98"] = tHuakui2015_Text[18222]["Option98"]
tNpcGossip[18222]["Option99"] = tHuakui2015_Text[18222]["Option99"]
tNpcGossip[18222]["OptionFunc96"]="Huakui2015_Change</N>18222</N>1"
tNpcGossip[18222]["OptionFunc97"]="Huakui2015_Change</N>18222</N>2"
tNpcGossip[18222]["OptionFunc98"]="Huakui2015_Change</N>18222</N>3"
tNpcGossip[18222]["OptionFunc99"]="Huakui2015_Change</N>18222</N>4"

tNpcGossip[18222]["Text46-1"] = {4611}
tNpcGossip[18222]["Text4611"] = tHuakui2015_Text[18222]["Text4611"]
tNpcGossip[18222]["tOption46-1"] = {100}

tNpcGossip[18222]["Text46-2"] = {4621}
tNpcGossip[18222]["Text4621"] = tHuakui2015_Text[18222]["Text4621"]
tNpcGossip[18222]["tOption46-2"] = {100}

--报名规则和投票规则
tNpcGossip[18222]["Text47-1"] = {4711,4712,4713,4714,4715}
tNpcGossip[18222]["Text4711"] = tHuakui2015_Text[18222]["Text4711"]
tNpcGossip[18222]["Text4712"] = tHuakui2015_Text[18222]["Text4712"]
tNpcGossip[18222]["Text4713"] = tHuakui2015_Text[18222]["Text4713"]
tNpcGossip[18222]["Text4714"] = tHuakui2015_Text[18222]["Text4714"]
tNpcGossip[18222]["Text4715"] = tHuakui2015_Text[18222]["Text4715"]
tNpcGossip[18222]["tOption47-1"] = {101,102}
tNpcGossip[18222]["Option101"] = tHuakui2015_Text[18222]["Option101"]
tNpcGossip[18222]["Option102"] = tHuakui2015_Text[18222]["Option102"]
tNpcGossip[18222]["OptionPoint101"]="48"

tNpcGossip[18222]["Text48-1"] = {4811,4812,4813,4814}
tNpcGossip[18222]["Text4811"] = tHuakui2015_Text[18222]["Text4811"]
tNpcGossip[18222]["Text4812"] = tHuakui2015_Text[18222]["Text4812"]
tNpcGossip[18222]["Text4813"] = tHuakui2015_Text[18222]["Text4813"]
tNpcGossip[18222]["Text4814"] = tHuakui2015_Text[18222]["Text4814"]
tNpcGossip[18222]["tOption48-1"] = {103,104,102}
tNpcGossip[18222]["Option103"] = tHuakui2015_Text[18222]["Option103"]
tNpcGossip[18222]["Option104"] = tHuakui2015_Text[18222]["Option104"]
tNpcGossip[18222]["OptionPoint103"]="49"
tNpcGossip[18222]["OptionPoint104"]="47"

tNpcGossip[18222]["Text49-1"] = {4911,4912,4913,4914}
tNpcGossip[18222]["Text4911"] = tHuakui2015_Text[18222]["Text4911"]
tNpcGossip[18222]["Text4912"] = tHuakui2015_Text[18222]["Text4912"]
tNpcGossip[18222]["Text4913"] = tHuakui2015_Text[18222]["Text4913"]
tNpcGossip[18222]["Text4914"] = tHuakui2015_Text[18222]["Text4914"]
tNpcGossip[18222]["tOption49-1"] = {105,102}
tNpcGossip[18222]["Option105"] = tHuakui2015_Text[18222]["Option105"]
tNpcGossip[18222]["OptionPoint105"]="48"

-- 活动后对白
tNpcGossip[18222]["Text1-3"] = {131,132,133}
tNpcGossip[18222]["Text131"] = tHuakui2015_Text[18222]["Text131"]
tNpcGossip[18222]["Text132"] = tHuakui2015_Text[18222]["Text132"]
tNpcGossip[18222]["Text133"] = tHuakui2015_Text[18222]["Text133"]
tNpcGossip[18222]["tOption1-3"] = {6,3,5,8,106}
tNpcGossip[18222]["ChkFunc1-3"] = function ()
	return not Sys_ChkFullTime(tHuakui2015_Cont["ActivityTime"])
end

-- 女神报名
-- 活动前对白
tNpcGossip[18223]["Text1-1"] = {111,112,113}
tNpcGossip[18223]["Text111"] = tHuakui2015_Text[18223]["Text111"]
tNpcGossip[18223]["Text112"] = tHuakui2015_Text[18223]["Text112"]
tNpcGossip[18223]["Text113"] = tHuakui2015_Text[18223]["Text113"]
tNpcGossip[18223]["tOption1-1"] = {1}
tNpcGossip[18223]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tHuakui2015_Cont["BeforeActivityTime"])
end

tNpcGossip[18223]["Option1"] = tHuakui2015_Text[18223]["Option1"]

-- 活动中对白
tNpcGossip[18223]["Text1-2"] = {121,122,123,124}
tNpcGossip[18223]["Text121"] = tHuakui2015_Text[18223]["Text121"]
tNpcGossip[18223]["Text122"] = tHuakui2015_Text[18223]["Text122"]
tNpcGossip[18223]["Text123"] = tHuakui2015_Text[18223]["Text123"]
tNpcGossip[18223]["Text124"] = tHuakui2015_Text[18223]["Text124"]
tNpcGossip[18223]["tOption1-2"] = {2,3,4,5,6,8,9}
tNpcGossip[18223]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tHuakui2015_Cont["ActivityTime"])
end
-- 快让我报名！我要当男神！
tNpcGossip[18223]["Option2"] = tHuakui2015_Text[18223]["Option2"]
tNpcGossip[18223]["OptionFunc2"]="Huakui2015_RegistConditions</N>18223"
-- 查看男神参赛者积分。
tNpcGossip[18223]["Option3"] = tHuakui2015_Text[18223]["Option3"]
tNpcGossip[18223]["OptionFunc3"]="Huakui2015_OpenWebSite</N>18223"
--为我心爱的男神投票点赞。
tNpcGossip[18223]["Option4"] = tHuakui2015_Text[18223]["Option4"]
tNpcGossip[18223]["OptionFunc4"]="Huakui2015_HandInConditions</N>18223"
--查看自身的粉丝爱心积分。
tNpcGossip[18223]["Option5"] = tHuakui2015_Text[18223]["Option5"]
tNpcGossip[18223]["OptionFunc5"]="Huakui2015_FanPoint</N>18223"
--领取粉丝爱心礼包。
tNpcGossip[18223]["Option6"] = tHuakui2015_Text[18223]["Option6"]
tNpcGossip[18223]["OptionPoint6"]="38"
--兑换投票点赞品
tNpcGossip[18223]["Option7"] = tHuakui2015_Text[18223]["Option7"]
tNpcGossip[18223]["OptionFunc7"]="Huakui2015_ChangeCheck</N>18223"

--前往活动页面查看详情。
tNpcGossip[18223]["Option8"] = tHuakui2015_Text[18223]["Option8"]
tNpcGossip[18223]["OptionFunc8"]="Huakui2015_OpenWebSite</N>18223"
--报名规则和投票规则。
tNpcGossip[18223]["Option9"] = tHuakui2015_Text[18223]["Option9"]
tNpcGossip[18223]["OptionPoint9"]="47"


tNpcGossip[18223]["Text2-1"] = {211,212}
tNpcGossip[18223]["Text211"] = tHuakui2015_Text[18223]["Text211"]
tNpcGossip[18223]["Text212"] = tHuakui2015_Text[18223]["Text212"]
tNpcGossip[18223]["tOption2-1"] = {10}

tNpcGossip[18223]["Text2-2"] = {221,222}
tNpcGossip[18223]["Text221"] = tHuakui2015_Text[18223]["Text221"]
tNpcGossip[18223]["Text222"] = tHuakui2015_Text[18223]["Text222"]
tNpcGossip[18223]["tOption2-2"] = {11}

tNpcGossip[18223]["Text2-3"] = {231}
tNpcGossip[18223]["Text231"] = ""
tNpcGossip[18223]["tOption2-3"] = {12}

tNpcGossip[18223]["Text2-4"] = {241,242}
tNpcGossip[18223]["Text241"] = tHuakui2015_Text[18223]["Text241"]
tNpcGossip[18223]["Text242"] = tHuakui2015_Text[18223]["Text242"]
tNpcGossip[18223]["tOption2-4"] = {13}

tNpcGossip[18223]["Text2-5"] = {251,252,253,254}
tNpcGossip[18223]["Text251"] = tHuakui2015_Text[18223]["Text251"]
tNpcGossip[18223]["Text252"] = tHuakui2015_Text[18223]["Text252"]
tNpcGossip[18223]["Text253"] = tHuakui2015_Text[18223]["Text253"]
tNpcGossip[18223]["Text254"] = tHuakui2015_Text[18223]["Text254"]
tNpcGossip[18223]["tOption2-5"] = {14,15,16,17,18}
tNpcGossip[18223]["ChkFunc2-5"] = function ()
	return Sys_ChkFullTime(tHuakui2015_Cont["ActivityTime"])
end

tNpcGossip[18223]["Option14"] = tHuakui2015_Text[18223]["Option14"]
tNpcGossip[18223]["Option15"] = tHuakui2015_Text[18223]["Option15"]
tNpcGossip[18223]["Option16"] = tHuakui2015_Text[18223]["Option16"]
tNpcGossip[18223]["Option17"] = tHuakui2015_Text[18223]["Option17"]
tNpcGossip[18223]["Option18"] = tHuakui2015_Text[18223]["Option18"]
tNpcGossip[18223]["OptionPoint14"]="3"
tNpcGossip[18223]["OptionPoint15"]="4"
tNpcGossip[18223]["OptionPoint16"]="5"
tNpcGossip[18223]["OptionPoint17"]="6"

tNpcGossip[18223]["Text3-1"] = {311}
tNpcGossip[18223]["Text311"] = tHuakui2015_Text[18223]["Text311"]
tNpcGossip[18223]["tOption3-1"] = {19,20}

tNpcGossip[18223]["Option19"] = tHuakui2015_Text[18223]["Option19"]
tNpcGossip[18223]["Option20"] = tHuakui2015_Text[18223]["Option20"]
tNpcGossip[18223]["OptionFunc19"]="Huakui2015_MaleRegistItem1</N>18223"

tNpcGossip[18223]["Text3-2"] = {321,322}
tNpcGossip[18223]["Text321"] = tHuakui2015_Text[18223]["Text321"]
tNpcGossip[18223]["Text322"] = tHuakui2015_Text[18223]["Text322"]
tNpcGossip[18223]["tOption3-2"] = {24}
tNpcGossip[18223]["Option24"] = tHuakui2015_Text[18223]["Option24"]

tNpcGossip[18223]["Text3-3"] = {331,332,333}
tNpcGossip[18223]["Text331"] = tHuakui2015_Text[18223]["Text331"]
tNpcGossip[18223]["Text332"] = tHuakui2015_Text[18223]["Text332"]
tNpcGossip[18223]["Text333"] = tHuakui2015_Text[18223]["Text333"]
tNpcGossip[18223]["tOption3-3"] = {25}
tNpcGossip[18223]["Option25"] = tHuakui2015_Text[18223]["Option25"]
tNpcGossip[18223]["OptionFunc25"]="Huakui2015_OpenWebSite</N>18223"

tNpcGossip[18223]["Text3-4"] = {341,342}
tNpcGossip[18223]["Text341"] = tHuakui2015_Text[18223]["Text341"]
tNpcGossip[18223]["Text342"] = tHuakui2015_Text[18223]["Text342"]
tNpcGossip[18223]["tOption3-4"] = {24}

tNpcGossip[18223]["Text3-5"] = {351,352}
tNpcGossip[18223]["Text351"] = tHuakui2015_Text[18223]["Text351"]
tNpcGossip[18223]["Text352"] = tHuakui2015_Text[18223]["Text352"]
tNpcGossip[18223]["tOption3-5"] = {24}

tNpcGossip[18223]["Text4-1"] = {411}
tNpcGossip[18223]["Text411"] = tHuakui2015_Text[18223]["Text411"]
tNpcGossip[18223]["tOption4-1"] = {21,20}
tNpcGossip[18223]["Option21"] = tHuakui2015_Text[18223]["Option21"]
tNpcGossip[18223]["OptionFunc21"]="Huakui2015_MaleRegistEmoney</N>18223"

tNpcGossip[18223]["Text4-2"] = {421,422}
tNpcGossip[18223]["Text421"] = tHuakui2015_Text[18223]["Text421"]
tNpcGossip[18223]["Text422"] = tHuakui2015_Text[18223]["Text422"]
tNpcGossip[18223]["tOption4-2"] = {24}

tNpcGossip[18223]["Text5-1"] = {511}
tNpcGossip[18223]["Text511"] = tHuakui2015_Text[18223]["Text511"]
tNpcGossip[18223]["tOption5-1"] = {22,20}
tNpcGossip[18223]["Option22"] = tHuakui2015_Text[18223]["Option22"]
tNpcGossip[18223]["OptionFunc22"]="Huakui2015_MaleRegistMoney</N>18223"

tNpcGossip[18223]["Text5-2"] = {521,522}
tNpcGossip[18223]["Text521"] = tHuakui2015_Text[18223]["Text521"]
tNpcGossip[18223]["Text522"] = tHuakui2015_Text[18223]["Text522"]
tNpcGossip[18223]["tOption5-2"] = {24}

tNpcGossip[18223]["Text6-1"] = {611}
tNpcGossip[18223]["Text611"] = tHuakui2015_Text[18223]["Text611"]
tNpcGossip[18223]["tOption6-1"] = {23,20}
tNpcGossip[18223]["Option23"] = tHuakui2015_Text[18223]["Option23"]
tNpcGossip[18223]["OptionFunc23"]="Huakui2015_MaleRegistItem2</N>18223"

tNpcGossip[18223]["Text6-2"] = {621,622}
tNpcGossip[18223]["Text621"] = tHuakui2015_Text[18223]["Text621"]
tNpcGossip[18223]["Text622"] = tHuakui2015_Text[18223]["Text622"]
tNpcGossip[18223]["tOption6-2"] = {24}

tNpcGossip[18223]["Text7-2"] = {721,722}
tNpcGossip[18223]["Text721"] = tHuakui2015_Text[18223]["Text721"]
tNpcGossip[18223]["Text722"] = tHuakui2015_Text[18223]["Text722"]
tNpcGossip[18223]["tOption7-2"] = {26}
tNpcGossip[18223]["Option26"] = tHuakui2015_Text[18223]["Option26"]

tNpcGossip[18223]["Text7-1"] = {711,712,713,714}
tNpcGossip[18223]["Text711"] = tHuakui2015_Text[18223]["Text711"]
tNpcGossip[18223]["Text712"] = tHuakui2015_Text[18223]["Text712"]
tNpcGossip[18223]["Text713"] = tHuakui2015_Text[18223]["Text713"]
tNpcGossip[18223]["Text714"] = tHuakui2015_Text[18223]["Text714"]
tNpcGossip[18223]["tOption7-1"] = {27,28,29,30,31,32}
tNpcGossip[18223]["Option27"] = tHuakui2015_Text[18223]["Option27"]
tNpcGossip[18223]["Option28"] = tHuakui2015_Text[18223]["Option28"]
tNpcGossip[18223]["Option29"] = tHuakui2015_Text[18223]["Option29"]
tNpcGossip[18223]["Option30"] = tHuakui2015_Text[18223]["Option30"]
tNpcGossip[18223]["Option31"] = tHuakui2015_Text[18223]["Option31"]
tNpcGossip[18223]["Option32"] = tHuakui2015_Text[18223]["Option32"]
tNpcGossip[18223]["OptionFunc27"]="Huakui2015_HandInType</N>18223</N>1"
tNpcGossip[18223]["OptionFunc28"]="Huakui2015_HandInType</N>18223</N>3"
tNpcGossip[18223]["OptionFunc29"]="Huakui2015_HandInType</N>18223</N>9"
tNpcGossip[18223]["OptionFunc30"]="Huakui2015_HandInType</N>18223</N>99"
tNpcGossip[18223]["OptionFunc31"]="Huakui2015_HandInType</N>18223</N>999"



tNpcGossip[18223]["Text8-1"] = {811,812,813}
tNpcGossip[18223]["Text811"] = tHuakui2015_Text[18223]["Text811"]
tNpcGossip[18223]["Text812"] = tHuakui2015_Text[18223]["Text812"]
tNpcGossip[18223]["Text813"] = tHuakui2015_Text[18223]["Text813"]
tNpcGossip[18223]["tOption8-1"] = {33,34,35,36,37}
tNpcGossip[18223]["Option33"] = tHuakui2015_Text[18223]["Option33"]
tNpcGossip[18223]["Option34"] = tHuakui2015_Text[18223]["Option34"]
tNpcGossip[18223]["Option35"] = tHuakui2015_Text[18223]["Option35"]
tNpcGossip[18223]["Option36"] = tHuakui2015_Text[18223]["Option36"]
tNpcGossip[18223]["Option37"] = tHuakui2015_Text[18223]["Option37"]
tNpcGossip[18223]["OptionFunc33"]="Huakui2015_HandIn</N>18223</N>1"
tNpcGossip[18223]["OptionFunc34"]="Huakui2015_HandIn</N>18223</N>2"
tNpcGossip[18223]["OptionFunc35"]="Huakui2015_HandIn</N>18223</N>3"
tNpcGossip[18223]["OptionFunc36"]="Huakui2015_HandIn</N>18223</N>4"
tNpcGossip[18223]["OptionPoint37"]="7"


tNpcGossip[18223]["Text14-1"] = {1411}
tNpcGossip[18223]["Text1411"] = tHuakui2015_Text[18223]["Text1411"]
tNpcGossip[18223]["tOption14-1"] = {55}
tNpcGossip[18223]["Option55"] = tHuakui2015_Text[18223]["Option55"]

tNpcGossip[18223]["Text14-2"] = {1421}
tNpcGossip[18223]["Text1421"] = tHuakui2015_Text[18223]["Text1421"]
tNpcGossip[18223]["tOption14-2"] = {56}
tNpcGossip[18223]["Option56"] = tHuakui2015_Text[18223]["Option56"]

tNpcGossip[18223]["Text14-3"] = {1431,1432}
tNpcGossip[18223]["Text1431"] = tHuakui2015_Text[18223]["Text1431"]
tNpcGossip[18223]["tOption14-3"] = {57,58}
tNpcGossip[18223]["Option57"] = tHuakui2015_Text[18223]["Option57"]
tNpcGossip[18223]["Option58"] = tHuakui2015_Text[18223]["Option58"]
tNpcGossip[18223]["OptionFunc57"]="Huakui2015_HandInConfirm</N>18223"

tNpcGossip[18223]["Text14-4"] = {1441,1442}
tNpcGossip[18223]["Text1441"] = tHuakui2015_Text[18223]["Text1441"]
tNpcGossip[18223]["Text1442"] = tHuakui2015_Text[18223]["Text1442"]
tNpcGossip[18223]["tOption14-4"] = {59}
tNpcGossip[18223]["Option59"] = tHuakui2015_Text[18223]["Option59"]

tNpcGossip[18223]["Text14-5"] = {1451}
tNpcGossip[18223]["Text1451"] = tHuakui2015_Text[18223]["Text1451"]
tNpcGossip[18223]["tOption14-5"] = {55}



tNpcGossip[18223]["Text37-1"] = {3711}
tNpcGossip[18223]["Text3711"] = tHuakui2015_Text[18223]["Text3711"]
tNpcGossip[18223]["tOption37-1"] = {79}
tNpcGossip[18223]["Option79"] = tHuakui2015_Text[18223]["Option79"]

tNpcGossip[18223]["Text37-2"] = {3721}
tNpcGossip[18223]["Text3721"] = tHuakui2015_Text[18223]["Text3721"]
tNpcGossip[18223]["tOption37-2"] = {80}
tNpcGossip[18223]["Option80"] = tHuakui2015_Text[18223]["Option80"]

tNpcGossip[18223]["Text38-1"] = {3811,3812,3813}
tNpcGossip[18223]["Text3811"] = tHuakui2015_Text[18223]["Text3811"]
tNpcGossip[18223]["Text3812"] = tHuakui2015_Text[18223]["Text3812"]
tNpcGossip[18223]["Text3813"] = tHuakui2015_Text[18223]["Text3813"]
tNpcGossip[18223]["tOption38-1"] = {81,82,83,84}
tNpcGossip[18223]["Option81"] = tHuakui2015_Text[18223]["Option81"]
tNpcGossip[18223]["Option82"] = tHuakui2015_Text[18223]["Option82"]
tNpcGossip[18223]["Option83"] = tHuakui2015_Text[18223]["Option83"]
tNpcGossip[18223]["Option84"] = tHuakui2015_Text[18223]["Option84"]
tNpcGossip[18223]["OptionFunc81"]="Huakui2015_Award02000</N>18223"
tNpcGossip[18223]["OptionFunc82"]="Huakui2015_Award10000</N>18223"
tNpcGossip[18223]["OptionFunc83"]="Huakui2015_Award30000</N>18223"

tNpcGossip[18223]["Text38-1"] = {3811,3812,3813}
tNpcGossip[18223]["Text3811"] = tHuakui2015_Text[18223]["Text3811"]
tNpcGossip[18223]["Text3812"] = tHuakui2015_Text[18223]["Text3812"]
tNpcGossip[18223]["Text3813"] = tHuakui2015_Text[18223]["Text3813"]
tNpcGossip[18223]["tOption38-1"] = {81,82,83,84}
tNpcGossip[18223]["Option81"] = tHuakui2015_Text[18223]["Option81"]
tNpcGossip[18223]["Option82"] = tHuakui2015_Text[18223]["Option82"]
tNpcGossip[18223]["Option83"] = tHuakui2015_Text[18223]["Option83"]
tNpcGossip[18223]["Option84"] = tHuakui2015_Text[18223]["Option84"]
tNpcGossip[18223]["OptionFunc81"]="Huakui2015_Award02000</N>18223"
tNpcGossip[18223]["OptionFunc82"]="Huakui2015_Award10000</N>18223"
tNpcGossip[18223]["OptionFunc83"]="Huakui2015_Award30000</N>18223"


tNpcGossip[18223]["Text39-1"] = {3911,3912}
tNpcGossip[18223]["Text3911"] = tHuakui2015_Text[18223]["Text3911"]
tNpcGossip[18223]["Text3912"] = tHuakui2015_Text[18223]["Text3912"]
tNpcGossip[18223]["Text3913"] = tHuakui2015_Text[18223]["Text3913"]
tNpcGossip[18223]["tOption39-1"] = {85}
tNpcGossip[18223]["Option85"] = tHuakui2015_Text[18223]["Option85"]

tNpcGossip[18223]["Text40-1"] = {4011,4012,4013}
tNpcGossip[18223]["Text4011"] = tHuakui2015_Text[18223]["Text4011"]
tNpcGossip[18223]["Text4012"] = tHuakui2015_Text[18223]["Text4012"]
tNpcGossip[18223]["Text4013"] = tHuakui2015_Text[18223]["Text4013"]
tNpcGossip[18223]["tOption40-1"] = {86,84}
tNpcGossip[18223]["Option86"] = tHuakui2015_Text[18223]["Option86"]
tNpcGossip[18223]["OptionFunc86"]="Huakui2015_Award02000Confirm</N>18223"


tNpcGossip[18223]["Text41-1"] = {4111}
tNpcGossip[18223]["Text4111"] = tHuakui2015_Text[18223]["Text4111"]
tNpcGossip[18223]["tOption41-1"] = {87}
tNpcGossip[18223]["Option87"] = tHuakui2015_Text[18223]["Option87"]

tNpcGossip[18223]["Text41-2"] = {4121}
tNpcGossip[18223]["Text4121"] = tHuakui2015_Text[18223]["Text4121"]
tNpcGossip[18223]["tOption40-2"] = {87}

tNpcGossip[18223]["Text42-1"] = {4211,4212,4213}
tNpcGossip[18223]["Text4211"] = tHuakui2015_Text[18223]["Text4211"]
tNpcGossip[18223]["Text4212"] = tHuakui2015_Text[18223]["Text4212"]
tNpcGossip[18223]["Text4213"] = tHuakui2015_Text[18223]["Text4213"]
tNpcGossip[18223]["tOption42-1"] = {89,84}
tNpcGossip[18223]["Option89"] = tHuakui2015_Text[18223]["Option89"]
tNpcGossip[18223]["OptionFunc89"]="Huakui2015_Award10000Confirm</N>18223"

tNpcGossip[18223]["Text43-1"] = {4311,4312,4313}
tNpcGossip[18223]["Text4311"] = tHuakui2015_Text[18223]["Text4311"]
tNpcGossip[18223]["Text4312"] = tHuakui2015_Text[18223]["Text4312"]
tNpcGossip[18223]["Text4313"] = tHuakui2015_Text[18223]["Text4313"]
tNpcGossip[18223]["tOption43-1"] = {90,84}
tNpcGossip[18223]["Option90"] = tHuakui2015_Text[18223]["Option90"]
tNpcGossip[18223]["OptionFunc90"]="Huakui2015_Award30000Confirm</N>18223"

tNpcGossip[18223]["Text44-1"] = {4411,4412,4413}
tNpcGossip[18223]["Text4411"] = tHuakui2015_Text[18223]["Text4411"]
tNpcGossip[18223]["Text4412"] = tHuakui2015_Text[18223]["Text4412"]
tNpcGossip[18223]["Text4413"] = tHuakui2015_Text[18223]["Text4413"]
tNpcGossip[18223]["tOption44-1"] = {91,92,93,94,95,84}
tNpcGossip[18223]["Option91"] = tHuakui2015_Text[18223]["Option91"]
tNpcGossip[18223]["Option92"] = tHuakui2015_Text[18223]["Option92"]
tNpcGossip[18223]["Option93"] = tHuakui2015_Text[18223]["Option93"]
tNpcGossip[18223]["Option94"] = tHuakui2015_Text[18223]["Option94"]
tNpcGossip[18223]["Option95"] = tHuakui2015_Text[18223]["Option95"]
tNpcGossip[18223]["OptionFunc91"]="Huakui2015_ChangeType</N>18223</N>1"
tNpcGossip[18223]["OptionFunc92"]="Huakui2015_ChangeType</N>18223</N>3"
tNpcGossip[18223]["OptionFunc93"]="Huakui2015_ChangeType</N>18223</N>9"
tNpcGossip[18223]["OptionFunc94"]="Huakui2015_ChangeType</N>18223</N>99"
tNpcGossip[18223]["OptionFunc95"]="Huakui2015_ChangeType</N>18223</N>999"

tNpcGossip[18223]["Text45-1"] = {4511}
tNpcGossip[18223]["Text4511"] = tHuakui2015_Text[18223]["Text4511"]
tNpcGossip[18223]["tOption45-1"] = {96,97,98,99,84}
tNpcGossip[18223]["Option96"] = tHuakui2015_Text[18223]["Option96"]
tNpcGossip[18223]["Option97"] = tHuakui2015_Text[18223]["Option97"]
tNpcGossip[18223]["Option98"] = tHuakui2015_Text[18223]["Option98"]
tNpcGossip[18223]["Option99"] = tHuakui2015_Text[18223]["Option99"]
tNpcGossip[18223]["OptionFunc96"]="Huakui2015_Change</N>18223</N>1"
tNpcGossip[18223]["OptionFunc97"]="Huakui2015_Change</N>18223</N>2"
tNpcGossip[18223]["OptionFunc98"]="Huakui2015_Change</N>18223</N>3"
tNpcGossip[18223]["OptionFunc99"]="Huakui2015_Change</N>18223</N>4"

tNpcGossip[18223]["Text46-1"] = {4611}
tNpcGossip[18223]["Text4611"] = tHuakui2015_Text[18223]["Text4611"]
tNpcGossip[18223]["tOption46-1"] = {100}

tNpcGossip[18223]["Text46-2"] = {4621}
tNpcGossip[18223]["Text4621"] = tHuakui2015_Text[18223]["Text4621"]
tNpcGossip[18223]["tOption46-2"] = {100}

--报名规则和投票规则
tNpcGossip[18223]["Text47-1"] = {4711,4712,4713,4714,4715}
tNpcGossip[18223]["Text4711"] = tHuakui2015_Text[18223]["Text4711"]
tNpcGossip[18223]["Text4712"] = tHuakui2015_Text[18223]["Text4712"]
tNpcGossip[18223]["Text4713"] = tHuakui2015_Text[18223]["Text4713"]
tNpcGossip[18223]["Text4714"] = tHuakui2015_Text[18223]["Text4714"]
tNpcGossip[18223]["Text4715"] = tHuakui2015_Text[18223]["Text4715"]
tNpcGossip[18223]["tOption47-1"] = {101,102}
tNpcGossip[18223]["Option101"] = tHuakui2015_Text[18223]["Option101"]
tNpcGossip[18223]["Option102"] = tHuakui2015_Text[18223]["Option102"]
tNpcGossip[18223]["OptionPoint101"]="48"

tNpcGossip[18223]["Text48-1"] = {4811,4812,4813,4814}
tNpcGossip[18223]["Text4811"] = tHuakui2015_Text[18223]["Text4811"]
tNpcGossip[18223]["Text4812"] = tHuakui2015_Text[18223]["Text4812"]
tNpcGossip[18223]["Text4813"] = tHuakui2015_Text[18223]["Text4813"]
tNpcGossip[18223]["Text4814"] = tHuakui2015_Text[18223]["Text4814"]
tNpcGossip[18223]["tOption48-1"] = {103,104,102}
tNpcGossip[18223]["Option103"] = tHuakui2015_Text[18223]["Option103"]
tNpcGossip[18223]["Option104"] = tHuakui2015_Text[18223]["Option104"]
tNpcGossip[18223]["OptionPoint103"]="49"
tNpcGossip[18223]["OptionPoint104"]="47"

tNpcGossip[18223]["Text49-1"] = {4911,4912,4913,4914}
tNpcGossip[18223]["Text4911"] = tHuakui2015_Text[18223]["Text4911"]
tNpcGossip[18223]["Text4912"] = tHuakui2015_Text[18223]["Text4912"]
tNpcGossip[18223]["Text4913"] = tHuakui2015_Text[18223]["Text4913"]
tNpcGossip[18223]["Text4914"] = tHuakui2015_Text[18223]["Text4914"]
tNpcGossip[18223]["tOption49-1"] = {105,102}
tNpcGossip[18223]["Option105"] = tHuakui2015_Text[18223]["Option105"]
tNpcGossip[18223]["OptionPoint105"]="48"

-- 活动后对白
tNpcGossip[18223]["Text1-3"] = {131,132,133}
tNpcGossip[18223]["Text131"] = tHuakui2015_Text[18223]["Text131"]
tNpcGossip[18223]["Text132"] = tHuakui2015_Text[18223]["Text132"]
tNpcGossip[18223]["Text133"] = tHuakui2015_Text[18223]["Text133"]
tNpcGossip[18223]["tOption1-3"] = {6,3,5,8,106}
tNpcGossip[18223]["ChkFunc1-3"] = function ()
	return not Sys_ChkFullTime(tHuakui2015_Cont["ActivityTime"])
end











