------------------------------------------------------------------------------------
--Name:			[简体征服][活动任务]春节跨服活动之帮派年兽争霸赛
--Purpose:		春节跨服活动之帮派年兽争霸赛
--Creator: 		丁晨
--Created:		2015/01/05
------------------------------------------------------------------------------------
--任务需求：
--玩家击杀国境服怪物，为所在帮派赢积分。
------------------------------------------------------------------------------------
--物品：
--727504 背包信
------------------------------------------------------------------------------------
--掩码说明
--task_detail 35002 data1 记录年兽数量 
--task_detail 35002 data2 记录金铃雄狮数量
--task_detail 35002 data3 记录杀人数量
--task_detail 35002 data4 记录总分
--task_detail 35002 data6 记录今日是否领取过
--task_detail 35005 data1 记录金铃雄狮泰斗
--task_detail 35005 data2 记录金元宝箱
--LOGid 12000015 帮派资金、节日礼包数量、一道真气、免费修炼次数
--LOGid 12000018 国境年兽怪数量
--LOGid 12000019 国境金铃雄狮怪数量
--LOGid 12000020 国境服击杀人数量
------------------------------------------------------------------------------------
--命名规范
--CrossFestivalTask_MonsterNian
------------------------------------------------------------------------------------
--NpcType 3539 3540 3541
------------------------------------------------------------------------------------

--TaskDetail掩码
local tCrossFestivalTask_MonsterNian_TaskDetail = {}
	tCrossFestivalTask_MonsterNian_TaskDetail["Task_Id"] = 35002
	tCrossFestivalTask_MonsterNian_TaskDetail["TaskAdd_Id"] = 35005
	--奖励配置 
local tCrossFestivalTask_MonsterNian_Reward = {}
	--时效护心丹
	tCrossFestivalTask_MonsterNian_Reward["RewardId"] = {}
	tCrossFestivalTask_MonsterNian_Reward["RewardId"]["ItemId"] =3002029
	tCrossFestivalTask_MonsterNian_Reward["RewardId"]["Addamount"] =1
	tCrossFestivalTask_MonsterNian_Reward["RewardId"]["Monopoly"] =0
	tCrossFestivalTask_MonsterNian_Reward["RewardId"]["Save_time"] =2880
	tCrossFestivalTask_MonsterNian_Reward["RewardId"]["Active"] = 1
	
	--真气上限
	tCrossFestivalTask_MonsterNian_Reward["MakiLimit"] = 5
	tCrossFestivalTask_MonsterNian_Reward["AddMaki"] = 1
	--免费修炼次数
	tCrossFestivalTask_MonsterNian_Reward["CultivateLimit"] = 1000000
	tCrossFestivalTask_MonsterNian_Reward["AddCult"] = 10000
	
	--通用节日礼包
	tCrossFestivalTask_MonsterNian_Reward["GiftBagId"] = 3376
	--帮派基础资金 
	tCrossFestivalTask_MonsterNian_Reward["FactionMoney"] = 200000000
	--节日奖励 数量
	tCrossFestivalTask_MonsterNian_Reward["PreheatRewardBagNum"] = 2
	--春节礼包加倍
	tCrossFestivalTask_MonsterNian_Reward["CrossoverBag"] = 2 
	
	--预热基金1倍
	tCrossFestivalTask_MonsterNian_Reward["FrontierCurrentMoney"] = 1
	--春节基金10倍
	tCrossFestivalTask_MonsterNian_Reward["FrontierMoney"] = 10 
	--领奖分数点超过分数点才能领取节日礼包
	tCrossFestivalTask_MonsterNian_Reward["ScoreLimit"] = 50 
	--杀人8积分
	tCrossFestivalTask_MonsterNian_Reward["ScoreKiller"] = 8 
	--杀小怪1积分
	tCrossFestivalTask_MonsterNian_Reward["ScoreKillMonster"] = 1 
	--击杀宝箱5积分
	tCrossFestivalTask_MonsterNian_Reward["ScoreKillMonsterBox"] = 5
	--击杀小BOSS
	tCrossFestivalTask_MonsterNian_Reward["ScoreKillMonsterBoss"] = 30
	--队员分享范围
	tCrossFestivalTask_MonsterNian_Reward["TeamRange"] = 2
	--领取奖励光效
	tCrossFestivalTask_MonsterNian_Reward["FactionEffect"] = "accession"
	tCrossFestivalTask_MonsterNian_Reward["PrivateEffect"] = "relive"
	--击杀怪物光效
	tCrossFestivalTask_MonsterNian_Reward["KillSmallEffect"] = "upnumeber1"
	tCrossFestivalTask_MonsterNian_Reward["KillGoldSmallEffect"] = "upnumeber5"
	tCrossFestivalTask_MonsterNian_Reward["KillManEffect"] = "upnumeber8"
	tCrossFestivalTask_MonsterNian_Reward["KillWolfEffectL"] = "upnumeber3"
	tCrossFestivalTask_MonsterNian_Reward["KillWolfEffectR"] = "upnumeberright0"
	
	--每日活动次数
	tCrossFestivalTask_MonsterNian_Reward["Activity_Num"] = 3
	
	--怪物出生光效
	tCrossFestivalTask_MonsterNian_Reward["BornEffect"] = "zf2-e300"
	tCrossFestivalTask_MonsterNian_Reward["KillBossEffect"] = "zf2-e123_1"
	--玩家等级限制
	tCrossFestivalTask_MonsterNian_Reward["LevelLimit"] = 70 
	tCrossFestivalTask_MonsterNian_Reward["Incarnation"] = 2
	
-- log表
local tCrossFestivalTask_MonsterNian_Log = {}
	--获得个人礼包或帮派资金
	tCrossFestivalTask_MonsterNian_Log["CompleteLog"] = "0,0,0,0,12000015,2,%s,%s"
	--年兽击杀
	tCrossFestivalTask_MonsterNian_Log["FactionKillLog"] = "0,0,0,0,12000018,3,7659,%s"
	--金铃雄狮击杀
	tCrossFestivalTask_MonsterNian_Log["CrossoverLog"] = "0,0,0,0,12000019,3,7684,%s"
	--杀人击杀
	tCrossFestivalTask_MonsterNian_Log["KillerLog"] = "0,0,0,0,12000020,3,0,%s"
	--杀金铃雄狮泰斗
	tCrossFestivalTask_MonsterNian_Log["KillWolfLog"] = "0,0,0,0,12000030,3,7680,%s"
	--金元宝箱
	tCrossFestivalTask_MonsterNian_Log["KillBoxLog"] = "0,0,0,0,12000031,3,7681,%s"
	--帮派资金20代号
	tCrossFestivalTask_MonsterNian_Log["FactionMoneyLog"] = 20
	
	tCrossFestivalTask_MonsterNian_Log["BagIdLog"] = 12000015
	
	tCrossFestivalTask_MonsterNian_Log["RewardBagId"] = 3003625
	
	tCrossFestivalTask_MonsterNian_Log["MakiLog"] = 16
	
	tCrossFestivalTask_MonsterNian_Log["CultivateLog"] = 17

--怪物信息
local tCrossFestivalTask_MonsterNian_Info = {}
	--国境服
	tCrossFestivalTask_MonsterNian_Info["MapId"] = 3898
	--行动范围 本服
	tCrossFestivalTask_MonsterNian_Info["GeneratorLeft"] = 17306
	tCrossFestivalTask_MonsterNian_Info["GeneratorRight"] = 17307
	--怪物ID
	tCrossFestivalTask_MonsterNian_Info["MonsterId"] = {}
	tCrossFestivalTask_MonsterNian_Info["MonsterId"][1] = 7659
	tCrossFestivalTask_MonsterNian_Info["MonsterId"][2] = 7660
	tCrossFestivalTask_MonsterNian_Info["MonsterId"][3] = 7680
	tCrossFestivalTask_MonsterNian_Info["MonsterId"][4] = 7681
	tCrossFestivalTask_MonsterNian_Info["MonsterId"][5] = 7684
	--怪物坐标
	tCrossFestivalTask_MonsterNian_Info["Monster_Position"] = {}
	--大怪坐标
	tCrossFestivalTask_MonsterNian_Info["Monster_Position"][7659] ={}
	tCrossFestivalTask_MonsterNian_Info["Monster_Position"][7659][1] ={}
	tCrossFestivalTask_MonsterNian_Info["Monster_Position"][7659][1]["PosX"] = 234 
	tCrossFestivalTask_MonsterNian_Info["Monster_Position"][7659][1]["PosY"] = 255
	
	tCrossFestivalTask_MonsterNian_Info["Monster_Position"][7659][2] ={}
	tCrossFestivalTask_MonsterNian_Info["Monster_Position"][7659][2]["PosX"] = 257 
	tCrossFestivalTask_MonsterNian_Info["Monster_Position"][7659][2]["PosY"] = 238

	--背包信 
	tCrossFestivalTask_MonsterNian_Info["BagLetter"] = 1
	tCrossFestivalTask_MonsterNian_Info["BagLetterId"] = 727504
	
	tCrossFestivalTask_MonsterNian_Info["MonsterBronLeft"]= "20:45 20:45"
	tCrossFestivalTask_MonsterNian_Info["MonsterBronRight"]= "21:30 21:30"
	
	--年兽NPC
local tCrossFestivalTask_MonsterNian_Npc ={}
	tCrossFestivalTask_MonsterNian_Npc["NpcId"] = 18262
	tCrossFestivalTask_MonsterNian_Npc["BronMapId"] = 3898
	tCrossFestivalTask_MonsterNian_Npc["BronPosX"] = 234
	tCrossFestivalTask_MonsterNian_Npc["BronPosY"] = 243
	
	tCrossFestivalTask_MonsterNian_Npc["DieMapId"] = 5000
	tCrossFestivalTask_MonsterNian_Npc["DiePosX"] = 57
	tCrossFestivalTask_MonsterNian_Npc["DiePosY"] = 80
--time表
local tCrossFestivalTask_MonsterNian_ActivityTime = {}
	--预热版本
	tCrossFestivalTask_MonsterNian_ActivityTime["Preheat_Now_Time"] = "2015-02-19 00:00 2015-02-25 23:59"
--引导NPC
local CrossFestivalTask_MonsterNian_Npc = {}
	CrossFestivalTask_MonsterNian_Npc["NpcId"]= 17280
	CrossFestivalTask_MonsterNian_Npc["MapId"]= 1002
	CrossFestivalTask_MonsterNian_Npc["PosX"] = 311
	CrossFestivalTask_MonsterNian_Npc["PosY"] = 283
--击杀怪物触发事件
function CrossFestivalTask_MonsterNian_HauntMonster(nMosterId)
	--本服玩家
	if not User_IsCross() then
		return 
	end
	
	--不在活动期间
	if  not Sys_ChkFullTime(tCrossFestivalTask_MonsterNian_ActivityTime["Preheat_Now_Time"]) then
		return 
	end
	
	local nIndex = 1
	if nMosterId == tCrossFestivalTask_MonsterNian_Info["MonsterId"][1] then
		
		--年兽
		nIndex = 1
	elseif nMosterId == tCrossFestivalTask_MonsterNian_Info["MonsterId"][5] then
		
		--金铃狮子
		nIndex = 2
	elseif nMosterId == tCrossFestivalTask_MonsterNian_Info["MonsterId"][3] then
		
		-- 大金铃狮子
		nIndex = 4
	else
	
		--金元宝箱
		nIndex = 5
	end
	CrossFestivalTask_MonsterNian_TeamEnjoy(nIndex)
end

	
--队员分享积分
function CrossFestivalTask_MonsterNian_TeamEnjoy(nIndex)
	local nTaskId = tCrossFestivalTask_MonsterNian_TaskDetail["Task_Id"]
	local nTaskAddId = tCrossFestivalTask_MonsterNian_TaskDetail["TaskAdd_Id"]
	if nIndex~= 1 then
		
		--检测任务掩码是否存在
		if not Task_ChkTaskDetail(nTaskId) then
			Task_AddTaskDetail(nTaskId)
		end
		
			--是否今日已领过 不做记录
		if  Task_ChkTaskDetailValue(nTaskId,"6",">=",tCrossFestivalTask_MonsterNian_Reward["Activity_Num"]) then
			return
		end
		
	end
	local nValue = 0
	local nScore = 0
	local nAddScore = 0
	
	--计数年兽数量
	if nIndex == 1  then
		nValue = Get_TaskDetailData1(nTaskId)
		nValue = nValue + 1
		Task_SetTaskDetailData1(nTaskId,nValue)
		User_TalkChannel2005(tCrossFestivalTask_MonsterNian_Text["BroadcastKillFinishNoFac"])
		User_EffectAdd("self",tCrossFestivalTask_MonsterNian_Reward["FactionEffect"])
		CrossFestivalTask_MonsterNian_EffectDel()
		User_EffectAdd("self",tCrossFestivalTask_MonsterNian_Reward["KillBossEffect"])
		
		--是否移出年兽NPC
		local nMapId = tCrossFestivalTask_MonsterNian_Info["MapId"]
		
		--获取怪物数量
		-- local nMonsterNum = Monster_GetMonsterByName(nMapId,tCrossFestivalTask_MonsterNian_Text["MonsterBoss"])
		local nMonsterId = Get_MonsterType()
		local nMonsterNum = Get_SysTempData(1,nMapId,nMonsterId)
		Sys_SetTempData(1,nMapId,nMonsterId,nMonsterNum-1)
		nMonsterNum =Get_SysTempData(1,nMapId,nMonsterId)
		if nMonsterNum == 0 then
			local nNpcId = tCrossFestivalTask_MonsterNian_Npc["NpcId"] 
			local nMapId = tCrossFestivalTask_MonsterNian_Npc["BronMapId"]
			local nPosX  =tCrossFestivalTask_MonsterNian_Npc["BronPosX"]
			local nPosY  =tCrossFestivalTask_MonsterNian_Npc["BronPosY"]
			Npc_MoveNpcPos(nNpcId,nMapId,nPosX,nPosY)
		end
		local sUserName = Get_UserName()
		Map_SendBroadcastMsg(tCrossFestivalTask_MonsterNian_Info["MapId"],string.format(tCrossFestivalTask_MonsterNian_Text["KillMaster"],sUserName))
		Sys_SaveActionFestivalLog(string.format(tCrossFestivalTask_MonsterNian_Log["FactionKillLog"],1))
		
	--击杀金铃雄狮数量
	elseif nIndex == 2 then
		nValue = Get_TaskDetailData2(nTaskId)
		nValue = nValue + 1
		Task_SetTaskDetailData2(nTaskId,nValue)
		User_TalkChannel2005(tCrossFestivalTask_MonsterNian_Text["BroadcastKillFinishBox"])
		User_EffectAdd("self",tCrossFestivalTask_MonsterNian_Reward["KillSmallEffect"])
		nAddScore = tCrossFestivalTask_MonsterNian_Reward["ScoreKillMonster"] 
		Sys_SaveActionFestivalLog(string.format(tCrossFestivalTask_MonsterNian_Log["CrossoverLog"],1))
		
	--击杀跨服玩家数量
	elseif nIndex == 3 then
		nValue = Get_TaskDetailData3(nTaskId)
		nValue = nValue + 1
		Task_SetTaskDetailData3(nTaskId,nValue)
		User_TalkChannel2005(tCrossFestivalTask_MonsterNian_Text["BroadcastKillFinishPlayer"])
		User_EffectAdd("self",tCrossFestivalTask_MonsterNian_Reward["KillManEffect"])
		User_EffectAdd("self",tCrossFestivalTask_MonsterNian_Reward["PrivateEffect"])
		nAddScore= tCrossFestivalTask_MonsterNian_Reward["ScoreKiller"] 
		Sys_SaveActionFestivalLog(string.format(tCrossFestivalTask_MonsterNian_Log["KillerLog"],1))
	
	--击杀金铃雄狮泰斗
	elseif nIndex == 4 then
		nValue = Get_TaskDetailData1(nTaskAddId)
		nValue = nValue + 1
		Task_SetTaskDetailData1(nTaskAddId,nValue)
		User_TalkChannel2005(tCrossFestivalTask_MonsterNian_Text["BroadcastKillFinishWolf"])
		User_EffectAdd("self",tCrossFestivalTask_MonsterNian_Reward["KillWolfEffectL"])
		User_EffectAdd("self",tCrossFestivalTask_MonsterNian_Reward["KillWolfEffectR"])
		nAddScore= tCrossFestivalTask_MonsterNian_Reward["ScoreKillMonsterBoss"] 
		local sUserName = Get_UserName()
		Map_SendBroadcastMsg(tCrossFestivalTask_MonsterNian_Info["MapId"],string.format(tCrossFestivalTask_MonsterNian_Text["KillSmallMaster"],sUserName))
		Sys_SaveActionFestivalLog(string.format(tCrossFestivalTask_MonsterNian_Log["KillWolfLog"],1))
		
	--击杀金元宝箱
	else
		nValue = Get_TaskDetailData2(nTaskAddId)
		nValue = nValue + 1
		Task_SetTaskDetailData2(nTaskAddId,nValue)
		User_TalkChannel2005(tCrossFestivalTask_MonsterNian_Text["BroadcastKillFinishGoldBox"])
		User_EffectAdd("self",tCrossFestivalTask_MonsterNian_Reward["KillGoldSmallEffect"])
		nAddScore= tCrossFestivalTask_MonsterNian_Reward["ScoreKillMonsterBox"] 
		Sys_SaveActionFestivalLog(string.format(tCrossFestivalTask_MonsterNian_Log["KillBoxLog"],1))
	end
	
	if nIndex~= 1 then
		nScore = Get_TaskDetailData4(nTaskId) + nAddScore
		Task_SetTaskDetailData4(nTaskId,nScore)
		
		if nScore >= tCrossFestivalTask_MonsterNian_Reward["ScoreLimit"] then
			User_TalkChannel2005(tCrossFestivalTask_MonsterNian_Text["RewardFive"])
		end
	end
end

--怪物提前2分钟广播
function CrossFestivalTask_MonsterNian_MosterBroadcast()
	if  Sys_ChkFullTime(tCrossFestivalTask_MonsterNian_ActivityTime["Preheat_Now_Time"]) then
		local sBroadcast = tCrossFestivalTask_MonsterNian_Text["BroadcastBef"]
		Sys_GmBroadcast(sBroadcast)
	end
end
	
--创建大怪物与广播
function CrossFestivalTask_MonsterNian_MosterBoss()
	if Sys_ChkFullTime(tCrossFestivalTask_MonsterNian_ActivityTime["Preheat_Now_Time"]) then
		local nGenerator = tCrossFestivalTask_MonsterNian_Info["GeneratorLeft"]
		local nMapId = tCrossFestivalTask_MonsterNian_Info["MapId"]
		local nBossId = tCrossFestivalTask_MonsterNian_Info["MonsterId"][1]
		local nPosX = tCrossFestivalTask_MonsterNian_Info["Monster_Position"][nBossId][1]["PosX"]
		local nPosY = tCrossFestivalTask_MonsterNian_Info["Monster_Position"][nBossId][1]["PosY"]
		if Sys_ChkDayTime(tCrossFestivalTask_MonsterNian_Info["MonsterBronLeft"]) then
			nPosX = tCrossFestivalTask_MonsterNian_Info["Monster_Position"][nBossId][1]["PosX"]
			nPosY = tCrossFestivalTask_MonsterNian_Info["Monster_Position"][nBossId][1]["PosY"]
			nGenerator = tCrossFestivalTask_MonsterNian_Info["GeneratorLeft"]
		else
			nPosX = tCrossFestivalTask_MonsterNian_Info["Monster_Position"][nBossId][2]["PosX"]
			nPosY = tCrossFestivalTask_MonsterNian_Info["Monster_Position"][nBossId][2]["PosY"]
			nGenerator = tCrossFestivalTask_MonsterNian_Info["GeneratorRight"]
		end
		
		--移除NPC年兽
		local nNpcId = tCrossFestivalTask_MonsterNian_Npc["NpcId"] 
		local nDieMapId = tCrossFestivalTask_MonsterNian_Npc["DieMapId"]
		local nDiePosX  =tCrossFestivalTask_MonsterNian_Npc["DiePosX"]
		local nDiePosY  =tCrossFestivalTask_MonsterNian_Npc["DiePosY"]
		Npc_MoveNpcPos(nNpcId,nDieMapId,nDiePosX,nDiePosY)

	
		local sBroadcast = tCrossFestivalTask_MonsterNian_Text["BroadcastKillExplain"]
		Monster_AddMonster(nMapId,nPosX,nPosY,nGenerator,nBossId)
		local nMonsterNum =Get_SysTempData(1,nMapId,nMonsterId)
		Sys_SetTempData(1,nMapId,nMonsterId,nMonsterNum+1)
		Sys_GmBroadcast(sBroadcast)
		
		
	end
end
--领取奖励
function CrossFestivalTask_MonsterNian_ChkGetReward(nNpcId,nIndex)
		
	local nChkNum = 0
	local nFactionMoney = 0
	
	--判断是否在活动期间
	if  not Sys_ChkFullTime(tCrossFestivalTask_MonsterNian_ActivityTime["Preheat_Now_Time"]) then
		LinkNpcGossipFunc_New(nNpcId,"200-4")
		return
	end
	
	--判断是否2转70级
	if not User_JudgeLevelAndMetempsychosis(tCrossFestivalTask_MonsterNian_Reward["LevelLimit"]
	,tCrossFestivalTask_MonsterNian_Reward["Incarnation"]) then
		LinkNpcGossipFunc_New(nNpcId,"200-11")
		return
	end
	
	--计算 礼包奖励数量，与帮派资金总数
	local tData = {}
	local nTaskId = tCrossFestivalTask_MonsterNian_TaskDetail["Task_Id"]
	local nData1Value = Get_TaskDetailData1(nTaskId)
	local nData2Value = Get_TaskDetailData2(nTaskId)
	local nData3Value = Get_TaskDetailData3(nTaskId)
	
	table.insert(tData,nData1Value)
	table.insert(tData,nData2Value)
	table.insert(tData,nData3Value)
	
	local nMoneyMultiple = tCrossFestivalTask_MonsterNian_Reward["FrontierCurrentMoney"]	
	
	--判断是否满足领奖条件
	if nIndex == 1 then
		local nNumber = tData[nIndex]
		local nGuildId = Get_UserGuildId()
		
		if nGuildId == 0 then
			LinkNpcGossipFunc_New(nNpcId,"200-5")
			return
		end
		
		--判断是否有击杀年兽
		if nNumber > 0 then
			nFactionMoney = nFactionMoney + tCrossFestivalTask_MonsterNian_Reward["FactionMoney"]*nMoneyMultiple*nNumber
		else
			LinkNpcGossipFunc_New(nNpcId,"200-8")
			return
		end
		
		--增加帮派资金
		User_ChgSynMoney(nGuildId,nFactionMoney)
		User_TalkChannel2005(string.format(tCrossFestivalTask_MonsterNian_Text["FactionMoney"],nFactionMoney))
		
		--领取奖励 帮派资金 
		Sys_SaveActionFestivalLog(string.format(tCrossFestivalTask_MonsterNian_Log["CompleteLog"],tCrossFestivalTask_MonsterNian_Log["FactionMoneyLog"],nFactionMoney))
		LinkNpcGossipFunc_New(nNpcId,"200-2")
		
		--清除年兽数量
		
		Task_SetTaskDetailData1(nTaskId,0)
		
		User_EffectAdd("self",tCrossFestivalTask_MonsterNian_Reward["FactionEffect"])
		local sFaction = Get_UserSynDicateName(nGuildId)
		local sPlayerName = Get_UserName()
		Sys_GmBroadcast(string.format(tCrossFestivalTask_MonsterNian_Text["GetRewards"],sPlayerName,sFaction))
	else

		--检测任务掩码是否存在
		if not Task_ChkTaskDetail(nTaskId) then
			Task_AddTaskDetail(nTaskId)
		end
		
		--是否今日已领过
		if  Task_ChkTaskDetailValue(nTaskId,"6",">=",tCrossFestivalTask_MonsterNian_Reward["Activity_Num"]) then
		
			--今日已领取过秒杀卷
			LinkNpcGossipFunc_New(nNpcId,"200-10")
			return
		end
	
		
		local nScore = Get_TaskDetailData4(nTaskId)
		
		--是否满足50积分 
		if nScore >=  tCrossFestivalTask_MonsterNian_Reward["ScoreLimit"] then
			nChkNum = tCrossFestivalTask_MonsterNian_Reward["PreheatRewardBagNum"] 
		else
			LinkNpcGossipFunc_New(nNpcId,"200-9")
			return
		end
		
		--检测背包空间 加入时效护心丹
		if not User_CheckLeftSpace(nChkNum+1) then 
		
			--背包满
			LinkNpcGossipFunc_New(nNpcId,"200-3")
			return
		end
		
		local nItemId = tCrossFestivalTask_MonsterNian_Reward["GiftBagId"]
		
		for i=1, nChkNum do
		
			--增加礼包
			FestivalGeneralPackage_GetGift(nItemId,tCrossFestivalTask_MonsterNian_Log["BagIdLog"])
		end
		
		User_EffectAdd("self",tCrossFestivalTask_MonsterNian_Reward["PrivateEffect"])
		Sys_SaveActionFestivalLog(string.format(tCrossFestivalTask_MonsterNian_Log["CompleteLog"],tCrossFestivalTask_MonsterNian_Log["RewardBagId"],nChkNum))
		
		local bGongFu = false
		local bCultivate =false
		--是否自创武功
		if User_IsAlreadyCreateGongFu(0) then
			local nMaki = Get_UserGongFuInt(G_GONGFU_ATTR_GENUINEQI_LV,0)
			
			if nMaki < tCrossFestivalTask_MonsterNian_Reward["MakiLimit"] then
			
				--增加一道真气
				User_AddGongFuInt(G_GONGFU_ATTR_GENUINEQI_LV,tCrossFestivalTask_MonsterNian_Reward["AddMaki"],0)
				
				Sys_SaveActionFestivalLog(string.format(tCrossFestivalTask_MonsterNian_Log["CompleteLog"],tCrossFestivalTask_MonsterNian_Log["MakiLog"],tCrossFestivalTask_MonsterNian_Reward["AddMaki"]))
				bGongFu = true
			end
		end
		
		--增加免费修炼次数
		local nCult = Get_UserGongFuInt(G_GONGFU_ATTR_FREE_CULTIVATE_PARAM,0)
		local nCultNum = tCrossFestivalTask_MonsterNian_Reward["CultivateLimit"]- tCrossFestivalTask_MonsterNian_Reward["AddCult"]
		if nCult <= nCultNum   then
		
			--增加一次免费修炼次数
			User_AddGongFuInt(G_GONGFU_ATTR_FREE_CULTIVATE_PARAM,tCrossFestivalTask_MonsterNian_Reward["AddCult"],0)
			Sys_SaveActionFestivalLog(string.format(tCrossFestivalTask_MonsterNian_Log["CompleteLog"],tCrossFestivalTask_MonsterNian_Log["CultivateLog"],tCrossFestivalTask_MonsterNian_Reward["AddCult"]))
			bCultivate=true
		end
		
		if bGongFu and bCultivate then
			LinkNpcGossipFunc_New(nNpcId,"300-1")
		end
		
		if bGongFu then
			LinkNpcGossipFunc_New(nNpcId,"300-2")
		end
		
		if bCultivate then
			LinkNpcGossipFunc_New(nNpcId,"300-3")
		end
		
		--增加时效护心丹
		Item_AddItem(tCrossFestivalTask_MonsterNian_Reward["RewardId"]["ItemId"],0,tCrossFestivalTask_MonsterNian_Reward["RewardId"]["Addamount"],tCrossFestivalTask_MonsterNian_Reward["RewardId"]["Monopoly"],tCrossFestivalTask_MonsterNian_Reward["RewardId"]["Save_time"],tCrossFestivalTask_MonsterNian_Reward["RewardId"]["Active"])
		Sys_SaveActionFestivalLog(string.format(tCrossFestivalTask_MonsterNian_Log["CompleteLog"],tCrossFestivalTask_MonsterNian_Reward["RewardId"]["ItemId"],tCrossFestivalTask_MonsterNian_Reward["RewardId"]["Addamount"]))
		
		
		local nData6 = Get_TaskDetailData6(nTaskId)
		nData6 = nData6 + 1
		--记录今日已领取
		Task_SetTaskDetailData6(nTaskId,nData6)
		
		--清除击杀金元宝箱数量
		
		Task_SetTaskDetailData2(nTaskId,0)
		
		--清除击杀跨服玩家数量
	
		Task_SetTaskDetailData3(nTaskId,0)
	
		--清除击杀金铃雄狮泰斗数量
		
		Task_SetTaskDetailData1(tCrossFestivalTask_MonsterNian_TaskDetail["TaskAdd_Id"],0)
		
		--清除击杀金元宝箱
		
		Task_SetTaskDetailData2(tCrossFestivalTask_MonsterNian_TaskDetail["TaskAdd_Id"],0)
		
		--清空分数
		Task_SetTaskDetailData4(nTaskId,0)
	end
end


--击杀其他玩家
function CrossFestivalTask_MonsterNian_PlayerKill(nPlayerId)
	--本服玩家
	if not User_IsCross() then
		return 
	end
	
		--不在活动期间
	if  not Sys_ChkFullTime(tCrossFestivalTask_MonsterNian_ActivityTime["Preheat_Now_Time"]) then
		return 
	end
	
	--击杀国境服玩家才算
	if Get_UserMapId()~= tCrossFestivalTask_MonsterNian_Info["MapId"] then
		return 
	end
	
	CrossFestivalTask_MonsterNian_TeamEnjoy(3)
	
end 

--查询积分
function CrossFestivalTask_MonsterNian_GetScore(nNpcId)
	local nScore = 0
	local nTaskId = tCrossFestivalTask_MonsterNian_TaskDetail["Task_Id"]
	
	local nScore = Get_TaskDetailData4(nTaskId)
	tCrossFestivalTask_MonsterNian_Text[17280]["Text132"] = string.format(tCrossFestivalTask_MonsterNian_Text[17280]["Text131"], nScore)
	tNpcGossip[17280]["Text2021"]= tCrossFestivalTask_MonsterNian_Text[17280]["Text132"]
	LinkNpcGossipFunc_New(nNpcId,"200-12")
end

--上线触发加入背包信
function CrossFestivalTask_MonsterNian_PlayLogin()
	
	if   Sys_ChkFullTime(tCrossFestivalTask_MonsterNian_ActivityTime["Preheat_Now_Time"]) then
	
		--检测背包空间
		if not User_CheckLeftSpace(tCrossFestivalTask_MonsterNian_Info["BagLetter"]) then 
		
			Sys_MsgBox(tCrossFestivalTask_MonsterNian_Text["BagLetterNoti"])
			return
		end
		
		--检测物品是否存在
		if not Item_ChkItem(tCrossFestivalTask_MonsterNian_Info["BagLetterId"]) then
			Item_AddItem(tCrossFestivalTask_MonsterNian_Info["BagLetterId"],0,tCrossFestivalTask_MonsterNian_Info["BagLetter"])
			User_TalkChannel2005(tCrossFestivalTask_MonsterNian_Text["BagLetterGetSucc"])
		end
	end
end

--引导NPC处
function CrossFestivalTask_MonsterNian_Letter()
	local nNpcId = CrossFestivalTask_MonsterNian_Npc["NpcId"]
	local nMapId = CrossFestivalTask_MonsterNian_Npc["MapId"]
	local nPosX = CrossFestivalTask_MonsterNian_Npc["PosX"]
	local nPosY = CrossFestivalTask_MonsterNian_Npc["PosY"]
	
	Sys_GotoSomeWhere(nPosX,nPosY,nMapId,nNpcId)
end

--背包信查看积分
function CrossFestivalTask_MonsterNian_Score(nItemId)
	
	local nTaskId = tCrossFestivalTask_MonsterNian_TaskDetail["Task_Id"]

	local nScore = Get_TaskDetailData4(nTaskId)
	
	tCrossFestivalTask_MonsterNian_Text["GetRewardsBagText"] = string.format(tCrossFestivalTask_MonsterNian_Text["GetRewardsBag"],nScore)
	tItem[727504]["Text511"] = tCrossFestivalTask_MonsterNian_Text["GetRewardsBagText"]
	
	
	LinkItemGossipFunc_New(nItemId,"1-4")
end

--去除光效
function CrossFestivalTask_MonsterNian_EffectDel()
	User_EffectDel("self",tCrossFestivalTask_MonsterNian_Reward["KillBossEffect"])
end

-- 背包信
tItem[727504] = tItem[727504] or {}
tItem[727504]["Text1-1"] = {111,112}
tItem[727504]["Text111"] = tCrossFestivalTask_MonsterNian_Text["BagLetter"] 
tItem[727504]["Text112"] = tCrossFestivalTask_MonsterNian_Text["BagLetterNext"] 
tItem[727504]["Option1"] = tCrossFestivalTask_MonsterNian_Text["Option14"]
tItem[727504]["Option2"] = tCrossFestivalTask_MonsterNian_Text["Option15"]
tItem[727504]["Option3"] = tCrossFestivalTask_MonsterNian_Text["Option16"]
tItem[727504]["Option7"] = tCrossFestivalTask_MonsterNian_Text["Option18"]
tItem[727504]["ChkFunc1-1"] = function ()  
	if  not Sys_ChkFullTime(tCrossFestivalTask_MonsterNian_ActivityTime["Preheat_Now_Time"]) then
		if Item_ChkItem(tCrossFestivalTask_MonsterNian_Info["BagLetterId"])  then
			Item_DelItem(tCrossFestivalTask_MonsterNian_Info["BagLetterId"])
		end
		return false
	end
	return true
end
tItem[727504]["tOption1-1"] = {1,7,2,3}
tItem[727504]["OptionFunc1"]="CrossFestivalTask_MonsterNian_Letter"
tItem[727504]["OptionFunc2"]="LinkItemGossipFunc_New</N>727504</S>1-2"
tItem[727504]["OptionFunc3"]="LinkItemGossipFunc_New</N>727504</S>1-3"
tItem[727504]["OptionFunc7"]="CrossFestivalTask_MonsterNian_Score</N>727504"

--了解跨服访使节
tItem[727504]["Text1-2"] = {211,212}
tItem[727504]["Text211"] = tCrossFestivalTask_MonsterNian_Text["BagLetterCross"]
tItem[727504]["Text212"] = tCrossFestivalTask_MonsterNian_Text["BagLetterCrossNext"]
tItem[727504]["Option4"] = tCrossFestivalTask_MonsterNian_Text["Option17"]
tItem[727504]["tOption1-2"] = {4}
tItem[727504]["ChkFunc1-2"] = function ()  
	if not Sys_ChkFullTime(tCrossFestivalTask_MonsterNian_ActivityTime["Preheat_Now_Time"]) then
		return false
	end
	return true
end

--了解异兽争霸赛
tItem[727504]["Text1-3"] = {311,312,313,314}
tItem[727504]["Text311"] = tCrossFestivalTask_MonsterNian_Text["BagLetterNianA"] 
tItem[727504]["Text312"] = tCrossFestivalTask_MonsterNian_Text["BagLetterNianB"] 
tItem[727504]["Text313"] = tCrossFestivalTask_MonsterNian_Text["BagLetterNianC"] 
tItem[727504]["Text314"] = tCrossFestivalTask_MonsterNian_Text["BagLetterNianD"] 
tItem[727504]["Option5"] = tCrossFestivalTask_MonsterNian_Text["Option17"]
tItem[727504]["tOption1-3"] = {5}
tItem[727504]["ChkFunc1-3"] = function ()  
	if  not Sys_ChkFullTime(tCrossFestivalTask_MonsterNian_ActivityTime["Preheat_Now_Time"]) then
		return false
	end
	return true
end

--查看积分
tItem[727504]["Text1-4"] = {511}
tItem[727504]["Text511"] = tCrossFestivalTask_MonsterNian_Text["GetRewardsBagText"]
tItem[727504]["Option8"] = tCrossFestivalTask_MonsterNian_Text["Option17"]
tItem[727504]["tOption1-4"] = {8}
tItem[727504]["ChkFunc1-4"] = function ()  
	if  not Sys_ChkFullTime(tCrossFestivalTask_MonsterNian_ActivityTime["Preheat_Now_Time"]) then
		return false
	end
	return true
end

--节日已过
tItem[727504]["Text1-5"] = {411}
tItem[727504]["Text411"] = tCrossFestivalTask_MonsterNian_Text["BeOverdue"] 
tItem[727504]["Option6"] = tCrossFestivalTask_MonsterNian_Text["Option17"]
tItem[727504]["tOption1-5"] = {6}



--怪物配置
-- //年兽
-- tMonster[7659] = tMonster[7659] or {}
-- tMonster[7659]["tFunction"] = tMonster[7659]["tFunction"] or {}
-- table.insert(tMonster[7659]["tFunction"],CrossFestivalTask_MonsterNian_HauntMonster)
-- //金铃雄狮
-- tMonster[7660] = tMonster[7660] or {}
-- tMonster[7660]["tFunction"] = tMonster[7660]["tFunction"] or {}
-- table.insert(tMonster[7660]["tFunction"],CrossFestivalTask_MonsterNian_HauntMonster)
-- //金铃雄狮泰斗
-- tMonster[7680] = tMonster[7680] or {}
-- tMonster[7680]["tFunction"] = tMonster[7680]["tFunction"] or {}
-- table.insert(tMonster[7680]["tFunction"],CrossFestivalTask_MonsterNian_HauntMonster)
-- //金元宝箱
-- tMonster[7681] = tMonster[7681] or {}
-- tMonster[7681]["tFunction"] = tMonster[7681]["tFunction"] or {}
-- table.insert(tMonster[7681]["tFunction"],CrossFestivalTask_MonsterNian_HauntMonster)

-- tMonster[7684] = tMonster[7684] or {}
-- tMonster[7684]["tFunction"] = tMonster[7684]["tFunction"] or {}
-- table.insert(tMonster[7684]["tFunction"],CrossFestivalTask_MonsterNian_HauntMonster)

--击杀玩家 下架脚本
-- tUserKilled["tFunction"] = tUserKilled["tFunction"] or {}
-- table.insert(tUserKilled["tFunction"],CrossFestivalTask_MonsterNian_PlayerKill)
--时间函数触发
--'20:00-22:00' 一共2个时间点触发怪物
-- tOntimerMin_HM[2045] = tOntimerMin_HM[2045] or {}
-- table.insert(tOntimerMin_HM[2045],CrossFestivalTask_MonsterNian_MosterBoss)
-- tOntimerMin_HM[2130] = tOntimerMin_HM[2130] or {}
-- table.insert(tOntimerMin_HM[2130],CrossFestivalTask_MonsterNian_MosterBoss)

--提前5分钟2个时间点广播(怪物出现的地点)
-- tOntimerMin_HM[2040] = tOntimerMin_HM[2040] or {}
-- table.insert(tOntimerMin_HM[2040],CrossFestivalTask_MonsterNian_MosterBroadcast)
-- tOntimerMin_HM[2125] = tOntimerMin_HM[2125] or {}
-- table.insert(tOntimerMin_HM[2125],CrossFestivalTask_MonsterNian_MosterBroadcast)
--上线触发
--table.insert(tSystem_PlayLogin_Func,CrossFestivalTask_MonsterNian_PlayLogin)
---------------------------------------NPC对白----------------------------------------------------
--报名参赛对白 
tNpcGossip[17280] = tNpcGossip[17280] or DefaultNpc:new{}

tNpcGossip[17280]["Text200-1"] = {2001,2002,2003,2010}
tNpcGossip[17280]["Text2001"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text111"]
tNpcGossip[17280]["Text2002"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text112"]
tNpcGossip[17280]["Text2003"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text113"]
tNpcGossip[17280]["Text2010"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text114"]

tNpcGossip[17280]["Option201"] = tCrossFestivalTask_MonsterNian_Text[17280]["Option1"]
tNpcGossip[17280]["Option212"] = tCrossFestivalTask_MonsterNian_Text[17280]["Option8"]
tNpcGossip[17280]["Option213"] = tCrossFestivalTask_MonsterNian_Text[17280]["Option10"]
tNpcGossip[17280]["Option202"] = tCrossFestivalTask_MonsterNian_Text[17280]["Option2"]
tNpcGossip[17280]["Option221"] = tCrossFestivalTask_MonsterNian_Text[17280]["Option13"]

tNpcGossip[17280]["tOption200-1"] = {201,212,221,213,202}

tNpcGossip[17280]["ChkFunc200-1"] = function ()
	return  Sys_ChkFullTime(tCrossFestivalTask_MonsterNian_ActivityTime["Preheat_Now_Time"])
end
tNpcGossip[17280]["OptionFunc201"]="LinkNpcGossipFunc_New</N>17280</S>200-7"
tNpcGossip[17280]["OptionFunc212"]="LinkNpcGossipFunc_New</N>17280</S>200-6"
tNpcGossip[17280]["OptionFunc221"]="CrossFestivalTask_MonsterNian_GetScore</N>17280"
tNpcGossip[17280]["OptionPoint213"]="1"
--领取成功对白
tNpcGossip[17280]["Text200-2"] = {2004,2005}
tNpcGossip[17280]["Text2004"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text115"]
tNpcGossip[17280]["Text2005"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text116"]
tNpcGossip[17280]["Option203"] = tCrossFestivalTask_MonsterNian_Text[17280]["Option3"]
tNpcGossip[17280]["tOption200-2"] = {203}

--背包已满
tNpcGossip[17280]["Text200-3"] = {2006}
tNpcGossip[17280]["Text2006"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text117"]
tNpcGossip[17280]["Option204"] = tCrossFestivalTask_MonsterNian_Text[17280]["Option4"]
tNpcGossip[17280]["tOption200-3"] = {204}

--不在活动期间
tNpcGossip[17280]["Text200-4"] = {2007}
tNpcGossip[17280]["Text2007"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text118"]
tNpcGossip[17280]["Option205"] = tCrossFestivalTask_MonsterNian_Text[17280]["Option5"]
tNpcGossip[17280]["tOption200-4"] = {205}

--没有帮派
tNpcGossip[17280]["Text200-5"] = {2009}
tNpcGossip[17280]["Text2009"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text120"]
tNpcGossip[17280]["Option206"] = tCrossFestivalTask_MonsterNian_Text[17280]["Option6"]
tNpcGossip[17280]["tOption200-5"] = {206}


--了解活动详情
tNpcGossip[17280]["Text200-6"] = {2011,2012,2013,2014}
tNpcGossip[17280]["Text2011"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text122"]
tNpcGossip[17280]["Text2012"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text123"]
tNpcGossip[17280]["Text2013"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text124"]
tNpcGossip[17280]["Text2014"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text125"]

tNpcGossip[17280]["Option210"] = tCrossFestivalTask_MonsterNian_Text[17280]["Option10"]
tNpcGossip[17280]["Option211"] = tCrossFestivalTask_MonsterNian_Text[17280]["Option2"]
tNpcGossip[17280]["Option333"] = tCrossFestivalTask_MonsterNian_Text[17280]["Option14"]
tNpcGossip[17280]["tOption200-6"] = {333,210,211}
tNpcGossip[17280]["OptionFunc210"]="LinkNpcGossipFunc_New</N>17280</S>200-1"
tNpcGossip[17280]["OptionFunc333"]="LinkNpcGossipFunc_New</N>17280</S>200-13"


--具体如何获得积分？
tNpcGossip[17280]["Text200-13"] = {2111,2112,2113}
tNpcGossip[17280]["Text2111"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text133"]
tNpcGossip[17280]["Text2112"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text134"]
tNpcGossip[17280]["Text2113"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text135"]
tNpcGossip[17280]["Option310"] = tCrossFestivalTask_MonsterNian_Text[17280]["Option10"]
tNpcGossip[17280]["Option311"] = tCrossFestivalTask_MonsterNian_Text[17280]["Option9"]
tNpcGossip[17280]["tOption200-13"] = {310,311}
tNpcGossip[17280]["OptionFunc310"]="LinkNpcGossipFunc_New</N>17280</S>200-6"

--选择领取奖励
tNpcGossip[17280]["Text200-7"] = {2015}
tNpcGossip[17280]["Text2015"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text121"]
tNpcGossip[17280]["Option217"] = tCrossFestivalTask_MonsterNian_Text[17280]["Option11"]
tNpcGossip[17280]["Option218"] = tCrossFestivalTask_MonsterNian_Text[17280]["Option12"]
tNpcGossip[17280]["tOption200-7"] = {217,218}
tNpcGossip[17280]["OptionFunc217"]="CrossFestivalTask_MonsterNian_ChkGetReward</N>17280</N>1"
tNpcGossip[17280]["OptionFunc218"]="CrossFestivalTask_MonsterNian_ChkGetReward</N>17280</N>2"

--未击杀年兽
tNpcGossip[17280]["Text200-8"] = {2017}
tNpcGossip[17280]["Text2017"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text127"]
tNpcGossip[17280]["Option214"] = tCrossFestivalTask_MonsterNian_Text[17280]["Option6"]
tNpcGossip[17280]["tOption200-8"] = {214}

--积分不足20积分
tNpcGossip[17280]["Text200-9"] = {2018}
tNpcGossip[17280]["Text2018"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text128"]
tNpcGossip[17280]["Option215"] = tCrossFestivalTask_MonsterNian_Text[17280]["Option6"]
tNpcGossip[17280]["tOption200-9"] = {215}

--今日已领取
tNpcGossip[17280]["Text200-10"] = {2019}
tNpcGossip[17280]["Text2019"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text129"]
tNpcGossip[17280]["Option216"] = tCrossFestivalTask_MonsterNian_Text[17280]["Option6"]
tNpcGossip[17280]["tOption200-10"] = {216}

--未达到等级条件
tNpcGossip[17280]["Text200-11"] = {2020}
tNpcGossip[17280]["Text2020"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text130"]
tNpcGossip[17280]["Option219"] = tCrossFestivalTask_MonsterNian_Text[17280]["Option2"]
tNpcGossip[17280]["tOption200-11"] = {219}

--积分查询
tNpcGossip[17280]["Text200-12"] = {2021}
tNpcGossip[17280]["Text2021"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text132"]
tNpcGossip[17280]["Option220"] = tCrossFestivalTask_MonsterNian_Text[17280]["Option6"]
tNpcGossip[17280]["tOption200-12"] = {220}

--一道真气，一次自创武功免费修炼次数，一颗护心丹和两份节日欢庆礼包。
tNpcGossip[17280]["Text300-1"] = {3001}
tNpcGossip[17280]["Text3001"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text1600"]
tNpcGossip[17280]["Option300"] = tCrossFestivalTask_MonsterNian_Text[17280]["Option3"]
tNpcGossip[17280]["tOption300-1"] = {300}

--自创武功免费修炼次数，一颗护心丹和两份节日欢庆礼包
tNpcGossip[17280]["Text300-2"] = {3002}
tNpcGossip[17280]["Text3002"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text1601"]
tNpcGossip[17280]["Option301"] = tCrossFestivalTask_MonsterNian_Text[17280]["Option3"]
tNpcGossip[17280]["tOption300-2"] = {301}

--一道真气，一颗护心丹和两份节日欢庆礼包。
tNpcGossip[17280]["Text300-3"] = {3003}
tNpcGossip[17280]["Text3003"] = tCrossFestivalTask_MonsterNian_Text[17280]["Text1602"]
tNpcGossip[17280]["Option302"] = tCrossFestivalTask_MonsterNian_Text[17280]["Option3"]
tNpcGossip[17280]["tOption300-3"] = {302}

--灯笼对白 
tNpcGossip[18018] = tNpcGossip[18018] or DefaultNpc:new{}
tNpcGossip[18018]["OptionHidden"] = 1
tNpcGossip[18018]["Text1-1"] = {2001}
tNpcGossip[18018]["Text2001"] = tCrossFestivalTask_MonsterNian_Text[18018]["Text111"]
tNpcGossip[18018]["Option201"] = tCrossFestivalTask_MonsterNian_Text[18018]["Option1"]
tNpcGossip[18018]["tOption1-1"] = {201}

tNpcGossip[18027] = tNpcGossip[18027] or DefaultNpc:new{}
tNpcGossip[18027]["OptionHidden"] = 1
tNpcGossip[18027]["Text1-1"] = {2001}
tNpcGossip[18027]["Text2001"] = tCrossFestivalTask_MonsterNian_Text[18018]["Text111"]
tNpcGossip[18027]["Option201"] = tCrossFestivalTask_MonsterNian_Text[18018]["Option1"]
tNpcGossip[18027]["tOption1-1"] = {201}

tNpcGossip[18061] = tNpcGossip[18061] or DefaultNpc:new{}
tNpcGossip[18061]["OptionHidden"] = 1
tNpcGossip[18061]["Text1-1"] = {2001}
tNpcGossip[18061]["Text2001"] = tCrossFestivalTask_MonsterNian_Text[18018]["Text111"]
tNpcGossip[18061]["Option201"] = tCrossFestivalTask_MonsterNian_Text[18018]["Option1"]
tNpcGossip[18061]["tOption1-1"] = {201}

tNpcGossip[18062] = tNpcGossip[18062] or DefaultNpc:new{}
tNpcGossip[18062]["OptionHidden"] = 1
tNpcGossip[18062]["Text1-1"] = {2001}
tNpcGossip[18062]["Text2001"] = tCrossFestivalTask_MonsterNian_Text[18018]["Text111"]
tNpcGossip[18062]["Option201"] = tCrossFestivalTask_MonsterNian_Text[18018]["Option1"]
tNpcGossip[18062]["tOption1-1"] = {201}

tNpcGossip[18063] = tNpcGossip[18063] or DefaultNpc:new{}
tNpcGossip[18063]["OptionHidden"] = 1
tNpcGossip[18063]["Text1-1"] = {2001}
tNpcGossip[18063]["Text2001"] = tCrossFestivalTask_MonsterNian_Text[18018]["Text111"]
tNpcGossip[18063]["Option201"] = tCrossFestivalTask_MonsterNian_Text[18018]["Option1"]
tNpcGossip[18063]["tOption1-1"] = {201}

tNpcGossip[18064] = tNpcGossip[18064] or DefaultNpc:new{}
tNpcGossip[18064]["OptionHidden"] = 1
tNpcGossip[18064]["Text1-1"] = {2001}
tNpcGossip[18064]["Text2001"] = tCrossFestivalTask_MonsterNian_Text[18018]["Text111"]
tNpcGossip[18064]["Option201"] = tCrossFestivalTask_MonsterNian_Text[18018]["Option1"]
tNpcGossip[18064]["tOption1-1"] = {201}

tNpcGossip[18065] = tNpcGossip[18065] or DefaultNpc:new{}
tNpcGossip[18065]["OptionHidden"] = 1
tNpcGossip[18065]["Text1-1"] = {2001}
tNpcGossip[18065]["Text2001"] = tCrossFestivalTask_MonsterNian_Text[18018]["Text111"]
tNpcGossip[18065]["Option201"] = tCrossFestivalTask_MonsterNian_Text[18018]["Option1"]
tNpcGossip[18065]["tOption1-1"] = {201}

tNpcGossip[18066] = tNpcGossip[18066] or DefaultNpc:new{}
tNpcGossip[18066]["OptionHidden"] = 1
tNpcGossip[18066]["Text1-1"] = {2001}
tNpcGossip[18066]["Text2001"] = tCrossFestivalTask_MonsterNian_Text[18018]["Text111"]
tNpcGossip[18066]["Option201"] = tCrossFestivalTask_MonsterNian_Text[18018]["Option1"]
tNpcGossip[18066]["tOption1-1"] = {201}


--年兽NPC
tNpcGossip[18262] = tNpcGossip[18262] or DefaultNpc:new{}
tNpcGossip[18262]["OptionHidden"] = 1
tNpcGossip[18262]["Text1-1"] = {2001}
tNpcGossip[18262]["Text2001"] = tCrossFestivalTask_MonsterNian_Text[18262]["Text111"]
tNpcGossip[18262]["Option201"] = tCrossFestivalTask_MonsterNian_Text[18262]["Option1"]
tNpcGossip[18262]["tOption1-1"] = {201}

--跨服守备NPC
tNpcGossip[18101] = tNpcGossip[18101] or DefaultNpc:new{}
tNpcGossip[18101]["OptionHidden"] = 1
tNpcGossip[18101]["Text1-1"] = {2001}
tNpcGossip[18101]["Text2001"] = tCrossFestivalTask_MonsterNian_Text[18101]["Text111"]
tNpcGossip[18101]["Option201"] = tCrossFestivalTask_MonsterNian_Text[18101]["Option1"]
tNpcGossip[18101]["tOption1-1"] = {201}

--跨服守备NPC
tNpcGossip[18122] = tNpcGossip[18122] or DefaultNpc:new{}
tNpcGossip[18122]["OptionHidden"] = 1
tNpcGossip[18122]["Text1-1"] = {2001}
tNpcGossip[18122]["Text2001"] = tCrossFestivalTask_MonsterNian_Text[18101]["Text111"]
tNpcGossip[18122]["Option201"] = tCrossFestivalTask_MonsterNian_Text[18101]["Option1"]
tNpcGossip[18122]["tOption1-1"] = {201}

--跨服守备NPC
tNpcGossip[18116] = tNpcGossip[18116] or DefaultNpc:new{}
tNpcGossip[18116]["OptionHidden"] = 1
tNpcGossip[18116]["Text1-1"] = {2001}
tNpcGossip[18116]["Text2001"] = tCrossFestivalTask_MonsterNian_Text[18101]["Text111"]
tNpcGossip[18116]["Option201"] = tCrossFestivalTask_MonsterNian_Text[18101]["Option1"]
tNpcGossip[18116]["tOption1-1"] = {201}

--跨服守备NPC
tNpcGossip[18128] = tNpcGossip[18128] or DefaultNpc:new{}
tNpcGossip[18128]["OptionHidden"] = 1
tNpcGossip[18128]["Text1-1"] = {2001}
tNpcGossip[18128]["Text2001"] = tCrossFestivalTask_MonsterNian_Text[18101]["Text111"]
tNpcGossip[18128]["Option201"] = tCrossFestivalTask_MonsterNian_Text[18101]["Option1"]
tNpcGossip[18128]["tOption1-1"] = {201}

--跨服守备NPC
tNpcGossip[18134] = tNpcGossip[18134] or DefaultNpc:new{}
tNpcGossip[18134]["OptionHidden"] = 1
tNpcGossip[18134]["Text1-1"] = {2001}
tNpcGossip[18134]["Text2001"] = tCrossFestivalTask_MonsterNian_Text[18101]["Text111"]
tNpcGossip[18134]["Option201"] = tCrossFestivalTask_MonsterNian_Text[18101]["Option1"]
tNpcGossip[18134]["tOption1-1"] = {201}




