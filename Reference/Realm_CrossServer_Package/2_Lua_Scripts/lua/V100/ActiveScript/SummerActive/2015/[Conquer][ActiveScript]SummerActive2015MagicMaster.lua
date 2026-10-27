------------------------------------------------------------------------------------
--Name:			[征服][活动脚本]魔术大师(7.9-7.22)
--Purpose:		暑期活动--魔术大师(7.9-7.22)
--Creator:		王倩娜
--Created:		2015/07/05
------------------------------------------------------------------------------------

--	命名前缀
--	SummerActive2015_MagicMaster

--	掩码说明

-- stc(115,16) 记录第几次偷窥以及领奖情况
-- stc(115,17) 记录玩家获得的物品id

--LOGID	10001942

--常量表配置
local tSummerActive2015_MagicMaster_Cont = {}
	--活动时间
	tSummerActive2015_MagicMaster_Cont["ActivityTime"] = "2015-07-09 00:00 2015-07-22 23:59"
	tSummerActive2015_MagicMaster_Cont["BeforeActivityTime"] = "2015-01-01 00:00 2015-07-08 23:59"

	--玩家等级要求
	tSummerActive2015_MagicMaster_Cont["Metempsychosis"] = 0
	tSummerActive2015_MagicMaster_Cont["Level"] = 80
	
	-- 掩码
	-- stc(115,16) 记录第几次偷窥以及领奖情况
	tSummerActive2015_MagicMaster_Cont["PeepNum"] = {}
		tSummerActive2015_MagicMaster_Cont["PeepNum"]["Event"] = 115
		tSummerActive2015_MagicMaster_Cont["PeepNum"]["StcType"] = 16
		tSummerActive2015_MagicMaster_Cont["PeepNum"]["Phase"] = {}
			tSummerActive2015_MagicMaster_Cont["PeepNum"]["Phase"][1] = 1
			tSummerActive2015_MagicMaster_Cont["PeepNum"]["Phase"][2] = 2
			tSummerActive2015_MagicMaster_Cont["PeepNum"]["Phase"][3] = 3
			tSummerActive2015_MagicMaster_Cont["PeepNum"]["Phase"][4] = 4
					
	-- stc(115,17) 记录玩家获得的物品编号
	tSummerActive2015_MagicMaster_Cont["PReward"] = {}
	tSummerActive2015_MagicMaster_Cont["PReward"]["Event"] = 115
	tSummerActive2015_MagicMaster_Cont["PReward"]["StcType"] = 17


		-- 动态表
	tSummerActive2015_MagicMaster_Cont["Global"] = {}
		tSummerActive2015_MagicMaster_Cont["Global"]["Id"] = 50264
		
	--物品类型
	tSummerActive2015_MagicMaster_Cont["RewardType"] = {}
	tSummerActive2015_MagicMaster_Cont["RewardType"][1] = 1
	tSummerActive2015_MagicMaster_Cont["RewardType"][721022] = 1
	tSummerActive2015_MagicMaster_Cont["RewardType"][721032] = 1
	tSummerActive2015_MagicMaster_Cont["RewardType"][721042] = 1
	tSummerActive2015_MagicMaster_Cont["RewardType"][721052] = 1
	tSummerActive2015_MagicMaster_Cont["RewardType"][721063] = 1
	tSummerActive2015_MagicMaster_Cont["RewardType"][720894] = 1
	tSummerActive2015_MagicMaster_Cont["RewardType"][3000138] = 1
	tSummerActive2015_MagicMaster_Cont["RewardType"][3000121] = 1
	tSummerActive2015_MagicMaster_Cont["RewardType"][3000122] = 1
	tSummerActive2015_MagicMaster_Cont["RewardType"][3000123] = 1
	
	tSummerActive2015_MagicMaster_Cont["RewardType"][721259] = 2
	tSummerActive2015_MagicMaster_Cont["RewardType"][710214] = 2
	tSummerActive2015_MagicMaster_Cont["RewardType"][700102] = 2
	tSummerActive2015_MagicMaster_Cont["RewardType"][700122] = 2
	tSummerActive2015_MagicMaster_Cont["RewardType"][1088000] = 2
	tSummerActive2015_MagicMaster_Cont["RewardType"][729242] = 2
	
	tSummerActive2015_MagicMaster_Cont["RewardType"][721316] = 3
	tSummerActive2015_MagicMaster_Cont["RewardType"][720886] = 3
	tSummerActive2015_MagicMaster_Cont["RewardType"][727061] = 3
	tSummerActive2015_MagicMaster_Cont["RewardType"][727060] = 3
	tSummerActive2015_MagicMaster_Cont["RewardType"][720881] = 3
	tSummerActive2015_MagicMaster_Cont["RewardType"][723712] = 3

	tSummerActive2015_MagicMaster_Cont["ExpTime"] = 60

	--背包空间
	tSummerActive2015_MagicMaster_Cont["BagSpace"] = 1
	
-- --各种光效
	local tSummerActive2015_MagicMaster_Effect = {}
		tSummerActive2015_MagicMaster_Effect["Exp"] = "angelwing"
		tSummerActive2015_MagicMaster_Effect["Reward"] = "eidolon"
	
-- --LOG 表
	local tSummerActive2015_MagicMaster_LOG = {}
		--获得经验奖励
		tSummerActive2015_MagicMaster_LOG["Exp"] = "0,0,0,0,10001942,2,4,60"
		--获奖品
		tSummerActive2015_MagicMaster_LOG["Reward"] = "0,0,0,0,10001942,2,%d,1"
		
--读条数据
	tSummerActive2015_MagicMaster_Cont["Secs"] =  3
	tSummerActive2015_MagicMaster_Cont["ActionId"] = 220
	
--概率
	local  tSummerActive2015_MagicMaste_Award = {}
	tSummerActive2015_MagicMaste_Award["Reward"] = {}
	tSummerActive2015_MagicMaste_Award["Reward"][1] = {}
	tSummerActive2015_MagicMaste_Award["Reward"][1]["ItemChanceSum"] = 1000					

	tSummerActive2015_MagicMaste_Award["Reward"][1][1] = {}
	tSummerActive2015_MagicMaste_Award["Reward"][1][1]["RandomItemChanceType"] = 2			
	tSummerActive2015_MagicMaste_Award["Reward"][1][1]["ItemChance"] = 80					
	tSummerActive2015_MagicMaste_Award["Reward"][1][1]["Item_1"] = 1							

	tSummerActive2015_MagicMaste_Award["Reward"][1][2] = {}
	tSummerActive2015_MagicMaste_Award["Reward"][1][2]["RandomItemChanceType"] = 2
	tSummerActive2015_MagicMaste_Award["Reward"][1][2]["ItemChance"] = 80
	tSummerActive2015_MagicMaste_Award["Reward"][1][2]["Item_1"] = 720894

	tSummerActive2015_MagicMaste_Award["Reward"][1][3] = {}
	tSummerActive2015_MagicMaste_Award["Reward"][1][3]["RandomItemChanceType"] = 2
	tSummerActive2015_MagicMaste_Award["Reward"][1][3]["ItemChance"] = 50
	tSummerActive2015_MagicMaste_Award["Reward"][1][3]["Item_1"] = 3000138

	tSummerActive2015_MagicMaste_Award["Reward"][1][4] = {}
	tSummerActive2015_MagicMaste_Award["Reward"][1][4]["RandomItemChanceType"] = 2
	tSummerActive2015_MagicMaste_Award["Reward"][1][4]["ItemChance"] = 60
	tSummerActive2015_MagicMaste_Award["Reward"][1][4]["Item_1"] = 3000121

	tSummerActive2015_MagicMaste_Award["Reward"][1][5] = {}
	tSummerActive2015_MagicMaste_Award["Reward"][1][5]["RandomItemChanceType"] = 2
	tSummerActive2015_MagicMaste_Award["Reward"][1][5]["ItemChance"] = 30
	tSummerActive2015_MagicMaste_Award["Reward"][1][5]["Item_1"] = 3000122

	tSummerActive2015_MagicMaste_Award["Reward"][1][6] = {}
	tSummerActive2015_MagicMaste_Award["Reward"][1][6]["RandomItemChanceType"] = 2
	tSummerActive2015_MagicMaste_Award["Reward"][1][6]["ItemChance"] = 20
	tSummerActive2015_MagicMaste_Award["Reward"][1][6]["Item_1"] = 3000123

	tSummerActive2015_MagicMaste_Award["Reward"][1][7] = {}
	tSummerActive2015_MagicMaste_Award["Reward"][1][7]["RandomItemChanceType"] = 2
	tSummerActive2015_MagicMaste_Award["Reward"][1][7]["ItemChance"] = 100
	tSummerActive2015_MagicMaste_Award["Reward"][1][7]["Item_1"] = 721259

	tSummerActive2015_MagicMaste_Award["Reward"][1][8] = {}
	tSummerActive2015_MagicMaste_Award["Reward"][1][8]["RandomItemChanceType"] = 2
	tSummerActive2015_MagicMaste_Award["Reward"][1][8]["ItemChance"] = 40
	tSummerActive2015_MagicMaste_Award["Reward"][1][8]["Item_1"] = 710214

	tSummerActive2015_MagicMaste_Award["Reward"][1][9] = {}
	tSummerActive2015_MagicMaste_Award["Reward"][1][9]["RandomItemChanceType"] = 2
	tSummerActive2015_MagicMaste_Award["Reward"][1][9]["ItemChance"] = 50
	tSummerActive2015_MagicMaste_Award["Reward"][1][9]["Item_1"] = 700102

	tSummerActive2015_MagicMaste_Award["Reward"][1][10] = {}
	tSummerActive2015_MagicMaste_Award["Reward"][1][10]["RandomItemChanceType"] = 2
	tSummerActive2015_MagicMaste_Award["Reward"][1][10]["ItemChance"] = 50
	tSummerActive2015_MagicMaste_Award["Reward"][1][10]["Item_1"] = 700122

	tSummerActive2015_MagicMaste_Award["Reward"][1][11] = {}
	tSummerActive2015_MagicMaste_Award["Reward"][1][11]["RandomItemChanceType"] = 2
	tSummerActive2015_MagicMaste_Award["Reward"][1][11]["ItemChance"] = 5
	tSummerActive2015_MagicMaste_Award["Reward"][1][11]["Item_1"] = 1088000

	tSummerActive2015_MagicMaste_Award["Reward"][1][12] = {}
	tSummerActive2015_MagicMaste_Award["Reward"][1][12]["RandomItemChanceType"] = 2
	tSummerActive2015_MagicMaste_Award["Reward"][1][12]["ItemChance"] = 5
	tSummerActive2015_MagicMaste_Award["Reward"][1][12]["Item_1"] = 729242

	tSummerActive2015_MagicMaste_Award["Reward"][1][13] = {}
	tSummerActive2015_MagicMaste_Award["Reward"][1][13]["RandomItemChanceType"] = 2
	tSummerActive2015_MagicMaste_Award["Reward"][1][13]["ItemChance"] = 80
	tSummerActive2015_MagicMaste_Award["Reward"][1][13]["Item_1"] = 721316

	tSummerActive2015_MagicMaste_Award["Reward"][1][14] = {}
	tSummerActive2015_MagicMaste_Award["Reward"][1][14]["RandomItemChanceType"] = 2
	tSummerActive2015_MagicMaste_Award["Reward"][1][14]["ItemChance"] = 50
	tSummerActive2015_MagicMaste_Award["Reward"][1][14]["Item_1"] = 720886

	tSummerActive2015_MagicMaste_Award["Reward"][1][15] = {}
	tSummerActive2015_MagicMaste_Award["Reward"][1][15]["RandomItemChanceType"] = 2
	tSummerActive2015_MagicMaste_Award["Reward"][1][15]["ItemChance"] = 80
	tSummerActive2015_MagicMaste_Award["Reward"][1][15]["Item_1"] = 727061

	tSummerActive2015_MagicMaste_Award["Reward"][1][16] = {}
	tSummerActive2015_MagicMaste_Award["Reward"][1][16]["RandomItemChanceType"] = 2
	tSummerActive2015_MagicMaste_Award["Reward"][1][16]["ItemChance"] = 80
	tSummerActive2015_MagicMaste_Award["Reward"][1][16]["Item_1"] = 727060

	tSummerActive2015_MagicMaste_Award["Reward"][1][17] = {}
	tSummerActive2015_MagicMaste_Award["Reward"][1][17]["RandomItemChanceType"] = 2
	tSummerActive2015_MagicMaste_Award["Reward"][1][17]["ItemChance"] = 80
	tSummerActive2015_MagicMaste_Award["Reward"][1][17]["Item_1"] = 720881

	tSummerActive2015_MagicMaste_Award["Reward"][1][18] = {}
	tSummerActive2015_MagicMaste_Award["Reward"][1][18]["RandomItemChanceType"] = 2
	tSummerActive2015_MagicMaste_Award["Reward"][1][18]["ItemChance"] = 60
	tSummerActive2015_MagicMaste_Award["Reward"][1][18]["Item_1"] = 723712

	--概率给月光宝盒
	tSummerActive2015_MagicMaste_Award["MoonBox"] = {}
	tSummerActive2015_MagicMaste_Award["MoonBox"][1] = {}
	tSummerActive2015_MagicMaste_Award["MoonBox"][1]["ItemChanceSum"] = 1000					
                                           
	tSummerActive2015_MagicMaste_Award["MoonBox"][1][1] = {}
	tSummerActive2015_MagicMaste_Award["MoonBox"][1][1]["RandomItemChanceType"] = 2			
	tSummerActive2015_MagicMaste_Award["MoonBox"][1][1]["ItemChance"] = 200					
	tSummerActive2015_MagicMaste_Award["MoonBox"][1][1]["Item_1"] = 721022							
                                           
	tSummerActive2015_MagicMaste_Award["MoonBox"][1][2] = {}
	tSummerActive2015_MagicMaste_Award["MoonBox"][1][2]["RandomItemChanceType"] = 2
	tSummerActive2015_MagicMaste_Award["MoonBox"][1][2]["ItemChance"] = 200
	tSummerActive2015_MagicMaste_Award["MoonBox"][1][2]["Item_1"] = 721032
                                           
	tSummerActive2015_MagicMaste_Award["MoonBox"][1][3] = {}
	tSummerActive2015_MagicMaste_Award["MoonBox"][1][3]["RandomItemChanceType"] = 2
	tSummerActive2015_MagicMaste_Award["MoonBox"][1][3]["ItemChance"] = 200
	tSummerActive2015_MagicMaste_Award["MoonBox"][1][3]["Item_1"] = 721042
                                           
	tSummerActive2015_MagicMaste_Award["MoonBox"][1][4] = {}
	tSummerActive2015_MagicMaste_Award["MoonBox"][1][4]["RandomItemChanceType"] = 2
	tSummerActive2015_MagicMaste_Award["MoonBox"][1][4]["ItemChance"] = 200
	tSummerActive2015_MagicMaste_Award["MoonBox"][1][4]["Item_1"] = 721052
                                                 
	tSummerActive2015_MagicMaste_Award["MoonBox"][1][5] = {}
	tSummerActive2015_MagicMaste_Award["MoonBox"][1][5]["RandomItemChanceType"] = 2
	tSummerActive2015_MagicMaste_Award["MoonBox"][1][5]["ItemChance"] = 200
	tSummerActive2015_MagicMaste_Award["MoonBox"][1][5]["Item_1"] = 721063

	--奖励的限制次数
	local tSummerActive2015_MagicMaste_NumLimit = {}
		tSummerActive2015_MagicMaste_NumLimit[1] = {3000121,10,720894}
		tSummerActive2015_MagicMaste_NumLimit[2] = {3000122,5,720894}
		tSummerActive2015_MagicMaste_NumLimit[3] = {3000123,3,720894}
		tSummerActive2015_MagicMaste_NumLimit[4] = {1088000,1,721259}
		tSummerActive2015_MagicMaste_NumLimit[5] = {729242,1,721259}
		tSummerActive2015_MagicMaste_NumLimit[6] = {723712,10,721316}
	
	--自检清理
	local tSummerActive2015_MagicMaste_ClearGlobal = {}
		tSummerActive2015_MagicMaste_ClearGlobal["ActivityTime"] = "00:00 00:00"

-- --------------------------------------逻辑部分-----------------------------------------
--偷窥
function SummerActive2015_MagicMaster_PeepAction(nNpcId)
	--判断玩家等级
	if not User_JudgeLevelAndMetempsychosis(tSummerActive2015_MagicMaster_Cont["Level"],tSummerActive2015_MagicMaster_Cont["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	--判断第一次
	local nEvent = tSummerActive2015_MagicMaster_Cont["PeepNum"]["Event"]
	local nType = tSummerActive2015_MagicMaster_Cont["PeepNum"]["StcType"]
	
	if Task_ChkStcValue(nEvent,nType,">=",1) then
		if Task_StcInterval(nEvent,nType,2,4) then
			Task_SetStatistic(nEvent,nType,0,1,0)
			Task_SetStcTimestamp(nEvent,nType,0,0)
		
		elseif not Task_StcInterval(nEvent,nType,1,4) then
			User_TalkChannel2005(tSummerActive2015_MagicMaster_Text["OnlyTime"])
			return
		end
	end
	-- 读条
	local nSecs = tSummerActive2015_MagicMaster_Cont["Secs"]
	local sContent = tSummerActive2015_MagicMaster_Text["PeepContent"]
	local nActionId = tSummerActive2015_MagicMaster_Cont["ActionId"]
	local sFunc = string.format("SummerActive2015_MagicMaster_PeepNow</N>%d",nNpcId)
	
	 User_SetExplore(nSecs,sContent,nActionId,sFunc)  
	 
end

--偷窥
function SummerActive2015_MagicMaster_PeepNow(nNpcId)
	local nEvent = tSummerActive2015_MagicMaster_Cont["PeepNum"]["Event"]
	local nType = tSummerActive2015_MagicMaster_Cont["PeepNum"]["StcType"]

	local nRewardEvent = tSummerActive2015_MagicMaster_Cont["PReward"]["Event"]
	local nRewardType = tSummerActive2015_MagicMaster_Cont["PReward"]["StcType"]

	local nItemId = Get_UserStatisticValue(nRewardEvent,nRewardType)
	if nItemId == 1 then
		local flat,tMoonBox = Probabil_RandomAward(tSummerActive2015_MagicMaste_Award["MoonBox"],1)  
		local nMoonBoxId = tMoonBox[1]["tAward"][1]["Item_1"]
		nItemId = nMoonBoxId
		Task_SetStatistic(nRewardEvent,nRewardType,nItemId,1,0)
	end

	if Task_ChkStcValue(nEvent,nType,"==",0) then
	--第一次
			--偷窥成功
		Task_SetStatistic(nEvent,nType,tSummerActive2015_MagicMaster_Cont["PeepNum"]["Phase"][1],1,0)
		Task_SetStcTimestamp(nEvent,nType,0,0)
		
		SummerActive2015_MagicMaster_FirstPeep(nRewardEvent,nRewardType,nNpcId)
		
	elseif Task_ChkStcValue(nEvent,nType,"==",1) then
	-- 第二次
		if Task_StcInterval(nEvent,nType,1,4) then
			Task_SetStatistic(nEvent,nType,tSummerActive2015_MagicMaster_Cont["PeepNum"]["Phase"][2],1,0)
			Task_SetStcTimestamp(nEvent,nType,0,0)
			
			SummerActive2015_MagicMaster_AddEXP()
			
			local v = Get_UserStatisticValue(nRewardEvent,nRewardType)
			local nTemp = tSummerActive2015_MagicMaster_Cont["RewardType"][v]
			Sys_DialogText(tSummerActive2015_MagicMaster_Text[15812]["Text311"][nTemp])
			Sys_DialogOption(tSummerActive2015_MagicMaster_Text[15812]["Option2"],"</F>NULL")
			Sys_DialogEnd()
		end
		
	elseif Task_ChkStcValue(nEvent,nType,"==",2) then
	-- 第三次
		if Task_StcInterval(nEvent,nType,1,4) then
			Task_SetStatistic(nEvent,nType,tSummerActive2015_MagicMaster_Cont["PeepNum"]["Phase"][3],1,0)
			Task_SetStcTimestamp(nEvent,nType,0,0)
			
			SummerActive2015_MagicMaster_AddEXP()		
			
			local sItemName = tSummerActive2015_MagicMaster_Text["RewardName"][nItemId] 
			local stc = string.format(tSummerActive2015_MagicMaster_Text[15812]["Text411"],sItemName)
			
			Sys_DialogText(stc)
			Sys_DialogOption(tSummerActive2015_MagicMaster_Text[15812]["Option2"],"</F>NULL")
			Sys_DialogEnd()
		end	
		
	elseif Task_ChkStcValue(nEvent,nType,"==",3) then
		local sItemName = tSummerActive2015_MagicMaster_Text["RewardName"][nItemId] 
		local stc = string.format(tSummerActive2015_MagicMaster_Text[15812]["Text411"],sItemName)
		
		Sys_DialogText(stc)
		Sys_DialogOption(tSummerActive2015_MagicMaster_Text[15812]["Option2"],"</F>NULL")
		Sys_DialogEnd()
			
	elseif  Task_ChkStcValue(nEvent,nType,"==",4) then
		if Task_StcInterval(nEvent,nType,1,4) then
			Task_SetStatistic(nEvent,nType,tSummerActive2015_MagicMaster_Cont["PeepNum"]["Phase"][1],1,0)
			Task_SetStcTimestamp(nEvent,nType,0,0)
		
			SummerActive2015_MagicMaster_FirstPeep(nRewardEvent,nRewardType,nNpcId)
		end
	end		
end

function SummerActive2015_MagicMaster_FirstPeep(nRewardEvent,nRewardType,nNpcId)
	local flat,tNum = Probabil_RandomAward(tSummerActive2015_MagicMaste_Award["Reward"],1)  
	local nItemId = tNum[1]["tAward"][1]["Item_1"]
		--月光宝盒和是否超出全服数量。
		if nItemId == 1 then
			local flat,tMoonBox = Probabil_RandomAward(tSummerActive2015_MagicMaste_Award["MoonBox"],1)  
			local nMoonBoxId = tMoonBox[1]["tAward"][1]["Item_1"]
			nItemId = nMoonBoxId
		else 		
			for i = 1,6 do 
				if nItemId == tSummerActive2015_MagicMaste_NumLimit[i][1] then
					nItemId = SummerActive2015_MagicMaster_LimitNum(nItemId)
				end 
			end 
		end
	--奖励物品	
	Task_SetStatistic(nRewardEvent,nRewardType,nItemId,1,0)
	-- 经验奖励
	SummerActive2015_MagicMaster_AddEXP()
	LinkNpcGossipFunc_New(nNpcId,"2-2")

end

function SummerActive2015_MagicMaster_AddEXP()
	local nUserLev = Get_UserLevel()
	if nUserLev < 140 then
		User_AddExpTime(tSummerActive2015_MagicMaster_Cont["ExpTime"])
		Sys_SaveActionFestivalLog(tSummerActive2015_MagicMaster_LOG["Exp"])
		User_EffectAdd("self",tSummerActive2015_MagicMaster_Effect["Exp"])
		User_TalkChannel2005(tSummerActive2015_MagicMaster_Text["GetExp"])
	end
end

-- 是否达到单日上限数量
function SummerActive2015_MagicMaster_LimitNum(nItemId)
	local nGlobalId = tSummerActive2015_MagicMaster_Cont["Global"]["Id"]
	
	if nItemId == tSummerActive2015_MagicMaste_NumLimit[1][1] then
		local nData0 = Get_SysDynaGlobalData0(nGlobalId)
		if nData0 >= tSummerActive2015_MagicMaste_NumLimit[1][2] then
			return tSummerActive2015_MagicMaste_NumLimit[1][3]
		else 
			nData0 = nData0 + 1
			Sys_SetSynaGlobalData0(nGlobalId,nData0)
			return nItemId
		end
		
	elseif nItemId == tSummerActive2015_MagicMaste_NumLimit[2][1] then
		local nData1 = Get_SysDynaGlobalData1(nGlobalId)
		if nData1 >= tSummerActive2015_MagicMaste_NumLimit[2][2] then
			return tSummerActive2015_MagicMaste_NumLimit[2][3]
		else 
			nData1 = nData1 + 1
			Sys_SetSynaGlobalData1(nGlobalId,nData1)
			return nItemId
		end
		
	elseif nItemId == tSummerActive2015_MagicMaste_NumLimit[3][1] then 
		local nData2 = Get_SysDynaGlobalData2(nGlobalId)
		if nData2 >= tSummerActive2015_MagicMaste_NumLimit[3][2] then
			return tSummerActive2015_MagicMaste_NumLimit[3][3]
		else 
			nData2 = nData2 + 1
			Sys_SetSynaGlobalData2(nGlobalId,nData2)
			return nItemId
		end
		
	elseif nItemId == tSummerActive2015_MagicMaste_NumLimit[4][1] then 
		local nData3 = Get_SysDynaGlobalData3(nGlobalId)
		if nData3 >= tSummerActive2015_MagicMaste_NumLimit[4][2] then
			return tSummerActive2015_MagicMaste_NumLimit[4][3]
		else 
			nData3 = nData3 + 1
			Sys_SetSynaGlobalData3(nGlobalId,nData3)
			return nItemId
		end
		
	elseif nItemId == tSummerActive2015_MagicMaste_NumLimit[5][1] then 
		local nData4 = Get_SysDynaGlobalData4(nGlobalId)
		if nData4 >= tSummerActive2015_MagicMaste_NumLimit[5][2] then
			return tSummerActive2015_MagicMaste_NumLimit[5][3]
		else 
			nData4 = nData4 + 1
			Sys_SetSynaGlobalData4(nGlobalId,nData4)
			return nItemId
		end
		
	elseif nItemId == tSummerActive2015_MagicMaste_NumLimit[6][1] then
		local nData5 = Get_SysDynaGlobalData5(nGlobalId)
		if nData5 >= tSummerActive2015_MagicMaste_NumLimit[6][2] then
			return tSummerActive2015_MagicMaste_NumLimit[6][3]
		else 
			nData5 = nData5 + 1
			Sys_SetSynaGlobalData5(nGlobalId,nData5)
			return nItemId
		end
	else
		return nItemId
	end
end 


function SummerActive2015_MagicMaster_MagicAction(nNpcId)
	--判断玩家等级
	if not User_JudgeLevelAndMetempsychosis(tSummerActive2015_MagicMaster_Cont["Level"],tSummerActive2015_MagicMaster_Cont["Metempsychosis"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	--判断看到奖励
	local nEvent = tSummerActive2015_MagicMaster_Cont["PeepNum"]["Event"]
	local nType = tSummerActive2015_MagicMaster_Cont["PeepNum"]["StcType"]
	
	if Task_ChkStcValue(nEvent,nType,"==",3) then
		local nRewardEvent = tSummerActive2015_MagicMaster_Cont["PReward"]["Event"]
		local nRewardType = tSummerActive2015_MagicMaster_Cont["PReward"]["StcType"]
	
		local nItemId = Get_UserStatisticValue(nRewardEvent,nRewardType)
		if nItemId == 1 then
			local flat,tMoonBox = Probabil_RandomAward(tSummerActive2015_MagicMaste_Award["MoonBox"],1)  
			local nMoonBoxId = tMoonBox[1]["tAward"][1]["Item_1"]
			nItemId = nMoonBoxId
		end	
		
		local sItemName = tSummerActive2015_MagicMaster_Text["RewardName"][nItemId] 
		local sStr = string.format(tSummerActive2015_MagicMaster_Text[15811]["Text311"],sItemName)
		Sys_DialogText(sStr)
		Sys_DialogOption(tSummerActive2015_MagicMaster_Text[15811]["Option8"],"</F>SummerActive2015_MagicMaster_GetReward</N>15811")
		Sys_DialogFace()
		Sys_DialogEnd()

	else
		LinkNpcGossipFunc_New(nNpcId,"2-2")
	end 
end

function SummerActive2015_MagicMaster_GetReward(nNpcId)
	--背包空间
	if not User_CheckLeftSpace(tSummerActive2015_MagicMaster_Cont["BagSpace"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end
	
	local nEvent = tSummerActive2015_MagicMaster_Cont["PeepNum"]["Event"]
	local nType = tSummerActive2015_MagicMaster_Cont["PeepNum"]["StcType"]
	Task_SetStatistic(nEvent,nType,tSummerActive2015_MagicMaster_Cont["PeepNum"]["Phase"][4],1,0)
	Task_SetStcTimestamp(nEvent,nType,0,0)
	
	local nRewardEvent = tSummerActive2015_MagicMaster_Cont["PReward"]["Event"]
	local nRewardType = tSummerActive2015_MagicMaster_Cont["PReward"]["StcType"]
	
	local nItemId = Get_UserStatisticValue(nRewardEvent,nRewardType)
	local sItemName = tSummerActive2015_MagicMaster_Text["RewardName"][nItemId] 
	
	local sLog = string.format(tSummerActive2015_MagicMaster_LOG["Reward"],nItemId)
	local sStr = string.format(tSummerActive2015_MagicMaster_Text["GetReward"],sItemName)

	
	Item_AddItem(nItemId)
	Sys_SaveActionFestivalLog(sLog)
	User_EffectAdd("self",tSummerActive2015_MagicMaster_Effect["Reward"])
	User_TalkChannel2005(sStr)

end 
function SummerActive2015_MagicMaster_ClearGlobal()
	local nGlobalID = tSummerActive2015_MagicMaster_Cont["Global"]["Id"]
	
	if Sys_ChkFullTime(tSummerActive2015_MagicMaster_Cont["ActivityTime"]) and Sys_ChkDayTime(tSummerActive2015_MagicMaste_ClearGlobal["ActivityTime"]) then
		Sys_ResetAllSynaGlobalData(nGlobalID)
	end
end


--------------------------------------NPC模块-------------------------------------------
	--15812	神奇的魔术箱
	tNpcFace[2505] = 0
	tNpcGossip[15812] = tNpcGossip[15812] or DefaultNpc:new{}
	tNpcGossip[15812]["OptionHidden"] = 1


	--活动时间前
	tNpcGossip[15812]["Text1-1"] = {111}
	tNpcGossip[15812]["Text111"] = tSummerActive2015_MagicMaster_Text[15812]["Text111"]
	tNpcGossip[15812]["tOption1-1"] = {1}
	tNpcGossip[15812]["ChkFunc1-1"] = function()
		return Sys_ChkFullTime(tSummerActive2015_MagicMaster_Cont["BeforeActivityTime"])
	end

	--活动时间中
	tNpcGossip[15812]["Text1-2"] = {121}
	tNpcGossip[15812]["Text121"] = tSummerActive2015_MagicMaster_Text[15812]["Text121"]
	tNpcGossip[15812]["tOption1-2"] = {2}
	tNpcGossip[15812]["ChkFunc1-2"] = function()
		return Sys_ChkFullTime(tSummerActive2015_MagicMaster_Cont["ActivityTime"])
	end

	--活动时间后
	tNpcGossip[15812]["Text1-3"] = {131}
	tNpcGossip[15812]["Text131"] = tSummerActive2015_MagicMaster_Text[15812]["Text131"]
	tNpcGossip[15812]["tOption1-3"] = {1}

	--等级
	tNpcGossip[15812]["Text2-1"] = {211}
	tNpcGossip[15812]["Text211"] = tSummerActive2015_MagicMaster_Text[15812]["Text211"]
	tNpcGossip[15812]["tOption2-1"] = {1}
	
	--第一次对白
	tNpcGossip[15812]["Text2-2"] = {221}
	tNpcGossip[15812]["Text221"] = tSummerActive2015_MagicMaster_Text[15812]["Text221"]
	tNpcGossip[15812]["tOption2-2"] = {1}

	--第二次对白
	tNpcGossip[15812]["Text3-1"] = {311}
	tNpcGossip[15812]["Text311"] = tSummerActive2015_MagicMaster_Text[15812]["Text311"]
	tNpcGossip[15812]["tOption3-1"] = {3}
	
	tNpcGossip[15812]["Text3-2"] = {321}
	tNpcGossip[15812]["Text321"] = tSummerActive2015_MagicMaster_Text[15812]["Text321"]
	tNpcGossip[15812]["tOption3-2"] = {3}
	
	tNpcGossip[15812]["Text3-3"] = {331}
	tNpcGossip[15812]["Text331"] = tSummerActive2015_MagicMaster_Text[15812]["Text331"]
	tNpcGossip[15812]["tOption3-3"] = {3}

	--第三次对白
	tNpcGossip[15812]["Text4-1"] = {411}
	tNpcGossip[15812]["Text411"] = tSummerActive2015_MagicMaster_Text[15812]["Text411"]
	tNpcGossip[15812]["tOption4-1"] = {1}
	
	
	--npc选项
	tNpcGossip[15812]["Option1"] = tSummerActive2015_MagicMaster_Text[15812]["Option1"]
	tNpcGossip[15812]["Option2"] = tSummerActive2015_MagicMaster_Text[15812]["Option2"]
	tNpcGossip[15812]["OptionFunc2"]="SummerActive2015_MagicMaster_PeepAction</N>15812"
	tNpcGossip[15812]["OptionChkFunc2"] = function ()
		return  Sys_ChkFullTime(tSummerActive2015_MagicMaster_Cont["ActivityTime"])
	end

	tNpcGossip[15812]["Option3"] = tSummerActive2015_MagicMaster_Text[15812]["Option3"]

	
	--15811	神奇的魔术箱
	tNpcFace[2504] = 52
	tNpcGossip[15811] = tNpcGossip[15811] or DefaultNpc:new{}
	tNpcGossip[15811]["OptionHidden"] = 1
	
	--活动时间前
	tNpcGossip[15811]["Text1-1"] = {111,112,113}
	tNpcGossip[15811]["Text111"] = tSummerActive2015_MagicMaster_Text[15811]["Text111"]
	tNpcGossip[15811]["Text112"] = tSummerActive2015_MagicMaster_Text[15811]["Text112"]
	tNpcGossip[15811]["Text113"] = tSummerActive2015_MagicMaster_Text[15811]["Text113"]
	tNpcGossip[15811]["tOption1-1"] = {1}
	tNpcGossip[15811]["ChkFunc1-1"] = function()
		return Sys_ChkFullTime(tSummerActive2015_MagicMaster_Cont["BeforeActivityTime"])
	end

	--活动时间中
	tNpcGossip[15811]["Text1-2"] = {121,122,123}
	tNpcGossip[15811]["Text121"] = tSummerActive2015_MagicMaster_Text[15811]["Text121"]
	tNpcGossip[15811]["Text122"] = tSummerActive2015_MagicMaster_Text[15811]["Text122"]
	tNpcGossip[15811]["Text123"] = tSummerActive2015_MagicMaster_Text[15811]["Text123"]
	tNpcGossip[15811]["tOption1-2"] = {2,3,4}
	tNpcGossip[15811]["ChkFunc1-2"] = function()
		return Sys_ChkFullTime(tSummerActive2015_MagicMaster_Cont["ActivityTime"])
	end

	--活动时间后
	tNpcGossip[15811]["Text1-3"] = {131}
	tNpcGossip[15811]["Text131"] = tSummerActive2015_MagicMaster_Text[15811]["Text131"]
	tNpcGossip[15811]["tOption1-3"] = {5}
	
	--等级
	tNpcGossip[15811]["Text2-1"] = {211}
	tNpcGossip[15811]["Text211"] = tSummerActive2015_MagicMaster_Text[15811]["Text211"]
	tNpcGossip[15811]["tOption2-1"] = {6}
	
	--不符合3
	tNpcGossip[15811]["Text2-2"] = {221,222}
	tNpcGossip[15811]["Text221"] = tSummerActive2015_MagicMaster_Text[15811]["Text221"]
	tNpcGossip[15811]["Text222"] = tSummerActive2015_MagicMaster_Text[15811]["Text222"]
	tNpcGossip[15811]["tOption2-2"] = {7}
	
	--空间不足
	tNpcGossip[15811]["Text2-3"] = {231}
	tNpcGossip[15811]["Text231"] = tSummerActive2015_MagicMaster_Text[15811]["Text231"]
	tNpcGossip[15811]["tOption2-3"] = {6}
	
	--确认对白
	tNpcGossip[15811]["Text3-1"] = {311}
	tNpcGossip[15811]["Text311"] = tSummerActive2015_MagicMaster_Text[15811]["Text311"]
	tNpcGossip[15811]["tOption3-1"] = {8}
	
	--更多
	tNpcGossip[15811]["Text4-1"] = {411,412,413,414}
	tNpcGossip[15811]["Text411"] = tSummerActive2015_MagicMaster_Text[15811]["Text411"]
	tNpcGossip[15811]["Text412"] = tSummerActive2015_MagicMaster_Text[15811]["Text412"]
	tNpcGossip[15811]["Text413"] = tSummerActive2015_MagicMaster_Text[15811]["Text413"]
	tNpcGossip[15811]["Text414"] = tSummerActive2015_MagicMaster_Text[15811]["Text414"]
	tNpcGossip[15811]["tOption4-1"] = {9}
	
	--npc选项
	tNpcGossip[15811]["Option1"] = tSummerActive2015_MagicMaster_Text[15811]["Option1"]
	tNpcGossip[15811]["Option2"] = tSummerActive2015_MagicMaster_Text[15811]["Option2"]
	tNpcGossip[15811]["OptionFunc2"]="SummerActive2015_MagicMaster_MagicAction</N>15811"
	tNpcGossip[15811]["OptionChkFunc2"] = function ()
		return  Sys_ChkFullTime(tSummerActive2015_MagicMaster_Cont["ActivityTime"])
	end

	tNpcGossip[15811]["Option3"] = tSummerActive2015_MagicMaster_Text[15811]["Option3"]
	tNpcGossip[15811]["OptionPoint3"] = "4-1"
	
	tNpcGossip[15811]["Option4"] = tSummerActive2015_MagicMaster_Text[15811]["Option4"]
	tNpcGossip[15811]["Option5"] = tSummerActive2015_MagicMaster_Text[15811]["Option5"]
	tNpcGossip[15811]["Option6"] = tSummerActive2015_MagicMaster_Text[15811]["Option6"]
	tNpcGossip[15811]["Option7"] = tSummerActive2015_MagicMaster_Text[15811]["Option7"]
	tNpcGossip[15811]["Option8"] = tSummerActive2015_MagicMaster_Text[15811]["Option8"]
	
	tNpcGossip[15811]["Option9"] = tSummerActive2015_MagicMaster_Text[15811]["Option9"]


	
	

-- 时间自检触发
 --tSystem_Prompet_Func = tSystem_Prompet_Func or {}
-- table.insert(tSystem_Prompet_Func,SummerActive2015_MagicMaster_ClearGlobal)
	