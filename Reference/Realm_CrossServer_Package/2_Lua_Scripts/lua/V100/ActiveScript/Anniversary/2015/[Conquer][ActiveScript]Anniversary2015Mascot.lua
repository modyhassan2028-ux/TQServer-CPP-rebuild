------------------------------------------------------------------------------------
--Name:		[征服][活动脚本]周年吉祥物（4.27-5.11）
--Purpose:	调色大比拼
--Creator: 	严振飞
--Created:	2015/03/17
------------------------------------------------------------------------------------
--[[
任务需求：


]]--
------------------------------------------------------------------------------------
--掩码说明
--logid 10002169
--stc(122,52)	是否接受任务 0未接受 1已接受 2已完成
--stc(122,53)	是否已领取奖励 0未领取 1已领取
--stc(122,54)	袋子内是否有红狐 0没有 1有
--stc(122,55)	袋子内是否有粉兔 0没有 1有
--stc(122,56)	袋子内是否有银兔 0没有 1有
--stc(122,57)	袋子内是否有蓝狐 0没有 1有
--stc(122,58)	获得经验的次数 


--LOGid 10002169
------------------------------------------------------------------------------------
--命名规范
--Anniversary2015_Mascot_
------------------------------------------------------------------------------------
--STC掩码表
local tAnniversary2015_Mascot_Stc = {}
	--stc(122,52)	是否接受任务 0未接受 1已接受 2已完成
	tAnniversary2015_Mascot_Stc[1] = {}
	tAnniversary2015_Mascot_Stc[1]["Event"] = 122
	tAnniversary2015_Mascot_Stc[1]["Type"] = 52
	tAnniversary2015_Mascot_Stc[1]["Begin"] = 0
	tAnniversary2015_Mascot_Stc[1]["Accept"] = 1
	tAnniversary2015_Mascot_Stc[1]["Complete"] = 2
	
	--stc(122,53)	是否已领取奖励 0未领取 1已领取
	tAnniversary2015_Mascot_Stc[2] = {}
	tAnniversary2015_Mascot_Stc[2]["Event"] = 122
	tAnniversary2015_Mascot_Stc[2]["Type"] = 53
	tAnniversary2015_Mascot_Stc[2]["Begin"] = 0
	tAnniversary2015_Mascot_Stc[2]["Accept"] = 1
	tAnniversary2015_Mascot_Stc[2]["Complete"] = 2

	--stc(122,54)	袋子内是否有红狐 0没有 1有
	tAnniversary2015_Mascot_Stc[3] = {}
	tAnniversary2015_Mascot_Stc[3]["Event"] = 122
	tAnniversary2015_Mascot_Stc[3]["Type"] = 54
	tAnniversary2015_Mascot_Stc[3]["Begin"] = 0
	tAnniversary2015_Mascot_Stc[3]["Complete"] = 1

	--stc(122,55)	袋子内是否有粉兔 0没有 1有
	tAnniversary2015_Mascot_Stc[4] = {}
	tAnniversary2015_Mascot_Stc[4]["Event"] = 122
	tAnniversary2015_Mascot_Stc[4]["Type"] = 55
	tAnniversary2015_Mascot_Stc[4]["Begin"] = 0
	tAnniversary2015_Mascot_Stc[4]["Complete"] = 1
	
	--stc(122,56)	袋子内是否有银兔 0没有 1有
	tAnniversary2015_Mascot_Stc[5] = {}
	tAnniversary2015_Mascot_Stc[5]["Event"] = 122
	tAnniversary2015_Mascot_Stc[5]["Type"] = 56
	tAnniversary2015_Mascot_Stc[5]["Begin"] = 0
	tAnniversary2015_Mascot_Stc[5]["Complete"] = 1
	
	--stc(122,57)	袋子内是否有蓝狐 0没有 1有
	tAnniversary2015_Mascot_Stc[6] = {}
	tAnniversary2015_Mascot_Stc[6]["Event"] = 122
	tAnniversary2015_Mascot_Stc[6]["Type"] = 57
	tAnniversary2015_Mascot_Stc[6]["Begin"] = 0
	tAnniversary2015_Mascot_Stc[6]["Complete"] = 1

	--stc(122,58)	获得经验的次数 
	tAnniversary2015_Mascot_Stc[7] = {}
	tAnniversary2015_Mascot_Stc[7]["Event"] = 122
	tAnniversary2015_Mascot_Stc[7]["Type"] = 58
	tAnniversary2015_Mascot_Stc[7]["Begin"] = 0
	tAnniversary2015_Mascot_Stc[7]["Add"] = 1
	tAnniversary2015_Mascot_Stc[7]["Max"] = 6


--活动数据
local tAnniversary2015_Mascot_Data = {}
	--活动时间
	tAnniversary2015_Mascot_Data["Festival_BefTime"] = "2015-01-01 00:00 2015-05-06 23:59"
	tAnniversary2015_Mascot_Data["Festival_MidTime"] = "2015-05-07 00:00 2015-05-27 23:59"

	--等级限制
	tAnniversary2015_Mascot_Data["MinLevel"] = 80
	tAnniversary2015_Mascot_Data["MinMeto"] = 0
	
	--背包空间
	tAnniversary2015_Mascot_Data["ChkSpace"] = 1
	
	--宠物袋ID
	tAnniversary2015_Mascot_Data["PetBag"] = 3003514
	
	--判断宠物袋中是否有4种吉祥物（循环数据）
	tAnniversary2015_Mascot_Data["ForBegin"] = 3
	tAnniversary2015_Mascot_Data["ForEnd"] = 6
	
	--玩家转世
	tAnniversary2015_Mascot_Data["Meto_1"] = 1
	tAnniversary2015_Mascot_Data["Meto_2"] = 2
	
	--活动令牌数据
	tAnniversary2015_Mascot_Data["Pet"] = {}
	--	表示“祝”字
	tAnniversary2015_Mascot_Data["Pet"][16508] = 3003515
	tAnniversary2015_Mascot_Data["Pet"][16509] = 3003515
	tAnniversary2015_Mascot_Data["Pet"][16510] = 3003515
	tAnniversary2015_Mascot_Data["Pet"][16511] = 3003515

	--	表示“福”字
	tAnniversary2015_Mascot_Data["Pet"][16512] = 3003516
	tAnniversary2015_Mascot_Data["Pet"][16513] = 3003516
	tAnniversary2015_Mascot_Data["Pet"][16514] = 3003516
	tAnniversary2015_Mascot_Data["Pet"][16515] = 3003516

	--	表示“征”字
	tAnniversary2015_Mascot_Data["Pet"][16516] = 3003517
	tAnniversary2015_Mascot_Data["Pet"][16517] = 3003517
	tAnniversary2015_Mascot_Data["Pet"][16518] = 3003517
	tAnniversary2015_Mascot_Data["Pet"][16519] = 3003517

	--	表示“服”字
	tAnniversary2015_Mascot_Data["Pet"][16520] = 3003518
	tAnniversary2015_Mascot_Data["Pet"][16521] = 3003518
	tAnniversary2015_Mascot_Data["Pet"][16522] = 3003518
	tAnniversary2015_Mascot_Data["Pet"][16523] = 3003518

	
	--光效数据
	tAnniversary2015_Mascot_Data["EffectObj"] = "self"
	tAnniversary2015_Mascot_Data["Effect1"] = "zf2-e300"
	tAnniversary2015_Mascot_Data["Effect2"] = "CircleUp"
	--寄存器数据
	--tAnniversary2015_Mascot_Data["VarDataInx2"] = 2
	tAnniversary2015_Mascot_Data["VarStrInx3"] = 3
	
	--宠物满数量
	tAnniversary2015_Mascot_Data["PetMax"] = 4
	
	--移动宠物数据
	tAnniversary2015_Mascot_Data["CampMapId"] = 5000
	tAnniversary2015_Mascot_Data["CampMapPosX"] = 50
	tAnniversary2015_Mascot_Data["CampMapPosY"] = 50

	--倒计时时间
	tAnniversary2015_Mascot_Data["DelayTime"] = 20
	
	--满级
	tAnniversary2015_Mascot_Data["MaxLev"] = 140
	
	--增加的经验数据
	tAnniversary2015_Mascot_Data["AddExpTime"] = 10
	
--移动宠物NPC数据
local tAnniversary2015_Mascot_MoveNpc = {}
	tAnniversary2015_Mascot_MoveNpc["MapId"] = 1002
	tAnniversary2015_Mascot_MoveNpc[16508] = {}
	tAnniversary2015_Mascot_MoveNpc[16508]["PosX"] = 299
	tAnniversary2015_Mascot_MoveNpc[16508]["PosY"] = 347
	
	tAnniversary2015_Mascot_MoveNpc[16509] = {}
	tAnniversary2015_Mascot_MoveNpc[16509]["PosX"] = 279
	tAnniversary2015_Mascot_MoveNpc[16509]["PosY"] = 336

	tAnniversary2015_Mascot_MoveNpc[16510] = {}
	tAnniversary2015_Mascot_MoveNpc[16510]["PosX"] = 260
	tAnniversary2015_Mascot_MoveNpc[16510]["PosY"] = 380
	
	tAnniversary2015_Mascot_MoveNpc[16511] = {}
	tAnniversary2015_Mascot_MoveNpc[16511]["PosX"] = 328
	tAnniversary2015_Mascot_MoveNpc[16511]["PosY"] = 366

	tAnniversary2015_Mascot_MoveNpc[16512] = {}
	tAnniversary2015_Mascot_MoveNpc[16512]["PosX"] = 315
	tAnniversary2015_Mascot_MoveNpc[16512]["PosY"] = 385

	tAnniversary2015_Mascot_MoveNpc[16513] = {}
	tAnniversary2015_Mascot_MoveNpc[16513]["PosX"] = 298
	tAnniversary2015_Mascot_MoveNpc[16513]["PosY"] = 335

	tAnniversary2015_Mascot_MoveNpc[16514] = {}
	tAnniversary2015_Mascot_MoveNpc[16514]["PosX"] = 262
	tAnniversary2015_Mascot_MoveNpc[16514]["PosY"] = 337

	tAnniversary2015_Mascot_MoveNpc[16515] = {}
	tAnniversary2015_Mascot_MoveNpc[16515]["PosX"] = 251
	tAnniversary2015_Mascot_MoveNpc[16515]["PosY"] = 255

	tAnniversary2015_Mascot_MoveNpc[16516] = {}
	tAnniversary2015_Mascot_MoveNpc[16516]["PosX"] = 273
	tAnniversary2015_Mascot_MoveNpc[16516]["PosY"] = 399

	tAnniversary2015_Mascot_MoveNpc[16517] = {}
	tAnniversary2015_Mascot_MoveNpc[16517]["PosX"] = 320
	tAnniversary2015_Mascot_MoveNpc[16517]["PosY"] = 397

	tAnniversary2015_Mascot_MoveNpc[16518] = {}
	tAnniversary2015_Mascot_MoveNpc[16518]["PosX"] = 333
	tAnniversary2015_Mascot_MoveNpc[16518]["PosY"] = 371

	tAnniversary2015_Mascot_MoveNpc[16519] = {}
	tAnniversary2015_Mascot_MoveNpc[16519]["PosX"] = 332
	tAnniversary2015_Mascot_MoveNpc[16519]["PosY"] = 342

	tAnniversary2015_Mascot_MoveNpc[16520] = {}
	tAnniversary2015_Mascot_MoveNpc[16520]["PosX"] = 259
	tAnniversary2015_Mascot_MoveNpc[16520]["PosY"] = 321

	tAnniversary2015_Mascot_MoveNpc[16521] = {}
	tAnniversary2015_Mascot_MoveNpc[16521]["PosX"] = 336
	tAnniversary2015_Mascot_MoveNpc[16521]["PosY"] = 405

	tAnniversary2015_Mascot_MoveNpc[16522] = {}
	tAnniversary2015_Mascot_MoveNpc[16522]["PosX"] = 342
	tAnniversary2015_Mascot_MoveNpc[16522]["PosY"] = 352

	tAnniversary2015_Mascot_MoveNpc[16523] = {}
	tAnniversary2015_Mascot_MoveNpc[16523]["PosX"] = 260
	tAnniversary2015_Mascot_MoveNpc[16523]["PosY"] = 348
	
	--系统自检移动
	tAnniversary2015_Mascot_MoveNpc["ForBegin"] = 16508
	tAnniversary2015_Mascot_MoveNpc["ForEnd"] = 16523
	
	
--自动寻路数据
local tAnniversary2015_Mascot_FindNpc = {}
	tAnniversary2015_Mascot_FindNpc["NpcId"] = 16507
	tAnniversary2015_Mascot_FindNpc["MapId"] = 1002
	tAnniversary2015_Mascot_FindNpc["PosX"] = 287
	tAnniversary2015_Mascot_FindNpc["PosY"] = 385


--眩晕状态数据
local tAnniversary2015_Mascot_Status = {}
	tAnniversary2015_Mascot_Status["Status"] = 55
	tAnniversary2015_Mascot_Status["Power"] = 200
	tAnniversary2015_Mascot_Status["Secs"] = 5
	tAnniversary2015_Mascot_Status["Times"] = 1
	tAnniversary2015_Mascot_Status["RemainTime"] = 5
	tAnniversary2015_Mascot_Status["EndTime"] = 1
	tAnniversary2015_Mascot_Status["Recordable"] = 1


--LOG数据
local tAnniversary2015_Mascot_Log = {}
	--节日礼包
	tAnniversary2015_Mascot_Log["FestivalId"] = 3404
	tAnniversary2015_Mascot_Log["LogId"] = 10002169
	--获得宠物袋+删除宠物袋
	tAnniversary2015_Mascot_Log["GetPetBag"] = "0,0,0,0,10002169,2,3003514,1"
	tAnniversary2015_Mascot_Log["DelPetBag"] = "0,0,3003514,1,10002169,1,0,0"
	--获得经验
	tAnniversary2015_Mascot_Log["AddExpTime"] = "0,0,0,0,10002169,2,4,10"
	--删除令牌
	tAnniversary2015_Mascot_Log["DelToken"] = "0,0,%s,1,10002169,1,0,0"
	--获得节日礼包
	tAnniversary2015_Mascot_Log["AwardPackage"] = "0,0,%s,1,10002169,2,3003625,1"


--几率配置表
local tAnniversary2015_Mascot_Probabil = {}
	--讨好宠物成功概率
	tAnniversary2015_Mascot_Probabil[1] = {}
	tAnniversary2015_Mascot_Probabil[1][1] = {}
	tAnniversary2015_Mascot_Probabil[1][1]["ItemChanceSum"] = 100
	
	tAnniversary2015_Mascot_Probabil[1][1][1] = {}
	tAnniversary2015_Mascot_Probabil[1][1][1]["RandomItemChanceType"] = 2
	tAnniversary2015_Mascot_Probabil[1][1][1]["ItemChance"] = 30
	tAnniversary2015_Mascot_Probabil[1][1][1]["Item_1"] = true

	tAnniversary2015_Mascot_Probabil[1][1][2] = {}
	tAnniversary2015_Mascot_Probabil[1][1][2]["RandomItemChanceType"] = 2
	tAnniversary2015_Mascot_Probabil[1][1][2]["ItemChance"] = 70
	tAnniversary2015_Mascot_Probabil[1][1][2]["Item_1"] = false

	--怪物触发成功概率
	tAnniversary2015_Mascot_Probabil[2] = {}
	tAnniversary2015_Mascot_Probabil[2][1] = {}
	tAnniversary2015_Mascot_Probabil[2][1]["ItemChanceSum"] = 100
	
	tAnniversary2015_Mascot_Probabil[2][1][1] = {}
	tAnniversary2015_Mascot_Probabil[2][1][1]["RandomItemChanceType"] = 2
	tAnniversary2015_Mascot_Probabil[2][1][1]["ItemChance"] = 10
	tAnniversary2015_Mascot_Probabil[2][1][1]["Item_1"] = true

	tAnniversary2015_Mascot_Probabil[2][1][2] = {}
	tAnniversary2015_Mascot_Probabil[2][1][2]["RandomItemChanceType"] = 2
	tAnniversary2015_Mascot_Probabil[2][1][2]["ItemChance"] = 90
	tAnniversary2015_Mascot_Probabil[2][1][2]["Item_1"] = false
	
	--怪物成功出发后概率
	tAnniversary2015_Mascot_Probabil[3] = {}
	tAnniversary2015_Mascot_Probabil[3][1] = {}
	tAnniversary2015_Mascot_Probabil[3][1]["ItemChanceSum"] = 100
	
	tAnniversary2015_Mascot_Probabil[3][1][1] = {}
	tAnniversary2015_Mascot_Probabil[3][1][1]["RandomItemChanceType"] = 2
	tAnniversary2015_Mascot_Probabil[3][1][1]["ItemChance"] = 25
	tAnniversary2015_Mascot_Probabil[3][1][1]["Item_1"] = 3003515

	tAnniversary2015_Mascot_Probabil[3][1][2] = {}
	tAnniversary2015_Mascot_Probabil[3][1][2]["RandomItemChanceType"] = 2
	tAnniversary2015_Mascot_Probabil[3][1][2]["ItemChance"] = 25
	tAnniversary2015_Mascot_Probabil[3][1][2]["Item_1"] = 3003516

	tAnniversary2015_Mascot_Probabil[3][1][3] = {}
	tAnniversary2015_Mascot_Probabil[3][1][3]["RandomItemChanceType"] = 2
	tAnniversary2015_Mascot_Probabil[3][1][3]["ItemChance"] = 25
	tAnniversary2015_Mascot_Probabil[3][1][3]["Item_1"] = 3003517

	tAnniversary2015_Mascot_Probabil[3][1][4] = {}
	tAnniversary2015_Mascot_Probabil[3][1][4]["RandomItemChanceType"] = 2
	tAnniversary2015_Mascot_Probabil[3][1][4]["ItemChance"] = 25
	tAnniversary2015_Mascot_Probabil[3][1][4]["Item_1"] = 3003518

	

------------------------------------------逻辑部分-------------------------------------------
--移动宠物NPC
function Anniversary2015_Mascot_MoveNpcFunC()
	
	for nNpcId = tAnniversary2015_Mascot_MoveNpc["ForBegin"],tAnniversary2015_Mascot_MoveNpc["ForEnd"] do
		local nMapId = tAnniversary2015_Mascot_MoveNpc["MapId"]
		local nPosX = tAnniversary2015_Mascot_MoveNpc[nNpcId]["PosX"]
		local nPosY = tAnniversary2015_Mascot_MoveNpc[nNpcId]["PosY"]
		Npc_MoveNpcPos(nNpcId,nMapId,nPosX,nPosY)
	end
end



---【我要帮你。】
function Anniversary2015_Mascot_JoinFestival(nNpcId)
	--活动时间判断
	if not Sys_ChkFullTime(tAnniversary2015_Mascot_Data["Festival_MidTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end

	--玩家等级判断
	if not User_JudgeLevelAndMetempsychosis(tAnniversary2015_Mascot_Data["MinLevel"],tAnniversary2015_Mascot_Data["MinMeto"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	--是否有宠物袋
	if not Item_ChkItem(tAnniversary2015_Mascot_Data["PetBag"]) then
		
		--判断背包空间
		if not User_CheckLeftSpace(tAnniversary2015_Mascot_Data["ChkSpace"]) then
			LinkNpcGossipFunc_New(nNpcId,"2-3")
			return
		end
		
		--成功接收任务
		Task_SetStatistic(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],tAnniversary2015_Mascot_Stc[1]["Accept"],1)
		Task_SetStcTimestamp(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],0)
		--重置袋中的吉祥物
		Task_SetStatistic(tAnniversary2015_Mascot_Stc[3]["Event"],tAnniversary2015_Mascot_Stc[3]["Type"],tAnniversary2015_Mascot_Stc[1]["Begin"],1)
		Task_SetStatistic(tAnniversary2015_Mascot_Stc[4]["Event"],tAnniversary2015_Mascot_Stc[4]["Type"],tAnniversary2015_Mascot_Stc[1]["Begin"],1)
		Task_SetStatistic(tAnniversary2015_Mascot_Stc[5]["Event"],tAnniversary2015_Mascot_Stc[5]["Type"],tAnniversary2015_Mascot_Stc[1]["Begin"],1)
		Task_SetStatistic(tAnniversary2015_Mascot_Stc[6]["Event"],tAnniversary2015_Mascot_Stc[6]["Type"],tAnniversary2015_Mascot_Stc[1]["Begin"],1)
		--给袋子
		Item_AddItem(tAnniversary2015_Mascot_Data["PetBag"])
		Sys_SaveActionFestivalLog(tAnniversary2015_Mascot_Log["GetPetBag"])
	else
		--已经有宠物袋
		Task_SetStatistic(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],tAnniversary2015_Mascot_Stc[1]["Accept"],1)
		Task_SetStcTimestamp(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],0)
	end
	
	--成功领取任务对白
	LinkNpcGossipFunc_New(nNpcId,"2-2")
end



---【补领吉祥宠物袋】
function Anniversary2015_Mascot_RewardPetBag(nNpcId)
	--活动时间判断
	if not Sys_ChkFullTime(tAnniversary2015_Mascot_Data["Festival_MidTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end

	--判断任务掩码是否为0
	if Task_ChkStcValue(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],"==",tAnniversary2015_Mascot_Stc[1]["Begin"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	--是否隔天
	if Task_StcInterval(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],1,4) then
		Task_SetStatistic(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],0,1)
		Task_SetStcTimestamp(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],0)
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end 
	
	--判断是否已接受任务
	if not Task_ChkStcValue(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],"==",tAnniversary2015_Mascot_Stc[1]["Accept"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	--是否有宠物袋
	if Item_ChkItem(tAnniversary2015_Mascot_Data["PetBag"]) then
		Sys_MsgBox(tAnniversary2015_Mascot_Text["HavePetBag"])
		return
	end
	
	--背包空间
	if not User_CheckLeftSpace(tAnniversary2015_Mascot_Data["ChkSpace"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end
	
	--重置袋中的吉祥物
	Task_SetStatistic(tAnniversary2015_Mascot_Stc[3]["Event"],tAnniversary2015_Mascot_Stc[3]["Type"],tAnniversary2015_Mascot_Stc[3]["Begin"],1)
	Task_SetStatistic(tAnniversary2015_Mascot_Stc[4]["Event"],tAnniversary2015_Mascot_Stc[4]["Type"],tAnniversary2015_Mascot_Stc[4]["Begin"],1)
	Task_SetStatistic(tAnniversary2015_Mascot_Stc[5]["Event"],tAnniversary2015_Mascot_Stc[5]["Type"],tAnniversary2015_Mascot_Stc[5]["Begin"],1)
	Task_SetStatistic(tAnniversary2015_Mascot_Stc[6]["Event"],tAnniversary2015_Mascot_Stc[6]["Type"],tAnniversary2015_Mascot_Stc[6]["Begin"],1)
	--给袋子
	Item_AddItem(tAnniversary2015_Mascot_Data["PetBag"])
	Sys_SaveActionFestivalLog(tAnniversary2015_Mascot_Log["GetPetBag"])
	Sys_MsgBox(tAnniversary2015_Mascot_Text["RewardSuccess"])
end



--【喏，给您吉祥四宝。】
function Anniversary2015_Mascot_GiveItem(nNpcId)
	--活动时间判断
	if not Sys_ChkFullTime(tAnniversary2015_Mascot_Data["Festival_MidTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end

	--判断任务掩码是否为0
	if Task_ChkStcValue(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],"==",tAnniversary2015_Mascot_Stc[1]["Begin"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end

	--是否隔天
	if Task_StcInterval(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],1,4) then
		Task_SetStatistic(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],0,1)
		Task_SetStcTimestamp(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],0)
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end

	--判断是否已完成任务
	if not Task_ChkStcValue(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],"==",tAnniversary2015_Mascot_Stc[1]["Accept"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end

	--是否领取奖励
	if not Task_ChkStcValue(tAnniversary2015_Mascot_Stc[2]["Event"],tAnniversary2015_Mascot_Stc[2]["Type"],"==",tAnniversary2015_Mascot_Stc[2]["Begin"]) then
		
		--是否隔天
		if Task_StcInterval(tAnniversary2015_Mascot_Stc[2]["Event"],tAnniversary2015_Mascot_Stc[2]["Type"],1,4) then
			Task_SetStatistic(tAnniversary2015_Mascot_Stc[2]["Event"],tAnniversary2015_Mascot_Stc[2]["Type"],0,1)
			Task_SetStcTimestamp(tAnniversary2015_Mascot_Stc[2]["Event"],tAnniversary2015_Mascot_Stc[2]["Type"],0)
		else
			--已领奖出对白
			LinkNpcGossipFunc_New(nNpcId,"3-1")
			return
		end
	end 

	--是否有宠物袋
	if not Item_ChkItem(tAnniversary2015_Mascot_Data["PetBag"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end

	--判断宠物袋中是否有4种吉祥物
	local nBegin = tAnniversary2015_Mascot_Data["ForBegin"]
	local nEnd = tAnniversary2015_Mascot_Data["ForEnd"]
	for nStcNum = nBegin,nEnd do
		if Task_ChkStcValue(tAnniversary2015_Mascot_Stc[nStcNum]["Event"],tAnniversary2015_Mascot_Stc[nStcNum]["Type"],"==",tAnniversary2015_Mascot_Stc[nStcNum]["Begin"]) then
			LinkNpcGossipFunc_New(nNpcId,"3-2")
			return
			
			--是否隔天
		elseif Task_StcInterval(tAnniversary2015_Mascot_Stc[nStcNum]["Event"],tAnniversary2015_Mascot_Stc[nStcNum]["Type"],1,4) then
			Task_SetStatistic(tAnniversary2015_Mascot_Stc[nStcNum]["Event"],tAnniversary2015_Mascot_Stc[nStcNum]["Type"],0,1)
			Task_SetStcTimestamp(tAnniversary2015_Mascot_Stc[nStcNum]["Event"],tAnniversary2015_Mascot_Stc[nStcNum]["Type"],0)
			LinkNpcGossipFunc_New(nNpcId,"3-2")
			return
		end
	end

	--重置袋中的吉祥物
	Task_SetStatistic(tAnniversary2015_Mascot_Stc[3]["Event"],tAnniversary2015_Mascot_Stc[3]["Type"],tAnniversary2015_Mascot_Stc[3]["Begin"],1)
	Task_SetStatistic(tAnniversary2015_Mascot_Stc[4]["Event"],tAnniversary2015_Mascot_Stc[4]["Type"],tAnniversary2015_Mascot_Stc[4]["Begin"],1)
	Task_SetStatistic(tAnniversary2015_Mascot_Stc[5]["Event"],tAnniversary2015_Mascot_Stc[5]["Type"],tAnniversary2015_Mascot_Stc[5]["Begin"],1)
	Task_SetStatistic(tAnniversary2015_Mascot_Stc[6]["Event"],tAnniversary2015_Mascot_Stc[6]["Type"],tAnniversary2015_Mascot_Stc[6]["Begin"],1)

	--删除宠物袋
	if Item_ChkItem(tAnniversary2015_Mascot_Data["PetBag"]) then
		Item_DelItem(tAnniversary2015_Mascot_Data["PetBag"])
	end

	--置掩码
	Task_SetStatistic(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],tAnniversary2015_Mascot_Stc[1]["Complete"],1)
	Task_SetStatistic(tAnniversary2015_Mascot_Stc[2]["Event"],tAnniversary2015_Mascot_Stc[2]["Type"],tAnniversary2015_Mascot_Stc[2]["Complete"],1)
	Task_SetStcTimestamp(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],0)
	Task_SetStcTimestamp(tAnniversary2015_Mascot_Stc[2]["Event"],tAnniversary2015_Mascot_Stc[2]["Type"],0)

	--给奖励+打LOG+播光效+出对白
	local sLog_GiveColor = string.format(tAnniversary2015_Mascot_Log["AwardPackage"],tAnniversary2015_Mascot_Data["PetBag"])
	FestivalGeneralPackage_GetGift(tAnniversary2015_Mascot_Log["FestivalId"],tAnniversary2015_Mascot_Log["LogId"])
	Sys_SaveActionFestivalLog(sLog_GiveColor)
	User_EffectAdd(tAnniversary2015_Mascot_Data["EffectObj"],tAnniversary2015_Mascot_Data["Effect1"])
	LinkNpcGossipFunc_New(nNpcId,"3-3")
end


--【我该怎么帮您噜？】
function Anniversary2015_Mascot_Introduction(nNpcId)
	--活动时间判断
	if not Sys_ChkFullTime(tAnniversary2015_Mascot_Data["Festival_MidTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end

	LinkNpcGossipFunc_New(nNpcId,"4-1")
end

--【什么令牌用于吸引什么吉祥物？】
function Anniversary2015_Mascot_MascotRule(nNpcId)
	--活动时间判断
	if not Sys_ChkFullTime(tAnniversary2015_Mascot_Data["Festival_MidTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end
	
	LinkNpcGossipFunc_New(nNpcId,"5-1")
end



--宠物NPC移回活动场地
function Anniversary2015_Mascot_MoveBackPet(nNpcId)
	--移动NPC回活动场地
	local nMapId = tAnniversary2015_Mascot_MoveNpc["MapId"]
	local nPosX = tAnniversary2015_Mascot_MoveNpc[nNpcId]["PosX"]
	local nPosY = tAnniversary2015_Mascot_MoveNpc[nNpcId]["PosY"]
	
	Npc_MoveNpcPos(nNpcId,nMapId,nPosX,nPosY)
end



--【送您令牌勾引您。】
function Anniversary2015_Mascot_GiveToken(nStcId)
	local nNpcId = Get_NpcId()
	
	--活动时间判断
	if not Sys_ChkFullTime(tAnniversary2015_Mascot_Data["Festival_MidTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-1")
		return
	end
	
	--判断任务掩码是否为0
	if Task_ChkStcValue(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],"==",tAnniversary2015_Mascot_Stc[1]["Begin"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-1")
		return
	end

	--是否隔天
	if Task_StcInterval(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],1,4) then
		Task_SetStatistic(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],0,1)
		Task_SetStcTimestamp(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],0)
		LinkNpcGossipFunc_New(nNpcId,"1-1")
		return
	end

	--是否有宠物袋
	if not Item_ChkItem(tAnniversary2015_Mascot_Data["PetBag"]) then
		LinkNpcGossipFunc_New(16508,"1-2")
		return
	end
	
	--判断袋子内是否有红狐
	if not Task_ChkStcValue(tAnniversary2015_Mascot_Stc[nStcId]["Event"],tAnniversary2015_Mascot_Stc[nStcId]["Type"],"==",tAnniversary2015_Mascot_Stc[nStcId]["Begin"]) then
		
		--是否隔天
		if not Task_StcInterval(tAnniversary2015_Mascot_Stc[nStcId]["Event"],tAnniversary2015_Mascot_Stc[nStcId]["Type"],1,4) then
			Sys_MsgBox(tAnniversary2015_Mascot_Text["HaveMascot"])
			return
		end
	end
	

	local nNpcName = Get_NpcName(nNpcId)
	local nUserId = Get_UserId()
	
	--寄存器存储
	--User_SetVarData(tAnniversary2015_Mascot_Data["VarDataInx2"],nNpcId,nUserId)
	User_SetVarStr(tAnniversary2015_Mascot_Data["VarStrInx3"],nNpcName,nUserId)

	--是否存在令牌
	if not Item_ChkItem(tAnniversary2015_Mascot_Data["Pet"][nNpcId]) then
		local sMsgBoxText = string.format(tAnniversary2015_Mascot_Text["NoCorrectPet"],nNpcName)
		Sys_MsgBox(sMsgBoxText)
		local nStatus = tAnniversary2015_Mascot_Status["Status"]
		local nPower =  tAnniversary2015_Mascot_Status["Power"]
		local nSecs = tAnniversary2015_Mascot_Status["Secs"]
		local nTimes = tAnniversary2015_Mascot_Status["Times"]
		local nRemainTime = tAnniversary2015_Mascot_Status["RemainTime"]
		local nEndTime = tAnniversary2015_Mascot_Status["EndTime"]
		local nRecordable = tAnniversary2015_Mascot_Status["Recordable"]
		User_AddRoleStatus(nStatus,nPower,nSecs,nTimes,nRemainTime,nEndTime,nRecordable,0,0,nUserId)

		--移动NPC到5000地图
		local nMapId = tAnniversary2015_Mascot_Data["CampMapId"]
		local nPosX = tAnniversary2015_Mascot_Data["CampMapPosX"]
		local nPosY = tAnniversary2015_Mascot_Data["CampMapPosY"]
		Npc_MoveNpcPos(nNpcId,nMapId,nPosX,nPosY)

		--倒计时20秒后执行函数
		Sys_SetLuaTimer(tAnniversary2015_Mascot_Data["DelayTime"],string.format("Anniversary2015_Mascot_MoveBackPet</N>%d",nNpcId))
		return
	end

	--删除令牌
	Item_DelItem(tAnniversary2015_Mascot_Data["Pet"][nNpcId])
	--30/100几率
	local flat,tItem = Probabil_RandomAward(tAnniversary2015_Mascot_Probabil[1],1)
	local bValue = tItem[1]["tAward"][1]["Item_1"]

	--30/100几率失败
	if bValue then
	
		--判断获得经验次数
		if Task_ChkStcValue(tAnniversary2015_Mascot_Stc[7]["Event"],tAnniversary2015_Mascot_Stc[7]["Type"],"==",tAnniversary2015_Mascot_Stc[7]["Begin"]) then
		
			--是否隔天
			if Task_StcInterval(tAnniversary2015_Mascot_Stc[7]["Event"],tAnniversary2015_Mascot_Stc[7]["Type"],1,4) then
				Task_AddStatistic(tAnniversary2015_Mascot_Stc[7]["Event"],tAnniversary2015_Mascot_Stc[7]["Type"],tAnniversary2015_Mascot_Stc[7]["Add"],1)
				Task_SetStcTimestamp(tAnniversary2015_Mascot_Stc[7]["Event"],tAnniversary2015_Mascot_Stc[7]["Type"],0)

			--活动经验次数超过最大限制
			elseif Task_ChkStcValue(tAnniversary2015_Mascot_Stc[7]["Event"],tAnniversary2015_Mascot_Stc[7]["Type"],">=",tAnniversary2015_Mascot_Stc[7]["Max"]) then
				--+LOG+提示
				local sItemName = Get_UserVarStr(tAnniversary2015_Mascot_Data["VarStrInx3"],nUserId)
				local sText = string.format(tAnniversary2015_Mascot_Text["Defeat"],sItemName)
				Sys_MsgBox(sText)
				return
			end
		end
		
		--玩家等级
		local nUserLev = Get_UserLevel(nUserId)
		if nUserLev >= tAnniversary2015_Mascot_Data["MaxLev"] then
			local sItemName = Get_UserVarStr(tAnniversary2015_Mascot_Data["VarStrInx3"],nUserId)
			local sText = string.format(tAnniversary2015_Mascot_Text["Defeat"],sItemName)
			Sys_MsgBox(sText)
			return
		end
		
		--增加10分钟经验+LOG+提示
		local sItemName = Get_UserVarStr(tAnniversary2015_Mascot_Data["VarStrInx3"],nUserId)
		local sText = string.format(tAnniversary2015_Mascot_Text["AddExpTime"],sItemName)
		User_AddExpTime(tAnniversary2015_Mascot_Data["AddExpTime"])
		Sys_SaveActionFestivalLog(tAnniversary2015_Mascot_Log["AddExpTime"])
		Sys_MsgBox(sText)
		return
	end
	
	--70/100成功+特效+提示
	local sItemName = Get_UserVarStr(tAnniversary2015_Mascot_Data["VarStrInx3"],nUserId)
	local sTextSuccess = string.format(tAnniversary2015_Mascot_Text["Success"],sItemName)
	Task_SetStatistic(tAnniversary2015_Mascot_Stc[nStcId]["Event"],tAnniversary2015_Mascot_Stc[nStcId]["Type"],tAnniversary2015_Mascot_Stc[nStcId]["Complete"],1)
	Task_SetStcTimestamp(tAnniversary2015_Mascot_Stc[nStcId]["Event"],tAnniversary2015_Mascot_Stc[nStcId]["Type"],0)
	User_EffectAdd(tAnniversary2015_Mascot_Data["EffectObj"],tAnniversary2015_Mascot_Data["Effect2"])
	Sys_MsgBox(sTextSuccess)
end


--宠物选项判断函数
function Anniversary2015_Mascot_ChkOption()
	--活动时间判断
	if not Sys_ChkFullTime(tAnniversary2015_Mascot_Data["Festival_MidTime"]) then
		return false
	end
	
	--判断任务掩码是否为0
	if Task_ChkStcValue(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],"==",tAnniversary2015_Mascot_Stc[1]["Begin"]) then
		return false
	end
	
	--是否隔天
	if Task_StcInterval(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],1,4) then
		Task_SetStatistic(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],0,1)
		Task_SetStcTimestamp(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],0)
		return false
	end
	
	--是否已接受任务
	if not Task_ChkStcValue(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],"==",tAnniversary2015_Mascot_Stc[1]["Accept"]) then
		return false
	end
	
	return true
end


------------------------------------------物品逻辑-------------------------------------------

--寻路
function Anniversary2015_Mascot_FindNpcFunc()
	local nNpcId = tAnniversary2015_Mascot_FindNpc["NpcId"]
	local nMapId = tAnniversary2015_Mascot_FindNpc["MapId"]
	local nPosX = tAnniversary2015_Mascot_FindNpc["PosX"]
	local nPosY = tAnniversary2015_Mascot_FindNpc["PosY"]
	Sys_GotoSomeWhere(nPosX,nPosY,nMapId,nNpcId)
end



--关闭宠物袋
function Anniversary2015_Mascot_ClosePetPag()
	User_TalkChannel2005(tAnniversary2015_Mascot_Text["ClosePetPag"])
end


--【吉祥宠物袋】
function Anniversary2015_Mascot_ItemPetPag(nItemId)
	--活动时间判断
	if not Sys_ChkFullTime(tAnniversary2015_Mascot_Data["Festival_MidTime"]) then
	
		--删除宠物袋
		if Item_ChkItem(nItemId) then
			Item_DelItem(nItemId)
		end
		
		--LOG+提示
		Sys_SaveActionFestivalLog(tAnniversary2015_Mascot_Log["DelPetBag"])
		User_TalkChannel2005(tAnniversary2015_Mascot_Text["PetPagTimeOut"])
		return
	end
	
	--nPetNum袋内宠物数量
	local nPetNum = 0
	--判断袋内宠物数量
	local nBegin = tAnniversary2015_Mascot_Data["ForBegin"]
	local nEnd = tAnniversary2015_Mascot_Data["ForEnd"]
	for nStcNum = nBegin,nEnd do
		if not Task_ChkStcValue(tAnniversary2015_Mascot_Stc[nStcNum]["Event"],tAnniversary2015_Mascot_Stc[nStcNum]["Type"],"==",tAnniversary2015_Mascot_Stc[nStcNum]["Begin"]) then
			
			--是否隔天
			if Task_StcInterval(tAnniversary2015_Mascot_Stc[nStcNum]["Event"],tAnniversary2015_Mascot_Stc[nStcNum]["Type"],1,4) then
				Task_SetStatistic(tAnniversary2015_Mascot_Stc[nStcNum]["Event"],tAnniversary2015_Mascot_Stc[nStcNum]["Type"],0,1)
				Task_SetStcTimestamp(tAnniversary2015_Mascot_Stc[nStcNum]["Event"],tAnniversary2015_Mascot_Stc[nStcNum]["Type"],0)
			end
			
			--存在该宠物
			nPetNum = nPetNum + 1
		end
	end
	
	--宠物数量是否满足
	if nPetNum >= tAnniversary2015_Mascot_Data["PetMax"] then
		Sys_DialogText(tAnniversary2015_Mascot_Text["PetMaxText"])
		Sys_DialogOption(tAnniversary2015_Mascot_Text["PetMaxText-Option1"],"</F>Anniversary2015_Mascot_FindNpcFunc")
		Sys_DialogOption(tAnniversary2015_Mascot_Text["PetMaxText-Option2"],"</F>Anniversary2015_Mascot_ClosePetPag")
		Sys_DialogEnd()
		return
	end
	
	--袋内还差的宠物
	local nBegin = tAnniversary2015_Mascot_Data["ForBegin"]
	local nEnd = tAnniversary2015_Mascot_Data["ForEnd"]
	Sys_DialogText(tAnniversary2015_Mascot_Text["PetLackText"])
	for nStcNum = nBegin,nEnd do
		if not Task_ChkStcValue(tAnniversary2015_Mascot_Stc[nStcNum]["Event"],tAnniversary2015_Mascot_Stc[nStcNum]["Type"],"==",tAnniversary2015_Mascot_Stc[nStcNum]["Begin"]) then
			
			--是否隔天
			if Task_StcInterval(tAnniversary2015_Mascot_Stc[nStcNum]["Event"],tAnniversary2015_Mascot_Stc[nStcNum]["Type"],1,4) then
				Task_SetStatistic(tAnniversary2015_Mascot_Stc[nStcNum]["Event"],tAnniversary2015_Mascot_Stc[nStcNum]["Type"],0,1)
				Task_SetStcTimestamp(tAnniversary2015_Mascot_Stc[nStcNum]["Event"],tAnniversary2015_Mascot_Stc[nStcNum]["Type"],0)
				Sys_DialogText(tAnniversary2015_Mascot_Text["PetLackText1"][nStcNum])
			end
		else
			Sys_DialogText(tAnniversary2015_Mascot_Text["PetLackText1"][nStcNum])
		end
	end
	Sys_DialogText(tAnniversary2015_Mascot_Text["PetLackText2"])
	Sys_DialogText(tAnniversary2015_Mascot_Text["PetLackText3"])
	Sys_DialogText(tAnniversary2015_Mascot_Text["PetLackText4"])
	Sys_DialogOption(tAnniversary2015_Mascot_Text["PetLackText-Option"],"</F>Anniversary2015_Mascot_ClosePetPag")
	Sys_DialogEnd()
end


--【令牌】
function Anniversary2015_Mascot_ItemToken(nItemId)
	--活动时间判断
	if not Sys_ChkFullTime(tAnniversary2015_Mascot_Data["Festival_MidTime"]) then
		--删除令牌
		if Item_ChkItem(nItemId) then
			Item_DelAllItemByType(nItemId)
		end
		
		local sTokenName = tAnniversary2015_Mascot_Text["TokenName"][nItemId]
		local sLogText = string.format(tAnniversary2015_Mascot_Log["DelToken"],nItemId)
		local sTalkText = string.format(tAnniversary2015_Mascot_Text["DelToken"],sTokenName)
		--LOG+提示
		Sys_SaveActionFestivalLog(sLogText)
		User_TalkChannel2005(sTalkText)
		return
	end
end


------------------------------------------怪物逻辑-------------------------------------------

function Anniversary2015_Mascot_Monster()
	--活动时间判断
	if not Sys_ChkFullTime(tAnniversary2015_Mascot_Data["Festival_MidTime"]) then
		return
	end
	
	--判断任务掩码是否为0
	if Task_ChkStcValue(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],"==",tAnniversary2015_Mascot_Stc[1]["Begin"]) then
		return
	end
	
	--是否隔天
	if Task_StcInterval(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],1,4) then
		Task_SetStatistic(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],0,1)
		Task_SetStcTimestamp(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],0)
		return
	end

	--是否完成任务
	if not Task_ChkStcValue(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],"==",tAnniversary2015_Mascot_Stc[1]["Accept"]) then
		return
	end
	
	--3/100几率
	local flat,tItem = Probabil_RandomAward(tAnniversary2015_Mascot_Probabil[2],1)
	local bValue = tItem[1]["tAward"][1]["Item_1"]
	

	--3/100成功触发
	if bValue then 
	
		--25/100几率
		local flat,tItem = Probabil_RandomAward(tAnniversary2015_Mascot_Probabil[3],1)
		local nItemId = tItem[1]["tAward"][1]["Item_1"]

		Monster_SysDropItem(nItemId)
		User_TalkChannel2005(tAnniversary2015_Mascot_Text["Monster"])
	end
end




------------------------------------------NPC配置-------------------------------------------
---------------------NPC头像
tNpcFace[2943] = 121
---------------------NPC对话
------------------------------------------
-- // ==吉祥物大使吉祥== \\
tNpcGossip[16507] = tNpcGossip[16507] or DefaultNpc:new{}
tNpcGossip[16507]["OptionHidden"] = 1

---【起始对白】
tNpcGossip[16507]["Text1-1"] = {111,112,113} 		-- 活动时间前
tNpcGossip[16507]["Text1-2"] = {121} 				-- 活动时间后
tNpcGossip[16507]["Text1-3"] = {131,132,133} 		-- 活动时间中
tNpcGossip[16507]["Text1-4"] = {141} 				-- 已请假

---活动前
tNpcGossip[16507]["Text111"] = tAnniversary2015_Mascot_Text[16507]["Text111"]
tNpcGossip[16507]["Text112"] = tAnniversary2015_Mascot_Text[16507]["Text112"]
tNpcGossip[16507]["Text113"] = tAnniversary2015_Mascot_Text[16507]["Text113"]
tNpcGossip[16507]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tAnniversary2015_Mascot_Data["Festival_BefTime"])
end

---活动后
tNpcGossip[16507]["Text121"] = tAnniversary2015_Mascot_Text[16507]["Text121"]
tNpcGossip[16507]["ChkFunc1-2"] = function ()
	return not Sys_ChkFullTime(tAnniversary2015_Mascot_Data["Festival_MidTime"])
end

---活动中
tNpcGossip[16507]["Text131"] = tAnniversary2015_Mascot_Text[16507]["Text131"]
tNpcGossip[16507]["Text132"] = tAnniversary2015_Mascot_Text[16507]["Text132"]
tNpcGossip[16507]["Text133"] = tAnniversary2015_Mascot_Text[16507]["Text133"]

--选项
tNpcGossip[16507]["tOption1-1"] = {11}				-- 活动时间前
tNpcGossip[16507]["tOption1-2"] = {12}				-- 活动时间后
tNpcGossip[16507]["tOption1-3"] = {13,14,16,15,17}	-- 活动时间中
tNpcGossip[16507]["Option11"] = tAnniversary2015_Mascot_Text[16507]["Option11"]
tNpcGossip[16507]["Option12"] = tAnniversary2015_Mascot_Text[16507]["Option12"]
tNpcGossip[16507]["Option13"] = tAnniversary2015_Mascot_Text[16507]["Option13"]
tNpcGossip[16507]["OptionChkFunc13"] = function ()
	--判断任务掩码是否为0
	if Task_ChkStcValue(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],"==",tAnniversary2015_Mascot_Stc[1]["Begin"]) then
		return true
	end

	--是否隔天
	if Task_StcInterval(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],1,4) then
		Task_SetStatistic(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],0,1)
		Task_SetStcTimestamp(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],0)
		return true
	end
end
tNpcGossip[16507]["OptionFunc13"] = "Anniversary2015_Mascot_JoinFestival</N>16507"
tNpcGossip[16507]["Option14"] = tAnniversary2015_Mascot_Text[16507]["Option14"]
tNpcGossip[16507]["OptionChkFunc14"] = function ()
	--判断是否接受任务
	if Task_ChkStcValue(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],"==",tAnniversary2015_Mascot_Stc[1]["Accept"]) then
		return true
	end
end
tNpcGossip[16507]["OptionFunc14"] = "Anniversary2015_Mascot_RewardPetBag</N>16507"
tNpcGossip[16507]["Option15"] = tAnniversary2015_Mascot_Text[16507]["Option15"]
tNpcGossip[16507]["OptionChkFunc15"] = function ()
	--判断是否接受任务
	if Task_ChkStcValue(tAnniversary2015_Mascot_Stc[1]["Event"],tAnniversary2015_Mascot_Stc[1]["Type"],"==",tAnniversary2015_Mascot_Stc[1]["Accept"]) then
		return true
	end
end
tNpcGossip[16507]["OptionFunc15"] = "Anniversary2015_Mascot_GiveItem</N>16507"
tNpcGossip[16507]["Option16"] = tAnniversary2015_Mascot_Text[16507]["Option16"]
tNpcGossip[16507]["OptionFunc16"] = "Anniversary2015_Mascot_Introduction</N>16507"
tNpcGossip[16507]["Option17"] = tAnniversary2015_Mascot_Text[16507]["Option17"]



---【我要帮你。】
tNpcGossip[16507]["Text2-1"] = {211} 				--等级不足
tNpcGossip[16507]["Text2-2"] = {221,222,223,224} 	--成功接收任务
tNpcGossip[16507]["Text2-3"] = {231}				--背包空间不足
tNpcGossip[16507]["Text211"] = tAnniversary2015_Mascot_Text[16507]["Text211"]
tNpcGossip[16507]["Text221"] = sText221
tNpcGossip[16507]["Text222"] = tAnniversary2015_Mascot_Text[16507]["Text222"]
tNpcGossip[16507]["Text223"] = tAnniversary2015_Mascot_Text[16507]["Text223"]
tNpcGossip[16507]["Text224"] = tAnniversary2015_Mascot_Text[16507]["Text224"]
tNpcGossip[16507]["Text231"] = tAnniversary2015_Mascot_Text[16507]["Text231"]
--选项
tNpcGossip[16507]["tOption2-1"] = {21}				-- 等级不足
tNpcGossip[16507]["tOption2-2"] = {22}				-- 成功接收任务
tNpcGossip[16507]["tOption2-3"] = {23}				--背包空间不足
tNpcGossip[16507]["Option21"] = tAnniversary2015_Mascot_Text[16507]["Option21"]
tNpcGossip[16507]["Option22"] = tAnniversary2015_Mascot_Text[16507]["Option22"]
tNpcGossip[16507]["Option23"] = tAnniversary2015_Mascot_Text[16507]["Option23"]


--【喏，给您吉祥四宝。】
tNpcGossip[16507]["Text3-1"] = {311} 				--已完成任务
tNpcGossip[16507]["Text3-2"] = {321} 				--没有宠物袋
tNpcGossip[16507]["Text3-3"] = {331}				--成功上交
tNpcGossip[16507]["Text311"] = tAnniversary2015_Mascot_Text[16507]["Text311"]
tNpcGossip[16507]["Text321"] = tAnniversary2015_Mascot_Text[16507]["Text321"]
tNpcGossip[16507]["Text331"] = tAnniversary2015_Mascot_Text[16507]["Text331"]

--选项
tNpcGossip[16507]["tOption3-1"] = {31}			--已完成任务
tNpcGossip[16507]["tOption3-2"] = {32}			--带来的颜色不对
tNpcGossip[16507]["tOption3-3"] = {33}			--成功上交
tNpcGossip[16507]["Option31"] = tAnniversary2015_Mascot_Text[16507]["Option31"]
tNpcGossip[16507]["Option32"] = tAnniversary2015_Mascot_Text[16507]["Option32"]
tNpcGossip[16507]["Option33"] = tAnniversary2015_Mascot_Text[16507]["Option33"]



--【我该怎么帮您噜？】
tNpcGossip[16507]["Text4-1"] = {411,412,413,414} 		--活动内容介绍
tNpcGossip[16507]["Text411"] = tAnniversary2015_Mascot_Text[16507]["Text411"]
tNpcGossip[16507]["Text412"] = tAnniversary2015_Mascot_Text[16507]["Text412"]
tNpcGossip[16507]["Text413"] = tAnniversary2015_Mascot_Text[16507]["Text413"]
tNpcGossip[16507]["Text414"] = tAnniversary2015_Mascot_Text[16507]["Text414"]
--选项
tNpcGossip[16507]["tOption4-1"] = {41}			--活动内容介绍
tNpcGossip[16507]["Option41"] = tAnniversary2015_Mascot_Text[16507]["Option41"]
tNpcGossip[16507]["OptionFunc41"] = "Anniversary2015_Mascot_MascotRule</N>16507"



--【什么令牌用于吸引什么吉祥物？】
tNpcGossip[16507]["Text5-1"] = {511,512,513} 		--活动内容介绍
tNpcGossip[16507]["Text511"] = tAnniversary2015_Mascot_Text[16507]["Text511"]
tNpcGossip[16507]["Text512"] = tAnniversary2015_Mascot_Text[16507]["Text512"]
tNpcGossip[16507]["Text513"] = tAnniversary2015_Mascot_Text[16507]["Text513"]
--选项
tNpcGossip[16507]["tOption5-1"] = {51}
tNpcGossip[16507]["Option51"] = tAnniversary2015_Mascot_Text[16507]["Option51"]



------------------------------------------
-- // ==红狐== \\
tNpcGossip[16508] = tNpcGossip[16508] or DefaultNpc:new{}
tNpcGossip[16509] = tNpcGossip[16508] or DefaultNpc:new{}
tNpcGossip[16510] = tNpcGossip[16508] or DefaultNpc:new{}
tNpcGossip[16511] = tNpcGossip[16508] or DefaultNpc:new{}
tNpcGossip[16508]["OptionHidden"] = 1

---【起始对白】
tNpcGossip[16508]["Text1-1"] = {111} 	-- 闲聊对白
tNpcGossip[16508]["Text1-2"] = {121} 	-- 没有宠物袋对白
tNpcGossip[16508]["Text111"] = tAnniversary2015_Mascot_Text[16508]["Text111"]
tNpcGossip[16508]["Text121"] = tAnniversary2015_Mascot_Text[16508]["Text121"]
--选项
tNpcGossip[16508]["tOption1-1"] = {11,12}
tNpcGossip[16508]["tOption1-2"] = {13}
tNpcGossip[16508]["Option11"] = tAnniversary2015_Mascot_Text[16508]["Option11"]
tNpcGossip[16508]["OptionChkFunc11"] = function ()
	return Anniversary2015_Mascot_ChkOption()
end
tNpcGossip[16508]["OptionFunc11"] = "Anniversary2015_Mascot_GiveToken</N>3"
tNpcGossip[16508]["Option12"] = tAnniversary2015_Mascot_Text[16508]["Option12"]
tNpcGossip[16508]["Option13"] = tAnniversary2015_Mascot_Text[16508]["Option13"]



------------------------------------------
-- // ==粉兔== \\
tNpcGossip[16512] = tNpcGossip[16512] or DefaultNpc:new{}
tNpcGossip[16513] = tNpcGossip[16512] or DefaultNpc:new{}
tNpcGossip[16514] = tNpcGossip[16512] or DefaultNpc:new{}
tNpcGossip[16515] = tNpcGossip[16512] or DefaultNpc:new{}
tNpcGossip[16512]["OptionHidden"] = 1

---【起始对白】
tNpcGossip[16512]["Text1-1"] = {111} 	-- 闲聊对白
tNpcGossip[16512]["Text111"] = tAnniversary2015_Mascot_Text[16512]["Text111"]
--选项
tNpcGossip[16512]["tOption1-1"] = {11,12}
tNpcGossip[16512]["Option11"] = tAnniversary2015_Mascot_Text[16512]["Option11"]
tNpcGossip[16512]["OptionChkFunc11"] = function ()
	return Anniversary2015_Mascot_ChkOption()
end
tNpcGossip[16512]["OptionFunc11"] = "Anniversary2015_Mascot_GiveToken</N>4"
tNpcGossip[16512]["Option12"] = tAnniversary2015_Mascot_Text[16512]["Option12"]


------------------------------------------
-- // ==银兔== \\
tNpcGossip[16516] = tNpcGossip[16516] or DefaultNpc:new{}
tNpcGossip[16517] = tNpcGossip[16516] or DefaultNpc:new{}
tNpcGossip[16518] = tNpcGossip[16516] or DefaultNpc:new{}
tNpcGossip[16519] = tNpcGossip[16516] or DefaultNpc:new{}
tNpcGossip[16516]["OptionHidden"] = 1

---【起始对白】
tNpcGossip[16516]["Text1-1"] = {111} 	-- 闲聊对白
tNpcGossip[16516]["Text111"] = tAnniversary2015_Mascot_Text[16516]["Text111"]
--选项
tNpcGossip[16516]["tOption1-1"] = {11,12}
tNpcGossip[16516]["Option11"] = tAnniversary2015_Mascot_Text[16516]["Option11"]
tNpcGossip[16516]["OptionChkFunc11"] = function ()
	return Anniversary2015_Mascot_ChkOption()
end
tNpcGossip[16516]["OptionFunc11"] = "Anniversary2015_Mascot_GiveToken</N>5"
tNpcGossip[16516]["Option12"] = tAnniversary2015_Mascot_Text[16516]["Option12"]


------------------------------------------
-- // ==蓝狐== \\
tNpcGossip[16520] = tNpcGossip[16520] or DefaultNpc:new{}
tNpcGossip[16521] = tNpcGossip[16520] or DefaultNpc:new{}
tNpcGossip[16522] = tNpcGossip[16520] or DefaultNpc:new{}
tNpcGossip[16523] = tNpcGossip[16520] or DefaultNpc:new{}
tNpcGossip[16520]["OptionHidden"] = 1

---【起始对白】
tNpcGossip[16520]["Text1-1"] = {111} 	-- 闲聊对白
tNpcGossip[16520]["Text111"] = tAnniversary2015_Mascot_Text[16520]["Text111"]
--选项
tNpcGossip[16520]["tOption1-1"] = {11,12}
tNpcGossip[16520]["Option11"] = tAnniversary2015_Mascot_Text[16520]["Option11"]
tNpcGossip[16520]["OptionChkFunc11"] = function ()
	return Anniversary2015_Mascot_ChkOption()
end
tNpcGossip[16520]["OptionFunc11"] = "Anniversary2015_Mascot_GiveToken</N>6"
tNpcGossip[16520]["Option12"] = tAnniversary2015_Mascot_Text[16520]["Option12"]


------------------------------------------物品配置-------------------------------------------
------------------------------------------
-- // ==吉祥宠物袋== \\
tItem[3003514] = tItem[3003514] or {}
tItem[3003514]["Function"] = function (nItemId,sItemName)
	Anniversary2015_Mascot_ItemPetPag(nItemId)
end

-- // ==令牌== \\
tItem[3003515] = tItem[3003515] or {}
tItem[3003516] = tItem[3003515] or {}
tItem[3003517] = tItem[3003515] or {}
tItem[3003518] = tItem[3003515] or {}
tItem[3003515] = tItem[3003515] or {}tItem[3003515]["Function"] = function (nItemId,sItemName)
	Anniversary2015_Mascot_ItemToken(nItemId)
end






------------------------------------------怪物配置-------------------------------------------
--------第一片区1002
-- //叫天鸡		9593200
-- tMonster[1] = tMonster[1] or {}
-- tMonster[1]["tFunction"] = tMonster[1]["tFunction"] or {}
-- table.insert(tMonster[1]["tFunction"],Anniversary2015_Mascot_Monster)
-- //斑鸠王		9593210
-- tMonster[2] = tMonster[2] or {}
-- tMonster[2]["tFunction"] = tMonster[2]["tFunction"] or {}
-- table.insert(tMonster[2]["tFunction"],Anniversary2015_Mascot_Monster)
-- //罗罗鸟		9593220
-- tMonster[3] = tMonster[3] or {}
-- tMonster[3]["tFunction"] = tMonster[3]["tFunction"] or {}
-- table.insert(tMonster[3]["tFunction"],Anniversary2015_Mascot_Monster)
-- //幽冥鬼斧王		9593230
-- tMonster[4] = tMonster[4] or {}
-- tMonster[4]["tFunction"] = tMonster[4]["tFunction"] or {}
-- table.insert(tMonster[4]["tFunction"],Anniversary2015_Mascot_Monster)
-- //蹑空鬼斧王		9593240
-- tMonster[5] = tMonster[5] or {}
-- tMonster[5]["tFunction"] = tMonster[5]["tFunction"] or {}
-- table.insert(tMonster[5]["tFunction"],Anniversary2015_Mascot_Monster)

----------------------------------------
------第二片区1011
-- //翼蛇		9593250
-- tMonster[6] = tMonster[6] or {}
-- tMonster[6]["tFunction"] = tMonster[6]["tFunction"] or {}
-- table.insert(tMonster[6]["tFunction"],Anniversary2015_Mascot_Monster)
-- //土匪		9593260
-- tMonster[7] = tMonster[7] or {}
-- tMonster[7]["tFunction"] = tMonster[7]["tFunction"] or {}
-- table.insert(tMonster[7]["tFunction"],Anniversary2015_Mascot_Monster)
-- //火鼠		9593270
-- tMonster[8] = tMonster[8] or {}
-- tMonster[8]["tFunction"] = tMonster[8]["tFunction"] or {}
-- table.insert(tMonster[8]["tFunction"],Anniversary2015_Mascot_Monster)
-- //火精灵		9593280
-- tMonster[9] = tMonster[9] or {}
-- tMonster[9]["tFunction"] = tMonster[9]["tFunction"] or {}
-- table.insert(tMonster[9]["tFunction"],Anniversary2015_Mascot_Monster)

----------------------------------------
------第三片区1020
-- //须弥猴		9593310
-- tMonster[10] = tMonster[10] or {}
-- tMonster[10]["tFunction"] = tMonster[10]["tFunction"] or {}
-- table.insert(tMonster[10]["tFunction"],Anniversary2015_Mascot_Monster)
-- //巨臂猿		9593320
-- tMonster[11] = tMonster[11] or {}
-- tMonster[11]["tFunction"] = tMonster[11]["tFunction"] or {}
-- table.insert(tMonster[11]["tFunction"],Anniversary2015_Mascot_Monster)
-- //天雷巨猿	9593330
-- tMonster[12] = tMonster[12] or {}
-- tMonster[12]["tFunction"] = tMonster[12]["tFunction"] or {}
-- table.insert(tMonster[12]["tFunction"],Anniversary2015_Mascot_Monster)
-- //蛇人		9593340
-- tMonster[13] = tMonster[13] or {}
-- tMonster[13]["tFunction"] = tMonster[13]["tFunction"] or {}
-- table.insert(tMonster[13]["tFunction"],Anniversary2015_Mascot_Monster)


----------------------------------------
------第四片区1000
-- //沙怪		9593350
-- tMonster[14] = tMonster[14] or {}
-- tMonster[14]["tFunction"] = tMonster[14]["tFunction"] or {}
-- table.insert(tMonster[14]["tFunction"],Anniversary2015_Mascot_Monster)
-- //锤山怪		9593360
-- tMonster[15] = tMonster[15] or {}
-- tMonster[15]["tFunction"] = tMonster[15]["tFunction"] or {}
-- table.insert(tMonster[15]["tFunction"],Anniversary2015_Mascot_Monster)
-- //巨石怪		9593370
-- tMonster[16] = tMonster[16] or {}
-- tMonster[16]["tFunction"] = tMonster[16]["tFunction"] or {}
-- table.insert(tMonster[16]["tFunction"],Anniversary2015_Mascot_Monster)
-- //鬼刃		9593380
-- tMonster[17] = tMonster[17] or {}
-- tMonster[17]["tFunction"] = tMonster[17]["tFunction"] or {}
-- table.insert(tMonster[17]["tFunction"],Anniversary2015_Mascot_Monster)


------------------------------------------
--------第五片区1015
-- //金臂鸟人	4081200\9593400
-- tMonster[18] = tMonster[18] or {}
-- tMonster[18]["tFunction"] = tMonster[18]["tFunction"] or {}
-- table.insert(tMonster[18]["tFunction"],Anniversary2015_Mascot_Monster)
-- //银羽鹰王	9593410
-- tMonster[19] = tMonster[19] or {}
-- tMonster[19]["tFunction"] = tMonster[19]["tFunction"] or {}
-- table.insert(tMonster[19]["tFunction"],Anniversary2015_Mascot_Monster)
-- //湖岛强匪	9593420
-- tMonster[55] = tMonster[55] or {}
-- tMonster[55]["tFunction"] = tMonster[55]["tFunction"] or {}
-- table.insert(tMonster[55]["tFunction"],Anniversary2015_Mascot_Monster)


----------------------------------------
------第六片区1001
--//土墓蝠		9593460
-- tMonster[20] = tMonster[20] or {}
-- tMonster[20]["tFunction"] = tMonster[20]["tFunction"] or {}
-- table.insert(tMonster[20]["tFunction"],Anniversary2015_Mascot_Monster)
--//血蝙蝠		9593470
-- tMonster[56] = tMonster[56] or {}
-- tMonster[56]["tFunction"] = tMonster[56]["tFunction"] or {}
-- table.insert(tMonster[56]["tFunction"],Anniversary2015_Mascot_Monster)
--//牛怪		9593480
-- tMonster[57] = tMonster[57] or {}
-- tMonster[57]["tFunction"] = tMonster[57]["tFunction"] or {}
-- table.insert(tMonster[57]["tFunction"],Anniversary2015_Mascot_Monster)
--//红魔		9593490
-- tMonster[58] = tMonster[58] or {}
-- tMonster[58]["tFunction"] = tMonster[58]["tFunction"] or {}
-- table.insert(tMonster[58]["tFunction"],Anniversary2015_Mascot_Monster)


------------------------------------------
--------冰封地穴、 海滩片区
-- //缚灵	9438000
-- tMonster[2684] = tMonster[2684] or {}
-- tMonster[2684]["tFunction"] = tMonster[2684]["tFunction"] or {}
-- table.insert(tMonster[2684]["tFunction"],Anniversary2015_Mascot_Monster)
-- //深海亡魂	9438010
-- tMonster[2686] = tMonster[2686] or {}
-- tMonster[2686]["tFunction"] = tMonster[2686]["tFunction"] or {}
-- table.insert(tMonster[2686]["tFunction"],Anniversary2015_Mascot_Monster)
-- //冰凌腾蛇	9979200
-- tMonster[2411] = tMonster[2411] or {}
-- tMonster[2411]["tFunction"] = tMonster[2411]["tFunction"] or {}
-- table.insert(tMonster[2411]["tFunction"],Anniversary2015_Mascot_Monster)
-- //冰煞邪刀	9979210
-- tMonster[2416] = tMonster[2416] or {}
-- tMonster[2416]["tFunction"] = tMonster[2416]["tFunction"] or {}
-- table.insert(tMonster[2416]["tFunction"],Anniversary2015_Mascot_Monster)




------------------------------------------配置数据------------------------------------------
--时间函数触发
--'00 00'
-- tOntimerMin_M[00] = tOntimerMin_M[00] or {}
-- table.insert(tOntimerMin_M[00],Anniversary2015_Mascot_MoveNpcFunC)
--'10 10'
-- tOntimerMin_M[10] = tOntimerMin_M[10] or {}
-- table.insert(tOntimerMin_M[10],Anniversary2015_Mascot_MoveNpcFunC)
--'20 20'
-- tOntimerMin_M[20] = tOntimerMin_M[20] or {}
-- table.insert(tOntimerMin_M[20],Anniversary2015_Mascot_MoveNpcFunC)
--'30 30'
-- tOntimerMin_M[30] = tOntimerMin_M[30] or {}
-- table.insert(tOntimerMin_M[30],Anniversary2015_Mascot_MoveNpcFunC)
--'40 40'
-- tOntimerMin_M[40] = tOntimerMin_M[40] or {}
-- table.insert(tOntimerMin_M[40],Anniversary2015_Mascot_MoveNpcFunC)
--'50 50'
-- tOntimerMin_M[50] = tOntimerMin_M[50] or {}
-- table.insert(tOntimerMin_M[50],Anniversary2015_Mascot_MoveNpcFunC)
