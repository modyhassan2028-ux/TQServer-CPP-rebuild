------------------------------------------------------------------------------------
--Name:		[征服][活动脚本]卡牌月活动制作
--Purpose:	卡牌月活动制作
--Creator: 	严振飞
--Created:	2015/05/28
------------------------------------------------------------------------------------
--(135,49)---(136,02)
--掩码说明
---[1]	stc(135,24) 记录玩家的卡牌活动积分

----记录主神卡等级
---[2]	stc(135,49)	记录宙斯的等级
---[2]	stc(135,50)	记录赫拉的等级
---[2]	stc(135,51)	记录波塞冬的等级
---[2]	stc(135,52)	记录得墨忒耳的等级
---[2]	stc(135,53)	记录雅典娜的等级
---[2]	stc(135,54)	记录阿波罗的等级
---[2]	stc(135,55)	记录阿耳忒弥斯的等级
---[2]	stc(135,56)	记录阿佛洛狄忒的等级
---[2]	stc(135,57)	记录赫耳墨斯的等级
---[2]	stc(135,58)	记录阿瑞斯的等级
---[2]	stc(135,59)	记录赫淮斯托斯的等级
---[2]	stc(135,60)	记录狄俄倪索斯的等级
----记录主神卡攻击力
---[3]	stc(135,61)	记录宙斯的攻击力
---[3]	stc(135,62)	记录赫拉的攻击力
---[3]	stc(135,63)	记录波塞冬的攻击力
---[3]	stc(135,64)	记录得墨忒耳的攻击力
---[3]	stc(135,65)	记录雅典娜的攻击力
---[3]	stc(135,66)	记录阿波罗的攻击力
---[3]	stc(135,67)	记录阿耳忒弥斯的攻击力
---[3]	stc(135,68)	记录阿佛洛狄忒的攻击力
---[3]	stc(135,69)	记录赫耳墨斯的攻击力
---[3]	stc(135,70)	记录阿瑞斯的攻击力
---[3]	stc(135,71)	记录赫淮斯托斯的攻击力
---[3]	stc(135,72)	记录狄俄倪索斯的攻击力
----记录恶魔挑战阶段
---[4]	stc(135,73)	记录--万妖之祖堤丰--的挑战阶段
---[4]	stc(135,74)	记录--狂暴女神厄喀德娜--的挑战阶段
---[4]	stc(135,75)	记录--海怪利维坦--的挑战阶段
---[4]	stc(135,76)	记录--喷火兽喀迈拉--的挑战阶段
---[4]	stc(135,77)	记录--蛇发女妖美杜莎--的挑战阶段
---[4]	stc(135,78)	记录--半牛怪弥诺陶洛斯--的挑战阶段
---[4]	stc(135,79)	记录--海妖斯库拉--的挑战阶段
---[4]	stc(135,80)	记录--食人女怪安普莎--的挑战阶段
---[4]	stc(135,81)	记录--鸟身女妖哈耳庇埃--的挑战阶段
---[4]	stc(135,82)	记录--冥犬刻耳柏洛斯--的挑战阶段
---[4]	stc(135,83)	记录--勾魂使者凯瑞斯--的挑战阶段
---[4]	stc(135,84)	记录--独眼巨人兰杜迦--的挑战阶段
----记录恶魔的血量
---[5]	stc(135,85)	记录--万妖之祖堤丰--的血量
---[5]	stc(135,86)	记录--狂暴女神厄喀德娜--的血量
---[5]	stc(135,87)	记录--海怪利维坦--的血量
---[5]	stc(135,88)	记录--喷火兽喀迈拉--的血量
---[5]	stc(135,89)	记录--蛇发女妖美杜莎--的血量
---[5]	stc(135,90)	记录--半牛怪弥诺陶洛斯--的血量
---[5]	stc(135,91)	记录--海妖斯库拉--的血量
---[5]	stc(135,92)	记录--食人女怪安普莎--的血量
---[5]	stc(135,93)	记录--鸟身女妖哈耳庇埃--的血量
---[5]	stc(135,94)	记录--冥犬刻耳柏洛斯--的血量
---[5]	stc(135,95)	记录--勾魂使者凯瑞斯--的血量
---[5]	stc(135,96)	记录--独眼巨人兰杜迦--的血量

---[6]	stc(135,97)	记录恶魔的免费挑战次数
---[7]	stc(135,98)	记录玩家免费补领次数
---[8]	stc(135,99)	记录玩家免费打造圣物卡次数
---[9]	stc(136,0)	个位记录是否初始化过免费挑战次数
--					十位记录是否初始化过免费补领次数
--					百位记录是否初始化过免费打造圣物卡次数
--					千位记录是否进入过奥林匹斯之心
---[10]	stc(136,1)	记录击败恶魔个数
---[11]	stc(136,5)	记录解封宝藏次数
---[12]	stc(136,6)	记录超级宝藏地图杀怪数
---[13]	stc(136,7)	记录背包信是否获得





--动态存储表
--cq_dyna_global_data 50917
--data0		记录当前解开所有封印获得宝藏的人数\名次




--LOGid 10002414
------------------------------------------------------------------------------------
--命名规范
--FestivalCardMonth_
------------------------------------------------------------------------------------
--STC掩码表
local tFestivalCardMonth_Stc = {}
----------------------------------------
---------------------STC掩码记录玩家的卡牌活动积分
	tFestivalCardMonth_Stc[1] = {}
	tFestivalCardMonth_Stc[1]["EventData"] = 135
	tFestivalCardMonth_Stc[1]["TypeData"] = 24
	tFestivalCardMonth_Stc[1]["GetGodCard"] = 30	-- 获得新主神卡
	tFestivalCardMonth_Stc[1]["UpLev"] = 10			-- 主神卡升级
	
---------------------STC掩码记录主神卡等级
	tFestivalCardMonth_Stc[2] = {}
	tFestivalCardMonth_Stc[2]["Value"] = 1 --主神卡初始等级
	tFestivalCardMonth_Stc[2]["UpValue"] = 1 --升级增加等级
	---stc(135,49) 记录宙斯的等级
	tFestivalCardMonth_Stc[2][3006620] = {}
	tFestivalCardMonth_Stc[2][3006620]["EventData"] = 135
	tFestivalCardMonth_Stc[2][3006620]["TypeData"] = 49
	---stc(135,50) 记录赫拉的等级
	tFestivalCardMonth_Stc[2][3006621] = {}
	tFestivalCardMonth_Stc[2][3006621]["EventData"] = 135
	tFestivalCardMonth_Stc[2][3006621]["TypeData"] = 50
	---stc(135,51) 记录波塞冬的等级
	tFestivalCardMonth_Stc[2][3006622] = {}
	tFestivalCardMonth_Stc[2][3006622]["EventData"] = 135
	tFestivalCardMonth_Stc[2][3006622]["TypeData"] = 51
	---stc(135,52) 记录得墨忒耳的等级
	tFestivalCardMonth_Stc[2][3006623] = {}
	tFestivalCardMonth_Stc[2][3006623]["EventData"] = 135
	tFestivalCardMonth_Stc[2][3006623]["TypeData"] = 52
	---stc(135,53) 记录雅典娜的等级
	tFestivalCardMonth_Stc[2][3006624] = {}
	tFestivalCardMonth_Stc[2][3006624]["EventData"] = 135
	tFestivalCardMonth_Stc[2][3006624]["TypeData"] = 53
	---stc(135,54) 记录阿波罗的等级
	tFestivalCardMonth_Stc[2][3006625] = {}
	tFestivalCardMonth_Stc[2][3006625]["EventData"] = 135
	tFestivalCardMonth_Stc[2][3006625]["TypeData"] = 54
	---stc(135,55) 记录阿耳忒弥斯的等级
	tFestivalCardMonth_Stc[2][3006626] = {}
	tFestivalCardMonth_Stc[2][3006626]["EventData"] = 135
	tFestivalCardMonth_Stc[2][3006626]["TypeData"] = 55
	---stc(135,56) 记录阿佛洛狄忒的等级
	tFestivalCardMonth_Stc[2][3006627] = {}
	tFestivalCardMonth_Stc[2][3006627]["EventData"] = 135
	tFestivalCardMonth_Stc[2][3006627]["TypeData"] = 56
	---stc(135,57) 记录赫耳墨斯的等级
	tFestivalCardMonth_Stc[2][3006628] = {}
	tFestivalCardMonth_Stc[2][3006628]["EventData"] = 135
	tFestivalCardMonth_Stc[2][3006628]["TypeData"] = 57
	---stc(135,58) 记录阿瑞斯的等级
	tFestivalCardMonth_Stc[2][3006629] = {}
	tFestivalCardMonth_Stc[2][3006629]["EventData"] = 135
	tFestivalCardMonth_Stc[2][3006629]["TypeData"] = 58
	---stc(135,59) 记录赫淮斯托斯的等级
	tFestivalCardMonth_Stc[2][3006630] = {}
	tFestivalCardMonth_Stc[2][3006630]["EventData"] = 135
	tFestivalCardMonth_Stc[2][3006630]["TypeData"] = 59
	---stc(135,60) 记录狄俄倪索斯的等级
	tFestivalCardMonth_Stc[2][3006631] = {}
	tFestivalCardMonth_Stc[2][3006631]["EventData"] = 135
	tFestivalCardMonth_Stc[2][3006631]["TypeData"] = 60

	
---------------------STC掩码记录主神卡攻击
	tFestivalCardMonth_Stc[3] = {}
	---stc(135,61) 记录宙斯的攻击力
	tFestivalCardMonth_Stc[3][3006620] = {}
	tFestivalCardMonth_Stc[3][3006620]["EventData"] = 135
	tFestivalCardMonth_Stc[3][3006620]["TypeData"] = 61
	tFestivalCardMonth_Stc[3][3006620]["Value"] = 360 		--主神卡初始攻击力
	tFestivalCardMonth_Stc[3][3006620]["UpValue"] = 60 		--升级增加的攻击力
	---stc(135,62) 记录赫拉的攻击力
	tFestivalCardMonth_Stc[3][3006621] = {}
	tFestivalCardMonth_Stc[3][3006621]["EventData"] = 135
	tFestivalCardMonth_Stc[3][3006621]["TypeData"] = 62
	tFestivalCardMonth_Stc[3][3006621]["Value"] = 360 		--主神卡初始攻击力
	tFestivalCardMonth_Stc[3][3006621]["UpValue"] = 60 		--升级增加的攻击力
	---stc(135,63) 记录波塞冬的攻击力	
	tFestivalCardMonth_Stc[3][3006622] = {}
	tFestivalCardMonth_Stc[3][3006622]["EventData"] = 135
	tFestivalCardMonth_Stc[3][3006622]["TypeData"] = 63
	tFestivalCardMonth_Stc[3][3006622]["Value"] = 360 		--主神卡初始攻击力
	tFestivalCardMonth_Stc[3][3006622]["UpValue"] = 60 		--升级增加的攻击力
	---stc(135,64) 记录得墨忒耳的攻击力	
	tFestivalCardMonth_Stc[3][3006623] = {}
	tFestivalCardMonth_Stc[3][3006623]["EventData"] = 135
	tFestivalCardMonth_Stc[3][3006623]["TypeData"] = 64
	tFestivalCardMonth_Stc[3][3006623]["Value"] = 300 		--主神卡初始攻击力
	tFestivalCardMonth_Stc[3][3006623]["UpValue"] = 50 		--升级增加的攻击力
	---stc(135,65) 记录雅典娜的攻击力	
	tFestivalCardMonth_Stc[3][3006624] = {}
	tFestivalCardMonth_Stc[3][3006624]["EventData"] = 135
	tFestivalCardMonth_Stc[3][3006624]["TypeData"] = 65
	tFestivalCardMonth_Stc[3][3006624]["Value"] = 300 		--主神卡初始攻击力
	tFestivalCardMonth_Stc[3][3006624]["UpValue"] = 50 		--升级增加的攻击力
	---stc(135,66) 记录阿波罗的攻击力	
	tFestivalCardMonth_Stc[3][3006625] = {}
	tFestivalCardMonth_Stc[3][3006625]["EventData"] = 135
	tFestivalCardMonth_Stc[3][3006625]["TypeData"] = 66
	tFestivalCardMonth_Stc[3][3006625]["Value"] = 300 		--主神卡初始攻击力
	tFestivalCardMonth_Stc[3][3006625]["UpValue"] = 50 		--升级增加的攻击力
	---stc(135,67) 记录阿耳忒弥斯的攻击力	
	tFestivalCardMonth_Stc[3][3006626] = {}
	tFestivalCardMonth_Stc[3][3006626]["EventData"] = 135
	tFestivalCardMonth_Stc[3][3006626]["TypeData"] = 67
	tFestivalCardMonth_Stc[3][3006626]["Value"] = 300 		--主神卡初始攻击力
	tFestivalCardMonth_Stc[3][3006626]["UpValue"] = 50 		--升级增加的攻击力
	---stc(135,68) 记录阿佛洛狄忒的攻击力	
	tFestivalCardMonth_Stc[3][3006627] = {}
	tFestivalCardMonth_Stc[3][3006627]["EventData"] = 135
	tFestivalCardMonth_Stc[3][3006627]["TypeData"] = 68
	tFestivalCardMonth_Stc[3][3006627]["Value"] = 240 		--主神卡初始攻击力
	tFestivalCardMonth_Stc[3][3006627]["UpValue"] = 40 		--升级增加的攻击力
	---stc(135,69) 记录赫耳墨斯的攻击力	
	tFestivalCardMonth_Stc[3][3006628] = {}
	tFestivalCardMonth_Stc[3][3006628]["EventData"] = 135
	tFestivalCardMonth_Stc[3][3006628]["TypeData"] = 69
	tFestivalCardMonth_Stc[3][3006628]["Value"] = 240 		--主神卡初始攻击力
	tFestivalCardMonth_Stc[3][3006628]["UpValue"] = 40 		--升级增加的攻击力
	---stc(135,70) 记录阿瑞斯的攻击力	
	tFestivalCardMonth_Stc[3][3006629] = {}
	tFestivalCardMonth_Stc[3][3006629]["EventData"] = 135
	tFestivalCardMonth_Stc[3][3006629]["TypeData"] = 70
	tFestivalCardMonth_Stc[3][3006629]["Value"] = 240 		--主神卡初始攻击力
	tFestivalCardMonth_Stc[3][3006629]["UpValue"] = 40 		--升级增加的攻击力
	---stc(135,71) 记录赫淮斯托斯的攻击力	
	tFestivalCardMonth_Stc[3][3006630] = {}
	tFestivalCardMonth_Stc[3][3006630]["EventData"] = 135
	tFestivalCardMonth_Stc[3][3006630]["TypeData"] = 71
	tFestivalCardMonth_Stc[3][3006630]["Value"] = 240 		--主神卡初始攻击力
	tFestivalCardMonth_Stc[3][3006630]["UpValue"] = 40 		--升级增加的攻击力
	---stc(135,72) 记录狄俄倪索斯的攻击力	
	tFestivalCardMonth_Stc[3][3006631] = {}
	tFestivalCardMonth_Stc[3][3006631]["EventData"] = 135
	tFestivalCardMonth_Stc[3][3006631]["TypeData"] = 72
	tFestivalCardMonth_Stc[3][3006631]["Value"] = 240 		--主神卡初始攻击力
	tFestivalCardMonth_Stc[3][3006631]["UpValue"] = 40 		--升级增加的攻击力
	
---------------------记录恶魔挑战阶段
	tFestivalCardMonth_Stc[4] = {}
	tFestivalCardMonth_Stc[4]["AddValue"] = 1
	tFestivalCardMonth_Stc[4]["PhaseNum"] = 3 --共3个阶段
	tFestivalCardMonth_Stc[4]["Complete"] = 4
	---stc(135,73) 记录--万妖之祖堤丰--的挑战阶段
	tFestivalCardMonth_Stc[4][18579] = {}
	tFestivalCardMonth_Stc[4][18579]["EventData"] = 135
	tFestivalCardMonth_Stc[4][18579]["TypeData"] = 73
	---stc(135,74) 记录--狂暴女神厄喀德娜--的挑战阶段
	tFestivalCardMonth_Stc[4][18580] = {}
	tFestivalCardMonth_Stc[4][18580]["EventData"] = 135
	tFestivalCardMonth_Stc[4][18580]["TypeData"] = 74
	---stc(135,75) 记录--海怪利维坦--的挑战阶段
	tFestivalCardMonth_Stc[4][18581] = {}
	tFestivalCardMonth_Stc[4][18581]["EventData"] = 135
	tFestivalCardMonth_Stc[4][18581]["TypeData"] = 75
	---stc(135,76) 记录--喷火兽喀迈拉--的挑战阶段
	tFestivalCardMonth_Stc[4][18582] = {}
	tFestivalCardMonth_Stc[4][18582]["EventData"] = 135
	tFestivalCardMonth_Stc[4][18582]["TypeData"] = 76
	---stc(135,77) 记录--蛇发女妖美杜莎--的挑战阶段
	tFestivalCardMonth_Stc[4][18583] = {}
	tFestivalCardMonth_Stc[4][18583]["EventData"] = 135
	tFestivalCardMonth_Stc[4][18583]["TypeData"] = 77
	---stc(135,78) 记录--半牛怪弥诺陶洛斯--的挑战阶段
	tFestivalCardMonth_Stc[4][18584] = {}
	tFestivalCardMonth_Stc[4][18584]["EventData"] = 135
	tFestivalCardMonth_Stc[4][18584]["TypeData"] = 78
	---stc(135,79) 记录--海妖斯库拉--的挑战阶段
	tFestivalCardMonth_Stc[4][18585] = {}
	tFestivalCardMonth_Stc[4][18585]["EventData"] = 135
	tFestivalCardMonth_Stc[4][18585]["TypeData"] = 79
	---stc(135,80) 记录--食人女怪安普莎--的挑战阶段
	tFestivalCardMonth_Stc[4][18586] = {}
	tFestivalCardMonth_Stc[4][18586]["EventData"] = 135
	tFestivalCardMonth_Stc[4][18586]["TypeData"] = 80
	---stc(135,81) 记录--鸟身女妖哈耳庇埃--的挑战阶段
	tFestivalCardMonth_Stc[4][18587] = {}
	tFestivalCardMonth_Stc[4][18587]["EventData"] = 135
	tFestivalCardMonth_Stc[4][18587]["TypeData"] = 81
	---stc(135,82) 记录--冥犬刻耳柏洛斯--的挑战阶段
	tFestivalCardMonth_Stc[4][18588] = {}
	tFestivalCardMonth_Stc[4][18588]["EventData"] = 135
	tFestivalCardMonth_Stc[4][18588]["TypeData"] = 82
	---stc(135,83) 记录--勾魂使者凯瑞斯--的挑战阶段
	tFestivalCardMonth_Stc[4][18589] = {}
	tFestivalCardMonth_Stc[4][18589]["EventData"] = 135
	tFestivalCardMonth_Stc[4][18589]["TypeData"] = 83
	---stc(135,84) 记录--独眼巨人兰杜迦--的挑战阶段
	tFestivalCardMonth_Stc[4][18590] = {}
	tFestivalCardMonth_Stc[4][18590]["EventData"] = 135
	tFestivalCardMonth_Stc[4][18590]["TypeData"] = 84

---------------------记录恶魔的血量
	tFestivalCardMonth_Stc[5] = {}
	---stc(135,85) 记录--万妖之祖堤丰--血量
	tFestivalCardMonth_Stc[5][18579] = {}
	tFestivalCardMonth_Stc[5][18579]["EventData"] = 135
	tFestivalCardMonth_Stc[5][18579]["TypeData"] = 85
	tFestivalCardMonth_Stc[5][18579]["HP"] = 1800
	---stc(135,86) 记录--狂暴女神厄喀德娜--血量
	tFestivalCardMonth_Stc[5][18580] = {}
	tFestivalCardMonth_Stc[5][18580]["EventData"] = 135
	tFestivalCardMonth_Stc[5][18580]["TypeData"] = 86
	tFestivalCardMonth_Stc[5][18580]["HP"] = 1800
	---stc(135,87) 记录--海怪利维坦--血量
	tFestivalCardMonth_Stc[5][18581] = {}
	tFestivalCardMonth_Stc[5][18581]["EventData"] = 135
	tFestivalCardMonth_Stc[5][18581]["TypeData"] = 87
	tFestivalCardMonth_Stc[5][18581]["HP"] = 1800
	---stc(135,88) 记录--喷火兽喀迈拉--血量
	tFestivalCardMonth_Stc[5][18582] = {}
	tFestivalCardMonth_Stc[5][18582]["EventData"] = 135
	tFestivalCardMonth_Stc[5][18582]["TypeData"] = 88
	tFestivalCardMonth_Stc[5][18582]["HP"] = 1500
	---stc(135,89) 记录--蛇发女妖美杜莎--血量
	tFestivalCardMonth_Stc[5][18583] = {}
	tFestivalCardMonth_Stc[5][18583]["EventData"] = 135
	tFestivalCardMonth_Stc[5][18583]["TypeData"] = 89
	tFestivalCardMonth_Stc[5][18583]["HP"] = 1500
	---stc(135,90) 记录--半牛怪弥诺陶洛斯--血量
	tFestivalCardMonth_Stc[5][18584] = {}
	tFestivalCardMonth_Stc[5][18584]["EventData"] = 135
	tFestivalCardMonth_Stc[5][18584]["TypeData"] = 90
	tFestivalCardMonth_Stc[5][18584]["HP"] = 1500
	---stc(135,91) 记录--海妖斯库拉--血量
	tFestivalCardMonth_Stc[5][18585] = {}
	tFestivalCardMonth_Stc[5][18585]["EventData"] = 135
	tFestivalCardMonth_Stc[5][18585]["TypeData"] = 91
	tFestivalCardMonth_Stc[5][18585]["HP"] = 1500
	---stc(135,92) 记录--食人女怪安普莎--血量
	tFestivalCardMonth_Stc[5][18586] = {}
	tFestivalCardMonth_Stc[5][18586]["EventData"] = 135
	tFestivalCardMonth_Stc[5][18586]["TypeData"] = 92
	tFestivalCardMonth_Stc[5][18586]["HP"] = 1200
	---stc(135,93) 记录--鸟身女妖哈耳庇埃--血量
	tFestivalCardMonth_Stc[5][18587] = {}
	tFestivalCardMonth_Stc[5][18587]["EventData"] = 135
	tFestivalCardMonth_Stc[5][18587]["TypeData"] = 93
	tFestivalCardMonth_Stc[5][18587]["HP"] = 1200
	---stc(135,94) 记录--冥犬刻耳柏洛斯--血量
	tFestivalCardMonth_Stc[5][18588] = {}
	tFestivalCardMonth_Stc[5][18588]["EventData"] = 135
	tFestivalCardMonth_Stc[5][18588]["TypeData"] = 94
	tFestivalCardMonth_Stc[5][18588]["HP"] = 1200
	---stc(135,95) 记录--勾魂使者凯瑞斯--血量
	tFestivalCardMonth_Stc[5][18589] = {}
	tFestivalCardMonth_Stc[5][18589]["EventData"] = 135
	tFestivalCardMonth_Stc[5][18589]["TypeData"] = 95
	tFestivalCardMonth_Stc[5][18589]["HP"] = 1200
	---stc(135,96) 记录--独眼巨人兰杜迦--血量
	tFestivalCardMonth_Stc[5][18590] = {}
	tFestivalCardMonth_Stc[5][18590]["EventData"] = 135
	tFestivalCardMonth_Stc[5][18590]["TypeData"] = 96
	tFestivalCardMonth_Stc[5][18590]["HP"] = 1200

---------------------stc(135,97) 记录恶魔的免费挑战次数
	tFestivalCardMonth_Stc[6] = {}
	tFestivalCardMonth_Stc[6]["EventData"] = 135
	tFestivalCardMonth_Stc[6]["TypeData"] = 97
	tFestivalCardMonth_Stc[6]["Value"] = 10
	tFestivalCardMonth_Stc[6]["AddValue"] = 3		--恶魔挑战书增加数量
	tFestivalCardMonth_Stc[6]["SubValue"] = -1		--使用一次减少数量
	tFestivalCardMonth_Stc[6]["Complete"] = 0

---------------------stc(135,98) 记录玩家免费补领次数
	tFestivalCardMonth_Stc[7] = {}
	tFestivalCardMonth_Stc[7]["EventData"] = 135
	tFestivalCardMonth_Stc[7]["TypeData"] = 98
	tFestivalCardMonth_Stc[7]["AddValue"] = 1
	tFestivalCardMonth_Stc[7]["Complete"] = 3
	
---------------------STC掩码记录玩家可用免费打造圣物卡次数
	tFestivalCardMonth_Stc[8] = {}
	tFestivalCardMonth_Stc[8]["EventData"] = 135
	tFestivalCardMonth_Stc[8]["TypeData"] = 99
	tFestivalCardMonth_Stc[8]["Value"] = 10
	tFestivalCardMonth_Stc[8]["AddValue1"] = 1		--分解圣物卡增加数量
	tFestivalCardMonth_Stc[8]["AddValue3"] = 3		--恶魔挑战书增加数量
	tFestivalCardMonth_Stc[8]["Complete"] = 0
	
---------------------STC记录是否初始化过
	tFestivalCardMonth_Stc[9] = {}
	tFestivalCardMonth_Stc[9]["EventData"] = 136
	tFestivalCardMonth_Stc[9]["TypeData"] = 0
	--不同类型掩码存储位置
	tFestivalCardMonth_Stc[9]["Place"] = {}
	tFestivalCardMonth_Stc[9]["Place"][1] = 1		--个位记录是否初始化过免费挑战次数
	tFestivalCardMonth_Stc[9]["Place"][2] = 10		--十位记录是否初始化过免费补领次数
	tFestivalCardMonth_Stc[9]["Place"][3] = 100		--百位记录是否初始化过免费打造圣物卡次数
	
---------------------STC记录击败恶魔个数
	tFestivalCardMonth_Stc[10] = {}
	tFestivalCardMonth_Stc[10]["EventData"] = 136
	tFestivalCardMonth_Stc[10]["TypeData"] = 1
	tFestivalCardMonth_Stc[10]["AddValue"] = 1
	tFestivalCardMonth_Stc[10]["Phase"] = {}
	tFestivalCardMonth_Stc[10]["Phase"][1] = 3
	tFestivalCardMonth_Stc[10]["Phase"][2] = 6
	tFestivalCardMonth_Stc[10]["Phase"][3] = 9
	tFestivalCardMonth_Stc[10]["Phase"][4] = 12

---------------------记录解封宝藏次数
	tFestivalCardMonth_Stc[11] = {}
	tFestivalCardMonth_Stc[11]["EventData"] = 136
	tFestivalCardMonth_Stc[11]["TypeData"] = 5
	tFestivalCardMonth_Stc[11]["AddValue"] = 1
	tFestivalCardMonth_Stc[11]["Complete"] = 4
	
---------------------记录超级宝藏地图杀怪数
	tFestivalCardMonth_Stc[12] = {}
	tFestivalCardMonth_Stc[12]["EventData"] = 136
	tFestivalCardMonth_Stc[12]["TypeData"] = 6
	tFestivalCardMonth_Stc[12]["Complete"] = 8

------------------------------------------------------------------------------------
--动态存储表
local tFestivalCardMonth_DynaGlobal = {}
	tFestivalCardMonth_DynaGlobal[1] = 50917


------------------------------------------------------------------------------------
--活动数据
local tFestivalCardMonth_Data = {}
	-- 活动时间
	tFestivalCardMonth_Data["Festival_BefTime"] = "2014-01-01 00:00 2015-08-03 23:59"
	tFestivalCardMonth_Data["Festival_NowTime"] = "2015-08-04 00:00 2015-08-17 23:59"
	
	-- 网页链接
	tFestivalCardMonth_Data["WebLink"] = "http://event.co.99.com/godsclash"
	
	-- 正气令ID
	tFestivalCardMonth_Data["ChiToken"] = 729304
	
	-- 第一批BOSS掉落神器碎片个数
	tFestivalCardMonth_Data["PieceNum1"] = 10
	tFestivalCardMonth_Data["PiecePosX"] = 5
	tFestivalCardMonth_Data["PiecePosY"] = 5
	tFestivalCardMonth_Data["PieceExistTime"] = 60
	-- 第二批BOSS掉落神器碎片个数
	tFestivalCardMonth_Data["PieceNum2"] = 10
	tFestivalCardMonth_Data["GodPieceNum2"] = 1
	-- 第三批BOSS掉落神器碎片个数
	tFestivalCardMonth_Data["GodPieceNum3"] = 3
	-- 第四批BOSS掉落神器碎片个数
	tFestivalCardMonth_Data["GodPieceNum4"] = 5
	
	-- 购买幸运礼包天石数据
	tFestivalCardMonth_Data["LucyBagEMoney"] = {}
	tFestivalCardMonth_Data["LucyBagEMoney"][1] = 27
	tFestivalCardMonth_Data["LucyBagEMoney"][2] = 270
	tFestivalCardMonth_Data["LucyBagId"] = {}
	tFestivalCardMonth_Data["LucyBagId"][1] = 3006695
	tFestivalCardMonth_Data["LucyBagId"][2] = 3006696

	-- 补领天石数
	tFestivalCardMonth_Data["SupGodCardEMoney"] = 99
	-- 挑战天石数
	tFestivalCardMonth_Data["SupDekaronEMoney"] = 27
	-- 连续挑战几次
	tFestivalCardMonth_Data["SupDekaronTimes"] = 5
	
	-- 点天石上限
	tFestivalCardMonth_Data["EMonoMoneyTop"] = 999999999
	-- 等级，转世设置
	tFestivalCardMonth_Data["LevelTop"] = 140
	tFestivalCardMonth_Data["MinLevel"] = 120
	tFestivalCardMonth_Data["MinMeto"] = 0

	-- 背包空间
	tFestivalCardMonth_Data["ChkSpace1"] = 1
	tFestivalCardMonth_Data["ChkSpace2"] = 2
	tFestivalCardMonth_Data["ChkSpace3"] = 3
	tFestivalCardMonth_Data["ChkSpace4"] = 4
	tFestivalCardMonth_Data["ChkSpace10"] = 10
	-- 分解圣物卡获得碎片个数
	tFestivalCardMonth_Data["PieceId"] = 3006692
	tFestivalCardMonth_Data["PieceNum"] = 3
	
	-- 击败恶魔获得积分
	tFestivalCardMonth_Data["DemonPoint"] = {}
	tFestivalCardMonth_Data["DemonPoint"][1] = 10
	tFestivalCardMonth_Data["DemonPoint"][2] = 20
	tFestivalCardMonth_Data["DemonPoint"][3] = 30
	
	--进入奥林匹斯山数据
	tFestivalCardMonth_Data[18577] = {}
	tFestivalCardMonth_Data[18577]["MapId"] = 3948
	tFestivalCardMonth_Data[18577]["PosX"] = 47
	tFestivalCardMonth_Data[18577]["PosY"] = 55
	tFestivalCardMonth_Data[18577]["BoundX"] = 5
	tFestivalCardMonth_Data[18577]["BoundY"] = 5
	--返回双龙城
	tFestivalCardMonth_Data[18591] = {}
	tFestivalCardMonth_Data[18591]["MapId"] = 1002
	tFestivalCardMonth_Data[18591]["PosX"] = 302
	tFestivalCardMonth_Data[18591]["PosY"] = 288
	tFestivalCardMonth_Data[18591]["BoundX"] = 5
	tFestivalCardMonth_Data[18591]["BoundY"] = 5
	--进入奥林匹斯之心
	tFestivalCardMonth_Data[18578] = {}
	tFestivalCardMonth_Data[18578]["MapId"] = 3949
	tFestivalCardMonth_Data[18578]["PosX"] = 45
	tFestivalCardMonth_Data[18578]["PosY"] = 45
	tFestivalCardMonth_Data[18578]["BoundX"] = 5
	tFestivalCardMonth_Data[18578]["BoundY"] = 5
	--奥林匹克之心返回奥林匹斯山
	tFestivalCardMonth_Data[3949] = {}
	tFestivalCardMonth_Data[3949]["MapId"] = 3948
	tFestivalCardMonth_Data[3949]["PosX"] = 47
	tFestivalCardMonth_Data[3949]["PosY"] = 55
	tFestivalCardMonth_Data[3949]["BoundX"] = 5
	tFestivalCardMonth_Data[3949]["BoundY"] = 5


	--寻路--奥林匹斯神使(双龙城)
	tFestivalCardMonth_Data[3006632] = {}
	tFestivalCardMonth_Data[3006632]["NpcId"] = 18577
	tFestivalCardMonth_Data[3006632]["MapId"] = 1002
	tFestivalCardMonth_Data[3006632]["PosX"] = 298
	tFestivalCardMonth_Data[3006632]["PosY"] = 288
	--寻路--奥林匹斯神使(挑战地图)
	tFestivalCardMonth_Data[3948] = {}
	tFestivalCardMonth_Data[3948]["NpcId"] = 18591
	tFestivalCardMonth_Data[3948]["MapId"] = 3948
	tFestivalCardMonth_Data[3948]["PosX"] = 53
	tFestivalCardMonth_Data[3948]["PosY"] = 52

	--通用礼包ID
	tFestivalCardMonth_Data["FestivalId"] = 3370
	tFestivalCardMonth_Data["LogId"] = 10002414
	
	--合成主神卡包需要碎片数量
	tFestivalCardMonth_Data["CardPieceNum"] = 10
	
	--主神卡幸运连抽礼包次数
	tFestivalCardMonth_Data["SeriesBagNum"] = 10
	
	-- 背包信经验+修行值
	tFestivalCardMonth_Data["Type_Exp"] = 4
	tFestivalCardMonth_Data["Type_Cul"] = 6
	tFestivalCardMonth_Data["Letter_Exp"] = 30
	tFestivalCardMonth_Data["Letter_Cul"] = 15
	
	-- 光效数据
	tFestivalCardMonth_Data["EffectObj"] = "self"
	tFestivalCardMonth_Data["EffectMap"] = 3948
	tFestivalCardMonth_Data["Effect_1"] = "angelwing"
	tFestivalCardMonth_Data["Effect_2"] = "jsb_skyg_att"
	tFestivalCardMonth_Data["Effect_3"] = "zf2-e300"
	tFestivalCardMonth_Data["Effect_4"] = "zf2-e280"
	tFestivalCardMonth_Data["Effect_5"] = "accession"
------------------------------------------------------------------------------------
-- 圣物碎片数据
local tFestivalCardMonth_HolyPiece = {}
	tFestivalCardMonth_HolyPiece["ProbabilNum"] = 10
	tFestivalCardMonth_HolyPiece["DesignNum"] = 30
	tFestivalCardMonth_HolyPiece["CreateEMoney"] = 27

------------------------------------------------------------------------------------
-- 打开宝藏奖励数据
local tFestivalCardMonth_OpenBox = {}
	tFestivalCardMonth_OpenBox["STPillId"] = 3003126 	--究极通神丹
	tFestivalCardMonth_OpenBox["CoatId"] = 192605 		--御风逍遥外套
	tFestivalCardMonth_OpenBox["VitalPillId"] = 3000134 --回气丹礼包
	-- 赠点天石
	tFestivalCardMonth_OpenBox["MonoEMoney"] = {}
	tFestivalCardMonth_OpenBox["MonoEMoney"][1] = 50
	tFestivalCardMonth_OpenBox["MonoEMoney"][2] = 150
	tFestivalCardMonth_OpenBox["MonoEMoney"][3] = 300
	-- 3\6\9气力值
	tFestivalCardMonth_OpenBox["Strength"] = {}
	tFestivalCardMonth_OpenBox["Strength"][1] = 500
	tFestivalCardMonth_OpenBox["Strength"][2] = 1500
	tFestivalCardMonth_OpenBox["Strength"][3] = 5000
	-- 积分
	tFestivalCardMonth_OpenBox["Integral"] = {}
	tFestivalCardMonth_OpenBox["Integral"][1] = 1000
	tFestivalCardMonth_OpenBox["Integral"][2] = 900
	tFestivalCardMonth_OpenBox["Integral"][3] = 800
	tFestivalCardMonth_OpenBox["Integral"][4] = 700
	tFestivalCardMonth_OpenBox["Integral"][5] = 600
	tFestivalCardMonth_OpenBox["Integral"][6] = 500
	tFestivalCardMonth_OpenBox["Integral"][7] = 400
	tFestivalCardMonth_OpenBox["Integral"][8] = 300
	tFestivalCardMonth_OpenBox["Integral"][9] = 200
	tFestivalCardMonth_OpenBox["Integral"][10] = 100
	tFestivalCardMonth_OpenBox["Integral"][11] = 50
	-- 所有恶魔气力值
	tFestivalCardMonth_OpenBox["AllStrength"] = {}
	tFestivalCardMonth_OpenBox["AllStrength"][1] = 50000
	tFestivalCardMonth_OpenBox["AllStrength"][2] = 30000
	tFestivalCardMonth_OpenBox["AllStrength"][3] = 20000
	tFestivalCardMonth_OpenBox["AllStrength"][4] = 10000
	tFestivalCardMonth_OpenBox["AllStrength"][5] = 10000
	tFestivalCardMonth_OpenBox["AllStrength"][6] = 10000
	tFestivalCardMonth_OpenBox["AllStrength"][7] = 10000
	tFestivalCardMonth_OpenBox["AllStrength"][8] = 10000
	tFestivalCardMonth_OpenBox["AllStrength"][9] = 10000
	tFestivalCardMonth_OpenBox["AllStrength"][10] = 10000
	--究极通神丹（赠）
	tFestivalCardMonth_OpenBox["STPill"] = {}
	tFestivalCardMonth_OpenBox["STPill"][1] = 50
	tFestivalCardMonth_OpenBox["STPill"][2] = 40
	tFestivalCardMonth_OpenBox["STPill"][3] = 30
	tFestivalCardMonth_OpenBox["STPill"][4] = 30
	tFestivalCardMonth_OpenBox["STPill"][5] = 30
	tFestivalCardMonth_OpenBox["STPill"][6] = 30
	tFestivalCardMonth_OpenBox["STPill"][7] = 30
	tFestivalCardMonth_OpenBox["STPill"][8] = 30
	tFestivalCardMonth_OpenBox["STPill"][9] = 30
	tFestivalCardMonth_OpenBox["STPill"][10] = 30
	--御风逍遥外套时效
	tFestivalCardMonth_OpenBox["CoatTime"] = {}
	tFestivalCardMonth_OpenBox["CoatTime"][1] = 43200
	tFestivalCardMonth_OpenBox["CoatTime"][2] = 43200
	tFestivalCardMonth_OpenBox["CoatTime"][3] = 43200
	tFestivalCardMonth_OpenBox["CoatTime"][4] = 10080
	tFestivalCardMonth_OpenBox["CoatTime"][5] = 10080
	tFestivalCardMonth_OpenBox["CoatTime"][6] = 10080
	tFestivalCardMonth_OpenBox["CoatTime"][7] = 10080
	tFestivalCardMonth_OpenBox["CoatTime"][8] = 10080
	tFestivalCardMonth_OpenBox["CoatTime"][9] = 10080
	tFestivalCardMonth_OpenBox["CoatTime"][10] = 10080
	--外套天与小时转换率
	tFestivalCardMonth_OpenBox["Change"] = 1440
	--10名以下究极通神丹个数
	tFestivalCardMonth_OpenBox["TenUnder"] = 10
	
	
-------------------------------------【A、B、C类礼包】-----------------------------------------------
--说明</N> 礼包ID </N> 背包空间 </N> 奖励1 </N> 奖励1个数 </N> 奖励2 </N> 奖励2个数 </N> 奖励3 </N> 奖励3个数
local tFestivalCardMonth_OptionFunc = {}
	-- 初级圣光礼包
	tFestivalCardMonth_OptionFunc[3006864] = {}
	tFestivalCardMonth_OptionFunc[3006864][1] = "FestivalCardMonth_OpenPag</N>3006864</N>5</N>720027</N>1</N>3001283</N>5"
	tFestivalCardMonth_OptionFunc[3006864][2] = "FestivalCardMonth_OpenPag</N>3006864</N>1</N>729242</N>1</N>3003124</N>5"
	-- 中级圣光礼包
	tFestivalCardMonth_OptionFunc[3006865] = {}
	tFestivalCardMonth_OptionFunc[3006865][1] = "FestivalCardMonth_OpenPag</N>3006865</N>3</N>723727</N>3</N>300000</N>2</N>3005892</N>1"
	tFestivalCardMonth_OptionFunc[3006865][2] = "FestivalCardMonth_OpenPag</N>3006865</N>2</N>729242</N>2</N>723342</N>1"
	-- 高级圣光礼包
	tFestivalCardMonth_OptionFunc[3006866] = {}
	tFestivalCardMonth_OptionFunc[3006866][1] = "FestivalCardMonth_OpenPag</N>3006866</N>1</N>730003</N>1</N>3005893</N>1"
	tFestivalCardMonth_OptionFunc[3006866][2] = "FestivalCardMonth_OpenPag</N>3006866</N>0</N>3005360</N>1"
	-- 初级圣歌礼包
	tFestivalCardMonth_OptionFunc[3006867] = {}
	tFestivalCardMonth_OptionFunc[3006867][1] = "FestivalCardMonth_OpenPag</N>3006867</N>6</N>723017</N>3</N>1088001</N>3</N>3001283</N>3"
	tFestivalCardMonth_OptionFunc[3006867][2] = "FestivalCardMonth_OpenPag</N>3006867</N>1</N>723727</N>3</N>3003124</N>3"
	-- 中级圣歌礼包
	tFestivalCardMonth_OptionFunc[3006868] = {}
	tFestivalCardMonth_OptionFunc[3006868][1] = "FestivalCardMonth_OpenPag</N>3006868</N>2</N>720027</N>1</N>730002</N>1</N>723342</N>1"
	tFestivalCardMonth_OptionFunc[3006868][2] = "FestivalCardMonth_OpenPag</N>3006868</N>2</N>729242</N>1</N>3003125</N>5</N>728883</N>6"
	-- 高级圣歌礼包
	tFestivalCardMonth_OptionFunc[3006869] = {}
	tFestivalCardMonth_OptionFunc[3006869][1] = "FestivalCardMonth_OpenPag</N>3006869</N>1</N>700013</N>1</N>723727</N>5"
	tFestivalCardMonth_OptionFunc[3006869][2] = "FestivalCardMonth_OpenPag</N>3006869</N>1</N>700003</N>1</N>723727</N>5"
	tFestivalCardMonth_OptionFunc[3006869][3] = "FestivalCardMonth_OpenPag</N>3006869</N>2</N>729242</N>1</N>3003126</N>2</N>3003124</N>5"
	-- 初级圣佑礼包
	tFestivalCardMonth_OptionFunc[3006870] = {}
	tFestivalCardMonth_OptionFunc[3006870][1] = "FestivalCardMonth_OpenPag</N>3006870</N>4</N>720128</N>2</N>1088001</N>2</N>3001283</N>2"
	tFestivalCardMonth_OptionFunc[3006870][2] = "FestivalCardMonth_OpenPag</N>3006870</N>1</N>723727</N>2</N>3003124</N>2"
	-- 中级圣佑礼包
	tFestivalCardMonth_OptionFunc[3006871] = {}
	tFestivalCardMonth_OptionFunc[3006871][1] = "FestivalCardMonth_OpenPag</N>3006871</N>4</N>3001283</N>2</N>730001</N>2</N>1200000</N>1"
	tFestivalCardMonth_OptionFunc[3006871][2] = "FestivalCardMonth_OpenPag</N>3006871</N>1</N>3003124</N>3</N>3003125</N>3"
	-- 高级圣佑礼包
	tFestivalCardMonth_OptionFunc[3006872] = {}
	tFestivalCardMonth_OptionFunc[3006872][1] = "FestivalCardMonth_OpenPag</N>3006872</N>2</N>720027</N>1</N>300000</N>1</N>728883</N>6"
	tFestivalCardMonth_OptionFunc[3006872][2] = "FestivalCardMonth_OpenPag</N>3006872</N>1</N>729242</N>1</N>3003126</N>1"

-------------------------------------【神赐宝箱】-----------------------------------------------
local tFestivalCardMonth_GodRewardBox = {}
	tFestivalCardMonth_GodRewardBox["RewardType"] = {}
----------------------奖励类型
	--天石
	tFestivalCardMonth_GodRewardBox["RewardType"][3006873] = {}
	tFestivalCardMonth_GodRewardBox["RewardType"][3006873][1] = 2
	tFestivalCardMonth_GodRewardBox["RewardType"][3006873][2] = 2
	tFestivalCardMonth_GodRewardBox["RewardType"][3006873][3] = 2
	tFestivalCardMonth_GodRewardBox["RewardType"][3006873][4] = 2
	--气力值
	tFestivalCardMonth_GodRewardBox["RewardType"][3006874] = {}
	tFestivalCardMonth_GodRewardBox["RewardType"][3006874][1] = 12
	tFestivalCardMonth_GodRewardBox["RewardType"][3006874][2] = 12
	tFestivalCardMonth_GodRewardBox["RewardType"][3006874][3] = 12
	tFestivalCardMonth_GodRewardBox["RewardType"][3006874][4] = 12
	--赠天石
	tFestivalCardMonth_GodRewardBox["RewardType"][3006875] = {}
	tFestivalCardMonth_GodRewardBox["RewardType"][3006875][1] = 3
	tFestivalCardMonth_GodRewardBox["RewardType"][3006875][2] = 3
	tFestivalCardMonth_GodRewardBox["RewardType"][3006875][3] = 3
	tFestivalCardMonth_GodRewardBox["RewardType"][3006875][4] = 3
	--龙珠
	tFestivalCardMonth_GodRewardBox["RewardType"][3006876] = {}
	tFestivalCardMonth_GodRewardBox["RewardType"][3006876][1] = 720028
	tFestivalCardMonth_GodRewardBox["RewardType"][3006876][2] = 1088000
	tFestivalCardMonth_GodRewardBox["RewardType"][3006876][3] = 1088000
	tFestivalCardMonth_GodRewardBox["RewardType"][3006876][4] = 1088000
	--流星卷
	tFestivalCardMonth_GodRewardBox["RewardType"][3006878] = {}
	tFestivalCardMonth_GodRewardBox["RewardType"][3006878][1] = 3004611
	tFestivalCardMonth_GodRewardBox["RewardType"][3006878][2] = 3004611
	tFestivalCardMonth_GodRewardBox["RewardType"][3006878][3] = 3004611
	tFestivalCardMonth_GodRewardBox["RewardType"][3006878][4] = 720027
	
----------------------奖励数量
	--天石
	tFestivalCardMonth_GodRewardBox[3006873] = {}
	tFestivalCardMonth_GodRewardBox[3006873][1] = 1000
	tFestivalCardMonth_GodRewardBox[3006873][2] = 500
	tFestivalCardMonth_GodRewardBox[3006873][3] = 100
	tFestivalCardMonth_GodRewardBox[3006873][4] = 50
	--气力值
	tFestivalCardMonth_GodRewardBox[3006874] = {}
	tFestivalCardMonth_GodRewardBox[3006874][1] = 30000
	tFestivalCardMonth_GodRewardBox[3006874][2] = 10000
	tFestivalCardMonth_GodRewardBox[3006874][3] = 5000
	tFestivalCardMonth_GodRewardBox[3006874][4] = 3000
	--赠天石
	tFestivalCardMonth_GodRewardBox[3006875] = {}
	tFestivalCardMonth_GodRewardBox[3006875][1] = 7000
	tFestivalCardMonth_GodRewardBox[3006875][2] = 5000
	tFestivalCardMonth_GodRewardBox[3006875][3] = 500
	tFestivalCardMonth_GodRewardBox[3006875][4] = 100
	--龙珠
	tFestivalCardMonth_GodRewardBox[3006876] = {}
	tFestivalCardMonth_GodRewardBox[3006876][1] = 1
	tFestivalCardMonth_GodRewardBox[3006876][2] = 5
	tFestivalCardMonth_GodRewardBox[3006876][3] = 3
	tFestivalCardMonth_GodRewardBox[3006876][4] = 2
	--赤炼石
	tFestivalCardMonth_GodRewardBox[3006877] = {}
	tFestivalCardMonth_GodRewardBox[3006877][1] = 730006
	tFestivalCardMonth_GodRewardBox[3006877][2] = 730005
	tFestivalCardMonth_GodRewardBox[3006877][3] = 730004
	tFestivalCardMonth_GodRewardBox[3006877][4] = 730003
	--流星卷
	tFestivalCardMonth_GodRewardBox[3006878] = {}
	tFestivalCardMonth_GodRewardBox[3006878][1] = 5
	tFestivalCardMonth_GodRewardBox[3006878][2] = 2
	tFestivalCardMonth_GodRewardBox[3006878][3] = 1
	tFestivalCardMonth_GodRewardBox[3006878][4] = 5

	
	
	
------------------------------------------------------------------------------------
-- 挑战恶魔获得奖励
local tFestivalCardMonth_DemonAward = {}
	-- 第一阶段
	tFestivalCardMonth_DemonAward[1] = {}
	tFestivalCardMonth_DemonAward[1][1] = {}		--对应的主神卡包（第一种奖励）
	tFestivalCardMonth_DemonAward[1][1][18579] = 3006632
	tFestivalCardMonth_DemonAward[1][1][18580] = 3006633
	tFestivalCardMonth_DemonAward[1][1][18581] = 3006634
	tFestivalCardMonth_DemonAward[1][1][18582] = 3006635
	tFestivalCardMonth_DemonAward[1][1][18583] = 3006636
	tFestivalCardMonth_DemonAward[1][1][18584] = 3006637
	tFestivalCardMonth_DemonAward[1][1][18585] = 3006638
	tFestivalCardMonth_DemonAward[1][1][18586] = 3006639
	tFestivalCardMonth_DemonAward[1][1][18587] = 3006640
	tFestivalCardMonth_DemonAward[1][1][18588] = 3006641
	tFestivalCardMonth_DemonAward[1][1][18589] = 3006642
	tFestivalCardMonth_DemonAward[1][1][18590] = 3006643
	tFestivalCardMonth_DemonAward[1][2] = {}		--对应恶魔的奖励礼包（第二种奖励）
	tFestivalCardMonth_DemonAward[1][2][18579] = 3006864
	tFestivalCardMonth_DemonAward[1][2][18580] = 3006864
	tFestivalCardMonth_DemonAward[1][2][18581] = 3006864
	tFestivalCardMonth_DemonAward[1][2][18582] = 3006867
	tFestivalCardMonth_DemonAward[1][2][18583] = 3006867
	tFestivalCardMonth_DemonAward[1][2][18584] = 3006867
	tFestivalCardMonth_DemonAward[1][2][18585] = 3006867
	tFestivalCardMonth_DemonAward[1][2][18586] = 3006870
	tFestivalCardMonth_DemonAward[1][2][18587] = 3006870
	tFestivalCardMonth_DemonAward[1][2][18588] = 3006870
	tFestivalCardMonth_DemonAward[1][2][18589] = 3006870
	tFestivalCardMonth_DemonAward[1][2][18590] = 3006870
	-- 第二阶段
	tFestivalCardMonth_DemonAward[2] = {}
	tFestivalCardMonth_DemonAward[2][1] = {}		--对应的主神卡包（第一种奖励）
	tFestivalCardMonth_DemonAward[2][1][18579] = 3006632
	tFestivalCardMonth_DemonAward[2][1][18580] = 3006633
	tFestivalCardMonth_DemonAward[2][1][18581] = 3006634
	tFestivalCardMonth_DemonAward[2][1][18582] = 3006635
	tFestivalCardMonth_DemonAward[2][1][18583] = 3006636
	tFestivalCardMonth_DemonAward[2][1][18584] = 3006637
	tFestivalCardMonth_DemonAward[2][1][18585] = 3006638
	tFestivalCardMonth_DemonAward[2][1][18586] = 3006639
	tFestivalCardMonth_DemonAward[2][1][18587] = 3006640
	tFestivalCardMonth_DemonAward[2][1][18588] = 3006641
	tFestivalCardMonth_DemonAward[2][1][18589] = 3006642
	tFestivalCardMonth_DemonAward[2][1][18590] = 3006643
	tFestivalCardMonth_DemonAward[2][2] = {}		--对应恶魔的奖励礼包（第二种奖励）
	tFestivalCardMonth_DemonAward[2][2][18579] = 3006865
	tFestivalCardMonth_DemonAward[2][2][18580] = 3006865
	tFestivalCardMonth_DemonAward[2][2][18581] = 3006865
	tFestivalCardMonth_DemonAward[2][2][18582] = 3006868
	tFestivalCardMonth_DemonAward[2][2][18583] = 3006868
	tFestivalCardMonth_DemonAward[2][2][18584] = 3006868
	tFestivalCardMonth_DemonAward[2][2][18585] = 3006868
	tFestivalCardMonth_DemonAward[2][2][18586] = 3006871
	tFestivalCardMonth_DemonAward[2][2][18587] = 3006871
	tFestivalCardMonth_DemonAward[2][2][18588] = 3006871
	tFestivalCardMonth_DemonAward[2][2][18589] = 3006871
	tFestivalCardMonth_DemonAward[2][2][18590] = 3006871
	-- 第三阶段
	tFestivalCardMonth_DemonAward[3] = {}
	tFestivalCardMonth_DemonAward[3][1] = {}		--抽卡包（第一种奖励）
	tFestivalCardMonth_DemonAward[3][1][18579] = 3006695
	tFestivalCardMonth_DemonAward[3][1][18580] = 3006695
	tFestivalCardMonth_DemonAward[3][1][18581] = 3006695
	tFestivalCardMonth_DemonAward[3][1][18582] = 3006695
	tFestivalCardMonth_DemonAward[3][1][18583] = 3006695
	tFestivalCardMonth_DemonAward[3][1][18584] = 3006695
	tFestivalCardMonth_DemonAward[3][1][18585] = 3006695
	tFestivalCardMonth_DemonAward[3][1][18586] = 3006695
	tFestivalCardMonth_DemonAward[3][1][18587] = 3006695
	tFestivalCardMonth_DemonAward[3][1][18588] = 3006695
	tFestivalCardMonth_DemonAward[3][1][18589] = 3006695
	tFestivalCardMonth_DemonAward[3][1][18590] = 3006695
	tFestivalCardMonth_DemonAward[3][2] = {}		--对应恶魔的奖励礼包（第二种奖励）
	tFestivalCardMonth_DemonAward[3][2][18579] = 3006866
	tFestivalCardMonth_DemonAward[3][2][18580] = 3006866
	tFestivalCardMonth_DemonAward[3][2][18581] = 3006866
	tFestivalCardMonth_DemonAward[3][2][18582] = 3006869
	tFestivalCardMonth_DemonAward[3][2][18583] = 3006869
	tFestivalCardMonth_DemonAward[3][2][18584] = 3006869
	tFestivalCardMonth_DemonAward[3][2][18585] = 3006869
	tFestivalCardMonth_DemonAward[3][2][18586] = 3006872
	tFestivalCardMonth_DemonAward[3][2][18587] = 3006872
	tFestivalCardMonth_DemonAward[3][2][18588] = 3006872
	tFestivalCardMonth_DemonAward[3][2][18589] = 3006872
	tFestivalCardMonth_DemonAward[3][2][18590] = 3006872


------------------------------------------------------------------------------------
--主神卡ID==神器卡ID
local tFestivalCardMonth_ArtifactCard = {}
	--宙斯
	tFestivalCardMonth_ArtifactCard[3006620] = {}
	tFestivalCardMonth_ArtifactCard[3006620][1] = 3006656
	tFestivalCardMonth_ArtifactCard[3006620][2] = 3006657
	tFestivalCardMonth_ArtifactCard[3006620][3] = 3006658
	--赫拉
	tFestivalCardMonth_ArtifactCard[3006621] = {}
	tFestivalCardMonth_ArtifactCard[3006621][1] = 3006659
	tFestivalCardMonth_ArtifactCard[3006621][2] = 3006660
	tFestivalCardMonth_ArtifactCard[3006621][3] = 3006661
	--波塞冬
	tFestivalCardMonth_ArtifactCard[3006622] = {}
	tFestivalCardMonth_ArtifactCard[3006622][1] = 3006662
	tFestivalCardMonth_ArtifactCard[3006622][2] = 3006663
	tFestivalCardMonth_ArtifactCard[3006622][3] = 3006664
	--得墨忒耳
	tFestivalCardMonth_ArtifactCard[3006623] = {}
	tFestivalCardMonth_ArtifactCard[3006623][1] = 3006665
	tFestivalCardMonth_ArtifactCard[3006623][2] = 3006666
	tFestivalCardMonth_ArtifactCard[3006623][3] = 3006667
	--雅典娜
	tFestivalCardMonth_ArtifactCard[3006624] = {}
	tFestivalCardMonth_ArtifactCard[3006624][1] = 3006668
	tFestivalCardMonth_ArtifactCard[3006624][2] = 3006669
	tFestivalCardMonth_ArtifactCard[3006624][3] = 3006670
	--阿波罗
	tFestivalCardMonth_ArtifactCard[3006625] = {}
	tFestivalCardMonth_ArtifactCard[3006625][1] = 3006671
	tFestivalCardMonth_ArtifactCard[3006625][2] = 3006672
	tFestivalCardMonth_ArtifactCard[3006625][3] = 3006673
	--阿耳忒弥斯
	tFestivalCardMonth_ArtifactCard[3006626] = {}
	tFestivalCardMonth_ArtifactCard[3006626][1] = 3006674
	tFestivalCardMonth_ArtifactCard[3006626][2] = 3006675
	tFestivalCardMonth_ArtifactCard[3006626][3] = 3006676
	--阿佛洛狄忒
	tFestivalCardMonth_ArtifactCard[3006627] = {}
	tFestivalCardMonth_ArtifactCard[3006627][1] = 3006677
	tFestivalCardMonth_ArtifactCard[3006627][2] = 3006678
	tFestivalCardMonth_ArtifactCard[3006627][3] = 3006679
	--赫耳墨斯
	tFestivalCardMonth_ArtifactCard[3006628] = {}
	tFestivalCardMonth_ArtifactCard[3006628][1] = 3006680
	tFestivalCardMonth_ArtifactCard[3006628][2] = 3006681
	tFestivalCardMonth_ArtifactCard[3006628][3] = 3006682
	--阿瑞斯
	tFestivalCardMonth_ArtifactCard[3006629] = {}
	tFestivalCardMonth_ArtifactCard[3006629][1] = 3006683
	tFestivalCardMonth_ArtifactCard[3006629][2] = 3006684
	tFestivalCardMonth_ArtifactCard[3006629][3] = 3006685
	--赫淮斯托斯
	tFestivalCardMonth_ArtifactCard[3006630] = {}
	tFestivalCardMonth_ArtifactCard[3006630][1] = 3006686
	tFestivalCardMonth_ArtifactCard[3006630][2] = 3006687
	tFestivalCardMonth_ArtifactCard[3006630][3] = 3006688
	--狄俄倪索斯
	tFestivalCardMonth_ArtifactCard[3006631] = {}
	tFestivalCardMonth_ArtifactCard[3006631][1] = 3006689
	tFestivalCardMonth_ArtifactCard[3006631][2] = 3006690
	tFestivalCardMonth_ArtifactCard[3006631][3] = 3006691

------------------------------------------------------------------------------------
--主神卡ID==主神卡碎片ID
local tFestivalCardMonth_GodPiece = {}
	tFestivalCardMonth_GodPiece[3006620] = 3006644
	tFestivalCardMonth_GodPiece[3006621] = 3006645
	tFestivalCardMonth_GodPiece[3006622] = 3006646
	tFestivalCardMonth_GodPiece[3006623] = 3006647
	tFestivalCardMonth_GodPiece[3006624] = 3006648
	tFestivalCardMonth_GodPiece[3006625] = 3006649
	tFestivalCardMonth_GodPiece[3006626] = 3006650
	tFestivalCardMonth_GodPiece[3006627] = 3006651
	tFestivalCardMonth_GodPiece[3006628] = 3006652
	tFestivalCardMonth_GodPiece[3006629] = 3006653
	tFestivalCardMonth_GodPiece[3006630] = 3006654
	tFestivalCardMonth_GodPiece[3006631] = 3006655

------------------------------------------------------------------------------------
--主神卡包对应主神卡数据
local tFestivalCardMonth_CardPag = {}
	tFestivalCardMonth_CardPag[3006632] = 3006620
	tFestivalCardMonth_CardPag[3006633] = 3006621
	tFestivalCardMonth_CardPag[3006634] = 3006622
	tFestivalCardMonth_CardPag[3006635] = 3006623
	tFestivalCardMonth_CardPag[3006636] = 3006624
	tFestivalCardMonth_CardPag[3006637] = 3006625
	tFestivalCardMonth_CardPag[3006638] = 3006626
	tFestivalCardMonth_CardPag[3006639] = 3006627
	tFestivalCardMonth_CardPag[3006640] = 3006628
	tFestivalCardMonth_CardPag[3006641] = 3006629
	tFestivalCardMonth_CardPag[3006642] = 3006630
	tFestivalCardMonth_CardPag[3006643] = 3006631
------------------------------------------------------------------------------------
--主神卡碎片对应主神卡包数据
local tFestivalCardMonth_CardPiece = {}
	tFestivalCardMonth_CardPiece[3006644] = 3006632
	tFestivalCardMonth_CardPiece[3006645] = 3006633
	tFestivalCardMonth_CardPiece[3006646] = 3006634
	tFestivalCardMonth_CardPiece[3006647] = 3006635
	tFestivalCardMonth_CardPiece[3006648] = 3006636
	tFestivalCardMonth_CardPiece[3006649] = 3006637
	tFestivalCardMonth_CardPiece[3006650] = 3006638
	tFestivalCardMonth_CardPiece[3006651] = 3006639
	tFestivalCardMonth_CardPiece[3006652] = 3006640
	tFestivalCardMonth_CardPiece[3006653] = 3006641
	tFestivalCardMonth_CardPiece[3006654] = 3006642
	tFestivalCardMonth_CardPiece[3006655] = 3006643

------------------------------------------------------------------------------------
--恶魔对应的主神卡
local tFestivalCardMonth_Demon = {}
	tFestivalCardMonth_Demon[18579] = 3006620
	tFestivalCardMonth_Demon[18580] = 3006621
	tFestivalCardMonth_Demon[18581] = 3006622
	tFestivalCardMonth_Demon[18582] = 3006623
	tFestivalCardMonth_Demon[18583] = 3006624
	tFestivalCardMonth_Demon[18584] = 3006625
	tFestivalCardMonth_Demon[18585] = 3006626
	tFestivalCardMonth_Demon[18586] = 3006627
	tFestivalCardMonth_Demon[18587] = 3006628
	tFestivalCardMonth_Demon[18588] = 3006629
	tFestivalCardMonth_Demon[18589] = 3006630
	tFestivalCardMonth_Demon[18590] = 3006631
	




------------------------------------------------------------------------------------
--活动LOG数据
local tFestivalCardMonth_Log = {}
	-- 主神卡包打开LOG
	tFestivalCardMonth_Log["CardPag_GetHoly"] = "0,0,%d,1,10002414,2,%d[%d][%d],1[1][1]"
	tFestivalCardMonth_Log["CardPag_GetGodCard"] = "0,0,%d,1,10002414,2,%d,1"
	-- 主神卡碎片合成成功
	tFestivalCardMonth_Log["CardPiece_Success"] = "0,0,%d,10,10002414,2,%d,1"
	-- 圣物卡分解成功
	tFestivalCardMonth_Log["HolyCard_Success"] = "0,0,%d,10,10002414,2,3006692,3"
	-- 获得主神卡幸运礼包
	tFestivalCardMonth_Log["GetLucyBag"] = "%d,0,0,0,10002414,2,%d,1"
	-- 补领主神卡
	tFestivalCardMonth_Log["SupGodCard1"] = "%d,0,0,0,10002414,2,%d,1"
	tFestivalCardMonth_Log["SupGodCard2"] = "0,0,0,0,10002414,2,%d,1"
	-- 已挑战完3个阶段，继续挑战守卫给奖励
	tFestivalCardMonth_Log["FightDemon"] = {}
	tFestivalCardMonth_Log["FightDemon"][1] = "0,0,0,0,10002414,2,%d,1"
	tFestivalCardMonth_Log["FightDemon"][2] = "0,0,0,0,10002414,2,%d,1"
	tFestivalCardMonth_Log["FightDemon"][3] = "0,0,0,0,10002414,2,%d,1"
	tFestivalCardMonth_Log["FightDemonPiece"] = "0,0,0,0,10002414,2,%d,%d"
	-- 挑战恶魔各阶段给奖励
	tFestivalCardMonth_Log["DemonPhase"] = "0,0,0,0,10002414,2,%d[%d],%d[1]"
	--开宝藏给奖励
	tFestivalCardMonth_Log["OpenBox_1"] = "0,0,0,0,10002414,2,3[12],%d[%d]"
	tFestivalCardMonth_Log["OpenBox_2"] = "0,0,0,0,10002414,2,12[3003126][192605],%d[%d][1]"
	tFestivalCardMonth_Log["OpenBox_3"] = "0,0,0,0,10002414,2,3000134[3003126],10[10]"
	-- 打造圣物卡
	tFestivalCardMonth_Log["CreateHoly"] = "0,0,3006692,%d,10002414,2,%d,1"
	-- A,B,C类礼包奖励
	tFestivalCardMonth_Log["OpenPackage0"] = "0,0,%d,1,10002414,2,"
	tFestivalCardMonth_Log["OpenPackage1"] = "%d,%d"
	tFestivalCardMonth_Log["OpenPackage2"] = "%d[%d],%d[%d]"
	tFestivalCardMonth_Log["OpenPackage3"] = "%d[%d][%d],%d[%d][%d]"
	-- 打开主神卡幸运礼包
	tFestivalCardMonth_Log["OpenLuckyBag"] = "0,0,3006695,1,10002414,2,%d,%d"
	-- 打开主神卡幸运连抽礼包
	tFestivalCardMonth_Log["OpenSeriesBag"] = "0,0,3006696,1,10002414,2,%d,%d"
	-- 背包信
	tFestivalCardMonth_Log["Letter"] = "0,0,3006697,1,10002414,2,%d[%d],1[%d]"
	-- 神赐宝箱
	tFestivalCardMonth_Log["GodReward"] = "0,0,%d,1,10002414,2,%d,%d"
	-- 神赐赤炼石宝箱
	tFestivalCardMonth_Log["GodStone"] = "0,0,%d,1,10002414,2,%d,1"
	-- 击杀怪物
	tFestivalCardMonth_Log["Monster"] = "0,0,0,0,10002414,2,%d,1"
	-- 活跃礼包给圣物卡
	tFestivalCardMonth_Log["ActiveBag"] = "0,0,%d,1,10002414,2,%d,1"
	tFestivalCardMonth_Log["ChiToken"] = "0,0,%d,7,10002414,2,%d,1"
	-- 删除主神卡活动修行值
	tFestivalCardMonth_Log["DelGodCard"] = "0,0,%d,1,10002414,2,6,%d"
	
	
-- 活动emoney_buy记录
local tFestivalCardMonth_EmoneyBuy = {}
	-- [1] 27天石购买挑战机会 350 20062
	-- [2] 27天石购买打造机会 350 20063
	-- [3] 27天石购买幸运礼包 350 20064
	-- [3] 270天石购买幸运连抽礼包 350 20065
	-- [4] 99天石补领主神卡 350 20066
	-- [5] 打开最后宝盒获得天石 350 20067
	-- [6] 打开最后宝盒获得赠天石 350 20068
	-- [7] 阶段奖励赠品天石 350 20069
	
	tFestivalCardMonth_EmoneyBuy["EmoneyLog1"] = "350	20062	%d	%d	1	"
	tFestivalCardMonth_EmoneyBuy["EmoneyLog2"] = "350	20063	27	27	1	"
	tFestivalCardMonth_EmoneyBuy["EmoneyLog3"] = {}
	tFestivalCardMonth_EmoneyBuy["EmoneyLog3"][27] = "350	20064	27	27	1	"
	tFestivalCardMonth_EmoneyBuy["EmoneyLog3"][270] = "350	20065	270	270	1	"
	tFestivalCardMonth_EmoneyBuy["EmoneyLog4"] = "350	20066	99	99	1	"
	tFestivalCardMonth_EmoneyBuy["EmoneyLog5"] = "350	20067	-%d	-%d	1	"
	tFestivalCardMonth_EmoneyBuy["EmoneyLog6"] = "350	20068	0	0	-%d	"
	tFestivalCardMonth_EmoneyBuy["EmoneyLog7"] = "350	20069	0	0	-%d	"

	
	
	
----------------------------------------几率配置--------------------------------------------
local tFestivalCardMonth_Probabil = {}
----【已挑战完3个阶段，继续挑战守卫的概率】
	tFestivalCardMonth_Probabil[1] = {}
	tFestivalCardMonth_Probabil[1][1] = {}
	tFestivalCardMonth_Probabil[1][1]["ItemChanceSum"] = 100
	-- 第一种神器卡（18.00%）
	tFestivalCardMonth_Probabil[1][1][1] = {}
	tFestivalCardMonth_Probabil[1][1][1]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][1][1]["ItemChance"] = 18
	tFestivalCardMonth_Probabil[1][1][1]["Item_1"] = 1
	-- 第二种神器卡（18.00%）
	tFestivalCardMonth_Probabil[1][1][2] = {}
	tFestivalCardMonth_Probabil[1][1][2]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][1][2]["ItemChance"] = 18
	tFestivalCardMonth_Probabil[1][1][2]["Item_1"] = 2
	-- 第三种神器卡（18.00%）
	tFestivalCardMonth_Probabil[1][1][3] = {}
	tFestivalCardMonth_Probabil[1][1][3]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][1][3]["ItemChance"] = 18
	tFestivalCardMonth_Probabil[1][1][3]["Item_1"] = 3
	-- 50个碎片（14.00%）
	tFestivalCardMonth_Probabil[1][1][4] = {}
	tFestivalCardMonth_Probabil[1][1][4]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][1][4]["ItemChance"] = 14
	tFestivalCardMonth_Probabil[1][1][4]["Item_1"] = 50
	-- 30个碎片（15.00%）
	tFestivalCardMonth_Probabil[1][1][5] = {}
	tFestivalCardMonth_Probabil[1][1][5]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][1][5]["ItemChance"] = 15
	tFestivalCardMonth_Probabil[1][1][5]["Item_1"] = 30
	-- 10个碎片（17.00%）
	tFestivalCardMonth_Probabil[1][1][6] = {}
	tFestivalCardMonth_Probabil[1][1][6]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][1][6]["ItemChance"] = 17
	tFestivalCardMonth_Probabil[1][1][6]["Item_1"] = 10

----【随机打造圣物卡几率】
	tFestivalCardMonth_Probabil[1][2] = {}
	tFestivalCardMonth_Probabil[1][2]["ItemChanceSum"] = 36
	-- 霹雳权杖
	tFestivalCardMonth_Probabil[1][2][1] = {}
	tFestivalCardMonth_Probabil[1][2][1]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][1]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][1]["Item_1"]  = 3006656
	-- 宙斯之盾
	tFestivalCardMonth_Probabil[1][2][2] = {}
	tFestivalCardMonth_Probabil[1][2][2]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][2]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][2]["Item_1"]  = 3006657
	-- 橄榄枝皇冠
	tFestivalCardMonth_Probabil[1][2][3] = {}
	tFestivalCardMonth_Probabil[1][2][3]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][3]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][3]["Item_1"]  = 3006658
	-- 莲花法杖
	tFestivalCardMonth_Probabil[1][2][4] = {}
	tFestivalCardMonth_Probabil[1][2][4]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][4]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][4]["Item_1"]  = 3006659
	-- 黄金王冠
	tFestivalCardMonth_Probabil[1][2][5] = {}
	tFestivalCardMonth_Probabil[1][2][5]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][5]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][5]["Item_1"]  = 3006660
	-- 圣光百合
	tFestivalCardMonth_Probabil[1][2][6] = {}
	tFestivalCardMonth_Probabil[1][2][6]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][6]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][6]["Item_1"]  = 3006661
	-- 海神之刺
	tFestivalCardMonth_Probabil[1][2][7] = {}
	tFestivalCardMonth_Probabil[1][2][7]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][7]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][7]["Item_1"]  = 3006662
	-- 潮汐光环
	tFestivalCardMonth_Probabil[1][2][8] = {}
	tFestivalCardMonth_Probabil[1][2][8]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][8]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][8]["Item_1"]  = 3006663
	-- 圣兽海豚
	tFestivalCardMonth_Probabil[1][2][9] = {}
	tFestivalCardMonth_Probabil[1][2][9]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][9]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][9]["Item_1"]  = 3006664
	-- 黄金麦穗
	tFestivalCardMonth_Probabil[1][2][10] = {}
	tFestivalCardMonth_Probabil[1][2][10]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][10]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][10]["Item_1"]  = 3006665
	-- 财富镰刀
	tFestivalCardMonth_Probabil[1][2][11] = {}
	tFestivalCardMonth_Probabil[1][2][11]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][11]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][11]["Item_1"]  = 3006666
	-- 点金杖
	tFestivalCardMonth_Probabil[1][2][12] = {}
	tFestivalCardMonth_Probabil[1][2][12]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][12]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][12]["Item_1"]  = 3006667
	-- 庇护之盾
	tFestivalCardMonth_Probabil[1][2][13] = {}
	tFestivalCardMonth_Probabil[1][2][13]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][13]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][13]["Item_1"]  = 3006668
	-- 胜利女神像
	tFestivalCardMonth_Probabil[1][2][14] = {}
	tFestivalCardMonth_Probabil[1][2][14]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][14]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][14]["Item_1"]  = 3006669
	-- 帕拉斯长矛
	tFestivalCardMonth_Probabil[1][2][15] = {}
	tFestivalCardMonth_Probabil[1][2][15]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][15]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][15]["Item_1"]  = 3006670
	-- 太阳战车
	tFestivalCardMonth_Probabil[1][2][16] = {}
	tFestivalCardMonth_Probabil[1][2][16]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][16]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][16]["Item_1"]  = 3006671
	-- 光辉之箭
	tFestivalCardMonth_Probabil[1][2][17] = {}
	tFestivalCardMonth_Probabil[1][2][17]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][17]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][17]["Item_1"]  = 3006672
	-- 天鹅竖琴
	tFestivalCardMonth_Probabil[1][2][18] = {}
	tFestivalCardMonth_Probabil[1][2][18]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][18]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][18]["Item_1"]  = 3006673
	-- 圣鹿银车
	tFestivalCardMonth_Probabil[1][2][19] = {}
	tFestivalCardMonth_Probabil[1][2][19]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][19]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][19]["Item_1"]  = 3006674
	-- 半月弓
	tFestivalCardMonth_Probabil[1][2][20] = {}
	tFestivalCardMonth_Probabil[1][2][20]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][20]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][20]["Item_1"]  = 3006675
	-- 明月之光
	tFestivalCardMonth_Probabil[1][2][21] = {}
	tFestivalCardMonth_Probabil[1][2][21]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][21]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][21]["Item_1"]  = 3006676
	-- 爱神玫瑰
	tFestivalCardMonth_Probabil[1][2][22] = {}
	tFestivalCardMonth_Probabil[1][2][22]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][22]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][22]["Item_1"]  = 3006677
	-- 爱神腰带
	tFestivalCardMonth_Probabil[1][2][23] = {}
	tFestivalCardMonth_Probabil[1][2][23]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][23]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][23]["Item_1"]  = 3006678
	-- 爱神宝镜
	tFestivalCardMonth_Probabil[1][2][24] = {}
	tFestivalCardMonth_Probabil[1][2][24]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][24]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][24]["Item_1"]  = 3006679
	-- 银翼飞鞋
	tFestivalCardMonth_Probabil[1][2][25] = {}
	tFestivalCardMonth_Probabil[1][2][25]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][25]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][25]["Item_1"]  = 3006680
	-- 双蛇魔杖
	tFestivalCardMonth_Probabil[1][2][26] = {}
	tFestivalCardMonth_Probabil[1][2][26]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][26]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][26]["Item_1"]  = 3006681
	-- 里拉琴
	tFestivalCardMonth_Probabil[1][2][27] = {}
	tFestivalCardMonth_Probabil[1][2][27]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][27]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][27]["Item_1"]  = 3006682
	-- 战神铜矛
	tFestivalCardMonth_Probabil[1][2][28] = {}
	tFestivalCardMonth_Probabil[1][2][28]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][28]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][28]["Item_1"]  = 3006683
	-- 战神火炬
	tFestivalCardMonth_Probabil[1][2][29] = {}
	tFestivalCardMonth_Probabil[1][2][29]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][29]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][29]["Item_1"]  = 3006684
	-- 战神头盔
	tFestivalCardMonth_Probabil[1][2][30] = {}
	tFestivalCardMonth_Probabil[1][2][30]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][30]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][30]["Item_1"]  = 3006685
	-- 火神之锤
	tFestivalCardMonth_Probabil[1][2][31] = {}
	tFestivalCardMonth_Probabil[1][2][31]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][31]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][31]["Item_1"]  = 3006686
	-- 火神之钳
	tFestivalCardMonth_Probabil[1][2][32] = {}
	tFestivalCardMonth_Probabil[1][2][32]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][32]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][32]["Item_1"]  = 3006687
	-- 火神之砧
	tFestivalCardMonth_Probabil[1][2][33] = {}
	tFestivalCardMonth_Probabil[1][2][33]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][33]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][33]["Item_1"]  = 3006688
	-- 葡萄藤
	tFestivalCardMonth_Probabil[1][2][34] = {}
	tFestivalCardMonth_Probabil[1][2][34]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][34]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][34]["Item_1"]  = 3006689
	-- 酒神杖
	tFestivalCardMonth_Probabil[1][2][35] = {}
	tFestivalCardMonth_Probabil[1][2][35]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][35]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][35]["Item_1"]  = 3006690
	-- 双耳酒杯
	tFestivalCardMonth_Probabil[1][2][36] = {}
	tFestivalCardMonth_Probabil[1][2][36]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][2][36]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][2][36]["Item_1"]  = 3006691


----【主神卡碎片几率】
	tFestivalCardMonth_Probabil[1][3] = {}
	tFestivalCardMonth_Probabil[1][3]["ItemChanceSum"] = 12
	tFestivalCardMonth_Probabil[1][3][1] = {}
	tFestivalCardMonth_Probabil[1][3][2] = {}
	tFestivalCardMonth_Probabil[1][3][3] = {}
	tFestivalCardMonth_Probabil[1][3][4] = {}
	tFestivalCardMonth_Probabil[1][3][5] = {}
	tFestivalCardMonth_Probabil[1][3][6] = {}
	tFestivalCardMonth_Probabil[1][3][7] = {}
	tFestivalCardMonth_Probabil[1][3][8] = {}
	tFestivalCardMonth_Probabil[1][3][9] = {}
	tFestivalCardMonth_Probabil[1][3][10] = {}
	tFestivalCardMonth_Probabil[1][3][11] = {}
	tFestivalCardMonth_Probabil[1][3][12] = {}
	tFestivalCardMonth_Probabil[1][3][1]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][3][2]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][3][3]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][3][4]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][3][5]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][3][6]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][3][7]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][3][8]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][3][9]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][3][10]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][3][11]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][3][12]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][3][1]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][3][2]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][3][3]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][3][4]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][3][5]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][3][6]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][3][7]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][3][8]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][3][9]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][3][10]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][3][11]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][3][12]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][3][1]["Item_1"]  = 3006644
	tFestivalCardMonth_Probabil[1][3][2]["Item_1"]  = 3006645
	tFestivalCardMonth_Probabil[1][3][3]["Item_1"]  = 3006646
	tFestivalCardMonth_Probabil[1][3][4]["Item_1"]  = 3006647
	tFestivalCardMonth_Probabil[1][3][5]["Item_1"]  = 3006648
	tFestivalCardMonth_Probabil[1][3][6]["Item_1"]  = 3006649
	tFestivalCardMonth_Probabil[1][3][7]["Item_1"]  = 3006650
	tFestivalCardMonth_Probabil[1][3][8]["Item_1"]  = 3006651
	tFestivalCardMonth_Probabil[1][3][9]["Item_1"]  = 3006652
	tFestivalCardMonth_Probabil[1][3][10]["Item_1"] = 3006653
	tFestivalCardMonth_Probabil[1][3][11]["Item_1"] = 3006654
	tFestivalCardMonth_Probabil[1][3][12]["Item_1"] = 3006655


----【主神卡幸运(连抽)礼包】
	tFestivalCardMonth_Probabil[1][4] = {}
	tFestivalCardMonth_Probabil[1][4]["ItemChanceSum"] = 10000
	-- 主神卡礼包
	tFestivalCardMonth_Probabil[1][4][1] = {}
	tFestivalCardMonth_Probabil[1][4][1]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][4][1]["ItemChance"] = 900
	tFestivalCardMonth_Probabil[1][4][1]["Item_1"] = "GodCard"
	-- 主神卡碎片
	tFestivalCardMonth_Probabil[1][4][2] = {}
	tFestivalCardMonth_Probabil[1][4][2]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][4][2]["ItemChance"] = 1800
	tFestivalCardMonth_Probabil[1][4][2]["Item_1"] = "CardPiece"
	-- 圣物卡
	tFestivalCardMonth_Probabil[1][4][3] = {}
	tFestivalCardMonth_Probabil[1][4][3]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][4][3]["ItemChance"] = 3600
	tFestivalCardMonth_Probabil[1][4][3]["Item_1"] = "HolyCard"
	-- 圣物卡碎片50个
	tFestivalCardMonth_Probabil[1][4][4] = {}
	tFestivalCardMonth_Probabil[1][4][4]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][4][4]["ItemChance"] = 1150
	tFestivalCardMonth_Probabil[1][4][4]["Item_1"] = 50
	-- 圣物卡碎片30个
	tFestivalCardMonth_Probabil[1][4][5] = {}
	tFestivalCardMonth_Probabil[1][4][5]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][4][5]["ItemChance"] = 1250
	tFestivalCardMonth_Probabil[1][4][5]["Item_1"] = 30
	-- 圣物卡碎片30个
	tFestivalCardMonth_Probabil[1][4][6] = {}
	tFestivalCardMonth_Probabil[1][4][6]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][4][6]["ItemChance"] = 1300
	tFestivalCardMonth_Probabil[1][4][6]["Item_1"] = 10


----【神赐宝箱几率】
	tFestivalCardMonth_Probabil[1][5] = {}
	tFestivalCardMonth_Probabil[1][5]["ItemChanceSum"] = 10000
	-- 1000点	0.01%
	tFestivalCardMonth_Probabil[1][5][1] = {}
	tFestivalCardMonth_Probabil[1][5][1]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][5][1]["ItemChance"] = 1
	tFestivalCardMonth_Probabil[1][5][1]["Item_1"] = 1
	-- 500点	4.99%
	tFestivalCardMonth_Probabil[1][5][2] = {}
	tFestivalCardMonth_Probabil[1][5][2]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][5][2]["ItemChance"] = 499
	tFestivalCardMonth_Probabil[1][5][2]["Item_1"] = 2
	-- 100点	15.00%
	tFestivalCardMonth_Probabil[1][5][3] = {}
	tFestivalCardMonth_Probabil[1][5][3]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][5][3]["ItemChance"] = 1500
	tFestivalCardMonth_Probabil[1][5][3]["Item_1"] = 3
	-- 50点		80.00%
	tFestivalCardMonth_Probabil[1][5][4] = {}
	tFestivalCardMonth_Probabil[1][5][4]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][5][4]["ItemChance"] = 8000
	tFestivalCardMonth_Probabil[1][5][4]["Item_1"] = 4


----【宝藏守护者几率】
	tFestivalCardMonth_Probabil[1][6] = {}
	tFestivalCardMonth_Probabil[1][6]["ItemChanceSum"] = 100
	-- 神赐天石宝箱	10%
	tFestivalCardMonth_Probabil[1][6][1] = {}
	tFestivalCardMonth_Probabil[1][6][1]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][6][1]["ItemChance"] = 10
	tFestivalCardMonth_Probabil[1][6][1]["Item_1"] = 3006873
	-- 神赐气力值宝箱	25%
	tFestivalCardMonth_Probabil[1][6][2] = {}
	tFestivalCardMonth_Probabil[1][6][2]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][6][2]["ItemChance"] = 25
	tFestivalCardMonth_Probabil[1][6][2]["Item_1"] = 3006874
	-- 神赐天石宝箱（赠）	25%
	tFestivalCardMonth_Probabil[1][6][3] = {}
	tFestivalCardMonth_Probabil[1][6][3]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][6][3]["ItemChance"] = 25
	tFestivalCardMonth_Probabil[1][6][3]["Item_1"] = 3006875
	-- 神赐龙珠宝箱		10%
	tFestivalCardMonth_Probabil[1][6][4] = {}
	tFestivalCardMonth_Probabil[1][6][4]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][6][4]["ItemChance"] = 10
	tFestivalCardMonth_Probabil[1][6][4]["Item_1"] = 3006876
	-- 神赐赤炼石宝箱	10%
	tFestivalCardMonth_Probabil[1][6][5] = {}
	tFestivalCardMonth_Probabil[1][6][5]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][6][5]["ItemChance"] = 10
	tFestivalCardMonth_Probabil[1][6][5]["Item_1"] = 3006877
	-- 神赐流星卷宝箱	20%
	tFestivalCardMonth_Probabil[1][6][6] = {}
	tFestivalCardMonth_Probabil[1][6][6]["RandomItemChanceType"] = 2
	tFestivalCardMonth_Probabil[1][6][6]["ItemChance"] = 20
	tFestivalCardMonth_Probabil[1][6][6]["Item_1"] = 3006878


---------------------------------------NPC函数---------------------------------------------

--传送逻辑
function FestivalCardMonth_ChgMap(nNpcId)
	local nMapId = tFestivalCardMonth_Data[nNpcId]["MapId"]
	local nPosX = tFestivalCardMonth_Data[nNpcId]["PosX"]
	local nPosY = tFestivalCardMonth_Data[nNpcId]["PosY"]
	local nBoundX = tFestivalCardMonth_Data[nNpcId]["BoundX"]
	local nBoundY = tFestivalCardMonth_Data[nNpcId]["BoundY"]
	
	--将玩家传送到地图的指定区域
	User_UserRandBoundTrans(nMapId,nPosX,nPosY,nBoundX,nBoundY)
	User_TalkChannel2005(tFestivalCardMonth_Text[nNpcId]["ChgMap"])
end

-- 寻路函数
function FestivalCardMonth_FindWay(nObject)
	local nPosX = tFestivalCardMonth_Data[nObject]["PosX"]
	local nPosY = tFestivalCardMonth_Data[nObject]["PosY"]
	local nMapId = tFestivalCardMonth_Data[nObject]["MapId"]
	local nNpcId = tFestivalCardMonth_Data[nObject]["NpcId"]
	
	Sys_GotoSomeWhere(nPosX,nPosY,nMapId,nNpcId)
end

-- 多用掩码处理函数
function FestivalCardMonth_MultiStc(nPlaceNum)
	local nEventData_9 = tFestivalCardMonth_Stc[9]["EventData"]
	local nTypeData_9 = tFestivalCardMonth_Stc[9]["TypeData"]
	local nStcValue_9 = Get_UserStatisticValue(nEventData_9,nTypeData_9)
	local nPlaceValue_9 = tFestivalCardMonth_Stc[9]["Place"][nPlaceNum]
	local nMathValue = math.floor(nStcValue_9 / nPlaceValue_9) % 10

	--是否完成
	if nMathValue == 0 then
		Task_AddStatistic(nEventData_9,nTypeData_9,nPlaceValue_9,1)
		return true
	else
		return false
	end
end


--网页链接
function FestivalCardMonth_WebLink()
	local sWebAddress = tFestivalCardMonth_Data["WebLink"]
	User_SendWebPage(sWebAddress)
end


-- 活跃礼包给圣物卡
function FestivalCardMonth_ActiveBag(nItemId)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		return
	end

	--玩家等级判断
	if not User_JudgeLevelAndMetempsychosis(tFestivalCardMonth_Data["MinLevel"],tFestivalCardMonth_Data["MinMeto"]) then
		return
	end
	
	local flat,tItem = Probabil_RandomAward(tFestivalCardMonth_Probabil[1],2)
	local nNewItemId = tItem[1]["tAward"][1]["Item_1"]
	
	-- 给圣物卡
	Item_AddItem(nNewItemId)
	
	-- 提示
	local sItemName = Get_ItemtypeName(nNewItemId)
	local sLogText = string.format(tFestivalCardMonth_Log["ActiveBag"],nItemId,nNewItemId)
	
	-- 为正气令
	if nItemId == tFestivalCardMonth_Data["ChiToken"] then
		sLogText = string.format(tFestivalCardMonth_Log["ChiToken"],nItemId,nNewItemId)
	end
	
	local sTalkText = string.format(tFestivalCardMonth_Text["ActiveBag"],sItemName)
	Sys_SaveActionFestivalLog(sLogText)
	User_TalkChannel2005(sTalkText)
end



---------------------------------------NPC-奥林匹斯神使-逻辑---------------------------------------------
--【进入奥林匹斯山。】
function FestivalCardMonth_EnterMap(nNpcId)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end

	--玩家等级判断
	if not User_JudgeLevelAndMetempsychosis(tFestivalCardMonth_Data["MinLevel"],tFestivalCardMonth_Data["MinMeto"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	--进入奥林匹斯山
	FestivalCardMonth_ChgMap(nNpcId)
end


-- 【查询当前活动积分】
function FestivalCardMonth_ViewPoints(nNpcId)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	-- 玩家等级判断
	-- if not User_JudgeLevelAndMetempsychosis(tFestivalCardMonth_Data["MinLevel"],tFestivalCardMonth_Data["MinMeto"]) then
		-- LinkNpcGossipFunc_New(nNpcId,"3-1")
		-- return
	-- end
	
	local nPoints = Get_UserStatisticValue(tFestivalCardMonth_Stc[1]["EventData"],tFestivalCardMonth_Stc[1]["TypeData"])
	tNpcGossip[18577]["Text311"] = string.format(tFestivalCardMonth_Text[18577]["Text311"],nPoints)
	LinkNpcGossipFunc_New(nNpcId,"3-1")
end

-- 确认购买
function FestivalCardMonth_LucyBagConf(nNpcId,nItemId,nBagEMoney,sItemName)

	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	--判断背包空间
	if not User_CheckLeftSpace(tFestivalCardMonth_Data["ChkSpace1"]) then
		LinkNpcGossipFunc_New(nNpcId,"4-4")
		return
	end
	
	--天石不足
	local nEMoney = Get_UserEMoney()
	if nEMoney < nBagEMoney then
		LinkNpcGossipFunc_New(nNpcId,"4-3")
		return
	end

	--获得主神卡幸运礼包
	if User_AddEMoney(-nBagEMoney) then
		local sLogText = string.format(tFestivalCardMonth_Log["GetLucyBag"],nBagEMoney,nItemId)
		local sTalkText = string.format(tFestivalCardMonth_Text["LucyBagSuccess"],sItemName)
		Item_AddItem(nItemId)
		User_EffectAdd(tFestivalCardMonth_Data["EffectObj"],tFestivalCardMonth_Data["Effect_1"])
		Sys_SaveActionFestivalLog(sLogText)
		Sys_SaveEmoneyBuy(tFestivalCardMonth_EmoneyBuy["EmoneyLog3"][nBagEMoney])
		User_TalkChannel2005(sTalkText)
		LinkNpcGossipFunc_New(nNpcId,"4-1")
	end
end


-- 【主神卡幸运礼包（27天石）】
function FestivalCardMonth_GodLucyBag(nNpcId,nNum)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end

	-- 玩家等级判断
	if not User_JudgeLevelAndMetempsychosis(tFestivalCardMonth_Data["MinLevel"],tFestivalCardMonth_Data["MinMeto"]) then
		LinkNpcGossipFunc_New(nNpcId,"4-2")
		return
	end
	
	--天石不足
	local nEMoney = Get_UserEMoney()
	local nBagEMoney = tFestivalCardMonth_Data["LucyBagEMoney"][nNum]
	
	if nEMoney < nBagEMoney then
		LinkNpcGossipFunc_New(nNpcId,"4-3")
		return
	end
	
	--判断背包空间
	if not User_CheckLeftSpace(tFestivalCardMonth_Data["ChkSpace1"]) then
		LinkNpcGossipFunc_New(nNpcId,"4-4")
		return
	end
	
	--二次确认
	local nItemId = tFestivalCardMonth_Data["LucyBagId"][nNum]
	local sItemName = Get_ItemtypeName(nItemId)

	tNpcGossip[18577]["Text451"] = string.format(tFestivalCardMonth_Text[18577]["Text451"],nBagEMoney,sItemName)
	tNpcGossip[18577]["OptionFunc46"] = string.format("FestivalCardMonth_LucyBagConf</N>%d</N>%d</N>%d</S>%s",nNpcId,nItemId,nBagEMoney,sItemName)
	LinkNpcGossipFunc_New(nNpcId,"4-5")
end


--确认补领
function FestivalCardMonth_SupCardSure(nNpcId,nItemId,nEMoney,sItemName)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	--判断背包空间
	if not User_CheckLeftSpace(tFestivalCardMonth_Data["ChkSpace1"]) then
		LinkNpcGossipFunc_New(nNpcId,"5-4")
		return
	end
	
	local sLogText = ""
	--是否用天石补领
	if nEMoney ~= 0 then
		local nUserEMoney = Get_UserEMoney()
		--超过限制次数--天石不足
		if nUserEMoney < nEMoney then
			LinkNpcGossipFunc_New(nNpcId,"5-7")
			return
		end
	
		--扣除天石
		if User_AddEMoney(-nEMoney) then
			Sys_SaveEmoneyBuy(tFestivalCardMonth_EmoneyBuy["EmoneyLog4"])
			sLogText = string.format(tFestivalCardMonth_Log["SupGodCard1"],nEMoney,nItemId)
		end
	else
		sLogText = string.format(tFestivalCardMonth_Log["SupGodCard2"],nItemId)
	end
	
	local nEventData_7 = tFestivalCardMonth_Stc[7]["EventData"]
	local nTypeData_7 = tFestivalCardMonth_Stc[7]["TypeData"]
	local nAddValue_7 = tFestivalCardMonth_Stc[7]["AddValue"]
	Task_AddStatistic(nEventData_7,nTypeData_7,nAddValue_7,1)
	Item_AddItem(nItemId)
	local sTalkText = string.format(tFestivalCardMonth_Text["SupCardConfSuccess"],sItemName)
	Sys_SaveActionFestivalLog(sLogText)
	User_TalkChannel2005(sTalkText)
end


-- 【补领主神卡。】
function FestivalCardMonth_SupGodCard(nNpcId,nItemId)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	-- 玩家等级判断
	if not User_JudgeLevelAndMetempsychosis(tFestivalCardMonth_Data["MinLevel"],tFestivalCardMonth_Data["MinMeto"]) then
		LinkNpcGossipFunc_New(nNpcId,"5-3")
		return
	end
	
	--判断背包空间
	if not User_CheckLeftSpace(tFestivalCardMonth_Data["ChkSpace1"]) then
		LinkNpcGossipFunc_New(nNpcId,"5-4")
		return
	end
	
	--未拥有该主神卡
	local nEventData_2 = tFestivalCardMonth_Stc[2][nItemId]["EventData"]
	local nTypeData_2 = tFestivalCardMonth_Stc[2][nItemId]["TypeData"]
	local nValue_2 = tFestivalCardMonth_Stc[2]["Value"]
	if not Task_ChkStcValue(nEventData_2,nTypeData_2,">=",nValue_2) then
		LinkNpcGossipFunc_New(nNpcId,"5-5")
		return
	end
	
	--包裹内已有该主神卡
	if Item_ChkItem(nItemId) then
		LinkNpcGossipFunc_New(nNpcId,"5-6")
		return
	end
	
	--免费领取次数判断
	local nEventData_7 = tFestivalCardMonth_Stc[7]["EventData"]
	local nTypeData_7 = tFestivalCardMonth_Stc[7]["TypeData"]
	local nComplete_7 = tFestivalCardMonth_Stc[7]["Complete"]
	local sItemName = Get_ItemtypeName(nItemId)
	local sTextNum = ""
	local nEMoney = 0
	if Task_ChkStcValue(nEventData_7,nTypeData_7,">=",nComplete_7) then
		local nUserEMoney = Get_UserEMoney()
		--超过限制次数--天石不足
		if nUserEMoney < nEMoney then
			LinkNpcGossipFunc_New(nNpcId,"5-7")
			return
		end
		sTextNum = "5-9"
		tNpcGossip[18577]["Text591"] = string.format(tFestivalCardMonth_Text[18577]["Text591"],sItemName)
		nEMoney = tFestivalCardMonth_Data["SupGodCardEMoney"]
	--未超过限制次数
	else
		sTextNum = "5-8"
		tNpcGossip[18577]["Text581"] = string.format(tFestivalCardMonth_Text[18577]["Text581"],sItemName)
	end
	
	--二次确认
	local sFunc = string.format("FestivalCardMonth_SupCardSure</N>%d</N>%d</N>%d</S>%s",nNpcId,nItemId,nEMoney,sItemName)
	tNpcGossip[18577]["OptionFunc581"] = sFunc
	LinkNpcGossipFunc_New(nNpcId,sTextNum)
end


---------------------------------------NPC-奥林匹斯的宝藏-逻辑---------------------------------------------
-- 领取解封宝藏
function FestivalCardMonth_OpenGodBox(nNpcId)
	-- 活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-1")
		return
	end
	
	local nEventData_11 = tFestivalCardMonth_Stc[11]["EventData"]
	local nTypeData_11 = tFestivalCardMonth_Stc[11]["TypeData"]
	local nComplete_11 = tFestivalCardMonth_Stc[11]["Complete"]
	
	--是否所有宝藏已领取
	if Task_ChkStcValue(nEventData_11,nTypeData_11,">=",nComplete_11) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	local nStcValue_11 = Get_UserStatisticValue(nEventData_11,nTypeData_11)
	local nEventData_10 = tFestivalCardMonth_Stc[10]["EventData"]
	local nTypeData_10 = tFestivalCardMonth_Stc[10]["TypeData"]
	local nPhase = tFestivalCardMonth_Stc[10]["Phase"][nStcValue_11 + 1]
	
	-- 判断是否击败3\6\9\12个恶魔
	if not Task_ChkStcValue(nEventData_10,nTypeData_10,">=",nPhase) then
		local nDemonNum = Get_UserStatisticValue(nEventData_10,nTypeData_10)
		tNpcGossip[nNpcId]["Text141"] = string.format(tFestivalCardMonth_Text[nNpcId]["Text141"],nPhase)
		tNpcGossip[nNpcId]["Text142"] = string.format(tFestivalCardMonth_Text[nNpcId]["Text142"],nDemonNum)
		LinkNpcGossipFunc_New(nNpcId,"1-4")
		return
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(tFestivalCardMonth_Data["ChkSpace2"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-5")
		return
	end

	-- 3\6\9个恶魔给奖励
	local nPhaseTop = tFestivalCardMonth_Stc[10]["Phase"][4]
	if nPhaseTop > nPhase then
		local nMonoEMoney = tFestivalCardMonth_OpenBox["MonoEMoney"][nStcValue_11 + 1]
		local nStrengthValue = tFestivalCardMonth_OpenBox["Strength"][nStcValue_11 + 1]
		local nUserMonoEMoney = Get_UserMonoEMoney()
		local nLimit = tFestivalCardMonth_Data["EMonoMoneyTop"] - nMonoEMoney
		
		-- 点天石上限判断
		if nUserMonoEMoney > nLimit then
			LinkNpcGossipFunc_New(nNpcId,"1-6")
			return
		end
		
		-- 置掩码+给奖励
		local nAddValue_11 = tFestivalCardMonth_Stc[11]["AddValue"]
		Task_AddStatistic(nEventData_11,nTypeData_11,nAddValue_11,1)
		User_AddEMoneyMono(nMonoEMoney)
		Sys_SaveEmoneyBuy(string.format(tFestivalCardMonth_EmoneyBuy["EmoneyLog7"],nMonoEMoney))
		User_AddStrengthValue(nStrengthValue)
		
		local sLogText = string.format(tFestivalCardMonth_Log["OpenBox_1"],nMonoEMoney,nStrengthValue)
		User_EffectAdd(tFestivalCardMonth_Data["EffectObj"],tFestivalCardMonth_Data["Effect_3"])
		Sys_SaveActionFestivalLog(sLogText)
		tNpcGossip[nNpcId]["Text171"] = string.format(tFestivalCardMonth_Text[nNpcId]["Text171"],nPhase,nPhase/3,nMonoEMoney,nStrengthValue)
		LinkNpcGossipFunc_New(nNpcId,"1-7")

	-- 12个恶魔给奖励
	else
		local nDynaGlobalData0 = Get_SysDynaGlobalData0(tFestivalCardMonth_DynaGlobal[1])
		-- local nDynaGlobalData1 = Get_SysDynaGlobalData1(tFestivalCardMonth_DynaGlobal[1])
		local nRankNum = nDynaGlobalData0 + 1
		local nRankTop = #tFestivalCardMonth_OpenBox["Integral"]
		local nEventData_1 = tFestivalCardMonth_Stc[1]["EventData"]
		local nTypeData_1 = tFestivalCardMonth_Stc[1]["TypeData"]

		--是否10名以内
		local sUserName = Get_UserName()
		local sBroadText = string.format(tFestivalCardMonth_Text[18578]["GongGao"],sUserName,nRankNum)
		if nRankTop > nRankNum then
			local nStcAdd_1 = tFestivalCardMonth_OpenBox["Integral"][nRankNum]
			local nStrengthValue = tFestivalCardMonth_OpenBox["AllStrength"][nRankNum]
			local nItemId_1 = tFestivalCardMonth_OpenBox["STPillId"]
			local nItemNum_1 = tFestivalCardMonth_OpenBox["STPill"][nRankNum]
			local nItemId_2 = tFestivalCardMonth_OpenBox["CoatId"]
			local nSavetime_2 = tFestivalCardMonth_OpenBox["CoatTime"][nRankNum]
			
			-- 加积分
			Task_AddStatistic(nEventData_1,nTypeData_1,nStcAdd_1,1)
			--解封次数
			Task_AddStatistic(nEventData_11,nTypeData_11,tFestivalCardMonth_Stc[11]["AddValue"],1)
			User_AddStrengthValue(nStrengthValue)
			Item_AddItem(nItemId_1,0,nItemNum_1,3)
			Item_AddItem(nItemId_2,0,0,3,nSavetime_2)
			local sLogText = string.format(tFestivalCardMonth_Log["OpenBox_2"],nStrengthValue,nItemNum_1)
			local nSaveDay = nSavetime_2 / tFestivalCardMonth_OpenBox["Change"]
			User_EffectAdd(tFestivalCardMonth_Data["EffectObj"],tFestivalCardMonth_Data["Effect_5"])
			Sys_TalkBroadcast(sBroadText)
			Sys_SaveActionFestivalLog(sLogText)
			tNpcGossip[nNpcId]["Text181"] = string.format(tFestivalCardMonth_Text[nNpcId]["Text181"],nRankNum,nStrengthValue,nItemNum_1,nSaveDay,nStcAdd_1)
			LinkNpcGossipFunc_New(nNpcId,"1-8")
		--10名以外
		else
			local nStcAdd_1 = tFestivalCardMonth_OpenBox["Integral"][11]
			-- 加积分
			Task_AddStatistic(nEventData_1,nTypeData_1,nStcAdd_1,1)
			--解封次数
			Task_AddStatistic(nEventData_11,nTypeData_11,tFestivalCardMonth_Stc[11]["AddValue"],1)
			local nItemId_1 = tFestivalCardMonth_OpenBox["VitalPillId"]
			local nItemId_2 = tFestivalCardMonth_OpenBox["STPillId"]
			local nItemNum = tFestivalCardMonth_OpenBox["TenUnder"]
			Item_AddItem(nItemId_1,0,0,3)
			Item_AddItem(nItemId_2,0,nItemNum,3)
			User_EffectAdd(tFestivalCardMonth_Data["EffectObj"],tFestivalCardMonth_Data["Effect_5"])
			Sys_TalkBroadcast(sBroadText)
			Sys_SaveActionFestivalLog(tFestivalCardMonth_Log["OpenBox_3"])
			tNpcGossip[nNpcId]["Text191"] = string.format(tFestivalCardMonth_Text[nNpcId]["Text191"],nRankNum)
			LinkNpcGossipFunc_New(nNpcId,"1-9")
		end
		Sys_SetSynaGlobalData0(tFestivalCardMonth_DynaGlobal[1],nDynaGlobalData0+1)
		-- Sys_SetSynaGlobalData1(tFestivalCardMonth_DynaGlobal[1],nRankNum)
	end
end


-- 进入奥林匹斯之心
function FestivalCardMonth_IntoMap(nNpcId)
	-- 活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-1")
		return
	end
	
	local nEventData_10 = tFestivalCardMonth_Stc[10]["EventData"]
	local nTypeData_10 = tFestivalCardMonth_Stc[10]["TypeData"]
	local nComplete_10 = tFestivalCardMonth_Stc[10]["Phase"][4]
	-- 是否击败所有恶魔
	if not Task_ChkStcValue(nEventData_10,nTypeData_10,">=",nComplete_10) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	-- 是否已击杀8只守卫
	local nEventData_12 = tFestivalCardMonth_Stc[12]["EventData"]
	local nTypeData_12 = tFestivalCardMonth_Stc[12]["TypeData"]
	local nComplete_12 = tFestivalCardMonth_Stc[12]["Complete"]
	if Task_ChkStcValue(nEventData_12,nTypeData_12,">=",nComplete_12) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end

	-- 成功进入奥林匹斯之心
	FestivalCardMonth_ChgMap(nNpcId)
end

---------------------------------------NPC-万妖之祖堤丰-逻辑---------------------------------------------
-- 成功执行挑战函数
function FestivalCardMonth_FightSuc(nNpcId,nActNpcId,nFightNum)
	local nEventData_4 = tFestivalCardMonth_Stc[4][nActNpcId]["EventData"]
	local nTypeData_4 = tFestivalCardMonth_Stc[4][nActNpcId]["TypeData"]
	local nComplete_4 = tFestivalCardMonth_Stc[4]["Complete"]
	local nEventData_6 = tFestivalCardMonth_Stc[6]["EventData"]
	local nTypeData_6 = tFestivalCardMonth_Stc[6]["TypeData"]
	local nSubValue_6 = tFestivalCardMonth_Stc[6]["SubValue"]
	local nComplete_6 = tFestivalCardMonth_Stc[6]["Complete"]
	local sNpcName = Get_NpcName(nActNpcId)
	local sLogText = ""
	local nMapId = tFestivalCardMonth_Data["EffectMap"]
	local nPosX = Get_NpcPositionX(nActNpcId)
	local nPosY = Get_NpcPositionY(nActNpcId)
	
	--是否有免费挑战次数
	if not Task_ChkStcValue(nEventData_6,nTypeData_6,"==",nComplete_6) then
		--免费挑战次数-1
		Task_AddStatistic(nEventData_6,nTypeData_6,nSubValue_6,1)
	end

	-- 完成3个阶段挑战
	if Task_ChkStcValue(nEventData_4,nTypeData_4,">=",nComplete_4) then

		--完成3个阶段挑战，随机给相应奖励
		local flat,tItem = Probabil_RandomAward(tFestivalCardMonth_Probabil[1],1)
		local nAwardNum = tItem[1]["tAward"][1]["Item_1"]
		local nGodCardId = tFestivalCardMonth_Demon[nActNpcId]
		local nItemId = 0
		local nItemNum = 1
		local sLogText = ""
		
		-- 给的是圣物卡碎片
		if nAwardNum > #tFestivalCardMonth_ArtifactCard[nGodCardId] then
			nItemId = tFestivalCardMonth_Data["PieceId"]
			nItemNum = nAwardNum
			sLogText = string.format(tFestivalCardMonth_Log["FightDemonPiece"],nItemId,nAwardNum)
		-- 给神器卡
		else
			nItemId = tFestivalCardMonth_ArtifactCard[nGodCardId][nAwardNum]
			sLogText = string.format(tFestivalCardMonth_Log["FightDemon"][nAwardNum],nItemId)
		end
		
		local sItemName = Get_ItemtypeName(nItemId)
		--给奖励
		Item_AddItem(nItemId,0,nItemNum)
		User_EffectAdd(tFestivalCardMonth_Data["EffectObj"],tFestivalCardMonth_Data["Effect_3"])
		tNpcGossip[18579]["Text171"] = string.format(tFestivalCardMonth_Text[18579]["Text171"],sNpcName,nItemNum,sItemName)
	
	--未完成3个阶段
	else 
		local nItemId_1 = 0
		local nItemId_2 = 0
		local nAddNum = 0
		
		--确定是哪个阶段
		for nPhase = 1, tFestivalCardMonth_Stc[4]["PhaseNum"] do
			if Task_ChkStcValue(nEventData_4,nTypeData_4,"==",nPhase) then
			
				--给奖励
				nItemId_1 = tFestivalCardMonth_DemonAward[nPhase][1][nActNpcId]
				nItemId_2 = tFestivalCardMonth_DemonAward[nPhase][2][nActNpcId]
				nAddNum = nPhase
			end
		end
		
		--恶魔血量减
		local nGodCardId = tFestivalCardMonth_Demon[nActNpcId]
		local nEventData_3 = tFestivalCardMonth_Stc[3][nGodCardId]["EventData"]
		local nTypeData_3 = tFestivalCardMonth_Stc[3][nGodCardId]["TypeData"]
		local nEventData_5 = tFestivalCardMonth_Stc[5][nActNpcId]["EventData"]
		local nTypeData_5 = tFestivalCardMonth_Stc[5][nActNpcId]["TypeData"]
		local nStcValue_3 = Get_UserStatisticValue(nEventData_3,nTypeData_3) * nFightNum
		-- 血量低于攻击力
		if Task_ChkStcValue(nEventData_5,nTypeData_5,">=",nStcValue_3) then
			Task_AddStatistic(nEventData_5,nTypeData_5,-nStcValue_3,1)
		else
			Task_SetStatistic(nEventData_5,nTypeData_5,0,1)
		end
		
		-- 血量为0调整挑战阶段
		if not Task_ChkStcValue(nEventData_5,nTypeData_5,">",0) then
			
			-- 调整挑战阶段
			local nEventData_1 = tFestivalCardMonth_Stc[1]["EventData"]
			local nTypeData_1 = tFestivalCardMonth_Stc[1]["TypeData"]
			local nStcAdd_1 = tFestivalCardMonth_Data["DemonPoint"][nAddNum]
			local nAddValue_4 = tFestivalCardMonth_Stc[4]["AddValue"]
			
			-- 击败恶魔
			if nAddNum >= 3 then
				local nEventData_10 = tFestivalCardMonth_Stc[10]["EventData"]
				local nTypeData_10 = tFestivalCardMonth_Stc[10]["TypeData"]
				local nAddValue_10 = tFestivalCardMonth_Stc[10]["AddValue"]
				Task_AddStatistic(nEventData_10,nTypeData_10,nAddValue_10,1)
			end
			
			Task_AddStatistic(nEventData_4,nTypeData_4,nAddValue_4,1)
			Task_AddStatistic(nEventData_1,nTypeData_1,nStcAdd_1,1)
			
			-- 给奖励
			Item_AddItem(nItemId_1,0,nAddNum)
			Item_AddItem(nItemId_2)
			User_EffectAdd(tFestivalCardMonth_Data["EffectObj"],tFestivalCardMonth_Data["Effect_3"])
			sLogText = string.format(tFestivalCardMonth_Log["DemonPhase"],nItemId_1,nItemId_2,nAddNum)
			local sItemName1 = Get_ItemtypeName(nItemId_1)
			local sItemName2 = Get_ItemtypeName(nItemId_2)
			local sGodCardId = tFestivalCardMonth_Demon[nNpcId]
			local sGodCardName = Get_ItemtypeName(sGodCardId)
			local sUserName = Get_UserName()
			local sText172 = string.format(tFestivalCardMonth_Text[18579]["Text172"],sItemName1,sItemName2,nStcAdd_1)
			local sBroadText = string.format(tFestivalCardMonth_Text[18579]["GongGao"],sUserName,sGodCardName,nAddNum,sNpcName)
			Sys_TalkBroadcast(sBroadText)
			tNpcGossip[18579]["Text171"] = string.format(tFestivalCardMonth_Text[18579]["Text171"],sNpcName,nAddNum,sText172)
		
		else
			--血量未降为0时
			local nDemonHP_5 = Get_UserStatisticValue(nEventData_5,nTypeData_5)
			tNpcGossip[18579]["Text191"] = string.format(tFestivalCardMonth_Text[18579]["Text191"],nStcValue_3,nDemonHP_5)
			tNpcGossip[18579]["OptionFunc22"] = string.format("FestivalCardMonth_FightDemon</N>%d</N>%d",nNpcId,nActNpcId)
			LinkNpcGossipFunc_New(nNpcId,"1-9")
			Map_Effect(nMapId,nPosX,nPosY,tFestivalCardMonth_Data["Effect_2"])
			return
		end
	end
	
	Sys_SaveActionFestivalLog(sLogText)
	LinkNpcGossipFunc_New(nNpcId,"1-7")
	Map_Effect(nMapId,nPosX,nPosY,tFestivalCardMonth_Data["Effect_2"])
end


-- 没有免费挑战次数-用27天石挑战
function FestivalCardMonth_FightNoFree(nNpcId,nActNpcId,nFightNum)
	-- 活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-1")
		return
	end

	-- 判断背包空间
	if not User_CheckLeftSpace(tFestivalCardMonth_Data["ChkSpace2"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-6")
		return
	end

	--天石判断
	local nUserEMoney = Get_UserEMoney()
	local nEMoney = tFestivalCardMonth_Data["SupDekaronEMoney"] * nFightNum
	if nUserEMoney < nEMoney then
		LinkNpcGossipFunc_New(nNpcId,"1-8")
		return
	end

	--扣除天石
	if User_AddEMoney(-nEMoney) then
		FestivalCardMonth_FightSuc(nNpcId,nActNpcId,nFightNum)
		Sys_SaveEmoneyBuy(string.format(tFestivalCardMonth_EmoneyBuy["EmoneyLog1"],nEMoney,nEMoney))
	end
end



--确认挑战
function FestivalCardMonth_FightDone(nNpcId,nActNpcId)
	-- 活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-1")
		return
	end

	-- 判断背包空间
	if not User_CheckLeftSpace(tFestivalCardMonth_Data["ChkSpace2"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-6")
		return
	end
	
	local nEventData_6 = tFestivalCardMonth_Stc[6]["EventData"]
	local nTypeData_6 = tFestivalCardMonth_Stc[6]["TypeData"]
	local nComplete_6 = tFestivalCardMonth_Stc[6]["Complete"]
	local nFightTimes = tFestivalCardMonth_Data["SupDekaronTimes"]
	
	-- 是否有免费挑战次数
	if Task_ChkStcValue(nEventData_6,nTypeData_6,"==",nComplete_6) then
	
		--恶魔血量
		local nGodCardId = tFestivalCardMonth_Demon[nActNpcId]
		local nEventData_3 = tFestivalCardMonth_Stc[3][nGodCardId]["EventData"]
		local nTypeData_3 = tFestivalCardMonth_Stc[3][nGodCardId]["TypeData"]
		local nEventData_5 = tFestivalCardMonth_Stc[5][nActNpcId]["EventData"]
		local nTypeData_5 = tFestivalCardMonth_Stc[5][nActNpcId]["TypeData"]
		local nStcValue_3 = Get_UserStatisticValue(nEventData_3,nTypeData_3) * nFightTimes
		
		-- 血量低于攻击力
		if Task_ChkStcValue(nEventData_5,nTypeData_5,">=",nStcValue_3) then
			tNpcGossip[18579]["tOption1-5"] = {17,23,18}
		else
			tNpcGossip[18579]["tOption1-5"] = {17,18}
		end
		tNpcGossip[18579]["OptionFunc17"] = string.format("FestivalCardMonth_FightNoFree</N>%d</N>%d</N>%d",nNpcId,nActNpcId,1)
		tNpcGossip[18579]["OptionFunc23"] = string.format("FestivalCardMonth_FightNoFree</N>%d</N>%d</N>%d",nNpcId,nActNpcId,nFightTimes)
		LinkNpcGossipFunc_New(nNpcId,"1-5")
		return
	end
	
	--满足条件执行挑战函数
	FestivalCardMonth_FightSuc(nNpcId,nActNpcId,1)
end


-- 挑战恶魔
function FestivalCardMonth_FightDemon(nNpcId,nActNpcId)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-1")
		return
	end

	--没有主神卡
	if not Item_ChkItem(tFestivalCardMonth_Demon[nActNpcId]) then
		tNpcGossip[18579]["Text131"] = tFestivalCardMonth_Text[nActNpcId]["Text131"]
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	local nGodCardId = tFestivalCardMonth_Demon[nActNpcId]
	local sItemName = Get_ItemtypeName(nGodCardId)
	local nEventData_3 = tFestivalCardMonth_Stc[3][nGodCardId]["EventData"]
	local nTypeData_3 = tFestivalCardMonth_Stc[3][nGodCardId]["TypeData"]
	local nEventData_5 = tFestivalCardMonth_Stc[5][nActNpcId]["EventData"]
	local nTypeData_5 = tFestivalCardMonth_Stc[5][nActNpcId]["TypeData"]
	local nDemonHP_5 = tFestivalCardMonth_Stc[5][nActNpcId]["HP"]
	local nEventData_6 = tFestivalCardMonth_Stc[6]["EventData"]
	local nTypeData_6 = tFestivalCardMonth_Stc[6]["TypeData"]
	local nDemonActHP = 0
	local nDemonPower = 0
	local nDemonFree = Get_UserStatisticValue(nEventData_6,nTypeData_6)
	local sLinkText1 = tFestivalCardMonth_Text[nActNpcId]["Text142"]
	local sLinkText2 = ""
	local sLinkText3 = ""

	-- 恶魔血量为0
	if not Task_ChkStcValue(nEventData_5,nTypeData_5,">",0) then

		--是否完成挑战
		local nEventData_4 = tFestivalCardMonth_Stc[4][nActNpcId]["EventData"]
		local nTypeData_4 = tFestivalCardMonth_Stc[4][nActNpcId]["TypeData"]
		local nComplete_4 = tFestivalCardMonth_Stc[4]["Complete"]
		
		if not Task_ChkStcValue(nEventData_4,nTypeData_4,">=",nComplete_4) then
			
			--哪个挑战阶段(未完成3个阶段)
			local nPhase = Get_UserStatisticValue(nEventData_4,nTypeData_4)
			local nHP = nDemonHP_5 * nPhase
			
			nDemonActHP = nHP
			nDemonPower = Get_UserStatisticValue(nEventData_3,nTypeData_3)
			Task_SetStatistic(nEventData_5,nTypeData_5,nHP,1)
			
			--组合对白
			sLinkText2 = string.format(tFestivalCardMonth_Text[18579]["Text143"],nDemonActHP,sItemName,nDemonPower)
			sLinkText3 = string.format(tFestivalCardMonth_Text[18579]["Text144"],nDemonFree)
			tNpcGossip[18579]["Text142"] = sLinkText1..sLinkText2..sLinkText3
			
		--完成3个阶段挑战
		else
			sLinkText3 = string.format(tFestivalCardMonth_Text[18579]["Text144"],nDemonFree)
			tNpcGossip[18579]["Text142"] = sLinkText1..sLinkText3
		end
		
	-- 恶魔血量不为0
	else
		nDemonActHP = Get_UserStatisticValue(nEventData_5,nTypeData_5)
		nDemonPower = Get_UserStatisticValue(nEventData_3,nTypeData_3)
		sLinkText2 = string.format(tFestivalCardMonth_Text[18579]["Text143"],nDemonActHP,sItemName,nDemonPower)
		sLinkText3 = string.format(tFestivalCardMonth_Text[18579]["Text144"],nDemonFree)
		tNpcGossip[18579]["Text142"] = sLinkText1..sLinkText2..sLinkText3
	end
	
	--出对白
	tNpcGossip[18579]["Text141"] = tFestivalCardMonth_Text[nActNpcId]["Text141"]
	tNpcGossip[18579]["OptionFunc15"] = string.format("FestivalCardMonth_FightDone</N>%d</N>%d",nNpcId,nActNpcId)
	LinkNpcGossipFunc_New(nNpcId,"1-4")
end




---------------------------------------物品函数---------------------------------------------

------------------------------------【主神卡逻辑】------------------------------------------
-- 主神卡属性初始化
function FestivalCardMonth_GodCard_Define(nItemId)
	--主神卡等级STC数据
	local nEventData_2 = tFestivalCardMonth_Stc[2][nItemId]["EventData"]
	local nTypeData_2 = tFestivalCardMonth_Stc[2][nItemId]["TypeData"]
	local nValue_2 = tFestivalCardMonth_Stc[2]["Value"]

	--主神卡攻击力STC数据
	local nEventData_3 = tFestivalCardMonth_Stc[3][nItemId]["EventData"]
	local nTypeData_3 = tFestivalCardMonth_Stc[3][nItemId]["TypeData"]
	local nValue_3 = tFestivalCardMonth_Stc[3][nItemId]["Value"]
	
	--主神卡等级\攻击力初始化
	if Task_ChkStcValue(nEventData_2,nTypeData_2,"==",0) or Task_ChkStcValue(nEventData_3,nTypeData_3,"==",0) then
		Task_SetStatistic(nEventData_2,nTypeData_2,nValue_2,1)
		Task_SetStatistic(nEventData_3,nTypeData_3,nValue_3,1)
	end
end


--主神卡升级函数
function FestivalCardMonth_GodCard_UpLev(nItemId,sItemName)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		if Item_ChkItem(nItemId) and Item_DelAllItemByType(nItemId) then
			local sTalkText = tFestivalCardMonth_Text["Item_TimeOut"]
			User_TalkChannel2005(sTalkText)
		end
		return
	end

	--获取所需圣物卡ID
	local nHolyId1 = tFestivalCardMonth_ArtifactCard[nItemId][1]
	local nHolyId2 = tFestivalCardMonth_ArtifactCard[nItemId][2]
	local nHolyId3 = tFestivalCardMonth_ArtifactCard[nItemId][3]
	
	--是否存在需要的3种圣物卡
	if Item_ChkItem(nHolyId1) and Item_ChkItem(nHolyId2) and Item_ChkItem(nHolyId3) then
		
		--是否删除成功
		if Item_DelItem(nHolyId1) and Item_DelItem(nHolyId2) and Item_DelItem(nHolyId3) then
			local nEventData_1 = tFestivalCardMonth_Stc[1]["EventData"]
			local nTypeData_1 = tFestivalCardMonth_Stc[1]["TypeData"]
			local nUpValue_1 = tFestivalCardMonth_Stc[1]["UpLev"]
			local nEventData_2 = tFestivalCardMonth_Stc[2][nItemId]["EventData"]
			local nTypeData_2 = tFestivalCardMonth_Stc[2][nItemId]["TypeData"]
			local nUpValue_2 = tFestivalCardMonth_Stc[2]["UpValue"]
			local nEventData_3 = tFestivalCardMonth_Stc[3][nItemId]["EventData"]
			local nTypeData_3 = tFestivalCardMonth_Stc[3][nItemId]["TypeData"]
			local nUpValue_3 = tFestivalCardMonth_Stc[3][nItemId]["UpValue"]
			
			--升级成功，加积分、等级和攻击力增加
			Task_AddStatistic(nEventData_1,nTypeData_1,nUpValue_1,1)
			Task_AddStatistic(nEventData_2,nTypeData_2,nUpValue_2,1)
			Task_AddStatistic(nEventData_3,nTypeData_3,nUpValue_3,1)
			
			--取等级和攻击力数据
			local nHolyLev = Get_UserStatisticValue(nEventData_2,nTypeData_2)
			local nHolyPower = Get_UserStatisticValue(nEventData_3,nTypeData_3)
			local sDialogText = string.format(tFestivalCardMonth_Text["GodCard_UplevSuccess"],sItemName,nHolyLev,nHolyPower)
			User_EffectAdd(tFestivalCardMonth_Data["EffectObj"],tFestivalCardMonth_Data["Effect_1"])
			-- Sys_DialogTaskClear()
			Sys_DialogText(sDialogText)
			Sys_DialogOption(tFestivalCardMonth_Text["GodCard_Option3"], "</F>FestivalCardMonth_GodCard_UpLev</N>".. nItemId .."</S>".. sItemName)	
		end
	else
		local sHolyName1 = Get_ItemtypeName(nHolyId1)
		local sHolyName2 = Get_ItemtypeName(nHolyId2)
		local sHolyName3 = Get_ItemtypeName(nHolyId3)
		local sDialogText = string.format(tFestivalCardMonth_Text["GodCard_UplevFail"],sHolyName1,sHolyName2,sHolyName3)
		Sys_DialogText(sDialogText)
	end
	Sys_DialogOption(tFestivalCardMonth_Text["GodCard_Option4"], "</F>NULL")
	Sys_DialogItemFace(nItemId)
	Sys_DialogEnd()
end


--主神卡介绍
function FestivalCardMonth_GodCard_Desc(nItemId,sItemName)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		if Item_ChkItem(nItemId) and Item_DelAllItemByType(nItemId) then
			local sTalkText = tFestivalCardMonth_Text["Item_TimeOut"]
			User_TalkChannel2005(sTalkText)
		end
		return
	end
	
	--介绍对白
	-- Sys_DialogTaskClear()
	Sys_DialogText(tFestivalCardMonth_Text["GodCard_DescText1"][nItemId])
	Sys_DialogText(tFestivalCardMonth_Text["GodCard_DescText2"][nItemId])
	Sys_DialogText(tFestivalCardMonth_Text["GodCard_DescText3"][nItemId])
	Sys_DialogOption(tFestivalCardMonth_Text["GodCard_Option5"], "</F>FestivalCardMonth_GodCard_Main</N>".. nItemId .."</S>".. sItemName)
	Sys_DialogOption(tFestivalCardMonth_Text["GodCard_Option6"], "</F>NULL")
	Sys_DialogItemFace(nItemId)
	Sys_DialogEnd()
end


--主神卡接入函数
function FestivalCardMonth_GodCard_Main(nItemId,sItemName)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		if Item_ChkItem(nItemId) and Item_DelAllItemByType(nItemId) then
			local nEventData_2 = tFestivalCardMonth_Stc[2][nItemId]["EventData"]
			local nTypeData_2 = tFestivalCardMonth_Stc[2][nItemId]["TypeData"]
			local nEventData_3 = tFestivalCardMonth_Stc[3][nItemId]["EventData"]
			local nTypeData_3 = tFestivalCardMonth_Stc[3][nItemId]["TypeData"]
			local nLev = Get_UserStatisticValue(nEventData_2,nTypeData_2)
			local sName = Get_ItemtypeName(nItemId)
			local nPower = Get_UserStatisticValue(nEventData_3,nTypeData_3)
			
			-- 增加主神卡攻击值的修行值
			User_AddCultivation(nPower)
			
			local sLogText = string.format(tFestivalCardMonth_Log["DelGodCard"],nItemId,nPower)
			local sTalkText = string.format(tFestivalCardMonth_Text["GodCard_TimeOut"],nLev,sItemName,nPower)
			Sys_SaveActionFestivalLog(sLogText)
			User_TalkChannel2005(sTalkText)
		end
		return
	end

	--对白内容数据
	local sHolyName = tFestivalCardMonth_Text["HolyCard"][nItemId]

	--主神卡初始化
	FestivalCardMonth_GodCard_Define(nItemId)
	
	--取等级和攻击力数据
	local nEventData_2 = tFestivalCardMonth_Stc[2][nItemId]["EventData"]
	local nTypeData_2 = tFestivalCardMonth_Stc[2][nItemId]["TypeData"]
	local nEventData_3 = tFestivalCardMonth_Stc[3][nItemId]["EventData"]
	local nTypeData_3 = tFestivalCardMonth_Stc[3][nItemId]["TypeData"]
	local nHolyLev = Get_UserStatisticValue(nEventData_2,nTypeData_2)
	local nHolyPower = Get_UserStatisticValue(nEventData_3,nTypeData_3)

	--对白文字组合
	local sDialogText = string.format(tFestivalCardMonth_Text["GodCard_DialogText"],sItemName,sHolyName,nHolyLev,nHolyPower)
	-- Sys_DialogTaskClear()
	Sys_DialogText(sDialogText)
	Sys_DialogOption(tFestivalCardMonth_Text["GodCard_Option1"], "</F>FestivalCardMonth_GodCard_UpLev</N>".. nItemId .."</S>".. sItemName)
	Sys_DialogOption(tFestivalCardMonth_Text["GodCard_Option2"], "</F>FestivalCardMonth_GodCard_Desc</N>".. nItemId .."</S>".. sItemName)
	Sys_DialogItemFace(nItemId)
	Sys_DialogEnd()
end

-----------------------------------【主神卡包逻辑】------------------------------------------------
-- 寻路--奥林匹斯神使
function FestivalCardMonth_CardPag_FindWay(nItemId)
	-- 地图判断
	local nUserMapId = Get_UserMapId()
	local nMapId1 = tFestivalCardMonth_Data[3006632]["MapId"]
	local nMapId2 = tFestivalCardMonth_Data[18577]["MapId"]
	
	-- 双龙城
	if nUserMapId == nMapId1 then
		FestivalCardMonth_FindWay(nItemId)
	-- 挑战地图
	elseif nUserMapId == nMapId2 then
		FestivalCardMonth_FindWay(nMapId2)
	end
end




------------------------------------【圣物卡逻辑】------------------------------------------

--分解圣物卡
function FestivalCardMonth_HolyCard_Decompose(nItemId,sItemName)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		if Item_ChkItem(nItemId) and Item_DelAllItemByType(nItemId) then
			local sTalkText = tFestivalCardMonth_Text["Item_TimeOut"]
			User_TalkChannel2005(sTalkText)
		end
		return
	end
	
	--判断背包空间
	if not User_CheckLeftSpace(tFestivalCardMonth_Data["ChkSpace1"]) then
		Sys_MsgBox(tFestivalCardMonth_Text["HolyCard_BagFull"])
		return
	end
	
	--是否存在圣物卡
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		
		--增加免费打造圣物卡次数+给圣物卡碎片
		local nEventData_8 = tFestivalCardMonth_Stc[8]["EventData"]
		local nTypeData_8 = tFestivalCardMonth_Stc[8]["TypeData"]
		local nAddValue_8 = tFestivalCardMonth_Stc[8]["AddValue1"]
		Task_AddStatistic(nEventData_8,nTypeData_8,nAddValue_8,1)
		Item_AddItem(tFestivalCardMonth_Data["PieceId"],0,tFestivalCardMonth_Data["PieceNum"])
		
		local sLogText = string.format(tFestivalCardMonth_Log["HolyCard_Success"],nItemId)
		Sys_SaveActionFestivalLog(sLogText)
		User_TalkChannel2005(tFestivalCardMonth_Text["HolyCard_Success"])
	end
end

-- 圣物卡分解二次确认
function FestivalCardMonth_HolyCard_DecomDecision(nItemId,sItemName)
	
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		if Item_ChkItem(nItemId) and Item_DelAllItemByType(nItemId) then
			local sTalkText = tFestivalCardMonth_Text["Item_TimeOut"]
			User_TalkChannel2005(sTalkText)
		end
		return
	end
	
	-- 确认对白
	local sTalkText = string.format(tFestivalCardMonth_Text["HolyCard_DecText"],sItemName)
	Sys_DialogText(sTalkText)
	Sys_DialogOption(tFestivalCardMonth_Text["HolyCard_DecOption"], "</F>FestivalCardMonth_HolyCard_Decompose</N>".. nItemId .."</S>".. sItemName)
	Sys_DialogEnd()
end

------------------------------------【圣物卡碎片】------------------------------------------------
-- 成功打造
function FestivalCardMonth_CreateSuc(nItemId,nItemNum,nNewItemId,nEMoney)
	--判断背包空间
	if not User_CheckLeftSpace(tFestivalCardMonth_Data["ChkSpace1"]) then
		LinkItemGossipFunc_New(nItemId,"1-2")
		return
	end

	if nEMoney ~= nil then
		-- 天石判断
		local nUserEMoney = Get_UserEMoney()
		if nUserEMoney < nEMoney then
			LinkItemGossipFunc_New(nItemId,"1-4")
			return
		end
	
		--扣除天石
		if User_AddEMoney(-nEMoney) then
			Sys_SaveEmoneyBuy(tFestivalCardMonth_EmoneyBuy["EmoneyLog2"])
		end
	end
	
	-- 删除碎片
	if Item_ChkMulItem(nItemId,nItemId,nItemNum) and Item_DelMulItem(nItemId,nItemId,nItemNum) then
		local nAddItem = nNewItemId
		
		--随机打造
		if nNewItemId == 0 then
			local flat,tItem = Probabil_RandomAward(tFestivalCardMonth_Probabil[1],2)
			nAddItem = tItem[1]["tAward"][1]["Item_1"]
		end
		
		Item_AddItem(nAddItem)
		User_EffectAdd(tFestivalCardMonth_Data["EffectObj"],tFestivalCardMonth_Data["Effect_1"])
		local sItemName = Get_ItemtypeName(nAddItem)
		local sLogText = string.format(tFestivalCardMonth_Log["CreateHoly"],nItemNum,nNewItemId)
		local sTalkText = string.format(tFestivalCardMonth_Text[nItemId]["CreateSuccess"],sItemName)
		Sys_SaveActionFestivalLog(sLogText)
		User_TalkChannel2005(sTalkText)
	end
end



-- 打造函数
function FestivalCardMonth_CreateCard(nItemId,nItemNum,nNewItemId)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		if Item_ChkItem(nItemId) and Item_DelAllItemByType(nItemId) then
			local sTalkText = tFestivalCardMonth_Text["Item_TimeOut"]
			User_TalkChannel2005(sTalkText)
		end
		return
	end
	
	--判断背包空间
	if not User_CheckLeftSpace(tFestivalCardMonth_Data["ChkSpace1"]) then
		LinkItemGossipFunc_New(nItemId,"1-2")
		return
	end

	--碎片数量判断
	if not Item_ChkMulItem(nItemId,nItemId,nItemNum) then
		LinkItemGossipFunc_New(nItemId,"1-3")
		return
	end
	
	local nEventData_8 = tFestivalCardMonth_Stc[8]["EventData"]
	local nTypeData_8 = tFestivalCardMonth_Stc[8]["TypeData"]
	local nComplete_8 = tFestivalCardMonth_Stc[8]["Complete"]
	
	-- 是否有免费挑战次数
	if Task_ChkStcValue(nEventData_8,nTypeData_8,"==",nComplete_8) then
		
		-- 天石判断
		local nUserEMoney = Get_UserEMoney()
		local nEMoney = tFestivalCardMonth_HolyPiece["CreateEMoney"]
		if nUserEMoney < nEMoney then
			LinkItemGossipFunc_New(nItemId,"1-4")
			return
		end
		local sOptionFunc = "FestivalCardMonth_CreateSuc</N>3006692</N>%d</N>%d</N>%d"
		tItem[3006692]["tOption1-5"] = {16,17}
		tItem[3006692]["OptionFunc16"] = string.format(sOptionFunc,nItemNum,nNewItemId,nEMoney)
		LinkItemGossipFunc_New(nItemId,"1-5")
	else
		local nAddValue_8 = tFestivalCardMonth_Stc[8]["AddValue1"]
		Task_AddStatistic(nEventData_8,nTypeData_8,-nAddValue_8,1)
		FestivalCardMonth_CreateSuc(nItemId,nItemNum,nNewItemId)
	end
end


-------------------------------------【主神卡幸运礼包】------------------------------------------------
-- 打开主神卡幸运礼包
function FestivalCardMonth_OpenLuckyBag(nItemId)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		if Item_ChkItem(nItemId) and Item_DelAllItemByType(nItemId) then
			local sTalkText = tFestivalCardMonth_Text["Item_TimeOut"]
			User_TalkChannel2005(sTalkText)
		end
		return
	end
	
	--判断背包空间
	if not User_CheckLeftSpace(tFestivalCardMonth_Data["ChkSpace1"]) then
		User_TalkChannel2005(tFestivalCardMonth_Text[3006695]["PagFull"])
		return
	end
	
	local flat,tItem = Probabil_RandomAward(tFestivalCardMonth_Probabil[1],4)
	local nNewItemNum = tItem[1]["tAward"][1]["Item_1"]
	local nNewItemId = tFestivalCardMonth_Data["PieceId"]
	
	if type(nNewItemNum) ~= "number" then
		-- 给主神卡
		if nNewItemNum == "GodCard" then
			local flat,tItem = Probabil_RandomAward(tFestivalCardMonth_Probabil[1],3)
			local nCardPieceId = tItem[1]["tAward"][1]["Item_1"]
			nNewItemId = tFestivalCardMonth_CardPiece[nCardPieceId]
			nNewItemNum = 1
		-- 给主神卡碎片
		elseif nNewItemNum == "CardPiece" then
			local flat,tItem = Probabil_RandomAward(tFestivalCardMonth_Probabil[1],3)
			nNewItemId = tItem[1]["tAward"][1]["Item_1"]
			nNewItemNum = 3
		-- 给圣物卡
		elseif nNewItemNum == "HolyCard" then
			local flat,tItem = Probabil_RandomAward(tFestivalCardMonth_Probabil[1],2)
			nNewItemId = tItem[1]["tAward"][1]["Item_1"]
			nNewItemNum = 1
		end
	end
	
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		Item_AddItem(nNewItemId,0,nNewItemNum)
		local sItemName = Get_ItemtypeName(nNewItemId)
		local sLogText = string.format(tFestivalCardMonth_Log["OpenLuckyBag"],nNewItemId,nNewItemNum)
		local sTalkText = string.format(tFestivalCardMonth_Text[3006695]["AwardItem"],nNewItemNum,sItemName)
		User_EffectAdd(tFestivalCardMonth_Data["EffectObj"],tFestivalCardMonth_Data["Effect_1"])
		Sys_SaveActionFestivalLog(sLogText)
		User_TalkChannel2005(sTalkText)
	end
end
----------------------------------【主神卡幸运连抽礼包】------------------------------------------------
-- 打开主神卡幸运连抽礼包
function FestivalCardMonth_OpenSeriesBag(nItemId)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		if Item_ChkItem(nItemId) and Item_DelAllItemByType(nItemId) then
			local sTalkText = tFestivalCardMonth_Text["Item_TimeOut"]
			User_TalkChannel2005(sTalkText)
		end
		return
	end

	--判断背包空间
	if not User_CheckLeftSpace(tFestivalCardMonth_Data["ChkSpace10"]) then
		User_TalkChannel2005(tFestivalCardMonth_Text[3006696]["PagFull"])
		return
	end

	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		--连抽10次
		for i = 1, tFestivalCardMonth_Data["SeriesBagNum"] do
			local flat,tItemProbabil = Probabil_RandomAward(tFestivalCardMonth_Probabil[1],4)
			local nNewItemNum = tItemProbabil[1]["tAward"][1]["Item_1"]
			local nNewItemId = tFestivalCardMonth_Data["PieceId"]
			
			if type(nNewItemNum) ~= "number" then
				if nNewItemNum == "GodCard" then
					local flat,tItem = Probabil_RandomAward(tFestivalCardMonth_Probabil[1],3)
					local nCardPieceId = tItem[1]["tAward"][1]["Item_1"]
					nNewItemId = tFestivalCardMonth_CardPiece[nCardPieceId]
					nNewItemNum = 1
				-- 给主神卡碎片
				elseif nNewItemNum == "CardPiece" then
					local flat,tItem = Probabil_RandomAward(tFestivalCardMonth_Probabil[1],3)
					nNewItemId = tItem[1]["tAward"][1]["Item_1"]
					nNewItemNum = 3
					
				-- 给圣物卡
				elseif nNewItemNum == "HolyCard" then
					local flat,tItem = Probabil_RandomAward(tFestivalCardMonth_Probabil[1],2)
					nNewItemId = tItem[1]["tAward"][1]["Item_1"]
					nNewItemNum = 1
				end
			end
			
			Item_AddItem(nNewItemId,0,nNewItemNum)
			local sItemName = Get_ItemtypeName(nNewItemId)
			local sDialogText = tFestivalCardMonth_Text[3006696]["Text11".. i]
			tItem[3006696]["Text11".. i] = string.format(sDialogText,i,nNewItemNum,sItemName)
			sLogText = string.format(tFestivalCardMonth_Log["OpenSeriesBag"],nNewItemId,nNewItemNum)
			Sys_SaveActionFestivalLog(sLogText)
		end
		User_EffectAdd(tFestivalCardMonth_Data["EffectObj"],tFestivalCardMonth_Data["Effect_4"])
		LinkItemGossipFunc_New(nItemId,"1-1")
	end
end
---------------------------------【奥林匹斯神谕】------------------------------------------
-- 背包信接入函数
function FestivalCardMonth_Letter(nItemId,nFindWayId)
	local nGodCardId = 0
	local aAddType = 0
	local nAddValue = 0

	if Item_ChkItem(nItemId) and Item_DelAllItemByType(nItemId) then
		local flat,tItem = Probabil_RandomAward(tFestivalCardMonth_Probabil[1],3)
		local nNewItemId = tItem[1]["tAward"][1]["Item_1"]
		local nCardPagId = tFestivalCardMonth_CardPiece[nNewItemId]
		nGodCardId = tFestivalCardMonth_CardPag[nCardPagId]
		

		if Item_ChkItem(nGodCardId) then
			-- 主神卡包
			nGodCardId = nCardPagId
		else
			--给积分
			local nEventData_1 = tFestivalCardMonth_Stc[1]["EventData"]
			local nTypeData_1 = tFestivalCardMonth_Stc[1]["TypeData"]
			local nGetCard_1 = tFestivalCardMonth_Stc[1]["GetGodCard"]
			Task_AddStatistic(nEventData_1,nTypeData_1,nGetCard_1,1)
			-- 主神卡初始化
			FestivalCardMonth_GodCard_Define(nGodCardId)
		end
		
		Item_AddItem(nGodCardId)
		
		--等级判断
		local nUserLev = Get_UserLevel()
		
		--给经验
		if nUserLev < tFestivalCardMonth_Data["LevelTop"] then
			aAddType = tFestivalCardMonth_Data["Type_Exp"]
			nAddValue = tFestivalCardMonth_Data["Letter_Exp"]
			User_AddExpTime(nAddValue)
			
		--给修行值
		else
			aAddType = tFestivalCardMonth_Data["Type_Cul"]
			nAddValue = tFestivalCardMonth_Data["Letter_Cul"]
			User_AddCultivation(nAddValue)
		end
	end
	
	User_EffectAdd(tFestivalCardMonth_Data["EffectObj"],tFestivalCardMonth_Data["Effect_1"])
	local sItemName = Get_ItemtypeName(nGodCardId)
	local sLogText = string.format(tFestivalCardMonth_Log["Letter"],nGodCardId,aAddType,nAddValue)
	local sTalkText = string.format(tFestivalCardMonth_Text[nItemId]["Destroy"],sItemName,nAddValue,tFestivalCardMonth_Text[3006697][nAddValue])
	Sys_SaveActionFestivalLog(sLogText)
	User_TalkChannel2005(sTalkText)
	FestivalCardMonth_CardPag_FindWay(nFindWayId)
end


---------------------------------【A、B、C类礼包】------------------------------------------
-- 打开礼包
function FestivalCardMonth_OpenPag(nItemId,nBagNum,nReward1,nNum1,nReward2,nNum2,nReward3,nNum3)

	--判断背包空间
	if nBagNum ~= 0 then
		if not User_CheckLeftSpace(nBagNum) then
			LinkItemGossipFunc_New(3006864,"1-2")
			return
		end
	end
	
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		local sItemName1 = ""
		local sItemName2 = ""
		local sLogText0 = string.format(tFestivalCardMonth_Log["OpenPackage0"],nItemId)
		local sLogText1 = ""
		local sTalkText0 = tFestivalCardMonth_Text[3006864]["Reward0"]
		local sTalkText1 = ""
		local sTalkText2 = ""
		local sTalkText3 = ""
		--给第一个奖励
		if nReward1 ~= nil then
			sItemName1 = Get_ItemtypeName(nReward1)
			if nReward1 == 1088001 or nReward1 == 720027 then
				Item_AddItem(nReward1,0,nNum1)
				sTalkText1 = string.format(tFestivalCardMonth_Text[3006864]["Reward11"],nNum1,sItemName1)
			else
				Item_AddItem(nReward1,0,nNum1,3)
				sTalkText1 = string.format(tFestivalCardMonth_Text[3006864]["Reward1"],nNum1,sItemName1)
			end
			sLogText1 = string.format(tFestivalCardMonth_Log["OpenPackage1"],nReward1,nNum1)
			sTalkText0 = sTalkText0..sTalkText1
		end
		
		--给第二个奖励
		if nReward2 ~= nil then
			sItemName2 = Get_ItemtypeName(nReward2)
			if nReward2 == 300000 then
				Item_AddItem(nReward2,0,nNum2,3,0,0,0,16750080,255,150,0,2)
				sItemName2 = "+2"..sItemName2
				sTalkText2 = string.format(tFestivalCardMonth_Text[3006864]["Reward2"],nNum2,sItemName2)
			elseif nReward2 == 1088001 or nReward2 == 720027 then
				Item_AddItem(nReward2,0,nNum2)
				sTalkText2 = string.format(tFestivalCardMonth_Text[3006864]["Reward21"],nNum2,sItemName2)
			else
				Item_AddItem(nReward2,0,nNum2,3)
				sTalkText2 = string.format(tFestivalCardMonth_Text[3006864]["Reward2"],nNum2,sItemName2)
			end
			sLogText1 = string.format(tFestivalCardMonth_Log["OpenPackage2"],nReward1,nReward2,nNum1,nNum2)
			sTalkText0 = sTalkText0..sTalkText2
		end
		
		--给第三个奖励
		if nReward3 ~= nil then
			Item_AddItem(nReward3,0,nNum3,3)
			sItemName3 = Get_ItemtypeName(nReward3)
			sLogText1 = string.format(tFestivalCardMonth_Log["OpenPackage2"],nReward1,nReward2,nReward3,nNum1,nNum2,nNum3)
			sTalkText3 = string.format(tFestivalCardMonth_Text[3006864]["Reward2"],nNum3,sItemName3)
			sTalkText0 = sTalkText0..sTalkText3
		end
		Sys_SaveActionFestivalLog(sLogText0..sLogText1)
		User_TalkChannel2005(sTalkText0..".")
	end
end

------------------------------------------怪物配置-------------------------------------------
-- 怪物守卫函数
function FestivalCardMonth_Monster()
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		FestivalCardMonth_ChgMap(18591)
		return
	end

	-- 是否已杀8只
	local nEventData_12 = tFestivalCardMonth_Stc[12]["EventData"]
	local nTypeData_12 = tFestivalCardMonth_Stc[12]["TypeData"]
	local nComplete_12 = tFestivalCardMonth_Stc[12]["Complete"]
	if Task_ChkStcValue(nEventData_12,nTypeData_12,">=",nComplete_12) then
		FestivalCardMonth_ChgMap(3949)
		return
	end
	
	--判断背包空间
	if not User_CheckLeftSpace(tFestivalCardMonth_Data["ChkSpace1"]) then
		User_TalkChannel2005(tFestivalCardMonth_Text["Monster"]["FullBag"])
		return
	end

	local flat,tItem = Probabil_RandomAward(tFestivalCardMonth_Probabil[1],6)
	local nItemId = tItem[1]["tAward"][1]["Item_1"]

	Item_AddItem(nItemId)
	Task_AddStatistic(nEventData_12,nTypeData_12,1,1)
	local sItemName = Get_ItemtypeName(nItemId)
	local sLogText = string.format(tFestivalCardMonth_Log["Monster"],nItemId)
	local sTalkText = string.format(tFestivalCardMonth_Text["Monster"]["Item"],sItemName)
	Sys_SaveActionFestivalLog(sLogText)
	User_TalkChannel2005(sTalkText)
	
	-- 是否击杀8只
	if Task_ChkStcValue(nEventData_12,nTypeData_12,">=",nComplete_12) then
		FestivalCardMonth_ChgMap(3949)
		return
	end
end

-- 第一批BOSS
function FestivalCardMonth_BossMonster1()
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		return
	end
	
	--玩家等级判断
	if not User_JudgeLevelAndMetempsychosis(tFestivalCardMonth_Data["MinLevel"],tFestivalCardMonth_Data["MinMeto"]) then
		return
	end
	
	-- 掉落物品
	local nMapId = Get_MonsterMapID()
	local nItemId = tFestivalCardMonth_Data["PieceId"]
	local nPosX = Get_MonsterPosX()
	local nPosY = Get_MonsterPosY()
	local nCellx = tFestivalCardMonth_Data["PiecePosX"]
	local nCelly = tFestivalCardMonth_Data["PiecePosY"]
	local nItemNum = tFestivalCardMonth_Data["PieceNum1"]
	local nExistTime = tFestivalCardMonth_Data["PieceExistTime"]
	Map_DropMultiItems(nMapId, nItemId, nPosX, nPosY, nCellx, nCelly, nItemNum, nExistTime)
end

-- 第二批BOSS
function FestivalCardMonth_BossMonster2()
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		return
	end
	
	--玩家等级判断
	if not User_JudgeLevelAndMetempsychosis(tFestivalCardMonth_Data["MinLevel"],tFestivalCardMonth_Data["MinMeto"]) then
		return
	end

	-- 掉落物品圣物卡碎片
	local nMapId = Get_MonsterMapID()
	local nItemId = tFestivalCardMonth_Data["PieceId"]
	local nPosX = Get_MonsterPosX()
	local nPosY = Get_MonsterPosY()
	local nCellx = tFestivalCardMonth_Data["PiecePosX"]
	local nCelly = tFestivalCardMonth_Data["PiecePosY"]
	local nItemNum = tFestivalCardMonth_Data["PieceNum2"]
	local nExistTime = tFestivalCardMonth_Data["PieceExistTime"]
	Map_DropMultiItems(nMapId,nItemId,nPosX,nPosY,nCellx,nCelly,nItemNum,nExistTime)
	
	local flat,tItem = Probabil_RandomAward(tFestivalCardMonth_Probabil[1],3)
	local nNewItemId = tItem[1]["tAward"][1]["Item_1"]
	local nNewItemNum = tFestivalCardMonth_Data["GodPieceNum2"]
	Map_DropMultiItems(nMapId,nNewItemId,nPosX,nPosY,nCellx,nCelly,nNewItemNum,nExistTime)
	
end

-- 第三批BOSS
function FestivalCardMonth_BossMonster3()
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		return
	end
	
	--玩家等级判断
	if not User_JudgeLevelAndMetempsychosis(tFestivalCardMonth_Data["MinLevel"],tFestivalCardMonth_Data["MinMeto"]) then
		return
	end

	
	-- 掉落物品圣物卡碎片
	local nMapId = Get_MonsterMapID()
	local nPosX = Get_MonsterPosX()
	local nPosY = Get_MonsterPosY()
	local nCellx = tFestivalCardMonth_Data["PiecePosX"]
	local nCelly = tFestivalCardMonth_Data["PiecePosY"]
	local nItemNum = tFestivalCardMonth_Data["GodPieceNum3"]
	local nExistTime = tFestivalCardMonth_Data["PieceExistTime"]
	
	local flat,tItem = Probabil_RandomAward(tFestivalCardMonth_Probabil[1],3)
	local nItemId = tItem[1]["tAward"][1]["Item_1"]
	Map_DropMultiItems(nMapId,nItemId,nPosX,nPosY,nCellx,nCelly,nItemNum,nExistTime)
end

-- 第四批BOSS
function FestivalCardMonth_BossMonster4()
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		return
	end
	
	--玩家等级判断
	if not User_JudgeLevelAndMetempsychosis(tFestivalCardMonth_Data["MinLevel"],tFestivalCardMonth_Data["MinMeto"]) then
		return
	end
	
	-- 掉落物品圣物卡碎片
	local nMapId = Get_MonsterMapID()
	local nPosX = Get_MonsterPosX()
	local nPosY = Get_MonsterPosY()
	local nCellx = tFestivalCardMonth_Data["PiecePosX"]
	local nCelly = tFestivalCardMonth_Data["PiecePosY"]
	local nItemNum = tFestivalCardMonth_Data["GodPieceNum4"]
	local nExistTime = tFestivalCardMonth_Data["PieceExistTime"]
	
	local flat,tItem = Probabil_RandomAward(tFestivalCardMonth_Probabil[1],3)
	local nItemId = tItem[1]["tAward"][1]["Item_1"]
	Map_DropMultiItems(nMapId,nItemId,nPosX,nPosY,nCellx,nCelly,nItemNum,nExistTime)
end



------------------------------------------NPC配置-------------------------------------------
---------------------NPC头像
tNpcFace[3692] = 184
tNpcFace[3694] = 287
tNpcFace[3695] = 288
tNpcFace[3696] = 289
tNpcFace[3697] = 290
tNpcFace[3698] = 291
tNpcFace[3699] = 292
tNpcFace[3700] = 293
tNpcFace[3701] = 294
tNpcFace[3702] = 295
tNpcFace[3703] = 296
tNpcFace[3704] = 297
tNpcFace[3705] = 298

---------------------NPC对话
------------------------------------------
-- 【==奥林匹斯神使==】
tNpcGossip[18577] = tNpcGossip[18577] or DefaultNpc:new{}
tNpcGossip[18591] = tNpcGossip[18577] or DefaultNpc:new{}
tNpcGossip[18577]["OptionHidden"] = 1

---【起始对白】
tNpcGossip[18577]["Text1-1"] = {111,112} 			-- 活动时间前
tNpcGossip[18577]["Text1-2"] = {121} 				-- 活动时间后
tNpcGossip[18577]["Text1-3"] = {131,132,133} 		-- 活动时间中

---活动前
tNpcGossip[18577]["Text111"] = tFestivalCardMonth_Text[18577]["Text111"]
tNpcGossip[18577]["Text112"] = tFestivalCardMonth_Text[18577]["Text112"]
tNpcGossip[18577]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_BefTime"])
end

---活动后
tNpcGossip[18577]["Text121"] = tFestivalCardMonth_Text[18577]["Text121"]
tNpcGossip[18577]["ChkFunc1-2"] = function ()
	return not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"])
end

---活动中
tNpcGossip[18577]["Text131"] = tFestivalCardMonth_Text[18577]["Text131"]
tNpcGossip[18577]["Text132"] = tFestivalCardMonth_Text[18577]["Text132"]
tNpcGossip[18577]["Text133"] = tFestivalCardMonth_Text[18577]["Text133"]
--选项
tNpcGossip[18577]["tOption1-1"] = {11}					-- 活动时间前
tNpcGossip[18577]["tOption1-2"] = {12}					-- 活动时间后
tNpcGossip[18577]["tOption1-3"] = {18,13,14,15,16,17,19}	-- 活动时间中
tNpcGossip[18577]["Option11"] = tFestivalCardMonth_Text[18577]["Option11"]
tNpcGossip[18577]["Option12"] = tFestivalCardMonth_Text[18577]["Option12"]
tNpcGossip[18577]["Option13"] = tFestivalCardMonth_Text[18577]["Option13"]
tNpcGossip[18577]["OptionChkFunc13"] = function ()
	local nNpcId = Get_NpcId()
	--为进场NPC
	return nNpcId == 18577
end
tNpcGossip[18577]["Option14"] = tFestivalCardMonth_Text[18577]["Option14"]
tNpcGossip[18577]["OptionChkFunc14"] = function ()
	local nNpcId = Get_NpcId()
	--为离场NPC
	return nNpcId == 18591
end
tNpcGossip[18577]["Option15"] = tFestivalCardMonth_Text[18577]["Option15"]
tNpcGossip[18577]["Option16"] = tFestivalCardMonth_Text[18577]["Option16"]
tNpcGossip[18577]["Option17"] = tFestivalCardMonth_Text[18577]["Option17"]
tNpcGossip[18577]["Option18"] = tFestivalCardMonth_Text[18577]["Option18"]
tNpcGossip[18577]["Option19"] = tFestivalCardMonth_Text[18577]["Option19"]
tNpcGossip[18577]["OptionFunc13"] = "FestivalCardMonth_EnterMap</N>18577"
tNpcGossip[18577]["OptionFunc14"] = "FestivalCardMonth_ChgMap</N>18591"
tNpcGossip[18577]["OptionFunc15"] = "FestivalCardMonth_ViewPoints</N>18577"
tNpcGossip[18577]["OptionPoint16"] = "4"
tNpcGossip[18577]["OptionPoint17"] = "5"
tNpcGossip[18577]["OptionPoint18"] = "6"

--【进入奥林匹斯山。】
tNpcGossip[18577]["Text2-1"] = {211} 				--等级不足
tNpcGossip[18577]["Text211"] = tFestivalCardMonth_Text[18577]["Text211"]
--选项
tNpcGossip[18577]["tOption2-1"] = {21}				-- 等级不足
tNpcGossip[18577]["Option21"] = tFestivalCardMonth_Text[18577]["Option21"]


--【查询当前活动积分。】
tNpcGossip[18577]["Text3-1"] = {311,312}
tNpcGossip[18577]["Text311"] = tFestivalCardMonth_Text[18577]["Text311"]
tNpcGossip[18577]["Text312"] = tFestivalCardMonth_Text[18577]["Text312"]
--选项
tNpcGossip[18577]["tOption3-1"] = {31,32,33}
tNpcGossip[18577]["Option31"] = tFestivalCardMonth_Text[18577]["Option31"]
tNpcGossip[18577]["Option32"] = tFestivalCardMonth_Text[18577]["Option32"]
tNpcGossip[18577]["Option33"] = tFestivalCardMonth_Text[18577]["Option33"]
tNpcGossip[18577]["OptionFunc31"] = "FestivalCardMonth_WebLink"
tNpcGossip[18577]["OptionPoint32"] = "1"


-- 【购买幸运礼包。】
tNpcGossip[18577]["Text4-1"] = {411,412,413}		-- 初始对白
tNpcGossip[18577]["Text4-2"] = {421} 				-- 修为不足
tNpcGossip[18577]["Text4-3"] = {431} 				-- 天石不足
tNpcGossip[18577]["Text4-4"] = {441} 				-- 背包空间不足
tNpcGossip[18577]["Text4-5"] = {451} 				-- 二次确认
tNpcGossip[18577]["Text411"] = tFestivalCardMonth_Text[18577]["Text411"]
tNpcGossip[18577]["Text412"] = tFestivalCardMonth_Text[18577]["Text412"]
tNpcGossip[18577]["Text413"] = tFestivalCardMonth_Text[18577]["Text413"]
tNpcGossip[18577]["Text421"] = tFestivalCardMonth_Text[18577]["Text421"]
tNpcGossip[18577]["Text431"] = tFestivalCardMonth_Text[18577]["Text431"]
tNpcGossip[18577]["Text441"] = tFestivalCardMonth_Text[18577]["Text441"]
tNpcGossip[18577]["Text451"] = tFestivalCardMonth_Text[18577]["Text451"]

--选项
tNpcGossip[18577]["tOption4-1"] = {41,42,43,44}
tNpcGossip[18577]["tOption4-2"] = {45}
tNpcGossip[18577]["tOption4-3"] = {45}
tNpcGossip[18577]["tOption4-4"] = {45}
tNpcGossip[18577]["tOption4-5"] = {46,47}
tNpcGossip[18577]["Option41"] = tFestivalCardMonth_Text[18577]["Option41"]
tNpcGossip[18577]["Option42"] = tFestivalCardMonth_Text[18577]["Option42"]
tNpcGossip[18577]["Option43"] = tFestivalCardMonth_Text[18577]["Option43"]
tNpcGossip[18577]["Option44"] = tFestivalCardMonth_Text[18577]["Option44"]
tNpcGossip[18577]["Option45"] = tFestivalCardMonth_Text[18577]["Option45"]
tNpcGossip[18577]["Option46"] = tFestivalCardMonth_Text[18577]["Option46"]
tNpcGossip[18577]["Option47"] = tFestivalCardMonth_Text[18577]["Option47"]
tNpcGossip[18577]["OptionFunc41"] = "FestivalCardMonth_GodLucyBag</N>18577</N>1"
tNpcGossip[18577]["OptionFunc42"] = "FestivalCardMonth_GodLucyBag</N>18577</N>2"
tNpcGossip[18577]["OptionPoint43"] = "1"
tNpcGossip[18577]["OptionFunc46"] = ""


-- 【补领主神卡。】
tNpcGossip[18577]["Text5-1"] = {511,512,513}		-- 初始对白第一页
tNpcGossip[18577]["Text5-2"] = {511,512,513}		-- 初始对白第二页
tNpcGossip[18577]["Text5-3"] = {531}				-- 等级不足
tNpcGossip[18577]["Text5-4"] = {541}				-- 背包空间不足
tNpcGossip[18577]["Text5-5"] = {551}				-- 未拥有
tNpcGossip[18577]["Text5-6"] = {561}				-- 包裹内已有
tNpcGossip[18577]["Text5-7"] = {571}				-- 补领超过三次
tNpcGossip[18577]["Text5-8"] = {581}				-- 免费补领二次确认
tNpcGossip[18577]["Text5-9"] = {591}				-- 天石补领二次确认
tNpcGossip[18577]["Text511"] = tFestivalCardMonth_Text[18577]["Text511"]
tNpcGossip[18577]["Text512"] = tFestivalCardMonth_Text[18577]["Text512"]
tNpcGossip[18577]["Text513"] = tFestivalCardMonth_Text[18577]["Text513"]
tNpcGossip[18577]["Text531"] = tFestivalCardMonth_Text[18577]["Text531"]
tNpcGossip[18577]["Text541"] = tFestivalCardMonth_Text[18577]["Text541"]
tNpcGossip[18577]["Text551"] = tFestivalCardMonth_Text[18577]["Text551"]
tNpcGossip[18577]["Text561"] = tFestivalCardMonth_Text[18577]["Text561"]
tNpcGossip[18577]["Text571"] = tFestivalCardMonth_Text[18577]["Text571"]
tNpcGossip[18577]["Text581"] = tFestivalCardMonth_Text[18577]["Text581"]
tNpcGossip[18577]["Text591"] = tFestivalCardMonth_Text[18577]["Text591"]

--选项
tNpcGossip[18577]["tOption5-1"] = {511,512,513,514,515,516,517,518}
tNpcGossip[18577]["tOption5-2"] = {521,522,523,524,525,526,527,528}
tNpcGossip[18577]["tOption5-3"] = {531}
tNpcGossip[18577]["tOption5-4"] = {532}
tNpcGossip[18577]["tOption5-5"] = {532}
tNpcGossip[18577]["tOption5-6"] = {532}
tNpcGossip[18577]["tOption5-7"] = {532}
tNpcGossip[18577]["tOption5-8"] = {581,582}
tNpcGossip[18577]["tOption5-9"] = {581,582}
-- 第一页
tNpcGossip[18577]["Option511"] = tFestivalCardMonth_Text[18577]["Option511"]
tNpcGossip[18577]["Option512"] = tFestivalCardMonth_Text[18577]["Option512"]
tNpcGossip[18577]["Option513"] = tFestivalCardMonth_Text[18577]["Option513"]
tNpcGossip[18577]["Option514"] = tFestivalCardMonth_Text[18577]["Option514"]
tNpcGossip[18577]["Option515"] = tFestivalCardMonth_Text[18577]["Option515"]
tNpcGossip[18577]["Option516"] = tFestivalCardMonth_Text[18577]["Option516"]
tNpcGossip[18577]["Option517"] = tFestivalCardMonth_Text[18577]["Option517"]
tNpcGossip[18577]["Option518"] = tFestivalCardMonth_Text[18577]["Option518"]
tNpcGossip[18577]["OptionFunc511"] = "FestivalCardMonth_SupGodCard</N>18577</N>3006620"
tNpcGossip[18577]["OptionFunc512"] = "FestivalCardMonth_SupGodCard</N>18577</N>3006621"
tNpcGossip[18577]["OptionFunc513"] = "FestivalCardMonth_SupGodCard</N>18577</N>3006622"
tNpcGossip[18577]["OptionFunc514"] = "FestivalCardMonth_SupGodCard</N>18577</N>3006623"
tNpcGossip[18577]["OptionFunc515"] = "FestivalCardMonth_SupGodCard</N>18577</N>3006624"
tNpcGossip[18577]["OptionFunc516"] = "FestivalCardMonth_SupGodCard</N>18577</N>3006625"
tNpcGossip[18577]["OptionPoint517"] = "5-2"

-- 第二页
tNpcGossip[18577]["Option521"] = tFestivalCardMonth_Text[18577]["Option521"]
tNpcGossip[18577]["Option522"] = tFestivalCardMonth_Text[18577]["Option522"]
tNpcGossip[18577]["Option523"] = tFestivalCardMonth_Text[18577]["Option523"]
tNpcGossip[18577]["Option524"] = tFestivalCardMonth_Text[18577]["Option524"]
tNpcGossip[18577]["Option525"] = tFestivalCardMonth_Text[18577]["Option525"]
tNpcGossip[18577]["Option526"] = tFestivalCardMonth_Text[18577]["Option526"]
tNpcGossip[18577]["Option527"] = tFestivalCardMonth_Text[18577]["Option527"]
tNpcGossip[18577]["Option528"] = tFestivalCardMonth_Text[18577]["Option528"]
tNpcGossip[18577]["Option531"] = tFestivalCardMonth_Text[18577]["Option531"]
tNpcGossip[18577]["Option532"] = tFestivalCardMonth_Text[18577]["Option532"]
tNpcGossip[18577]["Option581"] = tFestivalCardMonth_Text[18577]["Option581"]
tNpcGossip[18577]["Option582"] = tFestivalCardMonth_Text[18577]["Option582"]
tNpcGossip[18577]["OptionFunc521"] = "FestivalCardMonth_SupGodCard</N>18577</N>3006626"
tNpcGossip[18577]["OptionFunc522"] = "FestivalCardMonth_SupGodCard</N>18577</N>3006627"
tNpcGossip[18577]["OptionFunc523"] = "FestivalCardMonth_SupGodCard</N>18577</N>3006628"
tNpcGossip[18577]["OptionFunc524"] = "FestivalCardMonth_SupGodCard</N>18577</N>3006629"
tNpcGossip[18577]["OptionFunc525"] = "FestivalCardMonth_SupGodCard</N>18577</N>3006630"
tNpcGossip[18577]["OptionFunc526"] = "FestivalCardMonth_SupGodCard</N>18577</N>3006631"
tNpcGossip[18577]["OptionPoint527"] = "5-1"
tNpcGossip[18577]["OptionFunc581"] = ""

-- 【了解活动详情。】
tNpcGossip[18577]["Text6-1"] = {611,612,613}		-- 初始对白
tNpcGossip[18577]["Text6-2"] = {621,622,623}		-- 主神卡如何获得？
tNpcGossip[18577]["Text6-3"] = {631,632,633}		-- 主神卡如何升级？
tNpcGossip[18577]["Text6-4"] = {641,642}			-- 圣物卡如何获得？
tNpcGossip[18577]["Text6-5"] = {651,652,653}		-- 圣物卡如何打造？
tNpcGossip[18577]["Text6-6"] = {661,662,663}		-- 了解恶魔挑战。
tNpcGossip[18577]["Text6-7"] = {671,672,673}		-- 了解奥林匹斯的宝藏。

tNpcGossip[18577]["Text611"] = tFestivalCardMonth_Text[18577]["Text611"]
tNpcGossip[18577]["Text612"] = tFestivalCardMonth_Text[18577]["Text612"]
tNpcGossip[18577]["Text613"] = tFestivalCardMonth_Text[18577]["Text613"]
tNpcGossip[18577]["Text621"] = tFestivalCardMonth_Text[18577]["Text621"]
tNpcGossip[18577]["Text622"] = tFestivalCardMonth_Text[18577]["Text622"]
tNpcGossip[18577]["Text623"] = tFestivalCardMonth_Text[18577]["Text623"]
tNpcGossip[18577]["Text631"] = tFestivalCardMonth_Text[18577]["Text631"]
tNpcGossip[18577]["Text632"] = tFestivalCardMonth_Text[18577]["Text632"]
tNpcGossip[18577]["Text633"] = tFestivalCardMonth_Text[18577]["Text633"]
tNpcGossip[18577]["Text641"] = tFestivalCardMonth_Text[18577]["Text641"]
tNpcGossip[18577]["Text642"] = tFestivalCardMonth_Text[18577]["Text642"]
tNpcGossip[18577]["Text651"] = tFestivalCardMonth_Text[18577]["Text651"]
tNpcGossip[18577]["Text652"] = tFestivalCardMonth_Text[18577]["Text652"]
tNpcGossip[18577]["Text653"] = tFestivalCardMonth_Text[18577]["Text653"]
tNpcGossip[18577]["Text661"] = tFestivalCardMonth_Text[18577]["Text661"]
tNpcGossip[18577]["Text662"] = tFestivalCardMonth_Text[18577]["Text662"]
tNpcGossip[18577]["Text663"] = tFestivalCardMonth_Text[18577]["Text663"]
tNpcGossip[18577]["Text671"] = tFestivalCardMonth_Text[18577]["Text671"]
tNpcGossip[18577]["Text672"] = tFestivalCardMonth_Text[18577]["Text672"]
tNpcGossip[18577]["Text673"] = tFestivalCardMonth_Text[18577]["Text673"]
--选项
tNpcGossip[18577]["tOption6-1"] = {60,61,62,63,64,65,66,67}
tNpcGossip[18577]["tOption6-2"] = {68,31,69}
tNpcGossip[18577]["tOption6-3"] = {68,69}
tNpcGossip[18577]["tOption6-4"] = {68,69}
tNpcGossip[18577]["tOption6-5"] = {68,69}
tNpcGossip[18577]["tOption6-6"] = {68,69}
tNpcGossip[18577]["tOption6-7"] = {68,69}
tNpcGossip[18577]["Option60"] = tFestivalCardMonth_Text[18577]["Option60"]
tNpcGossip[18577]["Option61"] = tFestivalCardMonth_Text[18577]["Option61"]
tNpcGossip[18577]["Option62"] = tFestivalCardMonth_Text[18577]["Option62"]
tNpcGossip[18577]["Option63"] = tFestivalCardMonth_Text[18577]["Option63"]
tNpcGossip[18577]["Option64"] = tFestivalCardMonth_Text[18577]["Option64"]
tNpcGossip[18577]["Option65"] = tFestivalCardMonth_Text[18577]["Option65"]
tNpcGossip[18577]["Option66"] = tFestivalCardMonth_Text[18577]["Option66"]
tNpcGossip[18577]["Option67"] = tFestivalCardMonth_Text[18577]["Option67"]
tNpcGossip[18577]["Option68"] = tFestivalCardMonth_Text[18577]["Option68"]
tNpcGossip[18577]["Option69"] = tFestivalCardMonth_Text[18577]["Option69"]
tNpcGossip[18577]["OptionPoint60"] = "6-2"
tNpcGossip[18577]["OptionPoint61"] = "6-3"
tNpcGossip[18577]["OptionPoint62"] = "6-4"
tNpcGossip[18577]["OptionPoint63"] = "6-5"
tNpcGossip[18577]["OptionPoint64"] = "6-6"
tNpcGossip[18577]["OptionPoint65"] = "6-7"
tNpcGossip[18577]["OptionPoint66"] = "1"
tNpcGossip[18577]["OptionPoint68"] = "6"


--------------------------------------
-- 【==奥林匹斯的宝藏==】
tNpcGossip[18578] = tNpcGossip[18578] or DefaultNpc:new{}
tNpcGossip[18578]["OptionHidden"] = 1

tNpcGossip[18578]["Text1-1"] = {111} 				-- 活动时间外
tNpcGossip[18578]["Text1-2"] = {121,122,124} 	-- 初始对白
tNpcGossip[18578]["Text1-3"] = {131} 				-- 所有宝藏已领取
tNpcGossip[18578]["Text1-4"] = {141,142} 				-- 开宝箱失败
tNpcGossip[18578]["Text1-5"] = {151} 				-- 背包空间不足
tNpcGossip[18578]["Text1-6"] = {161} 				-- 点天石数达上限
tNpcGossip[18578]["Text1-7"] = {171} 				-- 战胜3\6\9个恶魔奖励
tNpcGossip[18578]["Text1-8"] = {181} 				-- 战胜所有恶魔奖励（10名以内）
tNpcGossip[18578]["Text1-9"] = {191} 				-- 战胜所有恶魔奖励（10名以下）
tNpcGossip[18578]["Text111"] = tFestivalCardMonth_Text[18578]["Text111"]
tNpcGossip[18578]["Text121"] = tFestivalCardMonth_Text[18578]["Text121"]
tNpcGossip[18578]["Text122"] = tFestivalCardMonth_Text[18578]["Text122"]
tNpcGossip[18578]["Text124"] = tFestivalCardMonth_Text[18578]["Text124"]
tNpcGossip[18578]["Text131"] = tFestivalCardMonth_Text[18578]["Text131"]
tNpcGossip[18578]["Text141"] = tFestivalCardMonth_Text[18578]["Text141"]
tNpcGossip[18578]["Text142"] = tFestivalCardMonth_Text[18578]["Text142"]
tNpcGossip[18578]["Text151"] = tFestivalCardMonth_Text[18578]["Text151"]
tNpcGossip[18578]["Text161"] = tFestivalCardMonth_Text[18578]["Text161"]
tNpcGossip[18578]["Text171"] = tFestivalCardMonth_Text[18578]["Text171"]
tNpcGossip[18578]["Text181"] = tFestivalCardMonth_Text[18578]["Text181"]
tNpcGossip[18578]["Text191"] = tFestivalCardMonth_Text[18578]["Text191"]
tNpcGossip[18578]["ChkFunc1-1"] = function ()
	-- 活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		FestivalCardMonth_ChgMap(18591)
		return true
	else
		return false
	end
end
tNpcGossip[18578]["ChkFunc1-2"] = function ()
	local nDynaGlobalData0 = Get_SysDynaGlobalData0(tFestivalCardMonth_DynaGlobal[1])
	tNpcGossip[18578]["Text124"] = string.format(tFestivalCardMonth_Text[18578]["Text124"],nDynaGlobalData0)
	return true
end
--选项
tNpcGossip[18578]["tOption1-1"] = {11}
tNpcGossip[18578]["tOption1-2"] = {12,13,14,15}
tNpcGossip[18578]["tOption1-3"] = {16}
tNpcGossip[18578]["tOption1-4"] = {17}
tNpcGossip[18578]["tOption1-5"] = {18}
tNpcGossip[18578]["tOption1-6"] = {19}
tNpcGossip[18578]["tOption1-7"] = {20}
tNpcGossip[18578]["tOption1-8"] = {21}
tNpcGossip[18578]["tOption1-9"] = {22}
tNpcGossip[18578]["Option11"] = tFestivalCardMonth_Text[18578]["Option11"]
tNpcGossip[18578]["Option12"] = tFestivalCardMonth_Text[18578]["Option12"]
tNpcGossip[18578]["Option13"] = tFestivalCardMonth_Text[18578]["Option13"]
tNpcGossip[18578]["Option14"] = tFestivalCardMonth_Text[18578]["Option14"]
tNpcGossip[18578]["Option15"] = tFestivalCardMonth_Text[18578]["Option15"]
tNpcGossip[18578]["Option16"] = tFestivalCardMonth_Text[18578]["Option16"]
tNpcGossip[18578]["Option17"] = tFestivalCardMonth_Text[18578]["Option17"]
tNpcGossip[18578]["Option18"] = tFestivalCardMonth_Text[18578]["Option18"]
tNpcGossip[18578]["Option19"] = tFestivalCardMonth_Text[18578]["Option19"]
tNpcGossip[18578]["Option20"] = tFestivalCardMonth_Text[18578]["Option20"]
tNpcGossip[18578]["Option21"] = tFestivalCardMonth_Text[18578]["Option21"]
tNpcGossip[18578]["Option22"] = tFestivalCardMonth_Text[18578]["Option22"]
tNpcGossip[18578]["OptionFunc12"] = "FestivalCardMonth_OpenGodBox</N>18578"
tNpcGossip[18578]["OptionFunc13"] = "FestivalCardMonth_IntoMap</N>18578"
tNpcGossip[18578]["OptionPoint14"] = "3"


-- 【进入奥林匹斯之心。】
tNpcGossip[18578]["Text2-1"] = {211} 				-- 没有完成所有恶魔挑战
tNpcGossip[18578]["Text2-2"] = {221} 				-- 已进入过一次
tNpcGossip[18578]["Text211"] = tFestivalCardMonth_Text[18578]["Text211"]
tNpcGossip[18578]["Text221"] = tFestivalCardMonth_Text[18578]["Text221"]
-- 选项
tNpcGossip[18578]["tOption2-1"] = {211}
tNpcGossip[18578]["tOption2-2"] = {221}
tNpcGossip[18578]["Option211"] = tFestivalCardMonth_Text[18578]["Option211"]
tNpcGossip[18578]["Option221"] = tFestivalCardMonth_Text[18578]["Option221"]


-- 【查看宝藏详情】
tNpcGossip[18578]["Text3-1"] = {311,312,313,314,315} 				-- 初始对白
tNpcGossip[18578]["Text3-2"] = {321,322,323,324,325,326} 				-- 查看前5名奖励
tNpcGossip[18578]["Text3-3"] = {331,332,333,334,335,336,337} 				-- 查看5名之后奖励。
tNpcGossip[18578]["Text311"] = tFestivalCardMonth_Text[18578]["Text311"]
tNpcGossip[18578]["Text312"] = tFestivalCardMonth_Text[18578]["Text312"]
tNpcGossip[18578]["Text313"] = tFestivalCardMonth_Text[18578]["Text313"]
tNpcGossip[18578]["Text314"] = tFestivalCardMonth_Text[18578]["Text314"]
tNpcGossip[18578]["Text315"] = tFestivalCardMonth_Text[18578]["Text315"]
tNpcGossip[18578]["Text321"] = tFestivalCardMonth_Text[18578]["Text321"]
tNpcGossip[18578]["Text322"] = tFestivalCardMonth_Text[18578]["Text322"]
tNpcGossip[18578]["Text323"] = tFestivalCardMonth_Text[18578]["Text323"]
tNpcGossip[18578]["Text324"] = tFestivalCardMonth_Text[18578]["Text324"]
tNpcGossip[18578]["Text325"] = tFestivalCardMonth_Text[18578]["Text325"]
tNpcGossip[18578]["Text326"] = tFestivalCardMonth_Text[18578]["Text326"]
tNpcGossip[18578]["Text331"] = tFestivalCardMonth_Text[18578]["Text331"]
tNpcGossip[18578]["Text332"] = tFestivalCardMonth_Text[18578]["Text332"]
tNpcGossip[18578]["Text333"] = tFestivalCardMonth_Text[18578]["Text333"]
tNpcGossip[18578]["Text334"] = tFestivalCardMonth_Text[18578]["Text334"]
tNpcGossip[18578]["Text335"] = tFestivalCardMonth_Text[18578]["Text335"]
tNpcGossip[18578]["Text336"] = tFestivalCardMonth_Text[18578]["Text336"]
tNpcGossip[18578]["Text337"] = tFestivalCardMonth_Text[18578]["Text337"]
-- 选项
tNpcGossip[18578]["tOption3-1"] = {311,312,313,314}
tNpcGossip[18578]["tOption3-2"] = {321,322}
tNpcGossip[18578]["tOption3-3"] = {331,332}
tNpcGossip[18578]["Option311"] = tFestivalCardMonth_Text[18578]["Option311"]
tNpcGossip[18578]["Option312"] = tFestivalCardMonth_Text[18578]["Option312"]
tNpcGossip[18578]["Option313"] = tFestivalCardMonth_Text[18578]["Option313"]
tNpcGossip[18578]["Option314"] = tFestivalCardMonth_Text[18578]["Option314"]
tNpcGossip[18578]["Option321"] = tFestivalCardMonth_Text[18578]["Option321"]
tNpcGossip[18578]["Option322"] = tFestivalCardMonth_Text[18578]["Option322"]
tNpcGossip[18578]["Option331"] = tFestivalCardMonth_Text[18578]["Option331"]
tNpcGossip[18578]["Option332"] = tFestivalCardMonth_Text[18578]["Option332"]
tNpcGossip[18578]["OptionPoint311"] = "3-2"
tNpcGossip[18578]["OptionPoint312"] = "3-3"
tNpcGossip[18578]["OptionPoint313"] = "1-2"
tNpcGossip[18578]["OptionPoint321"] = "3-1"
tNpcGossip[18578]["OptionPoint331"] = "3-1"

------------------------------------------
-- 【==万妖之祖堤丰==】
tNpcGossip[18579] = tNpcGossip[18579] or DefaultNpc:new{}
tNpcGossip[18580] = tNpcGossip[18579] or DefaultNpc:new{}
tNpcGossip[18581] = tNpcGossip[18579] or DefaultNpc:new{}
tNpcGossip[18582] = tNpcGossip[18579] or DefaultNpc:new{}
tNpcGossip[18583] = tNpcGossip[18579] or DefaultNpc:new{}
tNpcGossip[18584] = tNpcGossip[18579] or DefaultNpc:new{}
tNpcGossip[18585] = tNpcGossip[18579] or DefaultNpc:new{}
tNpcGossip[18586] = tNpcGossip[18579] or DefaultNpc:new{}
tNpcGossip[18587] = tNpcGossip[18579] or DefaultNpc:new{}
tNpcGossip[18588] = tNpcGossip[18579] or DefaultNpc:new{}
tNpcGossip[18589] = tNpcGossip[18579] or DefaultNpc:new{}
tNpcGossip[18590] = tNpcGossip[18579] or DefaultNpc:new{}
tNpcGossip[18579]["OptionHidden"] = 1

---【起始对白】
tNpcGossip[18579]["Text1-1"] = {111}			-- 活动时间外
tNpcGossip[18579]["Text1-2"] = {121,122,123} 	-- 初始对白
tNpcGossip[18579]["Text1-3"] = {131} 			-- 没有主神卡
tNpcGossip[18579]["Text1-4"] = {141,142,143,144} 		-- 确认挑战
tNpcGossip[18579]["Text1-5"] = {151} 			-- 免费挑战次数不足
tNpcGossip[18579]["Text1-6"] = {161} 			-- 背包空间不足
tNpcGossip[18579]["Text1-7"] = {171} 			-- 挑战完成提示
tNpcGossip[18579]["Text1-8"] = {181} 			-- 天石不足
tNpcGossip[18579]["Text1-9"] = {191} 			-- 击败恶魔给奖励
tNpcGossip[18579]["Text111"] = tFestivalCardMonth_Text[18579]["Text111"]
tNpcGossip[18579]["Text121"] = tFestivalCardMonth_Text[18579]["Text121"]
tNpcGossip[18579]["Text122"] = tFestivalCardMonth_Text[18579]["Text122"]
tNpcGossip[18579]["Text123"] = tFestivalCardMonth_Text[18579]["Text123"]
tNpcGossip[18579]["Text131"] = tFestivalCardMonth_Text[18579]["Text131"]
tNpcGossip[18579]["Text141"] = tFestivalCardMonth_Text[18579]["Text141"]
tNpcGossip[18579]["Text142"] = tFestivalCardMonth_Text[18579]["Text142"]
tNpcGossip[18579]["Text151"] = tFestivalCardMonth_Text[18579]["Text151"]
tNpcGossip[18579]["Text161"] = tFestivalCardMonth_Text[18579]["Text161"]
tNpcGossip[18579]["Text171"] = tFestivalCardMonth_Text[18579]["Text171"]
tNpcGossip[18579]["Text181"] = tFestivalCardMonth_Text[18579]["Text181"]
tNpcGossip[18579]["Text191"] = tFestivalCardMonth_Text[18579]["Text191"]
tNpcGossip[18579]["ChkFunc1-1"] = function ()
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		FestivalCardMonth_ChgMap(18591)
		return true
	else
		return false
	end
end
tNpcGossip[18579]["ChkFunc1-2"] = function ()
	local nActNpcId = Get_NpcId()
	local nEventData_4 = tFestivalCardMonth_Stc[4][nActNpcId]["EventData"]
	local nTypeData_4 = tFestivalCardMonth_Stc[4][nActNpcId]["TypeData"]
	local nComplete_4 = tFestivalCardMonth_Stc[4]["Complete"]
	local sPhase = ""
	
	-- 阶段初始化
	if Task_ChkStcValue(nEventData_4,nTypeData_4,"==",0) then
		Task_SetStatistic(nEventData_4,nTypeData_4,1,1)
	end
	
	local nEventData_6 = tFestivalCardMonth_Stc[6]["EventData"]
	local nTypeData_6 = tFestivalCardMonth_Stc[6]["TypeData"]
	local nValue_6 = tFestivalCardMonth_Stc[6]["Value"]
	
	-- 免费挑战次数初始化
	if FestivalCardMonth_MultiStc(1) then
		Task_SetStatistic(nEventData_6,nTypeData_6,nValue_6,1)
		Task_SetStcTimestamp(nEventData_6,nTypeData_6,0)
	end
	
	-- 隔天重置次数
	if Task_StcInterval(nEventData_6,nTypeData_6,1,4) then
		-- 是否有10次以上
		if not Task_ChkStcValue(nEventData_6,nTypeData_6,">=",nValue_6) then
			Task_SetStatistic(nEventData_6,nTypeData_6,nValue_6,1)
			Task_SetStcTimestamp(nEventData_6,nTypeData_6,0)
		end
	end
	
	local nNpcId = Get_NpcId()
	--是否完成挑战
	if Task_ChkStcValue(nEventData_4,nTypeData_4,">=",nComplete_4) then
		local nGodCardId = tFestivalCardMonth_Demon[nNpcId]
		local sGodName = Get_ItemtypeName(nGodCardId)
		sPhase = tFestivalCardMonth_Text["FightComplete"]
		sPhaseAward = string.format(tFestivalCardMonth_Text["FightCompleteAwrad"],sGodName)
	else
		sPhase = Get_UserStatisticValue(nEventData_4,nTypeData_4)
		sPhaseAward = tFestivalCardMonth_Text["PhaseAward"][nActNpcId][sPhase]
	end
	
	tNpcGossip[18579]["Text121"] = tFestivalCardMonth_Text[nActNpcId]["Text121"]
	tNpcGossip[18579]["Text122"] = tFestivalCardMonth_Text[nActNpcId]["Text122"]
	tNpcGossip[18579]["Text123"] = string.format(tFestivalCardMonth_Text[18579]["Text123"],sPhase,sPhaseAward)
	tNpcGossip[18579]["OptionFunc12"] = string.format("FestivalCardMonth_FightDemon</N>%d</N>%d",nNpcId,nActNpcId)
	return true
end
--选项
tNpcGossip[18579]["tOption1-1"] = {11}
tNpcGossip[18579]["tOption1-2"] = {12,13}
tNpcGossip[18579]["tOption1-3"] = {14}
tNpcGossip[18579]["tOption1-4"] = {15,16}
tNpcGossip[18579]["tOption1-5"] = {17,23,18}
tNpcGossip[18579]["tOption1-6"] = {19}
tNpcGossip[18579]["tOption1-7"] = {20}
tNpcGossip[18579]["tOption1-8"] = {21}
tNpcGossip[18579]["tOption1-9"] = {22}
tNpcGossip[18579]["Option11"] = tFestivalCardMonth_Text[18579]["Option11"]
tNpcGossip[18579]["Option12"] = tFestivalCardMonth_Text[18579]["Option12"]
tNpcGossip[18579]["Option13"] = tFestivalCardMonth_Text[18579]["Option13"]
tNpcGossip[18579]["Option14"] = tFestivalCardMonth_Text[18579]["Option14"]
tNpcGossip[18579]["Option15"] = tFestivalCardMonth_Text[18579]["Option15"]
tNpcGossip[18579]["Option16"] = tFestivalCardMonth_Text[18579]["Option16"]
tNpcGossip[18579]["Option17"] = tFestivalCardMonth_Text[18579]["Option17"]
tNpcGossip[18579]["Option18"] = tFestivalCardMonth_Text[18579]["Option18"]
tNpcGossip[18579]["Option19"] = tFestivalCardMonth_Text[18579]["Option19"]
tNpcGossip[18579]["Option20"] = tFestivalCardMonth_Text[18579]["Option20"]
tNpcGossip[18579]["Option21"] = tFestivalCardMonth_Text[18579]["Option21"]
tNpcGossip[18579]["Option22"] = tFestivalCardMonth_Text[18579]["Option22"]
tNpcGossip[18579]["Option23"] = tFestivalCardMonth_Text[18579]["Option23"]
tNpcGossip[18579]["OptionFunc12"] = "FestivalCardMonth_FightDemon</N>18579</N>18579"
tNpcGossip[18579]["OptionFunc15"] = "FestivalCardMonth_FightDone</N>18579</N>18579"
tNpcGossip[18579]["OptionFunc17"] = "FestivalCardMonth_FightNoFree"
tNpcGossip[18579]["OptionFunc23"] = "FestivalCardMonth_FightNoFree"
tNpcGossip[18579]["OptionFunc22"] = "FestivalCardMonth_FightDemon</N>18579</N>18579"



------------------------------------------物品配置-------------------------------------------
------------------------------------------------【12主神卡】------------------------------------------------
---------------------物品头像
tItemFace[3006620] = 275
tItemFace[3006621] = 276
tItemFace[3006622] = 277
tItemFace[3006623] = 278
tItemFace[3006624] = 279
tItemFace[3006625] = 280
tItemFace[3006626] = 281
tItemFace[3006627] = 282
tItemFace[3006628] = 283
tItemFace[3006629] = 284
tItemFace[3006630] = 285
tItemFace[3006631] = 286
------------------------------------------------
tItem[3006620] = tItem[3006620] or {}
tItem[3006621] = tItem[3006620] or {}
tItem[3006622] = tItem[3006620] or {}
tItem[3006623] = tItem[3006620] or {}
tItem[3006624] = tItem[3006620] or {}
tItem[3006625] = tItem[3006620] or {}
tItem[3006626] = tItem[3006620] or {}
tItem[3006627] = tItem[3006620] or {}
tItem[3006628] = tItem[3006620] or {}
tItem[3006629] = tItem[3006620] or {}
tItem[3006630] = tItem[3006620] or {}
tItem[3006631] = tItem[3006620] or {}
tItem[3006620]["Function"] = function (nItemId,sItemName)
	--接入对白函数
	FestivalCardMonth_GodCard_Main(nItemId,sItemName)
end


------------------------------------------------【主神卡包】------------------------------------------------
tItem[3006632] = tItem[3006632] or {}
tItem[3006633] = tItem[3006632] or {}
tItem[3006634] = tItem[3006632] or {}
tItem[3006635] = tItem[3006632] or {}
tItem[3006636] = tItem[3006632] or {}
tItem[3006637] = tItem[3006632] or {}
tItem[3006638] = tItem[3006632] or {}
tItem[3006639] = tItem[3006632] or {}
tItem[3006640] = tItem[3006632] or {}
tItem[3006641] = tItem[3006632] or {}
tItem[3006642] = tItem[3006632] or {}
tItem[3006643] = tItem[3006632] or {}
tItem[3006632]["Function"] = function (nItemId,sItemName)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		for i = 0, tFestivalCardMonth_Probabil[1][3]["ItemChanceSum"] - 1 do
			nDelItemId = 3006632 + i
			if Item_ChkItem(nDelItemId) then
				Item_DelAllItemByType(nDelItemId)
			end
		end
		
		local sTalkText = tFestivalCardMonth_Text["Item_TimeOut"]
		User_TalkChannel2005(sTalkText)
		return
	end
	
	local nGodCardId = tFestivalCardMonth_CardPag[nItemId]
	local nEventData_2 = tFestivalCardMonth_Stc[2][nGodCardId]["EventData"]
	local nTypeData_2 = tFestivalCardMonth_Stc[2][nGodCardId]["TypeData"]
	local nValue_2 = tFestivalCardMonth_Stc[2]["Value"]
	local sLogText = ""
	local sTalkText = ""
	
	--是否已获得过主神卡
	if Task_ChkStcValue(nEventData_2,nTypeData_2,">=",nValue_2) then
		
		--判断背包空间
		if not User_CheckLeftSpace(tFestivalCardMonth_Data["ChkSpace3"]) then
			Sys_MsgBox(tFestivalCardMonth_Text["CardPag_PagFull"])
			return
		end
		
		--删除卡包
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			
			--给圣物卡
			for nHolyNum = 1, #tFestivalCardMonth_ArtifactCard[nGodCardId] do
				Item_AddItem(tFestivalCardMonth_ArtifactCard[nGodCardId][nHolyNum])
			end
			
			--LOG和提示数据组合
			local nHolyId1 = tFestivalCardMonth_ArtifactCard[nGodCardId][1]
			local nHolyId2 = tFestivalCardMonth_ArtifactCard[nGodCardId][2]
			local nHolyId3 = tFestivalCardMonth_ArtifactCard[nGodCardId][3]
			local sHolyName = tFestivalCardMonth_Text["HolyCard"][nGodCardId]
			sLogText = string.format(tFestivalCardMonth_Log["CardPag_GetHoly"],nItemId,nHolyId1,nHolyId2,nHolyId3)
			sTalkText = string.format(tFestivalCardMonth_Text["CardPag_GetHoly"],sItemName,sHolyName)
		end
	
	--未获得主神卡
	elseif not User_CheckLeftSpace(tFestivalCardMonth_Data["ChkSpace1"]) then
		--判断背包空间
		Sys_MsgBox(tFestivalCardMonth_Text["CardPag_PagFull"])
		return
		
	elseif Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		local nEventData_1 = tFestivalCardMonth_Stc[1]["EventData"]
		local nTypeData_1 = tFestivalCardMonth_Stc[1]["TypeData"]
		local nGetCard = tFestivalCardMonth_Stc[1]["GetGodCard"]
		--给积分
		Task_AddStatistic(nEventData_1,nTypeData_1,nGetCard,1)
		
		--主神卡初始化
		local nGodCardId = tFestivalCardMonth_CardPag[nItemId]
		FestivalCardMonth_GodCard_Define(nGodCardId)
		
		--给主神卡
		Item_AddItem(nGodCardId)
		
		--LOG和提示数据组合
		local sGodCardName = tFestivalCardMonth_Text["GodCard"][nGodCardId]
		sLogText = string.format(tFestivalCardMonth_Log["CardPag_GetGodCard"],nItemId,nGodCardId)
		sTalkText = string.format(tFestivalCardMonth_Text["CardPag_GetGodCard"],sItemName,sGodCardName)
	end
	
	--LOG+提示
	User_EffectAdd(tFestivalCardMonth_Data["EffectObj"],tFestivalCardMonth_Data["Effect_1"])
	Sys_SaveActionFestivalLog(sLogText)
	User_TalkChannel2005(sTalkText)
end



------------------------------------------------【主神卡碎片】------------------------------------------------
tItem[3006644] = tItem[3006644] or {}
tItem[3006645] = tItem[3006644] or {}
tItem[3006646] = tItem[3006644] or {}
tItem[3006647] = tItem[3006644] or {}
tItem[3006648] = tItem[3006644] or {}
tItem[3006649] = tItem[3006644] or {}
tItem[3006650] = tItem[3006644] or {}
tItem[3006651] = tItem[3006644] or {}
tItem[3006652] = tItem[3006644] or {}
tItem[3006653] = tItem[3006644] or {}
tItem[3006654] = tItem[3006644] or {}
tItem[3006655] = tItem[3006644] or {}
tItem[3006644]["Function"] = function (nItemId,sItemName)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		for i = 0, tFestivalCardMonth_Probabil[1][3]["ItemChanceSum"] - 1 do
			nDelItemId = 3006644 + i
			if Item_ChkItem(nDelItemId) then
				Item_DelAllItemByType(nDelItemId)
			end
		end
		
		local sTalkText = tFestivalCardMonth_Text["Item_TimeOut"]
		User_TalkChannel2005(sTalkText)
		return
	end
	
	-- 背包空间
	if not User_CheckLeftSpace(tFestivalCardMonth_Data["ChkSpace1"]) then
		User_TalkChannel2005(tFestivalCardMonth_Text["CardPag_PagFull"])
		return
	end
	
	local nCarPagId = tFestivalCardMonth_CardPiece[nItemId]
	local sPagName = tFestivalCardMonth_Text["CardPag"][nCarPagId]

	--是否有10张主神卡碎片
	if not Item_ChkMulItem(nItemId,nItemId,tFestivalCardMonth_Data["CardPieceNum"]) then
		local sMsgText = string.format(tFestivalCardMonth_Text["CardPiece_Fail"],sItemName,sPagName)
		Sys_MsgBox(sMsgText)
		return
	end
	
	--删除成功
	if Item_DelMulItem(nItemId,nItemId,tFestivalCardMonth_Data["CardPieceNum"]) then
		Item_AddItem(nCarPagId)
		local sLogText = string.format(tFestivalCardMonth_Log["CardPiece_Success"],nItemId,nCarPagId)
		local sTalkText = string.format(tFestivalCardMonth_Text["CardPiece_Success"],sItemName,sPagName)
		User_EffectAdd(tFestivalCardMonth_Data["EffectObj"],tFestivalCardMonth_Data["Effect_4"])
		Sys_SaveActionFestivalLog(sLogText)
		User_TalkChannel2005(sTalkText)
	end
end


------------------------------------------------【圣物卡】------------------------------------------------
tItem[3006656] = tItem[3006656] or {}
tItem[3006657] = tItem[3006656] or {}
tItem[3006658] = tItem[3006656] or {}
tItem[3006659] = tItem[3006656] or {}
tItem[3006660] = tItem[3006656] or {}
tItem[3006661] = tItem[3006656] or {}
tItem[3006662] = tItem[3006656] or {}
tItem[3006663] = tItem[3006656] or {}
tItem[3006664] = tItem[3006656] or {}
tItem[3006665] = tItem[3006656] or {}
tItem[3006666] = tItem[3006656] or {}
tItem[3006667] = tItem[3006656] or {}
tItem[3006668] = tItem[3006656] or {}
tItem[3006669] = tItem[3006656] or {}
tItem[3006670] = tItem[3006656] or {}
tItem[3006671] = tItem[3006656] or {}
tItem[3006672] = tItem[3006656] or {}
tItem[3006673] = tItem[3006656] or {}
tItem[3006674] = tItem[3006656] or {}
tItem[3006675] = tItem[3006656] or {}
tItem[3006676] = tItem[3006656] or {}
tItem[3006677] = tItem[3006656] or {}
tItem[3006678] = tItem[3006656] or {}
tItem[3006679] = tItem[3006656] or {}
tItem[3006680] = tItem[3006656] or {}
tItem[3006681] = tItem[3006656] or {}
tItem[3006682] = tItem[3006656] or {}
tItem[3006683] = tItem[3006656] or {}
tItem[3006684] = tItem[3006656] or {}
tItem[3006685] = tItem[3006656] or {}
tItem[3006686] = tItem[3006656] or {}
tItem[3006687] = tItem[3006656] or {}
tItem[3006688] = tItem[3006656] or {}
tItem[3006689] = tItem[3006656] or {}
tItem[3006690] = tItem[3006656] or {}
tItem[3006691] = tItem[3006656] or {}
tItem[3006656]["Function"] = function (nItemId,sItemName)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then

		for i = 0, tFestivalCardMonth_Probabil[1][2]["ItemChanceSum"] - 1 do
			nDelItemId = 3006656 + i
			if Item_ChkItem(nDelItemId) then
				Item_DelAllItemByType(nDelItemId)
			end
		end
	
		local sTalkText = tFestivalCardMonth_Text["Item_TimeOut"]
		User_TalkChannel2005(sTalkText)
		return
	end

	-- Sys_DialogTaskClear()
	Sys_DialogText(tFestivalCardMonth_Text["HolyCard_DialogText1"][nItemId])
	Sys_DialogText(tFestivalCardMonth_Text["HolyCard_DialogText2"][nItemId])
	Sys_DialogOption(tFestivalCardMonth_Text["HolyCard_Option1"], "</F>FestivalCardMonth_HolyCard_DecomDecision</N>".. nItemId .."</S>".. sItemName)
	-- Sys_DialogOption(tFestivalCardMonth_Text["HolyCard_Option2"], "</F>NULL")
	Sys_DialogEnd()
end


------------------------------------------------【圣物卡碎片】------------------------------------------------
tItem[3006692] = tItem[3006692] or {}
tItem[3006692]["Function"] = function (nItemId,sItemName)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		if Item_ChkItem(nItemId) and Item_DelAllItemByType(nItemId) then
			local sTalkText = tFestivalCardMonth_Text["Item_TimeOut"]
			User_TalkChannel2005(sTalkText)
		end
		return
	end
	
	LinkItemGossipFunc_New(nItemId,"1-1")
end
tItem[3006692]["Text1-1"] = {111,112,113}		-- 初始对白
tItem[3006692]["Text1-2"] = {121}				-- 背包空间不足
tItem[3006692]["Text1-3"] = {131}				-- 数量不足
tItem[3006692]["Text1-4"] = {141}				-- 天石不足
tItem[3006692]["Text1-5"] = {151}				-- 天石二次确认
tItem[3006692]["Text111"] = tFestivalCardMonth_Text[3006692]["Text111"] 
tItem[3006692]["Text112"] = tFestivalCardMonth_Text[3006692]["Text112"]
tItem[3006692]["Text113"] = tFestivalCardMonth_Text[3006692]["Text113"]
tItem[3006692]["Text121"] = tFestivalCardMonth_Text[3006692]["Text121"]
tItem[3006692]["Text131"] = tFestivalCardMonth_Text[3006692]["Text131"]
tItem[3006692]["Text141"] = tFestivalCardMonth_Text[3006692]["Text141"]
tItem[3006692]["Text151"] = tFestivalCardMonth_Text[3006692]["Text151"]
tItem[3006692]["ChkFunc1-1"] = function ()
	local nEventData_8 = tFestivalCardMonth_Stc[8]["EventData"]
	local nTypeData_8 = tFestivalCardMonth_Stc[8]["TypeData"]
	local nValue_8 = tFestivalCardMonth_Stc[8]["Value"]
	
	-- 免费挑战次数初始化
	if FestivalCardMonth_MultiStc(3) then
		Task_SetStatistic(nEventData_8,nTypeData_8,nValue_8,1)
		Task_SetStcTimestamp(nEventData_8,nTypeData_8,0)
	end
	
	-- 隔天重置次数
	if Task_StcInterval(nEventData_8,nTypeData_8,1,4) then
		-- 次数是否超过10次
		if not Task_ChkStcValue(nEventData_8,nTypeData_8,">=",nValue_8) then
			Task_SetStatistic(nEventData_8,nTypeData_8,nValue_8,1)
			Task_SetStcTimestamp(nEventData_8,nTypeData_8,0)
		end
	end
	
	local nStcValue_8 = Get_UserStatisticValue(nEventData_8,nTypeData_8)
	tItem[3006692]["Text113"] = string.format(tFestivalCardMonth_Text[3006692]["Text113"],nStcValue_8)
	return true
end
-- 选项
tItem[3006692]["tOption1-1"] = {11,12}
tItem[3006692]["tOption1-2"] = {13}
tItem[3006692]["tOption1-3"] = {14}
tItem[3006692]["tOption1-4"] = {15}
tItem[3006692]["tOption1-5"] = {16,17}
tItem[3006692]["Option11"] = tFestivalCardMonth_Text[3006692]["Option11"]
tItem[3006692]["Option12"] = tFestivalCardMonth_Text[3006692]["Option12"]
tItem[3006692]["Option13"] = tFestivalCardMonth_Text[3006692]["Option13"]
tItem[3006692]["Option14"] = tFestivalCardMonth_Text[3006692]["Option14"]
tItem[3006692]["Option15"] = tFestivalCardMonth_Text[3006692]["Option15"]
tItem[3006692]["Option16"] = tFestivalCardMonth_Text[3006692]["Option16"]
tItem[3006692]["Option17"] = tFestivalCardMonth_Text[3006692]["Option17"]
tItem[3006692]["OptionFunc11"] = "FestivalCardMonth_CreateCard</N>3006692</N>10</N>0"
tItem[3006692]["OptionPoint12"] = "2"
tItem[3006692]["OptionFunc16"] = ""



-- 【指定打造】
tItem[3006692]["Text2-1"] = {211}		-- 选择主神（第一页）
tItem[3006692]["Text2-2"] = {221}		-- 选择主神（第二页）
tItem[3006692]["Text211"] = tFestivalCardMonth_Text[3006692]["Text211"]
tItem[3006692]["Text221"] = tFestivalCardMonth_Text[3006692]["Text221"]
-- 选项
tItem[3006692]["tOption2-1"] = {211,212,213,214,215,216,217,218}
tItem[3006692]["tOption2-2"] = {221,222,223,224,225,226,227,228}
tItem[3006692]["Option211"] = tFestivalCardMonth_Text[3006692]["Option211"]
tItem[3006692]["Option212"] = tFestivalCardMonth_Text[3006692]["Option212"]
tItem[3006692]["Option213"] = tFestivalCardMonth_Text[3006692]["Option213"]
tItem[3006692]["Option214"] = tFestivalCardMonth_Text[3006692]["Option214"]
tItem[3006692]["Option215"] = tFestivalCardMonth_Text[3006692]["Option215"]
tItem[3006692]["Option216"] = tFestivalCardMonth_Text[3006692]["Option216"]
tItem[3006692]["Option217"] = tFestivalCardMonth_Text[3006692]["Option217"]
tItem[3006692]["Option218"] = tFestivalCardMonth_Text[3006692]["Option218"]
tItem[3006692]["Option221"] = tFestivalCardMonth_Text[3006692]["Option221"]
tItem[3006692]["Option222"] = tFestivalCardMonth_Text[3006692]["Option222"]
tItem[3006692]["Option223"] = tFestivalCardMonth_Text[3006692]["Option223"]
tItem[3006692]["Option224"] = tFestivalCardMonth_Text[3006692]["Option224"]
tItem[3006692]["Option225"] = tFestivalCardMonth_Text[3006692]["Option225"]
tItem[3006692]["Option226"] = tFestivalCardMonth_Text[3006692]["Option226"]
tItem[3006692]["Option227"] = tFestivalCardMonth_Text[3006692]["Option227"]
tItem[3006692]["Option228"] = tFestivalCardMonth_Text[3006692]["Option228"]
tItem[3006692]["OptionPoint211"] = "3-1"
tItem[3006692]["OptionPoint212"] = "3-2"
tItem[3006692]["OptionPoint213"] = "3-3"
tItem[3006692]["OptionPoint214"] = "3-4"
tItem[3006692]["OptionPoint215"] = "3-5"
tItem[3006692]["OptionPoint216"] = "3-6"
tItem[3006692]["OptionPoint217"] = "2-2"
tItem[3006692]["OptionPoint218"] = "1"
tItem[3006692]["OptionPoint221"] = "4-1"
tItem[3006692]["OptionPoint222"] = "4-2"
tItem[3006692]["OptionPoint223"] = "4-3"
tItem[3006692]["OptionPoint224"] = "4-4"
tItem[3006692]["OptionPoint225"] = "4-5"
tItem[3006692]["OptionPoint226"] = "4-6"
tItem[3006692]["OptionPoint227"] = "2-1"
tItem[3006692]["OptionPoint228"] = "1"


-- 【第二层选择对白】（前6主神）
tItem[3006692]["Text3-1"] = {311}		-- 天父宙斯(Zeus)
tItem[3006692]["Text3-2"] = {321}		-- 天后赫拉(Hera)
tItem[3006692]["Text3-3"] = {331}		-- 海神波塞冬(Poseidon)
tItem[3006692]["Text3-4"] = {341}		-- 丰饶女神德墨忒尔(Demeter)
tItem[3006692]["Text3-5"] = {351}		-- 智慧女神雅典娜(Athena)
tItem[3006692]["Text3-6"] = {361}		-- 光明之神阿波罗(Apollo)
tItem[3006692]["Text311"] = tFestivalCardMonth_Text[3006692]["Text311"]
tItem[3006692]["Text321"] = tFestivalCardMonth_Text[3006692]["Text321"]
tItem[3006692]["Text331"] = tFestivalCardMonth_Text[3006692]["Text331"]
tItem[3006692]["Text341"] = tFestivalCardMonth_Text[3006692]["Text341"]
tItem[3006692]["Text351"] = tFestivalCardMonth_Text[3006692]["Text351"]
tItem[3006692]["Text361"] = tFestivalCardMonth_Text[3006692]["Text361"]
-- 选项
tItem[3006692]["tOption3-1"] = {311,312,313,314,315}
tItem[3006692]["tOption3-2"] = {321,322,323,314,315}
tItem[3006692]["tOption3-3"] = {331,332,333,314,315}
tItem[3006692]["tOption3-4"] = {341,342,343,314,315}
tItem[3006692]["tOption3-5"] = {351,352,353,314,315}
tItem[3006692]["tOption3-6"] = {361,362,363,314,315}
tItem[3006692]["Option311"] = tFestivalCardMonth_Text[3006692]["Option311"]
tItem[3006692]["Option312"] = tFestivalCardMonth_Text[3006692]["Option312"]
tItem[3006692]["Option313"] = tFestivalCardMonth_Text[3006692]["Option313"]
tItem[3006692]["Option314"] = tFestivalCardMonth_Text[3006692]["Option314"]
tItem[3006692]["Option315"] = tFestivalCardMonth_Text[3006692]["Option315"]
tItem[3006692]["Option321"] = tFestivalCardMonth_Text[3006692]["Option321"]
tItem[3006692]["Option322"] = tFestivalCardMonth_Text[3006692]["Option322"]
tItem[3006692]["Option323"] = tFestivalCardMonth_Text[3006692]["Option323"]
tItem[3006692]["Option331"] = tFestivalCardMonth_Text[3006692]["Option331"]
tItem[3006692]["Option332"] = tFestivalCardMonth_Text[3006692]["Option332"]
tItem[3006692]["Option333"] = tFestivalCardMonth_Text[3006692]["Option333"]
tItem[3006692]["Option341"] = tFestivalCardMonth_Text[3006692]["Option341"]
tItem[3006692]["Option342"] = tFestivalCardMonth_Text[3006692]["Option342"]
tItem[3006692]["Option343"] = tFestivalCardMonth_Text[3006692]["Option343"]
tItem[3006692]["Option351"] = tFestivalCardMonth_Text[3006692]["Option351"]
tItem[3006692]["Option352"] = tFestivalCardMonth_Text[3006692]["Option352"]
tItem[3006692]["Option353"] = tFestivalCardMonth_Text[3006692]["Option353"]
tItem[3006692]["Option361"] = tFestivalCardMonth_Text[3006692]["Option361"]
tItem[3006692]["Option362"] = tFestivalCardMonth_Text[3006692]["Option362"]
tItem[3006692]["Option363"] = tFestivalCardMonth_Text[3006692]["Option363"]
tItem[3006692]["OptionFunc311"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006656"
tItem[3006692]["OptionFunc312"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006657"
tItem[3006692]["OptionFunc313"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006658"
tItem[3006692]["OptionFunc321"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006659"
tItem[3006692]["OptionFunc322"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006660"
tItem[3006692]["OptionFunc323"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006661"
tItem[3006692]["OptionFunc331"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006662"
tItem[3006692]["OptionFunc332"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006663"
tItem[3006692]["OptionFunc333"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006664"
tItem[3006692]["OptionFunc341"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006665"
tItem[3006692]["OptionFunc342"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006666"
tItem[3006692]["OptionFunc343"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006667"
tItem[3006692]["OptionFunc351"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006668"
tItem[3006692]["OptionFunc352"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006669"
tItem[3006692]["OptionFunc353"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006670"
tItem[3006692]["OptionFunc361"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006671"
tItem[3006692]["OptionFunc362"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006672"
tItem[3006692]["OptionFunc363"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006673"
tItem[3006692]["OptionPoint314"] = "1"
tItem[3006692]["OptionPoint315"] = "2-1"

-- 【第二层选择对白】（后6主神）
tItem[3006692]["Text4-1"] = {411}		-- 月之女神阿耳忒弥斯(Artemis)
tItem[3006692]["Text4-2"] = {421}		-- 爱之女神阿佛洛狄忒(Aphrodite)
tItem[3006692]["Text4-3"] = {431}		-- 商业之神赫耳墨斯(Hermes)
tItem[3006692]["Text4-4"] = {441}		-- 战神阿瑞斯(Ares)
tItem[3006692]["Text4-5"] = {451}		-- 火神赫菲斯托斯(Hephaistos)
tItem[3006692]["Text4-6"] = {461}		-- 酒神狄俄倪索斯(Dionysus)
tItem[3006692]["Text411"] = tFestivalCardMonth_Text[3006692]["Text411"]
tItem[3006692]["Text421"] = tFestivalCardMonth_Text[3006692]["Text421"]
tItem[3006692]["Text431"] = tFestivalCardMonth_Text[3006692]["Text431"]
tItem[3006692]["Text441"] = tFestivalCardMonth_Text[3006692]["Text441"]
tItem[3006692]["Text451"] = tFestivalCardMonth_Text[3006692]["Text451"]
tItem[3006692]["Text461"] = tFestivalCardMonth_Text[3006692]["Text461"]
-- 选项
tItem[3006692]["tOption4-1"] = {411,412,413,414,415}
tItem[3006692]["tOption4-2"] = {421,422,423,414,415}
tItem[3006692]["tOption4-3"] = {431,432,433,414,415}
tItem[3006692]["tOption4-4"] = {441,442,443,414,415}
tItem[3006692]["tOption4-5"] = {451,452,453,414,415}
tItem[3006692]["tOption4-6"] = {461,462,463,414,415}
tItem[3006692]["Option411"] = tFestivalCardMonth_Text[3006692]["Option411"]
tItem[3006692]["Option412"] = tFestivalCardMonth_Text[3006692]["Option412"]
tItem[3006692]["Option413"] = tFestivalCardMonth_Text[3006692]["Option413"]
tItem[3006692]["Option414"] = tFestivalCardMonth_Text[3006692]["Option414"]
tItem[3006692]["Option415"] = tFestivalCardMonth_Text[3006692]["Option415"]
tItem[3006692]["Option421"] = tFestivalCardMonth_Text[3006692]["Option421"]
tItem[3006692]["Option422"] = tFestivalCardMonth_Text[3006692]["Option422"]
tItem[3006692]["Option423"] = tFestivalCardMonth_Text[3006692]["Option423"]
tItem[3006692]["Option431"] = tFestivalCardMonth_Text[3006692]["Option431"]
tItem[3006692]["Option432"] = tFestivalCardMonth_Text[3006692]["Option432"]
tItem[3006692]["Option433"] = tFestivalCardMonth_Text[3006692]["Option433"]
tItem[3006692]["Option441"] = tFestivalCardMonth_Text[3006692]["Option441"]
tItem[3006692]["Option442"] = tFestivalCardMonth_Text[3006692]["Option442"]
tItem[3006692]["Option443"] = tFestivalCardMonth_Text[3006692]["Option443"]
tItem[3006692]["Option451"] = tFestivalCardMonth_Text[3006692]["Option451"]
tItem[3006692]["Option452"] = tFestivalCardMonth_Text[3006692]["Option452"]
tItem[3006692]["Option453"] = tFestivalCardMonth_Text[3006692]["Option453"]
tItem[3006692]["Option461"] = tFestivalCardMonth_Text[3006692]["Option461"]
tItem[3006692]["Option462"] = tFestivalCardMonth_Text[3006692]["Option462"]
tItem[3006692]["Option463"] = tFestivalCardMonth_Text[3006692]["Option463"]
tItem[3006692]["OptionFunc411"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006674"
tItem[3006692]["OptionFunc412"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006675"
tItem[3006692]["OptionFunc413"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006676"
tItem[3006692]["OptionFunc421"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006677"
tItem[3006692]["OptionFunc422"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006678"
tItem[3006692]["OptionFunc423"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006679"
tItem[3006692]["OptionFunc431"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006680"
tItem[3006692]["OptionFunc432"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006681"
tItem[3006692]["OptionFunc433"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006682"
tItem[3006692]["OptionFunc441"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006683"
tItem[3006692]["OptionFunc442"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006684"
tItem[3006692]["OptionFunc443"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006685"
tItem[3006692]["OptionFunc451"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006686"
tItem[3006692]["OptionFunc452"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006687"
tItem[3006692]["OptionFunc453"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006688"
tItem[3006692]["OptionFunc461"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006689"
tItem[3006692]["OptionFunc462"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006690"
tItem[3006692]["OptionFunc463"] = "FestivalCardMonth_CreateCard</N>3006692</N>30</N>3006691"
tItem[3006692]["OptionPoint414"] = "1"
tItem[3006692]["OptionPoint415"] = "2-2"



------------------------------------------------【恶魔挑战书】------------------------------------------------
tItem[3006693] = tItem[3006693] or {}
tItem[3006693]["Function"] = function (nItemId,sItemName)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		if Item_ChkItem(nItemId) and Item_DelAllItemByType(nItemId) then
			local sTalkText = tFestivalCardMonth_Text["Item_TimeOut"]
			User_TalkChannel2005(sTalkText)
		end
		return
	end
	
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		local nEventData_6 = tFestivalCardMonth_Stc[6]["EventData"]
		local nTypeData_6 = tFestivalCardMonth_Stc[6]["TypeData"]
		local nAddValue_6 = tFestivalCardMonth_Stc[6]["AddValue"]
		Task_AddStatistic(nEventData_6,nTypeData_6,nAddValue_6,1)
		User_TalkChannel2005(tFestivalCardMonth_Text[3006693]["UseDialog"])
	end
end

------------------------------------------------【圣物打造书】------------------------------------------------
tItem[3006694] = tItem[3006694] or {}
tItem[3006694]["Function"] = function (nItemId,sItemName)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		if Item_ChkItem(nItemId) and Item_DelAllItemByType(nItemId) then
			local sTalkText = tFestivalCardMonth_Text["Item_TimeOut"]
			User_TalkChannel2005(sTalkText)
		end
		return
	end
	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		local nEventData_8 = tFestivalCardMonth_Stc[8]["EventData"]
		local nTypeData_8 = tFestivalCardMonth_Stc[8]["TypeData"]
		local nAddValue_8 = tFestivalCardMonth_Stc[8]["AddValue3"]
		Task_AddStatistic(nEventData_8,nTypeData_8,nAddValue_8,1)
		User_TalkChannel2005(tFestivalCardMonth_Text[3006694]["UseDialog"])
	end
end


------------------------------------------------【主神卡幸运礼包】------------------------------------------------
tItem[3006695] = tItem[3006695] or {}
tItem[3006695]["Function"] = function (nItemId,sItemName)
	FestivalCardMonth_OpenLuckyBag(nItemId)
end

------------------------------------------------【主神卡幸运连抽礼包】------------------------------------------------
tItem[3006696] = tItem[3006696] or {}
tItem[3006696]["Function"] = function (nItemId,sItemName)
	FestivalCardMonth_OpenSeriesBag(nItemId)
end
tItem[3006696]["Text1-1"] = {111,112,113,114,115,116,117,118,119,1110}		-- 初始对白
tItem[3006696]["Text111"]  = tFestivalCardMonth_Text[3006696]["Text111"]
tItem[3006696]["Text112"]  = tFestivalCardMonth_Text[3006696]["Text112"]
tItem[3006696]["Text113"]  = tFestivalCardMonth_Text[3006696]["Text113"]
tItem[3006696]["Text114"]  = tFestivalCardMonth_Text[3006696]["Text114"]
tItem[3006696]["Text115"]  = tFestivalCardMonth_Text[3006696]["Text115"]
tItem[3006696]["Text116"]  = tFestivalCardMonth_Text[3006696]["Text116"]
tItem[3006696]["Text117"]  = tFestivalCardMonth_Text[3006696]["Text117"]
tItem[3006696]["Text118"]  = tFestivalCardMonth_Text[3006696]["Text118"]
tItem[3006696]["Text119"]  = tFestivalCardMonth_Text[3006696]["Text119"]
tItem[3006696]["Text1110"] = tFestivalCardMonth_Text[3006696]["Text1110"]
-- 选项
tItem[3006696]["tOption1-1"] = {11}
tItem[3006696]["Option11"] = tFestivalCardMonth_Text[3006696]["Option11"]





------------------------------------------------【奥林匹斯神谕】------------------------------------------------
tItem[3006697] = tItem[3006697] or {}
tItem[3006697]["Function"] = function (nItemId,sItemName)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalCardMonth_Data["Festival_NowTime"]) then
		if Item_ChkItem(nItemId) and Item_DelAllItemByType(nItemId) then
			local sTalkText = tFestivalCardMonth_Text["Item_TimeOut"]
			User_TalkChannel2005(sTalkText)
		end
		return
	end
	
	LinkItemGossipFunc_New(nItemId,"1-1")
end
tItem[3006697]["Text1-1"] = {111,112,113}		-- 初始对白
tItem[3006697]["Text111"] = tFestivalCardMonth_Text[3006697]["Text111"] 
tItem[3006697]["Text112"] = tFestivalCardMonth_Text[3006697]["Text112"]
tItem[3006697]["Text113"] = tFestivalCardMonth_Text[3006697]["Text113"] 
-- 选项
tItem[3006697]["tOption1-1"] = {11}
tItem[3006697]["Option11"] = tFestivalCardMonth_Text[3006697]["Option11"]
tItem[3006697]["OptionFunc11"]="FestivalCardMonth_Letter</N>3006697</N>3006632"




------------------------------------------------【A、B、C类礼包】------------------------------------------------

--------【初级圣光礼包】--------
tItem[3006864] = tItem[3006864] or {}
tItem[3006865] = tItem[3006864] or {}
tItem[3006866] = tItem[3006864] or {}
tItem[3006867] = tItem[3006864] or {}
tItem[3006868] = tItem[3006864] or {}
tItem[3006869] = tItem[3006864] or {}
tItem[3006870] = tItem[3006864] or {}
tItem[3006871] = tItem[3006864] or {}
tItem[3006872] = tItem[3006864] or {}
tItem[3006864]["Text1-1"] = {111,112,113,114}		-- 初始对白
tItem[3006864]["Text1-2"] = {121}					-- 背包空间不足
tItem[3006864]["Text111"] = tFestivalCardMonth_Text[3006864]["Text111"] 
tItem[3006864]["Text112"] = tFestivalCardMonth_Text[3006864]["Text112"]
tItem[3006864]["Text113"] = tFestivalCardMonth_Text[3006864]["Text113"] 
tItem[3006864]["Text114"] = tFestivalCardMonth_Text[3006864]["Text114"] 
tItem[3006864]["Text121"] = tFestivalCardMonth_Text[3006864]["Text121"]
tItem[3006864]["ChkFunc1-1"] = function ()
	local nItemId = Get_ItemType()
	tItem[3006864]["Text1-1"] = {111,112,113}
	tItem[3006864]["Text111"] = tFestivalCardMonth_Text[nItemId]["Text111"] 
	tItem[3006864]["Text112"] = tFestivalCardMonth_Text[nItemId]["Text112"]
	tItem[3006864]["tOption1-1"] = {11,12}
	tItem[3006864]["OptionFunc11"] = tFestivalCardMonth_OptionFunc[nItemId][1]
	tItem[3006864]["OptionFunc12"] = tFestivalCardMonth_OptionFunc[nItemId][2]
	
	-- 是否有第三种奖励
	local OptionFunc3 = tFestivalCardMonth_OptionFunc[nItemId][3]
	if OptionFunc3 ~= nil then
		tItem[3006864]["Text1-1"] = {111,112,114,113}
		tItem[3006864]["Text114"] = tFestivalCardMonth_Text[nItemId]["Text114"]
		tItem[3006864]["tOption1-1"] = {11,12,13}
		tItem[3006864]["OptionFunc13"] = OptionFunc3
	end
	return true
end
-- 选项
tItem[3006864]["tOption1-1"] = {11,12}
tItem[3006864]["tOption1-2"] = {14}
tItem[3006864]["Option11"] = tFestivalCardMonth_Text[3006864]["Option11"]
tItem[3006864]["Option12"] = tFestivalCardMonth_Text[3006864]["Option12"]
tItem[3006864]["Option13"] = tFestivalCardMonth_Text[3006864]["Option13"]
tItem[3006864]["Option14"] = tFestivalCardMonth_Text[3006864]["Option14"]
tItem[3006864]["OptionFunc11"]=""
tItem[3006864]["OptionFunc12"]=""
tItem[3006864]["OptionFunc13"]=""


------------------------------------------------【神赐天石宝箱】------------------------------------------------
tItem[3006873] = tItem[3006873] or {}
tItem[3006874] = tItem[3006873] or {}
tItem[3006875] = tItem[3006873] or {}
tItem[3006876] = tItem[3006873] or {}
tItem[3006878] = tItem[3006873] or {}
tItem[3006873]["Function"] = function (nItemId,sItemName)
	local flat,tItem = Probabil_RandomAward(tFestivalCardMonth_Probabil[1],5)
	local nAwardType = tItem[1]["tAward"][1]["Item_1"]
	local nReward = tFestivalCardMonth_GodRewardBox[nItemId][nAwardType]
	local nRewardType = tFestivalCardMonth_GodRewardBox["RewardType"][nItemId][nAwardType]
	
	-- 天石宝箱
	if nItemId == 3006873 then 
		local nUserEMoney = Get_UserEMoney()
		local nLimit = tFestivalCardMonth_Data["EMonoMoneyTop"] - nReward

		-- 点天石上限判断
		if nUserEMoney > nLimit then
			User_TalkChannel2005(tFestivalCardMonth_Text[3006873]["EMoneyFull"])
			return
		end
		
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			User_AddEMoney(nReward)
			Sys_SaveEmoneyBuy(string.format(tFestivalCardMonth_EmoneyBuy["EmoneyLog5"],nReward,nReward))
		end
		
	-- 气力值宝箱
	elseif nItemId == 3006874 then 
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			User_AddStrengthValue(nReward)
		end
		
	-- 赠品天石宝箱
	elseif nItemId == 3006875 then 
		local nUserMonoEMoney = Get_UserMonoEMoney()
		local nLimit = tFestivalCardMonth_Data["EMonoMoneyTop"] - nReward
		
		-- 赠点天石上限判断
		if nUserMonoEMoney > nLimit then
			User_TalkChannel2005(tFestivalCardMonth_Text[3006873]["EMoneyFull"])
			return
		end
		
		-- 给赠点天石
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			User_AddEMoneyMono(nReward)
			Sys_SaveEmoneyBuy(string.format(tFestivalCardMonth_EmoneyBuy["EmoneyLog6"],nReward))
		end
		
	-- 龙珠宝箱
	elseif nItemId == 3006876 then 
		-- 背包空间
		if not User_CheckLeftSpace(tFestivalCardMonth_Data["ChkSpace4"]) then
			User_TalkChannel2005(tFestivalCardMonth_Text["CardPag_PagFull"])
			return
		end
	
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			Item_AddItem(nRewardType,0,nReward)
		end
		
	-- 流星卷
	elseif nItemId == 3006878 then
		-- 背包空间
		if not User_CheckLeftSpace(tFestivalCardMonth_Data["ChkSpace4"]) then
			User_TalkChannel2005(tFestivalCardMonth_Text["CardPag_PagFull"])
			return
		end
	
		if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
			Item_AddItem(nRewardType,0,nReward)
		end
	end
	
	local sLogText = string.format(tFestivalCardMonth_Log["GodReward"],nItemId,nRewardType,nReward)
	local sTalkText = string.format(tFestivalCardMonth_Text[nItemId]["AwardItem"],sItemName,nReward)
	User_EffectAdd(tFestivalCardMonth_Data["EffectObj"],tFestivalCardMonth_Data["Effect_1"])
	Sys_SaveActionFestivalLog(sLogText)
	User_TalkChannel2005(sTalkText)
end

------------------------------------------------【神赐赤炼石宝箱】------------------------------------------------
tItem[3006877] = tItem[3006877] or {}
tItem[3006877]["Function"] = function (nItemId,sItemName)

	if Item_ChkItem(nItemId) and Item_DelItem(nItemId) then
		local flat,tItem = Probabil_RandomAward(tFestivalCardMonth_Probabil[1],5)
		local nAwardType = tItem[1]["tAward"][1]["Item_1"]
		local nNewItemId = tFestivalCardMonth_GodRewardBox[nItemId][nAwardType]
		Item_AddItem(nNewItemId)
		local sLogText = string.format(tFestivalCardMonth_Log["GodStone"],nItemId,nNewItemId)
		local sTalkText = string.format(tFestivalCardMonth_Text[nItemId][nAwardType],sItemName)
		Sys_SaveActionFestivalLog(sLogText)
		User_TalkChannel2005(sTalkText)
	end
end

------------------------------------------怪物配置-------------------------------------------
-- //宝藏守护者
-- tMonster[7749] = tMonster[7749] or {}
-- tMonster[7749]["tFunction"] = tMonster[7749]["tFunction"] or {}
-- table.insert(tMonster[7749]["tFunction"],FestivalCardMonth_Monster)


-----------------------------------------BOSS怪物-------------------------------------------
-- 第一批
-- 30	灵猕猴
-- tMonster[30] = tMonster[30] or {}
-- tMonster[30]["tFunction"] = tMonster[30]["tFunction"] or {}
-- table.insert(tMonster[30]["tFunction"],FestivalCardMonth_BossMonster1)
-- 31	巨吼猿
-- tMonster[31] = tMonster[31] or {}
-- tMonster[31]["tFunction"] = tMonster[31]["tFunction"] or {}
-- table.insert(tMonster[31]["tFunction"],FestivalCardMonth_BossMonster1)
-- 32	野莽雪猿
-- tMonster[32] = tMonster[32] or {}
-- tMonster[32]["tFunction"] = tMonster[32]["tFunction"] or {}
-- table.insert(tMonster[32]["tFunction"],FestivalCardMonth_BossMonster1)
-- 33	狂蛇妖
-- tMonster[33] = tMonster[33] or {}
-- tMonster[33]["tFunction"] = tMonster[33]["tFunction"] or {}
-- table.insert(tMonster[33]["tFunction"],FestivalCardMonth_BossMonster1)
-- 34	沙魔
-- tMonster[34] = tMonster[34] or {}
-- tMonster[34]["tFunction"] = tMonster[34]["tFunction"] or {}
-- table.insert(tMonster[34]["tFunction"],FestivalCardMonth_BossMonster1)
-- 35	敲山怪
-- tMonster[35] = tMonster[35] or {}
-- tMonster[35]["tFunction"] = tMonster[35]["tFunction"] or {}
-- table.insert(tMonster[35]["tFunction"],FestivalCardMonth_BossMonster1)
-- 36	擂石怪
-- tMonster[36] = tMonster[36] or {}
-- tMonster[36]["tFunction"] = tMonster[36]["tFunction"] or {}
-- table.insert(tMonster[36]["tFunction"],FestivalCardMonth_BossMonster1)
-- 37	魔刃
-- tMonster[37] = tMonster[37] or {}
-- tMonster[37]["tFunction"] = tMonster[37]["tFunction"] or {}
-- table.insert(tMonster[37]["tFunction"],FestivalCardMonth_BossMonster1)
-- 38	金臂鸟王
-- tMonster[38] = tMonster[38] or {}
-- tMonster[38]["tFunction"] = tMonster[38]["tFunction"] or {}
-- table.insert(tMonster[38]["tFunction"],FestivalCardMonth_BossMonster1)
-- 39	银羽魔鹰
-- tMonster[39] = tMonster[39] or {}
-- tMonster[39]["tFunction"] = tMonster[39]["tFunction"] or {}
-- table.insert(tMonster[39]["tFunction"],FestivalCardMonth_BossMonster1)
-- 40	大盗
-- tMonster[40] = tMonster[40] or {}
-- tMonster[40]["tFunction"] = tMonster[40]["tFunction"] or {}
-- table.insert(tMonster[40]["tFunction"],FestivalCardMonth_BossMonster1)

-- 第二批
-- 90	飞天蝠
-- tMonster[90] = tMonster[90] or {}
-- tMonster[90]["tFunction"] = tMonster[90]["tFunction"] or {}
-- table.insert(tMonster[90]["tFunction"],FestivalCardMonth_BossMonster2)
-- 91	嗜血蝠王
-- tMonster[91] = tMonster[91] or {}
-- tMonster[91]["tFunction"] = tMonster[91]["tFunction"] or {}
-- table.insert(tMonster[91]["tFunction"],FestivalCardMonth_BossMonster2)
-- 92	牛魔
-- tMonster[92] = tMonster[92] or {}
-- tMonster[92]["tFunction"] = tMonster[92]["tFunction"] or {}
-- table.insert(tMonster[92]["tFunction"],FestivalCardMonth_BossMonster2)
-- 93	绿魔
-- tMonster[93] = tMonster[93] or {}
-- tMonster[93]["tFunction"] = tMonster[93]["tFunction"] or {}
-- table.insert(tMonster[93]["tFunction"],FestivalCardMonth_BossMonster2)
-- 4151	熔岩狂魔
-- tMonster[4151] = tMonster[4151] or {}
-- tMonster[4151]["tFunction"] = tMonster[4151]["tFunction"] or {}
-- table.insert(tMonster[4151]["tFunction"],FestivalCardMonth_BossMonster2)

-- 第三批
-- 4171	晶魄雪妖
-- tMonster[4171] = tMonster[4171] or {}
-- tMonster[4171]["tFunction"] = tMonster[4171]["tFunction"] or {}
-- table.insert(tMonster[4171]["tFunction"],FestivalCardMonth_BossMonster3)
-- 4212	雪妖之魂
-- tMonster[4212] = tMonster[4212] or {}
-- tMonster[4212]["tFunction"] = tMonster[4212]["tFunction"] or {}
-- table.insert(tMonster[4212]["tFunction"],FestivalCardMonth_BossMonster3)

--第四批
-- 4220	啸海巨魔
-- tMonster[4220] = tMonster[4220] or {}
-- tMonster[4220]["tFunction"] = tMonster[4220]["tFunction"] or {}
-- table.insert(tMonster[4220]["tFunction"],FestivalCardMonth_BossMonster4)

