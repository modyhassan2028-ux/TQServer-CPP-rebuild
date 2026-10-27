------------------------------------------------------------------------------------
--Name:			[征服][任务脚本]跨服任务搬金砖
--Purpose:		跨服任务搬金砖
--Creator: 		郑鋆
--Created:		2014/12/16
------------------------------------------------------------------------------------

-- 命名前缀
-- ServiceTask_MoveGold_

-- 掩码说明
-- 136 32  是否领取过背包信
-- 136 33  npc处每天答题的次数

-- logId:	12000138


-- 常量表
local tServiceTask_MoveGold_Count = {}
	-- 玩家等级要求
	tServiceTask_MoveGold_Count["Metempsychosis"] = 1
	tServiceTask_MoveGold_Count["Level"] = 110

	-- 任务taskId
	tServiceTask_MoveGold_Count["TaskId"] = 30012
	
	-- 最多完成次数
	tServiceTask_MoveGold_Count["MaxNum"] = 3
	
	-- 动作ID
	tServiceTask_MoveGold_Count["Action"] = 220

	-- 奖励的积分值
	tServiceTask_MoveGold_Count["Score"] = 3
	
	tServiceTask_MoveGold_Count["PlunderEmoneyLog"] = "350	4311	0	0	1	"
	tServiceTask_MoveGold_Count["ShanghaiEmoneyLog"] = "350	4312	0	0	1	"

	-- 搬砖的范围
	tServiceTask_MoveGold_Count["MinPosX"] = 305
	tServiceTask_MoveGold_Count["MaxPosX"] = 321
	tServiceTask_MoveGold_Count["MinPosY"] = 271
	tServiceTask_MoveGold_Count["MaxPosY"] = 287
	
-- 各个品质的金砖对应的积分
local tServiceTask_MoveGold_Score = {}
	tServiceTask_MoveGold_Score[0] = 50
	tServiceTask_MoveGold_Score[1] = 70
	tServiceTask_MoveGold_Score[2] = 100
	tServiceTask_MoveGold_Score[3] = 150
	tServiceTask_MoveGold_Score[4] = 200

-- 津贴礼包配置
local tServiceTask_MoveGold_PackageAllowance = {}
	-- 至尊皇族津贴
	tServiceTask_MoveGold_PackageAllowance[3006989] = {}
	tServiceTask_MoveGold_PackageAllowance[3006989]["Space"] = 10
	tServiceTask_MoveGold_PackageAllowance[3006989]["Item"] = {}
	tServiceTask_MoveGold_PackageAllowance[3006989]["Item"][1] = {}
	tServiceTask_MoveGold_PackageAllowance[3006989]["Item"][1]["Id"] = 3002029
	tServiceTask_MoveGold_PackageAllowance[3006989]["Item"][1]["Attr"] = "0 10 0 0 1"
	tServiceTask_MoveGold_PackageAllowance[3006989]["Item"][2] = {}
	tServiceTask_MoveGold_PackageAllowance[3006989]["Item"][2]["Id"] = 3003124
	tServiceTask_MoveGold_PackageAllowance[3006989]["Item"][2]["Attr"] = "0 10 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tServiceTask_MoveGold_PackageAllowance[3006989]["StrengthValue"] = 1500
	tServiceTask_MoveGold_PackageAllowance[3006989]["Log"] = "0,0,3006989,1,12000138,2,3002029[3003124][12],10[10][1500]"

	-- 名门望族津贴
	tServiceTask_MoveGold_PackageAllowance[3006990] = {}
	tServiceTask_MoveGold_PackageAllowance[3006990]["Space"] = 8
	tServiceTask_MoveGold_PackageAllowance[3006990]["Item"] = {}
	tServiceTask_MoveGold_PackageAllowance[3006990]["Item"][1] = {}
	tServiceTask_MoveGold_PackageAllowance[3006990]["Item"][1]["Id"] = 3002029
	tServiceTask_MoveGold_PackageAllowance[3006990]["Item"][1]["Attr"] = "0 8 0 0 1"
	tServiceTask_MoveGold_PackageAllowance[3006990]["Item"][2] = {}
	tServiceTask_MoveGold_PackageAllowance[3006990]["Item"][2]["Id"] = 3003124
	tServiceTask_MoveGold_PackageAllowance[3006990]["Item"][2]["Attr"] = "0 8 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tServiceTask_MoveGold_PackageAllowance[3006990]["StrengthValue"] = 1000
	tServiceTask_MoveGold_PackageAllowance[3006990]["Log"] = "0,0,3006990,1,12000138,2,3002029[3003124][12],8[8][1000]"

	-- 达官贵人津贴
	tServiceTask_MoveGold_PackageAllowance[3006991] = {}
	tServiceTask_MoveGold_PackageAllowance[3006991]["Space"] = 5
	tServiceTask_MoveGold_PackageAllowance[3006991]["Item"] = {}
	tServiceTask_MoveGold_PackageAllowance[3006991]["Item"][1] = {}
	tServiceTask_MoveGold_PackageAllowance[3006991]["Item"][1]["Id"] = 3002029
	tServiceTask_MoveGold_PackageAllowance[3006991]["Item"][1]["Attr"] = "0 5 0 0 1"
	tServiceTask_MoveGold_PackageAllowance[3006991]["Item"][2] = {}
	tServiceTask_MoveGold_PackageAllowance[3006991]["Item"][2]["Id"] = 3003124
	tServiceTask_MoveGold_PackageAllowance[3006991]["Item"][2]["Attr"] = "0 5 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tServiceTask_MoveGold_PackageAllowance[3006991]["StrengthValue"] = 700
	tServiceTask_MoveGold_PackageAllowance[3006991]["Log"] = "0,0,3006991,1,12000138,2,3002029[3003124][12],5[5][700]"

	-- 保家卫国津贴
	tServiceTask_MoveGold_PackageAllowance[3006992] = {}
	tServiceTask_MoveGold_PackageAllowance[3006992]["Space"] = 2
	tServiceTask_MoveGold_PackageAllowance[3006992]["Item"] = {}
	tServiceTask_MoveGold_PackageAllowance[3006992]["Item"][1] = {}
	tServiceTask_MoveGold_PackageAllowance[3006992]["Item"][1]["Id"] = 3002029
	tServiceTask_MoveGold_PackageAllowance[3006992]["Item"][1]["Attr"] = "0 2 0 0 1"
	tServiceTask_MoveGold_PackageAllowance[3006992]["Item"][2] = {}
	tServiceTask_MoveGold_PackageAllowance[3006992]["Item"][2]["Id"] = 3003124
	tServiceTask_MoveGold_PackageAllowance[3006992]["Item"][2]["Attr"] = "0 3 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tServiceTask_MoveGold_PackageAllowance[3006992]["StrengthValue"] = 500
	tServiceTask_MoveGold_PackageAllowance[3006992]["Log"] = "0,0,3006992,1,12000138,2,3002029[3003124][12],2[3][500]"

	-- 绝世佳人津贴
	tServiceTask_MoveGold_PackageAllowance[3006993] = {}
	tServiceTask_MoveGold_PackageAllowance[3006993]["Space"] = 6
	tServiceTask_MoveGold_PackageAllowance[3006993]["Item"] = {}
	tServiceTask_MoveGold_PackageAllowance[3006993]["Item"][1] = {}
	tServiceTask_MoveGold_PackageAllowance[3006993]["Item"][1]["Id"] = 3002029
	tServiceTask_MoveGold_PackageAllowance[3006993]["Item"][1]["Attr"] = "0 6 0 0 1"
	tServiceTask_MoveGold_PackageAllowance[3006993]["Item"][2] = {}
	tServiceTask_MoveGold_PackageAllowance[3006993]["Item"][2]["Id"] = 3003124
	tServiceTask_MoveGold_PackageAllowance[3006993]["Item"][2]["Attr"] = "0 6 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3"
	tServiceTask_MoveGold_PackageAllowance[3006993]["StrengthValue"] = 800
	tServiceTask_MoveGold_PackageAllowance[3006993]["Log"] = "0,0,3006993,1,12000138,2,3002029[3003124][12],6[6][800]"

local tServiceTask_MoveGold_Allowance = {}
	-- 3007259	【特权】至尊皇族津贴	
	tServiceTask_MoveGold_Allowance[3007259] = {}
	tServiceTask_MoveGold_Allowance[3007259][1] = {}
	tServiceTask_MoveGold_Allowance[3007259][1]["Id"] = 3006989
	tServiceTask_MoveGold_Allowance[3007259][1]["Effect"] = "angelwing"
	tServiceTask_MoveGold_Allowance[3007259][1]["Index"] = "RewardTrainPackage"
	tServiceTask_MoveGold_Allowance[3007259][2] = {}
	tServiceTask_MoveGold_Allowance[3007259][2]["StrengthValue"] = 2000
	tServiceTask_MoveGold_Allowance[3007259][2]["Effect"] = "eidolon"
	tServiceTask_MoveGold_Allowance[3007259][2]["Index"] = "RewardStrengthValue"
	
	-- 3007260	【特权】名门望族津贴	
	tServiceTask_MoveGold_Allowance[3007260] = {}
	tServiceTask_MoveGold_Allowance[3007260][1] = {}
	tServiceTask_MoveGold_Allowance[3007260][1]["Id"] = 3006990
	tServiceTask_MoveGold_Allowance[3007260][1]["Effect"] = "angelwing"
	tServiceTask_MoveGold_Allowance[3007260][1]["Index"] = "RewardTrainPackage"
	tServiceTask_MoveGold_Allowance[3007260][2] = {}
	tServiceTask_MoveGold_Allowance[3007260][2]["StrengthValue"] = 1600
	tServiceTask_MoveGold_Allowance[3007260][2]["Effect"] = "eidolon"
	tServiceTask_MoveGold_Allowance[3007260][2]["Index"] = "RewardStrengthValue"
	
	-- 3007261	【特权】达官贵人津贴	
	tServiceTask_MoveGold_Allowance[3007261] = {}
	tServiceTask_MoveGold_Allowance[3007261][1] = {}
	tServiceTask_MoveGold_Allowance[3007261][1]["Id"] = 3006991
	tServiceTask_MoveGold_Allowance[3007261][1]["Effect"] = "angelwing"
	tServiceTask_MoveGold_Allowance[3007261][1]["Index"] = "RewardTrainPackage"
	tServiceTask_MoveGold_Allowance[3007261][2] = {}
	tServiceTask_MoveGold_Allowance[3007261][2]["StrengthValue"] = 1000
	tServiceTask_MoveGold_Allowance[3007261][2]["Effect"] = "eidolon"
	tServiceTask_MoveGold_Allowance[3007261][2]["Index"] = "RewardStrengthValue"
	
	-- 3007262	【特权】保家卫国津贴	
	tServiceTask_MoveGold_Allowance[3007262] = {}
	tServiceTask_MoveGold_Allowance[3007262][1] = {}
	tServiceTask_MoveGold_Allowance[3007262][1]["Id"] = 3006992
	tServiceTask_MoveGold_Allowance[3007262][1]["Effect"] = "angelwing"
	tServiceTask_MoveGold_Allowance[3007262][1]["Index"] = "RewardTrainPackage"
	tServiceTask_MoveGold_Allowance[3007262][2] = {}
	tServiceTask_MoveGold_Allowance[3007262][2]["StrengthValue"] = 600
	tServiceTask_MoveGold_Allowance[3007262][2]["Effect"] = "eidolon"
	tServiceTask_MoveGold_Allowance[3007262][2]["Index"] = "RewardStrengthValue"
	
	-- 3007263	【特权】绝世佳人津贴
	tServiceTask_MoveGold_Allowance[3007263] = {}
	tServiceTask_MoveGold_Allowance[3007263] = {}
	tServiceTask_MoveGold_Allowance[3007263][1] = {}
	tServiceTask_MoveGold_Allowance[3007263][1]["Id"] = 3006993
	tServiceTask_MoveGold_Allowance[3007263][1]["Effect"] = "angelwing"
	tServiceTask_MoveGold_Allowance[3007263][1]["Index"] = "RewardTrainPackage"
	tServiceTask_MoveGold_Allowance[3007263][2] = {}
	tServiceTask_MoveGold_Allowance[3007263][2]["StrengthValue"] = 1200
	tServiceTask_MoveGold_Allowance[3007263][2]["Effect"] = "eidolon"
	tServiceTask_MoveGold_Allowance[3007263][2]["Index"] = "RewardStrengthValue"

-- 俸禄礼包
local tServiceTask_MoveGold_SalaryPackage = {}
	tServiceTask_MoveGold_SalaryPackage["Log"] = "0,0,%d,1,12000138,2,12[14][6],%d[%d][%d]"
	-- 3006994	【庶民】俸禄礼包	
	tServiceTask_MoveGold_SalaryPackage[3006994] = {}
	tServiceTask_MoveGold_SalaryPackage[3006994]["AddStrengthValue"] = 100
	tServiceTask_MoveGold_SalaryPackage[3006994]["AddRidingPoints"] = 300
	tServiceTask_MoveGold_SalaryPackage[3006994]["AddCultivation"] = 40
	
	-- 3006995	【伍长】俸禄礼包
	tServiceTask_MoveGold_SalaryPackage[3006995] = {}
	tServiceTask_MoveGold_SalaryPackage[3006995]["AddStrengthValue"] = 150
	tServiceTask_MoveGold_SalaryPackage[3006995]["AddRidingPoints"] = 450
	tServiceTask_MoveGold_SalaryPackage[3006995]["AddCultivation"] = 60
	
	-- 3006996	【什长】俸禄礼包	
	tServiceTask_MoveGold_SalaryPackage[3006996] = {}
	tServiceTask_MoveGold_SalaryPackage[3006996]["AddStrengthValue"] = 180
	tServiceTask_MoveGold_SalaryPackage[3006996]["AddRidingPoints"] = 500
	tServiceTask_MoveGold_SalaryPackage[3006996]["AddCultivation"] = 70
	
	-- 3006997	【百夫长】俸禄礼包	
	tServiceTask_MoveGold_SalaryPackage[3006997] = {}
	tServiceTask_MoveGold_SalaryPackage[3006997]["AddStrengthValue"] = 210
	tServiceTask_MoveGold_SalaryPackage[3006997]["AddRidingPoints"] = 550
	tServiceTask_MoveGold_SalaryPackage[3006997]["AddCultivation"] = 80
	
	-- 3006998	【都尉】俸禄礼包	
	tServiceTask_MoveGold_SalaryPackage[3006998] = {}
	tServiceTask_MoveGold_SalaryPackage[3006998]["AddStrengthValue"] = 250
	tServiceTask_MoveGold_SalaryPackage[3006998]["AddRidingPoints"] = 600
	tServiceTask_MoveGold_SalaryPackage[3006998]["AddCultivation"] = 90
	
	-- 3006999	【校尉】俸禄礼包	
	tServiceTask_MoveGold_SalaryPackage[3006999] = {}
	tServiceTask_MoveGold_SalaryPackage[3006999]["AddStrengthValue"] = 280
	tServiceTask_MoveGold_SalaryPackage[3006999]["AddRidingPoints"] = 650
	tServiceTask_MoveGold_SalaryPackage[3006999]["AddCultivation"] = 100
	
	-- 3007000	【中郎将】俸禄礼包
	tServiceTask_MoveGold_SalaryPackage[3007000] = {}
	tServiceTask_MoveGold_SalaryPackage[3007000]["AddStrengthValue"] = 310
	tServiceTask_MoveGold_SalaryPackage[3007000]["AddRidingPoints"] = 700
	tServiceTask_MoveGold_SalaryPackage[3007000]["AddCultivation"] = 110
	
	-- 3007001	【裨将】俸禄礼包
	tServiceTask_MoveGold_SalaryPackage[3007001] = {}
	tServiceTask_MoveGold_SalaryPackage[3007001]["AddStrengthValue"] = 350
	tServiceTask_MoveGold_SalaryPackage[3007001]["AddRidingPoints"] = 750
	tServiceTask_MoveGold_SalaryPackage[3007001]["AddCultivation"] = 120
	
	-- 3007002	【偏将】俸禄礼包
	tServiceTask_MoveGold_SalaryPackage[3007002] = {}
	tServiceTask_MoveGold_SalaryPackage[3007002]["AddStrengthValue"] = 390
	tServiceTask_MoveGold_SalaryPackage[3007002]["AddRidingPoints"] = 800
	tServiceTask_MoveGold_SalaryPackage[3007002]["AddCultivation"] = 130
	
	-- 3007003	【将军】俸禄礼包
	tServiceTask_MoveGold_SalaryPackage[3007003] = {}
	tServiceTask_MoveGold_SalaryPackage[3007003]["AddStrengthValue"] = 430
	tServiceTask_MoveGold_SalaryPackage[3007003]["AddRidingPoints"] = 850
	tServiceTask_MoveGold_SalaryPackage[3007003]["AddCultivation"] = 140
	
	-- 3007004	【卫将军】俸禄礼包
	tServiceTask_MoveGold_SalaryPackage[3007004] = {}
	tServiceTask_MoveGold_SalaryPackage[3007004]["AddStrengthValue"] = 470
	tServiceTask_MoveGold_SalaryPackage[3007004]["AddRidingPoints"] = 900
	tServiceTask_MoveGold_SalaryPackage[3007004]["AddCultivation"] = 150
	
	-- 3007005	【车骑将军】俸禄礼包
	tServiceTask_MoveGold_SalaryPackage[3007005] = {}
	tServiceTask_MoveGold_SalaryPackage[3007005]["AddStrengthValue"] = 500
	tServiceTask_MoveGold_SalaryPackage[3007005]["AddRidingPoints"] = 1000
	tServiceTask_MoveGold_SalaryPackage[3007005]["AddCultivation"] = 160
	
	-- 3007006	【骠骑将军】俸禄礼包
	tServiceTask_MoveGold_SalaryPackage[3007006] = {}
	tServiceTask_MoveGold_SalaryPackage[3007006]["AddStrengthValue"] = 550
	tServiceTask_MoveGold_SalaryPackage[3007006]["AddRidingPoints"] = 1100
	tServiceTask_MoveGold_SalaryPackage[3007006]["AddCultivation"] = 180
	
	-- 3007007	【大将军】俸禄礼包
	tServiceTask_MoveGold_SalaryPackage[3007007] = {}
	tServiceTask_MoveGold_SalaryPackage[3007007]["AddStrengthValue"] = 600
	tServiceTask_MoveGold_SalaryPackage[3007007]["AddRidingPoints"] = 1200
	tServiceTask_MoveGold_SalaryPackage[3007007]["AddCultivation"] = 200
	
	-- 3007435	朝廷俸禄礼包
	tServiceTask_MoveGold_SalaryPackage[3007435] = {}
	tServiceTask_MoveGold_SalaryPackage[3007435]["AddStrengthValue"] = 200
	tServiceTask_MoveGold_SalaryPackage[3007435]["AddRidingPoints"] = 600
	tServiceTask_MoveGold_SalaryPackage[3007435]["AddCultivation"] = 140

--------------------------------------逻辑部分-----------------------------------------
-- 交砖NPC
function ServiceTask_MoveGold_Npc()
	-- 判断是否是跨服玩家
	if not User_IsCross() then
		SendHandBrickInfo(1)
	end
end

-- 搬砖函数
function ServiceTask_MoveGold_MoveBrick()
	local nUserId = Get_UserId()

	-- 判断是否加入联盟
	if not User_IsInLeague() then
		User_TalkChannel2005(tServiceTask_MoveGold_Text["NoAlliance"])
		return
	end

	-- 获取玩家当前所在服务器的金砖数量
	local nGoldNum = Get_CountryBrickAmount()

	-- 判断是否是跨服玩家
	if not User_IsCross(nUserId) then
		-- 判断是否本联盟的金砖
		local nCountryId = Get_CountryId()
		local nLeagueId = Get_UserLeagueId(nUserId)
		
		-- 判断本服是否有执政盟
		if nCountryId <= 0 then
			User_TalkChannel2005(tServiceTask_MoveGold_Text["NoAU"])
			return
		end
		
		-- 判断是否是本盟的玩家
		if nCountryId == nLeagueId then
			SendHandBrickInfo(0)
			return
		end
	end
	
	-- 判断是否可以掠夺
	if not User_IsInPlunderWar() then
		User_TalkChannel2005(tServiceTask_MoveGold_Text["NoPredatoryWar"])
		SendHandBrickInfo(0)
		return
	end

	-- 判断等级
	if not User_JudgeLevelAndMetempsychosis(tServiceTask_MoveGold_Count["Level"],tServiceTask_MoveGold_Count["Metempsychosis"]) then
		User_TalkChannel2005(tServiceTask_MoveGold_Text["NoLevel"])
		return
	end
	
	-- 判断金砖的数量
	-- if nGoldNum == nil or nGoldNum <= 0 then
		-- User_TalkChannel2005(tServiceTask_MoveGold_Text["NoGold"])
		-- return
	-- end
	--判断当前服务器金砖是否有九龙罩状态，有九龙罩状态不能搬砖
	if User_IsImmunePlunder() then
		User_TalkChannel2005(tServiceTask_MoveGold_Text["HaveJLZ"])
		return
	end
		
	-- 判断玩家位置
	local nCellX = Get_UserPositionX(nUserId)
	local nCellY = Get_UserPositionY(nUserId)
	
	if not (nCellX >= tServiceTask_MoveGold_Count["MinPosX"] and nCellX <= tServiceTask_MoveGold_Count["MaxPosX"]
			and nCellY >= tServiceTask_MoveGold_Count["MinPosY"] and nCellY <= tServiceTask_MoveGold_Count["MaxPosY"] ) then
	
		User_TalkChannel2005(tServiceTask_MoveGold_Text["NoRange"])
		return
	end

	Sys_SaveActionParamLog("action_gz","0,0,0,0,18000077,2,0,0")
	
	local nNpcId = Get_NpcId()
	User_BeginMoveGoldBrick(tServiceTask_MoveGold_Count["Action"],tServiceTask_MoveGold_Text["Read"],nNpcId,nUserId)
end

-- 搬砖成功操作
function ServiceTask_MoveGold_MoveSuccess()
	local nQuality = Get_BrickQuality()
	
	if nQuality < 0 then
		User_TalkChannel2005(tServiceTask_MoveGold_Text["MoveSuccess"])
	else
		User_TalkChannel2005(tServiceTask_MoveGold_Text["Quality"][nQuality])
	end
	
	Sys_SaveEmoneyBuy(tServiceTask_MoveGold_Count["PlunderEmoneyLog"])
end

-- 搬砖失败提示
function ServiceTask_MoveGold_MoveFail()
	User_TalkChannel2005(tServiceTask_MoveGold_Text["MoveFail"])
end

-- 交砖成功函数
-- nNormal 表示区分正常交砖还是国家没金砖的时候交砖的奖励
-- nQuality	金砖的品质
function ServiceTask_MoveGold_MakeBrickSuccess(nNormal,nQuality)
	User_TalkChannel2005(tServiceTask_MoveGold_Text["MoveGoldSuccess"])
	Sys_SaveEmoneyBuy(tServiceTask_MoveGold_Count["ShanghaiEmoneyLog"])

	-- local nTaskId = tServiceTask_MoveGold_Count["TaskId"]
	
	-- 判断是否有接任务
	-- if Task_ChkTaskDetail(nTaskId) then
		-- local nTime = os.time()

		-- 判断是否隔天
		-- if Task_DetailInterval(nTaskId,1,4) then
			-- Task_SetTaskDetailData6(nTaskId,0)
		-- end
		
		-- local nData = Get_TaskDetailData6(nTaskId) + 1
		-- Task_SetTaskDetailData6(nTaskId,nData)
		-- Task_SetTaskDetailData7(nTaskId,nTime)
		-- Task_SetTaskDetailData1(nTaskId,0)

		-- 加积分
		if National_War_AddIntegral(tServiceTask_MoveGold_Score[nQuality]) then
			User_TalkChannel2005(string.format(tServiceTask_MoveGold_Text["Success"],tServiceTask_MoveGold_Score[nQuality]))
		end
		
		User_EffectAdd("self","accession")
	-- end
end

-- 交砖失败函数
function ServiceTask_MoveGold_MakeBrickFail()
	User_TalkChannel2005(tServiceTask_MoveGold_Text["MoveGoldFail"])
end

-- 建立联盟。
function ServiceTask_MoveGold_EstablishAlliance(nNpcId)
	-- 判断是否加入联盟
	if User_IsInLeague() then
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end
	
	local nRank = Get_UserGuildRank()

	-- 判断是否是帮主
	if nRank ~= 1000 then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	local nGuildId = Get_UserGuildId(nUserId)
	local nEmoney = Get_UserSynEmoney(nGuildId)
	
	-- 判断帮派天石数量是否够
	if nEmoney < 3000 then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	
	-- 判断帮派等级
	local nSynLevel = Get_UserSynLevel(nGuildId)
	if nSynLevel < 9 then
		User_TalkChannel2005(tServiceTask_MoveGold_Text["NoGangRank"])
		return
	end
	
	-- 判断本服战旗赛
	local nVexillum = Get_VexillumRank(nGuildId)
	
	if nVexillum > 7 or nVexillum < 0 then
		User_TalkChannel2005(tServiceTask_MoveGold_Text["NoStandardTournam"])
		return
	end

	User_OpenDialog(693)
end

-- 更改联盟名称
function ServiceTask_MoveGold_ChangeAllianceName(nNpcId)
	-- 判断是否加入联盟
	if not User_IsInLeague() then
		User_TalkChannel2005(tServiceTask_MoveGold_Text["NoLeague"])
		return
	end
	
	-- 判断是否是盟主
	if not User_IsLeagueLeader() then
		User_TalkChannel2005(tServiceTask_MoveGold_Text["DynamicAlliance"])
		return
	end

	User_OpenDialog(723)
end

-- 玩家每天上线免费领取喇叭
function ServiceTask_MoveGold_GetSpeakerNum()
	-- 判断今天是否领取过
	local nEvent = 136
	local nType = 16
	
	if not Task_StcInterval(nEvent,nType,1,4) then
		if Task_ChkStcValue(nEvent,nType,">=",1) then
			return
		end
	end
	
	-- 判断背包空间
	if not User_CheckLeftSpace(1) then
		User_TalkChannel2005(tServiceTask_MoveGold_Text["NoSpace1"])
		return
	end
	
	local nItemNum = User_GetSpeakerNumEveryDay()
	
	if nItemNum <= 0 then
		return
	end
	
	-- 判断是否有100个喇叭
	if Item_ChkMulItem(3002218,3002218,100,1) then
		User_TalkChannel2005(tServiceTask_MoveGold_Text["ItemNumFull"])
		return
	end

	local sItemAttr = string.format("0 %d 3 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 3",nItemNum)
	
	Item_AddNewItem(3002218,sItemAttr)
	Task_SetStatistic(nEvent,nType,1,1)
	Task_SetStcTimestamp(nEvent,nType,0,0)
	
	User_TalkChannel2005(string.format(tServiceTask_MoveGold_Text["RewardItem"],nItemNum))
end

-- 津贴礼包
function ServiceTask_MoveGold_PackageAllowance(nItemId)
	local nSpace = tServiceTask_MoveGold_PackageAllowance[nItemId]["Space"]
	
	-- 判断背包空间
	if not User_CheckLeftSpace(nSpace) then
		User_TalkChannel2005(tServiceTask_MoveGold_Text["NoSpace"])
		return
	end
	
	if Item_ChkItem(nItemId,1) and Item_DelItem(nItemId,1) then
		local sCont = tServiceTask_MoveGold_Text["OpenPackage"]
		local tItemNum = {}
		
		User_AddStrengthValue(tServiceTask_MoveGold_PackageAllowance[nItemId]["StrengthValue"])

		for i = 1,#tServiceTask_MoveGold_PackageAllowance[nItemId]["Item"] do
			local v = tServiceTask_MoveGold_PackageAllowance[nItemId]["Item"][i]
			local tItemAttr = Sys_Split(v["Attr"]," ")
			local sItemNum = tItemAttr[2]
			table.insert(tItemNum,tonumber(sItemNum))
			Item_AddNewItem(v["Id"],v["Attr"])
		end

		sCont = string.format(sCont,tItemNum[1],tItemNum[2])
		
		-- 打log
		Sys_SaveActionFestivalLog(tServiceTask_MoveGold_PackageAllowance[nItemId]["Log"])

		-- 给提示
		User_TalkChannel2005(sCont)
		
		User_EffectAdd("self","angelwing")
	end
end

-- 俸禄礼包
function ServiceTask_MoveGold_SalaryPackage(nItemId)
	if tServiceTask_MoveGold_SalaryPackage[nItemId] == nil then
		return
	end

	if Item_ChkItem(nItemId,1) and Item_DelItem(nItemId,1) then
		local nAddStrengthValue = tServiceTask_MoveGold_SalaryPackage[nItemId]["AddStrengthValue"]
		local nAddCultivation = tServiceTask_MoveGold_SalaryPackage[nItemId]["AddCultivation"] 
		local nAddRidingPoints = tServiceTask_MoveGold_SalaryPackage[nItemId]["AddRidingPoints"]
		local sLog = string.format(tServiceTask_MoveGold_SalaryPackage["Log"],nItemId,nAddStrengthValue,nAddRidingPoints,nAddCultivation)
		local sCount = string.format(tServiceTask_MoveGold_Text["OpenSalaryPackage"],nAddStrengthValue,nAddRidingPoints,nAddCultivation)
		
		-- 加气力值
		User_AddStrengthValue(nAddStrengthValue)
		-- 加修行值
		User_AddCultivation(nAddCultivation)
		-- 加骑宠积分
		User_AddRidingPoints(nAddRidingPoints)
		
		Sys_SaveActionFestivalLog(sLog)
		
		User_TalkChannel2005(sCount)
	end
end

-- 给修炼礼包
function ServiceTask_MoveGold_UseAllowance(nItemId,nType)
	if Item_ChkItem(nItemId,1) and Item_DelItem(nItemId,1) then
		local sIndex = tServiceTask_MoveGold_Allowance[nItemId][nType]["Index"]
		local sCount = tServiceTask_MoveGold_Text[sIndex]
		local sLog = "0,0,%d,1,12000138,2,%d,%d"
		
		if nType == 1 then
			local sItemName = Get_ItemtypeName(tServiceTask_MoveGold_Allowance[nItemId][nType]["Id"])
			Item_AddItem(tServiceTask_MoveGold_Allowance[nItemId][nType]["Id"])
			sLog = string.format(sLog,nItemId,tServiceTask_MoveGold_Allowance[nItemId][nType]["Id"],1)
			sCount = string.format(sCount,sItemName)
		else
			User_AddStrengthValue(tServiceTask_MoveGold_Allowance[nItemId][nType]["StrengthValue"])
			sLog = string.format(sLog,nItemId,12,tServiceTask_MoveGold_Allowance[nItemId][nType]["StrengthValue"])
			sCount = string.format(sCount,tServiceTask_MoveGold_Allowance[nItemId][nType]["StrengthValue"])
		end
		
		Sys_SaveActionFestivalLog(sLog)
		User_TalkChannel2005(sCount)
		User_EffectAdd("self",tServiceTask_MoveGold_Allowance[nItemId][nType]["Effect"])
	end
end

--------------------------------------NPC模块-------------------------------------------
-- 跨服任务大使
-- 选项
tNpcGossip[17400]["Option156"] = tServiceTask_MoveGold_Text[17400]["Option156"]
tNpcGossip[17400]["OptionFunc156"]="ServiceTask_MoveGold_Npc"

-- 联盟建立指挥官
tNpcFace[15] = 7
tNpcGossip[10003] = tNpcGossip[10003] or DefaultNpc:new{}
tNpcGossip[10003]["OptionHidden"] = 1

-- 【玩家选1、接受任务】
tNpcGossip[10003]["Text1-1"] = {111,112}
tNpcGossip[10003]["Text111"] = tServiceTask_MoveGold_Text[10003]["111"]
tNpcGossip[10003]["Text112"] = tServiceTask_MoveGold_Text[10003]["112"]
tNpcGossip[10003]["tOption1-1"] = {1,6,2}

tNpcGossip[10003]["Text2-1"] = {211}
tNpcGossip[10003]["Text211"] = tServiceTask_MoveGold_Text[10003]["211"]
tNpcGossip[10003]["tOption2-1"] = {3}

tNpcGossip[10003]["Text2-2"] = {221}
tNpcGossip[10003]["Text221"] = tServiceTask_MoveGold_Text[10003]["221"]
tNpcGossip[10003]["tOption2-2"] = {4}

tNpcGossip[10003]["Text2-3"] = {231}
tNpcGossip[10003]["Text231"] = tServiceTask_MoveGold_Text[10003]["231"]
tNpcGossip[10003]["tOption2-3"] = {5}

tNpcGossip[10003]["Option1"] = tServiceTask_MoveGold_Text[10003]["Option1"]
tNpcGossip[10003]["OptionFunc1"]="ServiceTask_MoveGold_EstablishAlliance</N>10003"
tNpcGossip[10003]["OptionChkFunc1"] = function ()
	return not User_IsInLeague()
end

tNpcGossip[10003]["Option2"] = tServiceTask_MoveGold_Text[10003]["Option2"]
tNpcGossip[10003]["Option3"] = tServiceTask_MoveGold_Text[10003]["Option3"]
tNpcGossip[10003]["Option4"] = tServiceTask_MoveGold_Text[10003]["Option4"]
tNpcGossip[10003]["Option5"] = tServiceTask_MoveGold_Text[10003]["Option5"]
tNpcGossip[10003]["Option6"] = tServiceTask_MoveGold_Text[10003]["Option6"]
tNpcGossip[10003]["OptionFunc6"]="ServiceTask_MoveGold_ChangeAllianceName</N>10003"
tNpcGossip[10003]["OptionChkFunc6"] = function ()
	return User_IsInLeague()
end

-- 津贴的礼包
-------------------------A包
tItem[3006989] = tItem[3006989] or {}
tItem[3006989]["Function"] = function(nItemId,sItemName)
	ServiceTask_MoveGold_PackageAllowance(nItemId)
end

tItem[3006990] = tItem[3006990] or {}
tItem[3006990]["Function"] = function(nItemId,sItemName)
	ServiceTask_MoveGold_PackageAllowance(nItemId)
end

tItem[3006991] = tItem[3006991] or {}
tItem[3006991]["Function"] = function(nItemId,sItemName)
	ServiceTask_MoveGold_PackageAllowance(nItemId)
end

tItem[3006992] = tItem[3006992] or {}
tItem[3006992]["Function"] = function(nItemId,sItemName)
	ServiceTask_MoveGold_PackageAllowance(nItemId)
end

tItem[3006993] = tItem[3006993] or {}
tItem[3006993]["Function"] = function(nItemId,sItemName)
	ServiceTask_MoveGold_PackageAllowance(nItemId)
end

-------------------------
-- 3007259	【特权】至尊皇族津贴
-- 3007260	【特权】名门望族津贴
-- 3007261	【特权】达官贵人津贴
-- 3007262	【特权】保家卫国津贴
-- 3007263	【特权】绝世佳人津贴

tItem[3007259] = tItem[3007259] or {}
tItem[3007259]["Text1-1"] = {111}
tItem[3007259]["Text111"] = tServiceTask_MoveGold_Text[3007259]["111"]
tItem[3007259]["tOption1-1"] = {1,2}
tItem[3007259]["Option1"] = tServiceTask_MoveGold_Text[3007259]["Option1"]
tItem[3007259]["OptionFunc1"]="ServiceTask_MoveGold_UseAllowance</N>3007259</N>1"
tItem[3007259]["Option2"] = tServiceTask_MoveGold_Text[3007259]["Option2"]
tItem[3007259]["OptionFunc2"]="ServiceTask_MoveGold_UseAllowance</N>3007259</N>2"

tItem[3007260] = tItem[3007260] or {}
tItem[3007260]["Text1-1"] = {111}
tItem[3007260]["Text111"] = tServiceTask_MoveGold_Text[3007260]["111"]
tItem[3007260]["tOption1-1"] = {1,2}
tItem[3007260]["Option1"] = tServiceTask_MoveGold_Text[3007260]["Option1"]
tItem[3007260]["OptionFunc1"]="ServiceTask_MoveGold_UseAllowance</N>3007260</N>1"
tItem[3007260]["Option2"] = tServiceTask_MoveGold_Text[3007260]["Option2"]
tItem[3007260]["OptionFunc2"]="ServiceTask_MoveGold_UseAllowance</N>3007260</N>2"

tItem[3007261] = tItem[3007261] or {}
tItem[3007261]["Text1-1"] = {111}
tItem[3007261]["Text111"] = tServiceTask_MoveGold_Text[3007261]["111"]
tItem[3007261]["tOption1-1"] = {1,2}
tItem[3007261]["Option1"] = tServiceTask_MoveGold_Text[3007261]["Option1"]
tItem[3007261]["OptionFunc1"]="ServiceTask_MoveGold_UseAllowance</N>3007261</N>1"
tItem[3007261]["Option2"] = tServiceTask_MoveGold_Text[3007261]["Option2"]
tItem[3007261]["OptionFunc2"]="ServiceTask_MoveGold_UseAllowance</N>3007261</N>2"

tItem[3007262] = tItem[3007262] or {}
tItem[3007262]["Text1-1"] = {111}
tItem[3007262]["Text111"] = tServiceTask_MoveGold_Text[3007262]["111"]
tItem[3007262]["tOption1-1"] = {1,2}
tItem[3007262]["Option1"] = tServiceTask_MoveGold_Text[3007262]["Option1"]
tItem[3007262]["OptionFunc1"]="ServiceTask_MoveGold_UseAllowance</N>3007262</N>1"
tItem[3007262]["Option2"] = tServiceTask_MoveGold_Text[3007262]["Option2"]
tItem[3007262]["OptionFunc2"]="ServiceTask_MoveGold_UseAllowance</N>3007262</N>2"

tItem[3007263] = tItem[3007263] or {}
tItem[3007263]["Text1-1"] = {111}
tItem[3007263]["Text111"] = tServiceTask_MoveGold_Text[3007263]["111"]
tItem[3007263]["tOption1-1"] = {1,2}
tItem[3007263]["Option1"] = tServiceTask_MoveGold_Text[3007263]["Option1"]
tItem[3007263]["OptionFunc1"]="ServiceTask_MoveGold_UseAllowance</N>3007263</N>1"
tItem[3007263]["Option2"] = tServiceTask_MoveGold_Text[3007263]["Option2"]
tItem[3007263]["OptionFunc2"]="ServiceTask_MoveGold_UseAllowance</N>3007263</N>2"

-- 俸禄礼包
tItem[3006994] = tItem[3006994] or {}
tItem[3006994]["Function"] = function(nItemId,sItemName)
	ServiceTask_MoveGold_SalaryPackage(nItemId)
end

tItem[3006995] = tItem[3006995] or {}
tItem[3006995]["Function"] = function(nItemId,sItemName)
	ServiceTask_MoveGold_SalaryPackage(nItemId)
end

tItem[3006996] = tItem[3006996] or {}
tItem[3006996]["Function"] = function(nItemId,sItemName)
	ServiceTask_MoveGold_SalaryPackage(nItemId)
end

tItem[3006997] = tItem[3006997] or {}
tItem[3006997]["Function"] = function(nItemId,sItemName)
	ServiceTask_MoveGold_SalaryPackage(nItemId)
end

tItem[3006998] = tItem[3006998] or {}
tItem[3006998]["Function"] = function(nItemId,sItemName)
	ServiceTask_MoveGold_SalaryPackage(nItemId)
end

tItem[3006999] = tItem[3006999] or {}
tItem[3006999]["Function"] = function(nItemId,sItemName)
	ServiceTask_MoveGold_SalaryPackage(nItemId)
end

tItem[3007000] = tItem[3007000] or {}
tItem[3007000]["Function"] = function(nItemId,sItemName)
	ServiceTask_MoveGold_SalaryPackage(nItemId)
end

tItem[3007001] = tItem[3007001] or {}
tItem[3007001]["Function"] = function(nItemId,sItemName)
	ServiceTask_MoveGold_SalaryPackage(nItemId)
end

tItem[3007002] = tItem[3007002] or {}
tItem[3007002]["Function"] = function(nItemId,sItemName)
	ServiceTask_MoveGold_SalaryPackage(nItemId)
end

tItem[3007003] = tItem[3007003] or {}
tItem[3007003]["Function"] = function(nItemId,sItemName)
	ServiceTask_MoveGold_SalaryPackage(nItemId)
end

tItem[3007004] = tItem[3007004] or {}
tItem[3007004]["Function"] = function(nItemId,sItemName)
	ServiceTask_MoveGold_SalaryPackage(nItemId)
end

tItem[3007005] = tItem[3007005] or {}
tItem[3007005]["Function"] = function(nItemId,sItemName)
	ServiceTask_MoveGold_SalaryPackage(nItemId)
end

tItem[3007006] = tItem[3007006] or {}
tItem[3007006]["Function"] = function(nItemId,sItemName)
	ServiceTask_MoveGold_SalaryPackage(nItemId)
end

tItem[3007007] = tItem[3007007] or {}
tItem[3007007]["Function"] = function(nItemId,sItemName)
	ServiceTask_MoveGold_SalaryPackage(nItemId)
end

tItem[3007435] = tItem[3007435] or {}
tItem[3007435]["Function"] = function(nItemId,sItemName)
	ServiceTask_MoveGold_SalaryPackage(nItemId)
end

tSystem_PlayLogin_Func = tSystem_PlayLogin_Func or {}
table.insert(tSystem_PlayLogin_Func,ServiceTask_MoveGold_GetSpeakerNum)