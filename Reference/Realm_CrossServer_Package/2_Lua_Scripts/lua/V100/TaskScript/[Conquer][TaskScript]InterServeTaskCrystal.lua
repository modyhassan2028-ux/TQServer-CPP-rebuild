------------------------------------------------------------------------------------
--Name:			[简体征服][任务脚本]国境晶矿
--Purpose:		[简体征服][任务脚本]国境晶矿
--Creator: 		张磊
--Created:		26/07/2015
------------------------------------------------------------------------------------

--[[
任务需求：
每小时在中间的刷新5个魔水晶，4个是小水晶和1个大号水晶，打爆该水晶就能获得魔水晶。魔水晶刷新在各个国
境服入口附近，并且每小时大水晶轮流出现在各个国境服的门口附近，引导玩家去找寻水晶并促发遭遇战。
获得魔水晶后，获得一个光效，返回本服后，上交魔水晶可以获得赤炼石，护心丹，究极通神丹，回气丹等奖励。

注：奖励随便写的  大水晶给赤炼石   小水晶 给  聚神丹

=================国家任务发布官处修改=======================================

接受任务（已经有了任务掩码，则不显示）
成功，1转110级玩家打上任务掩码并简要提示如何完成任务。
领取资源奖励
成功，点击选项扣除对应资源积分值，给予玩家奖励。
失败，身上并没有对应的积分值。

]]--

-- 命名前缀
---- ServiceTask_Crystal_

--掩码说明
--35006
--data1   表示 记录玩家破坏大水晶分数 【一个大水晶 1分】
--data2   表示 记录玩家破坏小水晶分数 【一个小水晶 1分】

--NPCtype

--3772  大水晶
--3773  小水晶


-------------------------------------------------------------------------------------------------------


--常亮表
local tServiceTask_Crystal_Cont = {}
	--玩家等级要求
	tServiceTask_Crystal_Cont["Metempsychosis"] = 1
	tServiceTask_Crystal_Cont["Level"] = 70
	
	--背包空间
	tServiceTask_Crystal_Cont["Space"] = 2
	
	--任务TaskID
	tServiceTask_Crystal_Cont["TaskId"] = 35006
	
	--暂定奖励
	----3002218  千里传音喇叭 【完成抢夺资源额外给的奖励】
	tServiceTask_Crystal_Cont["CrystalReward"] = 3002218
	tServiceTask_Crystal_Cont["CrystalNum"] = "0 3"
	
	
	tServiceTask_Crystal_Cont["MapId"] = 3935
	
	--水晶种类标示
	tServiceTask_Crystal_Cont["Flag_Big"] = 1
	tServiceTask_Crystal_Cont["Flag_Small"] = 2
	
	
	tServiceTask_Crystal_Cont["MonsterId_Big"] = 7860
	tServiceTask_Crystal_Cont["MonsterId_Small"] = 7861
	
	tServiceTask_Crystal_Cont["Name_Big"] = "BigCrystal"	
	tServiceTask_Crystal_Cont["Generator"] = 17980
	
	tServiceTask_Crystal_Cont["self"] = "self"
	tServiceTask_Crystal_Cont["effect"] = "zf2-e300"
	
	--大水晶完成
	tServiceTask_Crystal_Cont["Big_effect"] = "zf2-e129"
	tServiceTask_Crystal_Cont["Small_effect"] = "relive"
	
	tServiceTask_Crystal_Cont["Add_JF"] = 50
	
	--限制
	--赠品天石上限
	tServiceTask_Crystal_Cont["Emoney_Limit"] = 999999999
	tServiceTask_Crystal_Cont["Emoney_Mono"] = 50
	
	-- 全局动态存储表
	tServiceTask_Crystal_Cont["Global_Data"] = 50942

	-- 免费修炼次数上限	
	tServiceTask_Crystal_Cont["FureePract"] = 1000000	
	
	-- 御敌积分掩码
	tServiceTask_Crystal_Cont["YD_Task"] = 35007
	
	-- 御敌积分(小水晶)
	tServiceTask_Crystal_Cont["YDJF_Small"] = 10
	-- 御敌积分（大水晶）
	tServiceTask_Crystal_Cont["YDJF_Big"] = 50
	
	
-- 水晶坐标点
local tServiceTask_Crystal_Npc = {}	
	tServiceTask_Crystal_Npc[1] = {{214,284},{285,387},{381,379},{369,281},{297,216}}
	tServiceTask_Crystal_Npc[2] = {{233,244},{245,317},{308,374},{369,329},{344,249}}

-- 奖励几率配置

local tServiceTask_Crystal_Reward = {}

-- 大水晶 标示编号： 1 
	tServiceTask_Crystal_Reward[1] = {}
	tServiceTask_Crystal_Reward[1]["ItemChanceSum"] = 10000
-- 天道酬勤卷（赠）		20%		3001407	（每天限制100张）		超过给200点气力值
	tServiceTask_Crystal_Reward[1][1] = {}
	tServiceTask_Crystal_Reward[1][1]["RandomItemChanceType"] = 2
	tServiceTask_Crystal_Reward[1][1]["ItemChance"] = 2000
	tServiceTask_Crystal_Reward[1][1]["Item_1"] = 3001407
	tServiceTask_Crystal_Reward[1][1]["Is_3001407"] = true
	tServiceTask_Crystal_Reward[1][1]["ItemAttr"] = "0 0 3"
	tServiceTask_Crystal_Reward[1][1]["Index"] = 1
	tServiceTask_Crystal_Reward[1][1]["Limit"] = 20
	tServiceTask_Crystal_Reward[1][1]["MoreThanLimit"] = 200
	tServiceTask_Crystal_Reward[1][1]["Log_1"] = "0,0,1,0,12000184,2,3001407,1"
	tServiceTask_Crystal_Reward[1][1]["Log_2"] = "0,0,1,0,12000184,2,12,200"
	
	-- 100赠点天石		5%
	tServiceTask_Crystal_Reward[1][2] = {}
	tServiceTask_Crystal_Reward[1][2]["RandomItemChanceType"] = 2
	tServiceTask_Crystal_Reward[1][2]["ItemChance"] = 200
	tServiceTask_Crystal_Reward[1][2]["Item_1"] = 100
	tServiceTask_Crystal_Reward[1][2]["IsEmoney"] = true	
	tServiceTask_Crystal_Reward[1][2]["Index"] = 2
	tServiceTask_Crystal_Reward[1][2]["Limit"] = 2
	tServiceTask_Crystal_Reward[1][2]["MoreThanLimit"] = 200
	tServiceTask_Crystal_Reward[1][2]["Log_1"] = "0,0,1,0,12000184,2,3,100"
	tServiceTask_Crystal_Reward[1][2]["Log_2"] = "0,0,1,0,12000184,2,12,200"
	
	-- 正气浩然卷（赠）   3002431		10%
	tServiceTask_Crystal_Reward[1][3] = {}
	tServiceTask_Crystal_Reward[1][3]["RandomItemChanceType"] = 2
	tServiceTask_Crystal_Reward[1][3]["ItemChance"] = 1000
	tServiceTask_Crystal_Reward[1][3]["Item_1"] = 3002431
	tServiceTask_Crystal_Reward[1][3]["ItemAttr"] = "0 0 3"
	tServiceTask_Crystal_Reward[1][3]["Index"] = 3
	tServiceTask_Crystal_Reward[1][3]["Log"] = "0,0,1,0,12000184,2,3002431,1"
	
	-- 200点气力值		25%
	tServiceTask_Crystal_Reward[1][4] = {}
	tServiceTask_Crystal_Reward[1][4]["RandomItemChanceType"] = 2
	tServiceTask_Crystal_Reward[1][4]["ItemChance"] = 2500
	tServiceTask_Crystal_Reward[1][4]["Item_1"] = 200
	tServiceTask_Crystal_Reward[1][4]["IsStrength"] = true
	tServiceTask_Crystal_Reward[1][4]["Index"] = 4
	tServiceTask_Crystal_Reward[1][4]["Log"] = "0,0,1,0,12000184,2,12,200"
	
	-- 3个究极通神丹（大爆丹）		13%	3003126	究极通神丹
	tServiceTask_Crystal_Reward[1][5] = {}
	tServiceTask_Crystal_Reward[1][5]["RandomItemChanceType"] = 2
	tServiceTask_Crystal_Reward[1][5]["ItemChance"] = 1300
	tServiceTask_Crystal_Reward[1][5]["Item_1"] = 3003126
	tServiceTask_Crystal_Reward[1][5]["ItemAttr"] = "0 3 3"
	tServiceTask_Crystal_Reward[1][5]["Index"] = 5
	tServiceTask_Crystal_Reward[1][5]["Log"] = "0,0,1,0,12000184,2,3003126,3"
	
	-- 1个秘令		10%	
	tServiceTask_Crystal_Reward[1][6] = {}
	tServiceTask_Crystal_Reward[1][6]["RandomItemChanceType"] = 2
	tServiceTask_Crystal_Reward[1][6]["ItemChance"] = 1000
	tServiceTask_Crystal_Reward[1][6]["Item_1"] = {}
	tServiceTask_Crystal_Reward[1][6]["Item_1"][1] = 3004895	--力量秘令
	tServiceTask_Crystal_Reward[1][6]["Item_1"][2] = 3004896	--精神秘令
	tServiceTask_Crystal_Reward[1][6]["Item_1"][3] = 3004897	--体质秘令
	tServiceTask_Crystal_Reward[1][6]["Item_1"][4] = 3004898	--灵巧秘令
	tServiceTask_Crystal_Reward[1][6]["ItemAttr"] = "0 1"
	tServiceTask_Crystal_Reward[1][6]["Index"] = 6
	tServiceTask_Crystal_Reward[1][6]["Log"] = "0,0,1,0,12000184,2,%d,1"
	
	-- 秘制免费修炼丹*10  （赠） 20% 3002926	秘制免费修炼丹
	tServiceTask_Crystal_Reward[1][7] = {}
	tServiceTask_Crystal_Reward[1][7]["RandomItemChanceType"] = 2
	tServiceTask_Crystal_Reward[1][7]["ItemChance"] = 2000
	tServiceTask_Crystal_Reward[1][7]["Item_1"] = 3002926
	tServiceTask_Crystal_Reward[1][7]["ItemAttr"] = "0 10 3"
	tServiceTask_Crystal_Reward[1][7]["Index"] = 7
	tServiceTask_Crystal_Reward[1][7]["Log"] = "0,0,1,0,12000184,2,3002926,10"
	
	
-- 小水晶 标示： 2
	tServiceTask_Crystal_Reward[2] = {}
	tServiceTask_Crystal_Reward[2]["ItemChanceSum"] = 10000
	
-- 天道酬勤卷（赠）		20%		3001407	（每天限制100张）		超过给200点气力值	
	tServiceTask_Crystal_Reward[2][1] = {}
	tServiceTask_Crystal_Reward[2][1]["RandomItemChanceType"] = 2
	tServiceTask_Crystal_Reward[2][1]["ItemChance"] = 500
	tServiceTask_Crystal_Reward[2][1]["Item_1"] = 3001407
	tServiceTask_Crystal_Reward[2][1]["Is_3001407"] = true
	tServiceTask_Crystal_Reward[2][1]["ItemAttr"] = "0 0 3"
	tServiceTask_Crystal_Reward[2][1]["Index"] = 1
	tServiceTask_Crystal_Reward[2][1]["Limit"] = 20
	tServiceTask_Crystal_Reward[2][1]["MoreThanLimit"] = 50
	tServiceTask_Crystal_Reward[2][1]["Log_1"] = "0,0,2,0,12000184,2,3001407,1"
	tServiceTask_Crystal_Reward[2][1]["Log_2"] = "0,0,2,0,12000184,2,12,50"
	
	-- 免费修炼次数+2+喇叭		25%	3002218	千里传音喇叭  为修修炼给 50点气力值
	tServiceTask_Crystal_Reward[2][2] = {}
	tServiceTask_Crystal_Reward[2][2]["RandomItemChanceType"] = 2
	tServiceTask_Crystal_Reward[2][2]["ItemChance"] = 2500
	tServiceTask_Crystal_Reward[2][2]["Item_1"] = 20000
	tServiceTask_Crystal_Reward[2][2]["Item_2"] = 3002218
	tServiceTask_Crystal_Reward[2][2]["ItemAttr"] = "0 1 3"
	tServiceTask_Crystal_Reward[2][2]["NoWuGong"] = 50
	tServiceTask_Crystal_Reward[2][2]["IsXiuLian"] = true
	tServiceTask_Crystal_Reward[2][2]["Index"] = 2
	tServiceTask_Crystal_Reward[2][2]["Log_1"] = "0,0,2,0,12000184,2,17[3002218],2[1]"
	tServiceTask_Crystal_Reward[2][2]["Log_2"] = "0,0,2,0,12000184,2,12,50"
	
	-- 2个护心丹（时效激活）/未转给聚神丹（赠）		25%
	tServiceTask_Crystal_Reward[2][3] = {}
	tServiceTask_Crystal_Reward[2][3]["RandomItemChanceType"] = 2
	tServiceTask_Crystal_Reward[2][3]["ItemChance"] = 2500
	tServiceTask_Crystal_Reward[2][3]["Item_1"] = 3002029
	tServiceTask_Crystal_Reward[2][3]["Item_2"] = 723700
	tServiceTask_Crystal_Reward[2][3]["Item_3"] = 50
	tServiceTask_Crystal_Reward[2][3]["ItemAttr_1"] = "0 2 0 0 1"
	tServiceTask_Crystal_Reward[2][3]["ItemAttr_2"] = "0 1 3"
	tServiceTask_Crystal_Reward[2][3]["Metempsychosis_2"] = 2
	tServiceTask_Crystal_Reward[2][3]["Metempsychosis_Level"] = 30
	tServiceTask_Crystal_Reward[2][3]["Exp_limit"] = 60
	tServiceTask_Crystal_Reward[2][3]["IsHuXinDan"] = true	
	tServiceTask_Crystal_Reward[2][3]["Index"] = 3
	tServiceTask_Crystal_Reward[2][3]["Log_1"] = "0,0,2,0,12000184,2,3002029,2"
	tServiceTask_Crystal_Reward[2][3]["Log_2"] = "0,0,2,0,12000184,2,723700,1"
	tServiceTask_Crystal_Reward[2][3]["Log_3"] = "0,0,2,0,12000184,2,12,50"
	
	-- 50点气力值+喇叭		15%
	tServiceTask_Crystal_Reward[2][4] = {}
	tServiceTask_Crystal_Reward[2][4]["RandomItemChanceType"] = 2
	tServiceTask_Crystal_Reward[2][4]["ItemChance"] = 500
	tServiceTask_Crystal_Reward[2][4]["Item_1"] = 50
	tServiceTask_Crystal_Reward[2][4]["Item_2"] = 3002218
	tServiceTask_Crystal_Reward[2][4]["ItemAttr"] = "0 1 3"	
	tServiceTask_Crystal_Reward[2][4]["IsStrength_LB"] = true
	tServiceTask_Crystal_Reward[2][4]["Index"] = 4
	tServiceTask_Crystal_Reward[2][4]["Log"] = "0,0,2,0,12000184,2,12[3002218],50[1]"
	
	-- 免费修炼丹  （赠）		15%	3002926	秘制免费修炼丹
	tServiceTask_Crystal_Reward[2][5] = {}
	tServiceTask_Crystal_Reward[2][5]["RandomItemChanceType"] = 2
	tServiceTask_Crystal_Reward[2][5]["ItemChance"] = 1500
	tServiceTask_Crystal_Reward[2][5]["Item_1"] = 3002926
	tServiceTask_Crystal_Reward[2][5]["ItemAttr"] = "0 0 3"
	tServiceTask_Crystal_Reward[2][5]["Index"] = 5
	tServiceTask_Crystal_Reward[2][5]["Log"] = "0,0,2,0,12000184,2,3002926,1"
	
	-- 1个强炼丹（赠）		10%	3003124	免费强炼丹
	tServiceTask_Crystal_Reward[2][6] = {}
	tServiceTask_Crystal_Reward[2][6]["RandomItemChanceType"] = 2
	tServiceTask_Crystal_Reward[2][6]["ItemChance"] = 1000
	tServiceTask_Crystal_Reward[2][6]["Item_1"] = 3003124
	tServiceTask_Crystal_Reward[2][6]["ItemAttr"] = "0 0 3"
	tServiceTask_Crystal_Reward[2][6]["Index"] = 6
	tServiceTask_Crystal_Reward[2][6]["Log"] = "0,0,0,0,12000184,2,3003124,1"
	
	-- 1个通神丹（赠）		10%	3003125	通神丹
	tServiceTask_Crystal_Reward[2][7] = {}
	tServiceTask_Crystal_Reward[2][7]["RandomItemChanceType"] = 2
	tServiceTask_Crystal_Reward[2][7]["ItemChance"] = 1000
	tServiceTask_Crystal_Reward[2][7]["Item_1"] = 3003125
	tServiceTask_Crystal_Reward[2][7]["ItemAttr"] = "0 0 3"
	tServiceTask_Crystal_Reward[2][7]["Index"] = 7
	tServiceTask_Crystal_Reward[2][7]["Log"] = "0,0,0,0,12000184,2,3003125,1"

	-- 灵宝护气丹 3007269   5%
	tServiceTask_Crystal_Reward[2][8] = {}
	tServiceTask_Crystal_Reward[2][8]["RandomItemChanceType"] = 2
	tServiceTask_Crystal_Reward[2][8]["ItemChance"] = 500
	tServiceTask_Crystal_Reward[2][8]["Item_1"] = 3007269
	tServiceTask_Crystal_Reward[2][8]["ItemAttr"] = "0 1"
	tServiceTask_Crystal_Reward[2][8]["Index"] = 8
	tServiceTask_Crystal_Reward[2][8]["Log"] = "0,0,0,0,12000184,2,3007269,1"


--emoney_LOG
local tServiceTask_Crystal_EmoneyLOG = {}

	tServiceTask_Crystal_EmoneyLOG["DemageCrystal"] = "350	4303	0	0	1	"
	tServiceTask_Crystal_EmoneyLOG["Complete"] = "350	4304	0	0	1	"
	-- tServiceTask_Crystal_EmoneyLOG["DemageCrystal_Small"] = "350	4303	0	0	1	"


------------------------------------------------------逻辑部分
-- 怪物 触发函数
function ServiceTask_Crystal_Damage()

	local nMonsterId = Get_MonsterType()
	
	if not User_IsCross() and Get_UserMapId() ~= tServiceTask_Crystal_Cont["MapId"] then
		return
	end

	local nTaskId = tServiceTask_Crystal_Cont["TaskId"]
	
	if not Task_ChkTaskDetail(nTaskId) then
		Task_AddTaskDetail(nTaskId)
	end
	
	--判断 水晶种类并进行 掩码加值
	if nMonsterId ~=  tServiceTask_Crystal_Cont["MonsterId_Big"] and nMonsterId ~= tServiceTask_Crystal_Cont["MonsterId_Small"] then
		return
	end
	
	if nMonsterId == tServiceTask_Crystal_Cont["MonsterId_Big"] then
	
		local nData = Get_TaskDetailData1(nTaskId) + 1			
		Task_SetTaskDetailData1(nTaskId,nData)
		User_TalkChannel2005(tServiceTask_Crystal_Text["DamageCrystal_Big"])
		if FirstPerson_AddKillMonsterNum then
			FirstPerson_AddKillMonsterNum(nil, 9)
		end
		InterServeTask_Killer_TeamEnjoy(1,tServiceTask_Crystal_Cont["YDJF_Big"])
		
	elseif nMonsterId == tServiceTask_Crystal_Cont["MonsterId_Small"] then
	
		local nData = Get_TaskDetailData2(nTaskId) + 1			
		Task_SetTaskDetailData2(nTaskId,nData)
		User_TalkChannel2005(tServiceTask_Crystal_Text["DamageCrystal_Small"])
		if FirstPerson_AddKillMonsterNum then
			FirstPerson_AddKillMonsterNum(nil, 1)
		end
		InterServeTask_Killer_TeamEnjoy(1,tServiceTask_Crystal_Cont["YDJF_Small"])
	end
	
	-- task 
	-- local Task_YD = tServiceTask_Crystal_Cont["YD_Task"]
	-- if Task_ChkTaskDetail(Task_YD) then
		-- local nNum = Get_TaskDetailData1(Task_YD) + tServiceTask_Crystal_Cont["YD_JF"]
		-- Task_SetTaskDetailData1(Task_YD,nNum)
		-- local str = string.format(tServiceTask_Crystal_Text["Sys_YDJF"],tostring(Get_TaskDetailData1(Task_YD)))
		-- User_TalkChannel2005(str)
	-- end
	

	Sys_SaveEmoneyBuy(tServiceTask_Crystal_EmoneyLOG["DemageCrystal"])
	User_EffectDel(tServiceTask_Crystal_Cont["self"],tServiceTask_Crystal_Cont["effect"])
	User_EffectAdd(tServiceTask_Crystal_Cont["self"],tServiceTask_Crystal_Cont["effect"])
	
end

-- 国家发布官领取奖励

function ServiceTask_Crystal_GetRewards(nNpcId,nFlag)
	if User_IsCross() then
		return
	end

	local nMetempsychosis = tServiceTask_Crystal_Cont["Metempsychosis"]
	local nLevel = tServiceTask_Crystal_Cont["Level"]
	
	if not User_JudgeLevelAndMetempsychosis(nLevel,nMetempsychosis) then
		LinkNpcGossipFunc_New(nNpcId,"300-1")
		return
	end

	local nTaskId = tServiceTask_Crystal_Cont["TaskId"]
	
	if not Task_ChkTaskDetail(nTaskId) then
		LinkNpcGossipFunc_New(nNpcId,"300-2")
		return
	end
	
	--判断玩家兑换那种奖励
	if nFlag ~= tServiceTask_Crystal_Cont["Flag_Big"] and nFlag ~= tServiceTask_Crystal_Cont["Flag_Small"] then
		return
	end
	
	local nSpaceNum = tServiceTask_Crystal_Cont["Space"]
	
	if not User_CheckLeftSpace(nSpaceNum) then
		User_TalkChannel2005(tServiceTask_Crystal_Text["NoSpace"])
		return
	end
	
	--判断是否赠品天石过多
	local nEmoney_Mono = Get_UserMonoEMoney()
	if nEmoney_Mono > (tServiceTask_Crystal_Cont["Emoney_Limit"] - tServiceTask_Crystal_Cont["Emoney_Mono"]) then
		User_TalkChannel2005(tServiceTask_Crystal_Text["MoreEmoney"])
		return
	end	
	
	if nFlag == tServiceTask_Crystal_Cont["Flag_Big"] then
		local nData = Get_TaskDetailData1(nTaskId)	
		
		if nData <= 0 then
			LinkNpcGossipFunc_New(nNpcId,"300-3")
			return
		else
			local nData_1 = Get_TaskDetailData1(nTaskId) - 1
			Task_SetTaskDetailData1(nTaskId,nData_1)
		end
		
	elseif nFlag == tServiceTask_Crystal_Cont["Flag_Small"] then
		local nData = Get_TaskDetailData2(nTaskId)
		if nData <= 0 then
			LinkNpcGossipFunc_New(nNpcId,"300-4")
			return
		else
			local nData_1 = Get_TaskDetailData2(nTaskId) - 1
			Task_SetTaskDetailData2(nTaskId,nData_1)
		end
	else
		return
	end
	
	-- 完成给积分
	-- if National_War_AddIntegral(tServiceTask_Crystal_Cont["Add_JF"]) then
	
		-- local str_1 = string.format(tServiceTask_Crystal_Text["Get_JF"],tServiceTask_Crystal_Cont["Add_JF"])
		-- User_TalkChannel2005(str_1)
	-- end
	
	--给奖励
	local nIndex,tAward = Probabil_RandomAward(tServiceTask_Crystal_Reward,nFlag)
	local nItem = tAward[1]["tAward"][1]["Item_1"]
	local str_Log = ""
	local sFlag = ""
	
	-- 天道酬勤卷（赠）
	if tAward[1]["tAward"][1]["Is_3001407"] == true then

		if Get_SysDynaGlobalData0(tServiceTask_Crystal_Cont["Global_Data"]) >= tAward[1]["tAward"][1]["Limit"] then

			-- 给200气力值
			User_AddStrengthValue(tAward[1]["tAward"][1]["MoreThanLimit"])
			str_Log = tAward[1]["tAward"][1]["Log_2"]
			sFlag = "1-2"
		else
			local nData = Get_SysDynaGlobalData0(tServiceTask_Crystal_Cont["Global_Data"]) + 1
			Sys_SetSynaGlobalData0(tServiceTask_Crystal_Cont["Global_Data"],nData)
			Item_AddNewItem(nItem,tAward[1]["tAward"][1]["ItemAttr"])
			str_Log = tAward[1]["tAward"][1]["Log_1"]
			sFlag = "1-1"
		end
	elseif tAward[1]["tAward"][1]["IsEmoney"] == true then

		if Get_SysDynaGlobalData1(tServiceTask_Crystal_Cont["Global_Data"]) >= tAward[1]["tAward"][1]["Limit"] then

			-- 给200气力值
			User_AddStrengthValue(tAward[1]["tAward"][1]["MoreThanLimit"])
			str_Log = tAward[1]["tAward"][1]["Log_2"]
			sFlag = "1-2"
		else
			local nData = Get_SysDynaGlobalData1(tServiceTask_Crystal_Cont["Global_Data"]) + 1
			Sys_SetSynaGlobalData1(tServiceTask_Crystal_Cont["Global_Data"],nData)
			User_AddEMoneyMono(nItem)
			str_Log = tAward[1]["tAward"][1]["Log_1"]
			sFlag = "2-1"
		end
	elseif tAward[1]["tAward"][1]["IsStrength"] == true then

			User_AddStrengthValue(nItem)
			str_Log = tAward[1]["tAward"][1]["Log"]
			sFlag = "1-2"
	elseif 	tAward[1]["tAward"][1]["IsXiuLian"] == true then

		if User_IsAlreadyCreateGongFu(0) and  Get_UserGongFureePractNum() <= (tServiceTask_Crystal_Cont["FureePract"] - tAward[1]["tAward"][1]["Item_1"])  then

			User_AddGongFuFreePractNum(nItem)
			Item_AddNewItem(tAward[1]["tAward"][1]["Item_2"],tAward[1]["tAward"][1]["ItemAttr"])
			str_Log = tAward[1]["tAward"][1]["Log_1"]
			sFlag = "2-1"
		else
			User_AddStrengthValue(tAward[1]["tAward"][1]["NoWuGong"])
			str_Log = tAward[1]["tAward"][1]["Log_2"]
			sFlag = "2-2"
		end
	elseif tAward[1]["tAward"][1]["IsHuXinDan"] == true then

		if User_JudgeLevelAndMetempsychosis(tAward[1]["tAward"][1]["Metempsychosis_Level"],tAward[1]["tAward"][1]["Metempsychosis_2"]) then

			Item_AddNewItem(nItem,tAward[1]["tAward"][1]["ItemAttr_1"])
			str_Log = tAward[1]["tAward"][1]["Log_1"]
			sFlag = "3-1"
		elseif Get_SysDynaGlobalData2(tServiceTask_Crystal_Cont["Global_Data"]) < tAward[1]["tAward"][1]["Exp_limit"] then
			local nData = Get_SysDynaGlobalData2(tServiceTask_Crystal_Cont["Global_Data"]) + 1
			Sys_SetSynaGlobalData2(tServiceTask_Crystal_Cont["Global_Data"],nData)
			Item_AddNewItem(tAward[1]["tAward"][1]["Item_2"],tAward[1]["tAward"][1]["ItemAttr_2"])
			str_Log = tAward[1]["tAward"][1]["Log_2"]
			sFlag = "3-2"
		else
			User_AddStrengthValue(tAward[1]["tAward"][1]["Item_3"])
			str_Log = tAward[1]["tAward"][1]["Log_3"]
			sFlag = "2-2"
		end
	elseif tAward[1]["tAward"][1]["IsStrength_LB"] == true then

			User_AddStrengthValue(nItem)
			Item_AddNewItem(tAward[1]["tAward"][1]["Item_2"],tAward[1]["tAward"][1]["ItemAttr"])
			str_Log = tAward[1]["tAward"][1]["Log"]
			sFlag = "4-1"
	elseif type(tAward[1]["tAward"][1]["Item_1"]) == "table" then

			local nRandom = math.random(1,4) 
			Item_AddNewItem(tAward[1]["tAward"][1]["Item_1"][nRandom],tAward[1]["tAward"][1]["ItemAttr"])
			str_Log = string.format(tAward[1]["tAward"][1]["Log"],tAward[1]["tAward"][1]["Item_1"][nRandom])
			sFlag = string.format("6-%d",nRandom)
	else	
			Item_AddNewItem(nItem,tAward[1]["tAward"][1]["ItemAttr"])
			str_Log = tAward[1]["tAward"][1]["Log"]
			sFlag = tAward[1]["tAward"][1]["Index"]
	end
		
		
	Sys_SaveActionFestivalLog(str_Log)
	User_TalkChannel2005(tServiceTask_Crystal_GetReward[nFlag][sFlag])
	Task_SetTaskDetailCompleteFlag(nTaskId,1)
	Sys_SaveEmoneyBuy(tServiceTask_Crystal_EmoneyLOG["Complete"])
	
	if nFlag == tServiceTask_Crystal_Cont["Flag_Big"] then
		User_EffectDel(tServiceTask_Crystal_Cont["self"],tServiceTask_Crystal_Cont["Big_effect"])
		User_EffectAdd(tServiceTask_Crystal_Cont["self"],tServiceTask_Crystal_Cont["Big_effect"])
	else
		User_EffectDel(tServiceTask_Crystal_Cont["self"],tServiceTask_Crystal_Cont["Small_effect"])
		User_EffectAdd(tServiceTask_Crystal_Cont["self"],tServiceTask_Crystal_Cont["Small_effect"])
	end	
end

-- 国家发布官 接受任务函数
function ServiceTask_Crystal_AcceptTask(nNpcId)
	if User_IsCross() then
		return
	end

	local nMetempsychosis = tServiceTask_Crystal_Cont["Metempsychosis"]
	local nLevel = tServiceTask_Crystal_Cont["Level"]
	
	if not User_JudgeLevelAndMetempsychosis(nLevel,nMetempsychosis) then
		LinkNpcGossipFunc_New(nNpcId,"300-1")
		return
	end

	local nTaskId = tServiceTask_Crystal_Cont["TaskId"]
	
	if Task_ChkTaskDetail(nTaskId) then
		LinkNpcGossipFunc_New(nNpcId,"300-5")
		return
	end

	if Task_AddTaskDetail(nTaskId) then
		LinkNpcGossipFunc_New(nNpcId,"300-6")
		return
	end
end


-- 203W 刷新 水晶
function ServiceTask_Crystal_Flash()

		local nMapId = tServiceTask_Crystal_Cont["MapId"]
		local nMonsterId_Big = tServiceTask_Crystal_Cont["MonsterId_Big"]
		local sName = tServiceTask_Crystal_Cont["Name_Big"]
		local nGenId = tServiceTask_Crystal_Cont["Generator"]
		
	if Monster_GetMonsterByName(nMapId,sName) == 0 then
	
		Monster_DelMonster(nMapId,nMonsterId_Big)
		
		local nNum = math.random(1,5)
		
		for i = 1,2 do
			local nPosX = tServiceTask_Crystal_Npc[i][nNum][1] or tServiceTask_Crystal_Npc[i][1][1]
			local nPosY = tServiceTask_Crystal_Npc[i][nNum][2] or tServiceTask_Crystal_Npc[i][1][2]
	
			Monster_AddMonster(nMapId,nPosX,nPosY,nGenId,nMonsterId_Big)
		end
	end
end

-- 清理动态存储表
function ServiceTask_Crystal_Reset()
	local nGlobalId = tServiceTask_Crystal_Cont["Global_Data"]
		Sys_ResetAllSynaGlobalData(nGlobalId)
end

--------------------------------------------------------------------------NPC模块
tNpcGossip[17400] = tNpcGossip[17400] or DefaultNpc:new{}
tNpcGossip[17400]["OptionHidden"] = 1

tNpcGossip[17400]["Text300-7"] = {30071,30072}
tNpcGossip[17400]["Text30071"] = tServiceTask_Crystal_Text[17400]["Text30071"]
tNpcGossip[17400]["Text30072"] = tServiceTask_Crystal_Text[17400]["Text30072"]
tNpcGossip[17400]["tOption300-7"] = {302,305,306,304}
tNpcGossip[17400]["ChkFunc300-7"] = function ()
	local nNum1 = 0
	local nNum2 = 0
	
	if Task_ChkTaskDetail(tServiceTask_Crystal_Cont["TaskId"]) then
		nNum1 = Get_TaskDetailData1(tServiceTask_Crystal_Cont["TaskId"])
		nNum2 = Get_TaskDetailData2(tServiceTask_Crystal_Cont["TaskId"])
	end
	tNpcGossip[17400]["Text30072"] = string.format(tServiceTask_Crystal_Text[17400]["Text30072"],nNum1,nNum2)
	return true
end



-- tNpcGossip[17400]["Text300-8"] = {30081,30082}
-- tNpcGossip[17400]["Text30081"] = tServiceTask_Crystal_Text[17400]["Text30081"]
-- tNpcGossip[17400]["Text30082"] = tServiceTask_Crystal_Text[17400]["Text30082"]
-- tNpcGossip[17400]["tOption300-8"] = {305,306,304}


-- 等级不够对白
tNpcGossip[17400]["Text300-1"] = {30011,30012}
tNpcGossip[17400]["Text30011"] = tServiceTask_Crystal_Text[17400]["Text30011"]
tNpcGossip[17400]["Text30012"] = tServiceTask_Crystal_Text[17400]["Text30012"]
tNpcGossip[17400]["tOption300-1"] = {300}


-- 没有任务提示
tNpcGossip[17400]["Text300-2"] = {30021,30022}
tNpcGossip[17400]["Text30021"] = tServiceTask_Crystal_Text[17400]["Text30021"]
tNpcGossip[17400]["Text30022"] = tServiceTask_Crystal_Text[17400]["Text30022"]
tNpcGossip[17400]["tOption300-2"] = {300}

-- 有任务但是data1 大水晶
tNpcGossip[17400]["Text300-3"] = {30031,30032}
tNpcGossip[17400]["Text30031"] = tServiceTask_Crystal_Text[17400]["Text30031"]
tNpcGossip[17400]["Text30032"] = tServiceTask_Crystal_Text[17400]["Text30032"]
tNpcGossip[17400]["tOption300-3"] = {300}

-- 有任务但是data2 小水晶
tNpcGossip[17400]["Text300-4"] = {30041,30042}
tNpcGossip[17400]["Text30041"] = tServiceTask_Crystal_Text[17400]["Text30041"]
tNpcGossip[17400]["Text30042"] = tServiceTask_Crystal_Text[17400]["Text30042"]
tNpcGossip[17400]["tOption300-4"] = {300}

------接任务部分
-- 已有任务 提示
tNpcGossip[17400]["Text300-5"] = {30051,30052}
tNpcGossip[17400]["Text30051"] = tServiceTask_Crystal_Text[17400]["Text30051"]
tNpcGossip[17400]["Text30052"] = tServiceTask_Crystal_Text[17400]["Text30052"]
tNpcGossip[17400]["tOption300-5"] = {300}

-- 接取任务成功提示 提示
tNpcGossip[17400]["Text300-6"] = {30061,30062}
tNpcGossip[17400]["Text30061"] = tServiceTask_Crystal_Text[17400]["Text30061"]
tNpcGossip[17400]["Text30062"] = tServiceTask_Crystal_Text[17400]["Text30062"]
tNpcGossip[17400]["tOption300-6"] = {300}


-----------------选项

tNpcGossip[17400]["Option300"]=tServiceTask_Crystal_Text[17400]["Option300"]


tNpcGossip[17400]["Option301"]=tServiceTask_Crystal_Text[17400]["Option301"]
tNpcGossip[17400]["OptionPoint301"] = "300-7"

tNpcGossip[17400]["Option302"]=tServiceTask_Crystal_Text[17400]["Option302"]
tNpcGossip[17400]["OptionFunc302"]="ServiceTask_Crystal_AcceptTask</N>17400"
tNpcGossip[17400]["OptionChkFunc302"] = function ()
	if User_IsCross() then
		return false
	end

	local nTaskId = tServiceTask_Crystal_Cont["TaskId"]
	if Task_ChkTaskDetail(nTaskId) then
		return false
	else	
		return true
	end	
end

-- tNpcGossip[17400]["Option303"]=tServiceTask_Crystal_Text[17400]["Option303"]
-- tNpcGossip[17400]["OptionPoint303"] = "300-8"

tNpcGossip[17400]["Option304"]=tServiceTask_Crystal_Text[17400]["Option304"]

tNpcGossip[17400]["Option305"]=tServiceTask_Crystal_Text[17400]["Option305"]
tNpcGossip[17400]["OptionFunc305"]="ServiceTask_Crystal_GetRewards</N>17400</N>1"

tNpcGossip[17400]["Option306"]=tServiceTask_Crystal_Text[17400]["Option306"]
tNpcGossip[17400]["OptionFunc306"]="ServiceTask_Crystal_GetRewards</N>17400</N>2"

tNpcGossip[17400]["Option307"]=tServiceTask_Crystal_Text[17400]["Option307"]

------------------------------------------------怪物触发------------------------------

tMonster[7860] = tMonster[7860] or {}
tMonster[7860]["tFunction"] = tMonster[7860]["tFunction"] or {}
table.insert(tMonster[7860]["tFunction"],ServiceTask_Crystal_Damage)

tMonster[7861] = tMonster[7861] or {}
tMonster[7861]["tFunction"] = tMonster[7861]["tFunction"] or {}
table.insert(tMonster[7861]["tFunction"],ServiceTask_Crystal_Damage)



------------------------------------------------时间自检------------------------------
--203W 处理函数  每15分钟执行
tOntimerMin_M[00] = tOntimerMin_M[00] or {}
table.insert(tOntimerMin_M[00],ServiceTask_Crystal_Flash)

tOntimerMin_M[15] = tOntimerMin_M[15] or {}
table.insert(tOntimerMin_M[15],ServiceTask_Crystal_Flash)

tOntimerMin_M[30] = tOntimerMin_M[30] or {}
table.insert(tOntimerMin_M[30],ServiceTask_Crystal_Flash)

tOntimerMin_M[45] = tOntimerMin_M[45] or {}
table.insert(tOntimerMin_M[45],ServiceTask_Crystal_Flash)

--每天00:00 清理动态存储表
tOntimerMin_HM[0000] = tOntimerMin_HM[0000] or {}
table.insert(tOntimerMin_HM[0000],ServiceTask_Crystal_Reset)
