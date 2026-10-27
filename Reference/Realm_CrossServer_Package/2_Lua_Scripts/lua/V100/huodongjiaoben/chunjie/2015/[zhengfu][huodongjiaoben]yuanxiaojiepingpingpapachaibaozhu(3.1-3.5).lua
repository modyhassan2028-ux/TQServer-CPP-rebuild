------------------------------------------------------------------------------------
--Name:		[征服][活动脚本]元宵节之砰砰啪啪拆爆竹
--Purpose:	元宵节之砰砰啪啪拆爆竹
--Creator: 	严振飞
--Created:	2014/12/09
------------------------------------------------------------------------------------
--[[
任务需求：


]]--
------------------------------------------------------------------------------------
--掩码说明
---stc(131,90) --记录是否领取任务
---stc(131,91) --记录是否拆满10个爆竹
---stc(131,92) --记录是否领取奖励

--LOGid 10002403
------------------------------------------------------------------------------------
--物品说明
---3005530--爆竹处理器
---3005531--年兽的牙齿
------------------------------------------------------------------------------------
--命名规范
--FestivalSpring2015_RemoveFireks_
------------------------------------------------------------------------------------
--STC掩码表
local tFestivalSpring2015_RemoveFireks_Stc = {}
----------------------------------------
--stc(131,90)--记录是否领取任务
	tFestivalSpring2015_RemoveFireks_Stc[1] = {}
	tFestivalSpring2015_RemoveFireks_Stc[1]["Event"] = 131
	tFestivalSpring2015_RemoveFireks_Stc[1]["Type"] = 90
--stc(131,91)--记录是否拆满10个爆竹
	tFestivalSpring2015_RemoveFireks_Stc[2] = {}
	tFestivalSpring2015_RemoveFireks_Stc[2]["Event"] = 131
	tFestivalSpring2015_RemoveFireks_Stc[2]["Type"] = 91
	tFestivalSpring2015_RemoveFireks_Stc[2]["Finish"] = 10
--stc(131,92)--记录是否领取奖励
	tFestivalSpring2015_RemoveFireks_Stc[3] = {}
	tFestivalSpring2015_RemoveFireks_Stc[3]["Event"] = 131
	tFestivalSpring2015_RemoveFireks_Stc[3]["Type"] = 92


------------------------------------------------------------------------------------
--活动数据
local tFestivalSpring2015_RemoveFireks_Data = {}
	--活动时间
	tFestivalSpring2015_RemoveFireks_Data["Festival_BefTime"] = "2014-01-01 00:00 2015-02-28 23:59"
	tFestivalSpring2015_RemoveFireks_Data["Festival_NowTime"] = "2015-03-01 00:00 2015-03-05 23:59"
	--活动物品
	tFestivalSpring2015_RemoveFireks_Data["Item_MonsterCoat"] = 3005530
	tFestivalSpring2015_RemoveFireks_Data["Item_BangerTools"] = 3005531
	--背包空间
	tFestivalSpring2015_RemoveFireks_Data["ChkSpace"] = 1
	--几率数据
	tFestivalSpring2015_RemoveFireks_Data["EndNum"] = 100
	tFestivalSpring2015_RemoveFireks_Data["StartNum"] = {}
		--5%的几率获得年兽的牙齿
	tFestivalSpring2015_RemoveFireks_Data["StartNum"][1] = 5
		--点击爆竹3个范围内，10%几率直接爆炸
	tFestivalSpring2015_RemoveFireks_Data["StartNum"][2] = 10
		--尝试拆解，20%几率爆炸
	tFestivalSpring2015_RemoveFireks_Data["StartNum"][3] = 20
	
	--玩家与爆竹距离数据
	tFestivalSpring2015_RemoveFireks_Data["RangeMin"] = 3
	tFestivalSpring2015_RemoveFireks_Data["RangeMax"] = 6
	
	--自动寻路坐标（爆竹）
	tFestivalSpring2015_RemoveFireks_Data["Fireks"] = {}
	tFestivalSpring2015_RemoveFireks_Data["Fireks"]["NpcId"] = 0
	tFestivalSpring2015_RemoveFireks_Data["Fireks"]["MapId"] = 1002
	tFestivalSpring2015_RemoveFireks_Data["Fireks"]["PosX"] = 290
	tFestivalSpring2015_RemoveFireks_Data["Fireks"]["PosY"] = 417
	--自动寻路坐标（主NPC）
	tFestivalSpring2015_RemoveFireks_Data["Npc"] = {}
	tFestivalSpring2015_RemoveFireks_Data["Npc"]["NpcId"] = 17416
	tFestivalSpring2015_RemoveFireks_Data["Npc"]["MapId"] = 1002
	tFestivalSpring2015_RemoveFireks_Data["Npc"]["PosX"] = 273
	tFestivalSpring2015_RemoveFireks_Data["Npc"]["PosY"] = 378
	--获得经验值/修行值
	tFestivalSpring2015_RemoveFireks_Data["AddExp"] = 30
	tFestivalSpring2015_RemoveFireks_Data["AddCultivation"] = 15
	--等级，转世设置
	tFestivalSpring2015_RemoveFireks_Data["LevTop"] = 140
	tFestivalSpring2015_RemoveFireks_Data["MinLevel"] = 80
	tFestivalSpring2015_RemoveFireks_Data["MinMeto"] = 0
	--通用礼包ID
	tFestivalSpring2015_RemoveFireks_Data["FestivalId"] = 3370
	tFestivalSpring2015_RemoveFireks_Data["LogId"] = 10002403
	--爆炸光效
	tFestivalSpring2015_RemoveFireks_Data["EffectObj"] = "self"
	tFestivalSpring2015_RemoveFireks_Data["Effect_1"] = "fireball-bomb"
	--拆除成功光效
	tFestivalSpring2015_RemoveFireks_Data["Effect_2"] = "zf2-e011"
	--领奖成功光效
	tFestivalSpring2015_RemoveFireks_Data["Effect_3"] = "angelwing"
	--晕眩光效
	tFestivalSpring2015_RemoveFireks_Data["Effect_4"] = "BodyDisapear"
	tFestivalSpring2015_RemoveFireks_Data["Effect_4_Status"] = 55
	tFestivalSpring2015_RemoveFireks_Data["Effect_4_Power"] = 200
	tFestivalSpring2015_RemoveFireks_Data["Effect_4_Secs"] = 2
	tFestivalSpring2015_RemoveFireks_Data["Effect_4_Times"] = 1
	tFestivalSpring2015_RemoveFireks_Data["Effect_4_RemainTime"] = 2
	tFestivalSpring2015_RemoveFireks_Data["Effect_4_EndTime"] = 1
	tFestivalSpring2015_RemoveFireks_Data["Effect_4_Recordable"] = 1
	--读条数据
	tFestivalSpring2015_RemoveFireks_Data["ExploreTime"] = 2
	tFestivalSpring2015_RemoveFireks_Data["ExploreActionId"] = 220
	
------------------------------------------------------------------------------------
-- NPC爆竹的坐标表
local tFestivalSpring2015_RemoveFireks_Npc = {}
	tFestivalSpring2015_RemoveFireks_Npc["MapId"] = 1002
	--爆竹1
	tFestivalSpring2015_RemoveFireks_Npc[17417] = {}
	tFestivalSpring2015_RemoveFireks_Npc[17417]["PosX_1"] = 282
	tFestivalSpring2015_RemoveFireks_Npc[17417]["PosY_1"] = 413
	tFestivalSpring2015_RemoveFireks_Npc[17417]["PosX_2"] = 272
	tFestivalSpring2015_RemoveFireks_Npc[17417]["PosY_2"] = 422
	--爆竹2
	tFestivalSpring2015_RemoveFireks_Npc[17418] = {}
	tFestivalSpring2015_RemoveFireks_Npc[17418]["PosX_1"] = 271
	tFestivalSpring2015_RemoveFireks_Npc[17418]["PosY_1"] = 409
	tFestivalSpring2015_RemoveFireks_Npc[17418]["PosX_2"] = 299
	tFestivalSpring2015_RemoveFireks_Npc[17418]["PosY_2"] = 430
	--爆竹3
	tFestivalSpring2015_RemoveFireks_Npc[17419] = {}
	tFestivalSpring2015_RemoveFireks_Npc[17419]["PosX_1"] = 274
	tFestivalSpring2015_RemoveFireks_Npc[17419]["PosY_1"] = 401
	tFestivalSpring2015_RemoveFireks_Npc[17419]["PosX_2"] = 294
	tFestivalSpring2015_RemoveFireks_Npc[17419]["PosY_2"] = 420
	--爆竹4
	tFestivalSpring2015_RemoveFireks_Npc[17420] = {}
	tFestivalSpring2015_RemoveFireks_Npc[17420]["PosX_1"] = 283
	tFestivalSpring2015_RemoveFireks_Npc[17420]["PosY_1"] = 400
	tFestivalSpring2015_RemoveFireks_Npc[17420]["PosX_2"] = 285
	tFestivalSpring2015_RemoveFireks_Npc[17420]["PosY_2"] = 422
	--爆竹5
	tFestivalSpring2015_RemoveFireks_Npc[17421] = {}
	tFestivalSpring2015_RemoveFireks_Npc[17421]["PosX_1"] = 293
	tFestivalSpring2015_RemoveFireks_Npc[17421]["PosY_1"] = 403
	tFestivalSpring2015_RemoveFireks_Npc[17421]["PosX_2"] = 306
	tFestivalSpring2015_RemoveFireks_Npc[17421]["PosY_2"] = 425
	--爆竹6
	tFestivalSpring2015_RemoveFireks_Npc[17422] = {}
	tFestivalSpring2015_RemoveFireks_Npc[17422]["PosX_1"] = 300
	tFestivalSpring2015_RemoveFireks_Npc[17422]["PosY_1"] = 413
	tFestivalSpring2015_RemoveFireks_Npc[17422]["PosX_2"] = 305
	tFestivalSpring2015_RemoveFireks_Npc[17422]["PosY_2"] = 434
	--爆竹7
	tFestivalSpring2015_RemoveFireks_Npc[17423] = {}
	tFestivalSpring2015_RemoveFireks_Npc[17423]["PosX_1"] = 305
	tFestivalSpring2015_RemoveFireks_Npc[17423]["PosY_1"] = 404
	tFestivalSpring2015_RemoveFireks_Npc[17423]["PosX_2"] = 278
	tFestivalSpring2015_RemoveFireks_Npc[17423]["PosY_2"] = 417
	--爆竹8
	tFestivalSpring2015_RemoveFireks_Npc[17424] = {}
	tFestivalSpring2015_RemoveFireks_Npc[17424]["PosX_1"] = 283
	tFestivalSpring2015_RemoveFireks_Npc[17424]["PosY_1"] = 411
	tFestivalSpring2015_RemoveFireks_Npc[17424]["PosX_2"] = 296
	tFestivalSpring2015_RemoveFireks_Npc[17424]["PosY_2"] = 432

------------------------------------------------------------------------------------
--活动LOG数据
local tFestivalSpring2015_RemoveFireks_Log = {}
	--任务阶段
	tFestivalSpring2015_RemoveFireks_Log["Phase_1"] = "0,0,0,0,10002403,1[1],0,0"
	tFestivalSpring2015_RemoveFireks_Log["Phase_2"] = "0,0,0,0,10002403,1[2],0,0"
	--年兽的牙齿
	tFestivalSpring2015_RemoveFireks_Log["Get_MonsterCoat"] = "0,0,0,0,10002403,2,3005531,1"
	--获得经验值/修行值
	tFestivalSpring2015_RemoveFireks_Log["AddExp"] = "0,0,0,0,10002403,2,4,30"
	tFestivalSpring2015_RemoveFireks_Log["AddCultivation"] = "0,0,0,0,10002403,2,6,20"


------------------------------------------逻辑部分-------------------------------------------
-- 寻路函数
function FestivalSpring2015_RemoveFireks_FindWay(sObject)
	local nFireksPosX = tFestivalSpring2015_RemoveFireks_Data[sObject]["PosX"]
	local nFireksPosY = tFestivalSpring2015_RemoveFireks_Data[sObject]["PosY"]
	local nFireksMapId = tFestivalSpring2015_RemoveFireks_Data[sObject]["MapId"]
	local nObjNpcId = tFestivalSpring2015_RemoveFireks_Data[sObject]["NpcId"]
	
	Sys_GotoSomeWhere(nFireksPosX,nFireksPosY,nFireksMapId,nObjNpcId)
end


--- 玩家与爆竹距离判断
function FestivalSpring2015_RemoveFireks_ChkUserPos(nPosValue)
	--//nPosValue == 3（3格距离）初点击爆竹
	--//nPosValue == 6（6格距离）尝试拆解
	local nNpcId = Get_NpcId()
	local nUserPosX = Get_UserPositionX()
	local nUserPosY = Get_UserPositionY()
	local nFireksPosX = Get_NpcPositionX()
	local nFireksPosY = Get_NpcPositionY()
	
	--在nPosValue格范围外
	if nUserPosX < nFireksPosX - nPosValue or nUserPosX > nFireksPosX + nPosValue or nUserPosY < nFireksPosY - nPosValue or nUserPosY > nFireksPosY + nPosValue then
		if nPosValue == tFestivalSpring2015_RemoveFireks_Data["RangeMin"] then
			return false
		else 
			return true
		end

	--在nPosValue格范围内
	elseif nPosValue == tFestivalSpring2015_RemoveFireks_Data["RangeMin"] then
	
		--点击爆竹3个范围内，10%几率直接爆炸
		if Sys_Random(tFestivalSpring2015_RemoveFireks_Data["StartNum"][2],tFestivalSpring2015_RemoveFireks_Data["EndNum"]) then
			local nMapId = tFestivalSpring2015_RemoveFireks_Data["Fireks"]["MapId"]
			local nPosX = Get_NpcPositionX(nNpcId)
			local nPosY = Get_NpcPositionY(nNpcId)
		
			--移动爆竹
			FestivalSpring2015_RemoveFireks_Move(nNpcId)
			Map_Effect(nMapId,nPosX,nPosY,tFestivalSpring2015_RemoveFireks_Data["Effect_1"])
			
			--晕眩状态
			local nStatus = tFestivalSpring2015_RemoveFireks_Data["Effect_4_Status"]
			local nPower = tFestivalSpring2015_RemoveFireks_Data["Effect_4_Power"]
			local nSecs = tFestivalSpring2015_RemoveFireks_Data["Effect_4_Secs"]
			local nTimes = tFestivalSpring2015_RemoveFireks_Data["Effect_4_Times"]
			local nRemainTime = tFestivalSpring2015_RemoveFireks_Data["Effect_4_RemainTime"]
			local nEndTime = tFestivalSpring2015_RemoveFireks_Data["Effect_4_EndTime"]
			local nRecordable = tFestivalSpring2015_RemoveFireks_Data["Effect_4_Recordable"]
			local nUserId = Get_UserId()
			
			User_EffectAdd(tFestivalSpring2015_RemoveFireks_Data["EffectObj"],tFestivalSpring2015_RemoveFireks_Data["Effect_4"])
			User_AddRoleStatus(nStatus,nPower,nSecs,nTimes,nRemainTime,nEndTime,nRecordable,0,0,nUserId)
			return true
		else
			return false
		end
	else
		return false
	end
end


--- STC掩码逻辑
function FestivalSpring2015_RemoveFireks_ChkStc(nStcNum)
	local nEvent = tFestivalSpring2015_RemoveFireks_Stc[nStcNum]["Event"]
	local nType = tFestivalSpring2015_RemoveFireks_Stc[nStcNum]["Type"]
	
	--判断掩码是否为0
	if Task_ChkStcValue(nEvent,nType,"==",0) then
		return true
	end
	
	--判断是否隔天
	if Task_StcInterval(nEvent,nType,1,4) then
		
		--重置所有STC掩码
		for nStcNum = 1,#tFestivalSpring2015_RemoveFireks_Stc do
			local nEventReset = tFestivalSpring2015_RemoveFireks_Stc[nStcNum]["Event"]
			local nTypeReset = tFestivalSpring2015_RemoveFireks_Stc[nStcNum]["Type"]
			Task_SetStatistic(nEventReset,nTypeReset,0,1)
			Task_SetStcTimestamp(nEventReset,nTypeReset,0)
		end
		return true
	end
	
	--参加活动选项掩码（爆竹拆机个数判断）
	local nFinish = tFestivalSpring2015_RemoveFireks_Stc[2]["Finish"]
	if nStcNum == 2 then
		if Task_ChkStcValue(nEvent,nType,">=",nFinish) then
			return false
		else
			return true
		end
	end
	
	--不等0，未隔天
	return false
end


-- 获得奖励逻辑
function FestivalSpring2015_RemoveFireks_GetAward(nStcNum)
	--兑换年兽牙齿奖励（无掩码限制）
	if nStcNum == 0 then
		local nUserLev = Get_UserLevel()
		
		--背包里是否有牙齿判断
		if not Item_ChkItem(tFestivalSpring2015_RemoveFireks_Data["Item_MonsterCoat"]) then
			LinkNpcGossipFunc_New(nNpcId,"4-1")
			return
		end
		
		--删除年兽牙齿
		Item_DelItem(tFestivalSpring2015_RemoveFireks_Data["Item_MonsterCoat"])
		
		--满级玩家
		if nUserLev >= tFestivalSpring2015_RemoveFireks_Data["LevTop"] then
			User_AddCultivation(tFestivalSpring2015_RemoveFireks_Data["AddCultivation"])
			Sys_MsgBox(tFestivalSpring2015_RemoveFireks_Text["AddCultivation"])
			Sys_SaveActionFestivalLog(tFestivalSpring2015_RemoveFireks_Log["AddCultivation"])
			
		--未满级
		else
			User_AddExpTime(tFestivalSpring2015_RemoveFireks_Data["AddExp"])
			Sys_MsgBox(tFestivalSpring2015_RemoveFireks_Text["AddExp"])
			Sys_SaveActionFestivalLog(tFestivalSpring2015_RemoveFireks_Log["AddExp"])
		end
	
	--有掩码限制的奖励
	elseif nStcNum ~= 0 then
		local nEvent = tFestivalSpring2015_RemoveFireks_Stc[nStcNum]["Event"]
		local nType = tFestivalSpring2015_RemoveFireks_Stc[nStcNum]["Type"]
		--领取节日礼包
		if Item_ChkItem(tFestivalSpring2015_RemoveFireks_Data["Item_BangerTools"]) then
			Item_DelItem(tFestivalSpring2015_RemoveFireks_Data["Item_BangerTools"])
		end
		Task_SetStatistic(nEvent,nType,1,1)
		Task_SetStcTimestamp(nEvent,nType,0)
		User_EffectAdd(tFestivalSpring2015_RemoveFireks_Data["EffectObj"],tFestivalSpring2015_RemoveFireks_Data["Effect_3"])
		FestivalGeneralPackage_GetGift(tFestivalSpring2015_RemoveFireks_Data["FestivalId"],tFestivalSpring2015_RemoveFireks_Data["LogId"])
	end
end


-- 玩家参加活动
function FestivalSpring2015_RemoveFireks_Join(nNpcId)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalSpring2015_RemoveFireks_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end

	--玩家等级判断
	if not User_JudgeLevelAndMetempsychosis(tFestivalSpring2015_RemoveFireks_Data["MinLevel"],tFestivalSpring2015_RemoveFireks_Data["MinMeto"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	--是否已完成任务判断
	if not FestivalSpring2015_RemoveFireks_ChkStc(3) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	
	--是否已存在拆解器
	if Item_ChkItem(tFestivalSpring2015_RemoveFireks_Data["Item_BangerTools"]) then
		Task_SetStatistic(tFestivalSpring2015_RemoveFireks_Stc[1]["Event"],tFestivalSpring2015_RemoveFireks_Stc[1]["Type"],1,1)
		Task_SetStcTimestamp(tFestivalSpring2015_RemoveFireks_Stc[1]["Event"],tFestivalSpring2015_RemoveFireks_Stc[1]["Type"],0)
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end

	--背包空间不足
	if not User_CheckLeftSpace(tFestivalSpring2015_RemoveFireks_Data["ChkSpace"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-4")
		return
	end
	
	--报名成功,置掩码
	Task_SetStatistic(tFestivalSpring2015_RemoveFireks_Stc[1]["Event"],tFestivalSpring2015_RemoveFireks_Stc[1]["Type"],1,1)
	Task_SetStcTimestamp(tFestivalSpring2015_RemoveFireks_Stc[1]["Event"],tFestivalSpring2015_RemoveFireks_Stc[1]["Type"],0)
	
	--初始化已拆爆竹个数
	Task_SetStatistic(tFestivalSpring2015_RemoveFireks_Stc[2]["Event"],tFestivalSpring2015_RemoveFireks_Stc[2]["Type"],0,1)
	Task_SetStcTimestamp(tFestivalSpring2015_RemoveFireks_Stc[2]["Event"],tFestivalSpring2015_RemoveFireks_Stc[2]["Type"],0)
	
	--添加物品,打LOG
	Item_AddItem(tFestivalSpring2015_RemoveFireks_Data["Item_BangerTools"])
	Sys_SaveActionFestivalLog(tFestivalSpring2015_RemoveFireks_Log["Phase_1"])
	LinkNpcGossipFunc_New(nNpcId,"2-5")
end


--领取奖励
function FestivalSpring2015_RemoveFireks_Reward(nNpcId)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalSpring2015_RemoveFireks_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end 

	--玩家等级判断
	if not User_JudgeLevelAndMetempsychosis(tFestivalSpring2015_RemoveFireks_Data["MinLevel"],tFestivalSpring2015_RemoveFireks_Data["MinMeto"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	--是否领取过奖励判断
	if not FestivalSpring2015_RemoveFireks_ChkStc(3) then
		LinkNpcGossipFunc_New(nNpcId,"3-1")
		return
	end
	
	local nEvent = tFestivalSpring2015_RemoveFireks_Stc[2]["Event"]
	local nType = tFestivalSpring2015_RemoveFireks_Stc[2]["Type"]
	local nFinish = tFestivalSpring2015_RemoveFireks_Stc[2]["Finish"]
	
	--是否拆满10个爆竹判断
	if not Task_ChkStcValue(nEvent,nType,">=",nFinish) then
		LinkNpcGossipFunc_New(nNpcId,"3-2")
		return
	end
	
	--背包空间判断
	if not User_CheckLeftSpace(tFestivalSpring2015_RemoveFireks_Data["ChkSpace"]) then
		LinkNpcGossipFunc_New(nNpcId,"3-3")
		return
	end
	
	--获得节日礼包
	Sys_SaveActionFestivalLog(tFestivalSpring2015_RemoveFireks_Log["Phase_2"])
	FestivalSpring2015_RemoveFireks_GetAward(3)
	LinkNpcGossipFunc_New(nNpcId,"3-4")
end


--兑换牙齿
function FestivalSpring2015_RemoveFireks_Exchange(nNpcId)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalSpring2015_RemoveFireks_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	--玩家等级判断
	if not User_JudgeLevelAndMetempsychosis(tFestivalSpring2015_RemoveFireks_Data["MinLevel"],tFestivalSpring2015_RemoveFireks_Data["MinMeto"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	--背包里是否有牙齿判断
	if not Item_ChkItem(tFestivalSpring2015_RemoveFireks_Data["Item_MonsterCoat"]) then
		LinkNpcGossipFunc_New(nNpcId,"4-1")
		return
	end
	
	--兑换成功
	FestivalSpring2015_RemoveFireks_GetAward(0)
	User_EffectAdd(tFestivalSpring2015_RemoveFireks_Data["EffectObj"],tFestivalSpring2015_RemoveFireks_Data["Effect_3"])
	LinkNpcGossipFunc_New(nNpcId,"4-2")
end


--活动介绍
function FestivalSpring2015_RemoveFireks_Introduction(nNpcId)
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalSpring2015_RemoveFireks_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-3")
		return
	end
	
	--出介绍
	LinkNpcGossipFunc_New(nNpcId,"5-1")
end


-- 移动爆竹
function FestivalSpring2015_RemoveFireks_Move(nNpcId)
	local nPosX = Get_NpcPositionX(nNpcId)
	local nPosY = Get_NpcPositionY(nNpcId)
	local nMapId = tFestivalSpring2015_RemoveFireks_Npc["MapId"]
	local nPosX_1 = tFestivalSpring2015_RemoveFireks_Npc[nNpcId]["PosX_1"]
	local nPosY_1 = tFestivalSpring2015_RemoveFireks_Npc[nNpcId]["PosY_1"]
	local nPosX_2 = tFestivalSpring2015_RemoveFireks_Npc[nNpcId]["PosX_2"]
	local nPosY_2 = tFestivalSpring2015_RemoveFireks_Npc[nNpcId]["PosY_2"]

	--确定NPC移动坐标
	if nPosX == nPosX_1 then
		nPosX = nPosX_2
		nPosY = nPosY_2
	elseif nPosX == nPosX_2 then
		nPosX = nPosX_1
		nPosY = nPosY_1
	end

	--移动爆竹
	Npc_MoveNpcPos(nNpcId,nMapId,nPosX,nPosY)
end


--- 成功拆除爆竹
function FestivalSpring2015_RemoveFireks_Succee(nNpcId)
	local sTextNum = "2-5"
	local nMapId = tFestivalSpring2015_RemoveFireks_Data["Fireks"]["MapId"]
	local nPosX = Get_NpcPositionX(nNpcId)
	local nPosY = Get_NpcPositionY(nNpcId)
	local nEvent = tFestivalSpring2015_RemoveFireks_Stc[2]["Event"]
	local nType = tFestivalSpring2015_RemoveFireks_Stc[2]["Type"]
	local nFinish = tFestivalSpring2015_RemoveFireks_Stc[2]["Finish"]
	
	--5%的几率获得年兽的牙齿
	if Sys_Random(tFestivalSpring2015_RemoveFireks_Data["StartNum"][1],tFestivalSpring2015_RemoveFireks_Data["EndNum"]) then
		Item_AddItem(tFestivalSpring2015_RemoveFireks_Data["Item_MonsterCoat"])
		Sys_SaveActionFestivalLog(tFestivalSpring2015_RemoveFireks_Log["Get_MonsterCoat"])
		sTextNum = "2-6"
	end
	
	--置掩码
	Task_AddStatistic(tFestivalSpring2015_RemoveFireks_Stc[2]["Event"],tFestivalSpring2015_RemoveFireks_Stc[2]["Type"],1,0)
	Task_SetStcTimestamp(tFestivalSpring2015_RemoveFireks_Stc[2]["Event"],tFestivalSpring2015_RemoveFireks_Stc[2]["Type"],0)
	
	--移动爆竹
	FestivalSpring2015_RemoveFireks_Move(nNpcId)
	Map_Effect(nMapId,nPosX,nPosY,tFestivalSpring2015_RemoveFireks_Data["Effect_2"])

	--是否已拆解10个
	if Task_ChkStcValue(nEvent,nType,">=",nFinish) then
		Sys_MsgBox(tFestivalSpring2015_RemoveFireks_Text["Succee"],"FestivalSpring2015_RemoveFireks_FindWay</S>Npc")
		return
	end

	--出对白
	local sFireksNum = tostring(Get_UserStatisticValue(tFestivalSpring2015_RemoveFireks_Stc[2]["Event"],tFestivalSpring2015_RemoveFireks_Stc[2]["Type"]))
	tNpcGossip[17417]["Text251"] = string.format(tFestivalSpring2015_RemoveFireks_Text[17417]["Text251"],sFireksNum)
	tNpcGossip[17417]["Text261"] = string.format(tFestivalSpring2015_RemoveFireks_Text[17417]["Text261"],sFireksNum)
	LinkNpcGossipFunc_New(nNpcId,sTextNum)
end


--读条成功执行函数
function FestivalSpring2015_RemoveFireks_ExploreSuccess(nNpcId)

	--失败，爆炸
	if Sys_Random(tFestivalSpring2015_RemoveFireks_Data["StartNum"][3],tFestivalSpring2015_RemoveFireks_Data["EndNum"]) then
		local nMapId = tFestivalSpring2015_RemoveFireks_Data["Fireks"]["MapId"]
		local nPosX = Get_NpcPositionX(nNpcId)
		local nPosY = Get_NpcPositionY(nNpcId)
		
		--移动爆竹
		FestivalSpring2015_RemoveFireks_Move(nNpcId)
		Map_Effect(nMapId,nPosX,nPosY,tFestivalSpring2015_RemoveFireks_Data["Effect_1"])
		
		--晕眩状态
		local nStatus = tFestivalSpring2015_RemoveFireks_Data["Effect_4_Status"]
		local nPower = tFestivalSpring2015_RemoveFireks_Data["Effect_4_Power"]
		local nSecs = tFestivalSpring2015_RemoveFireks_Data["Effect_4_Secs"]
		local nTimes = tFestivalSpring2015_RemoveFireks_Data["Effect_4_Times"]
		local nRemainTime = tFestivalSpring2015_RemoveFireks_Data["Effect_4_RemainTime"]
		local nEndTime = tFestivalSpring2015_RemoveFireks_Data["Effect_4_EndTime"]
		local nRecordable = tFestivalSpring2015_RemoveFireks_Data["Effect_4_Recordable"]
		local nUserId = Get_UserId()
		
		User_EffectAdd(tFestivalSpring2015_RemoveFireks_Data["EffectObj"],tFestivalSpring2015_RemoveFireks_Data["Effect_4"])
		User_AddRoleStatus(nStatus,nPower,nSecs,nTimes,nRemainTime,nEndTime,nRecordable,0,0,nUserId)
		
		--出对白
		local sFireksNum = tostring(Get_UserStatisticValue(tFestivalSpring2015_RemoveFireks_Stc[2]["Event"],tFestivalSpring2015_RemoveFireks_Stc[2]["Type"]))
		tNpcGossip[17417]["Text241"] = string.format(tFestivalSpring2015_RemoveFireks_Text[17417]["Text241"],sFireksNum)
		LinkNpcGossipFunc_New(nNpcId,"2-4")
		return
	end
	
	--成功拆除
	FestivalSpring2015_RemoveFireks_Succee(nNpcId)
end


--尝试拆解
function FestivalSpring2015_RemoveFireks_Remove()
	local nNpcId = Get_NpcId()
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalSpring2015_RemoveFireks_Data["Festival_NowTime"]) then
		LinkNpcGossipFunc_New(nNpcId,"1-2")
		return
	end

	--失败，无处理器
	if not Item_ChkItem(tFestivalSpring2015_RemoveFireks_Data["Item_BangerTools"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-1")
		return
	end
	
	--失败，太远
	if FestivalSpring2015_RemoveFireks_ChkUserPos(tFestivalSpring2015_RemoveFireks_Data["RangeMax"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-2")
		return
	end
	
	--背包空间判断
	if not User_CheckLeftSpace(tFestivalSpring2015_RemoveFireks_Data["ChkSpace"]) then
		LinkNpcGossipFunc_New(nNpcId,"2-3")
		return
	end
	
	--读条
	local nSecs = tFestivalSpring2015_RemoveFireks_Data["ExploreTime"]
	local sContent = tFestivalSpring2015_RemoveFireks_Text["ExploreText"]
	local nActionId = tFestivalSpring2015_RemoveFireks_Data["ExploreActionId"]
	local sFunc = string.format("FestivalSpring2015_RemoveFireks_ExploreSuccess</N>%d",nNpcId)
	User_SetExplore(nSecs,sContent,nActionId,sFunc)
end


--爆竹接入函数
function FestivalSpring2015_RemoveFireks_FireksApi()
	--活动时间判断
	if not Sys_ChkFullTime(tFestivalSpring2015_RemoveFireks_Data["Festival_NowTime"]) then
		LinkNpcMain()
		return
	end

	--是否已领取奖励
	if not FestivalSpring2015_RemoveFireks_ChkStc(3) then
		LinkNpcMain()
		return
	end
	
	local nEvent = tFestivalSpring2015_RemoveFireks_Stc[2]["Event"]
	local nType = tFestivalSpring2015_RemoveFireks_Stc[2]["Type"]
	local nFinish = tFestivalSpring2015_RemoveFireks_Stc[2]["Finish"]

	--是否已拆解10个
	if Task_ChkStcValue(nEvent,nType,">=",nFinish) then
		Sys_MsgBox(tFestivalSpring2015_RemoveFireks_Text["Succee"],"FestivalSpring2015_RemoveFireks_FindWay</S>Npc")
		return
	else
		--接入npc模板
		LinkNpcMain()
	end
end


------------------------------------------物品配置-------------------------------------------
tItem[3005531] = tItem[3005531] or {} --爆竹处理器
tItem[3005531]["Function"] = function (nItemId,sItemName)

	--活动时间
	if not Sys_ChkFullTime(tFestivalSpring2015_RemoveFireks_Data["Festival_NowTime"]) then
		--删除全部同类物品
		if Item_ChkItem(tFestivalSpring2015_RemoveFireks_Data["Item_BangerTools"]) then
			Item_DelItem(tFestivalSpring2015_RemoveFireks_Data["Item_BangerTools"])
			User_TalkChannel2005(tFestivalSpring2015_RemoveFireks_Text["Item_TimeOut"])
		end
		return
	end
	
	--寻路去爆竹区域
	FestivalSpring2015_RemoveFireks_FindWay("Fireks")
end


------------------------------------------
tItem[3005530] = tItem[3005530] or {} --年兽的牙齿
tItem[3005530]["Function"] = function (nItemId,sItemName)

	--活动时间
	if not Sys_ChkFullTime(tFestivalSpring2015_RemoveFireks_Data["Festival_NowTime"]) then
		--删除全部同类物品
		if Item_ChkItem(tFestivalSpring2015_RemoveFireks_Data["Item_MonsterCoat"]) then
			Item_DelAllItemByType(tFestivalSpring2015_RemoveFireks_Data["Item_MonsterCoat"])
			User_TalkChannel2005(tFestivalSpring2015_RemoveFireks_Text["Item_TimeOut"])
		end
		return
	end
	
	User_TalkChannel2005(tFestivalSpring2015_RemoveFireks_Text["Item_MonsterCoat"])
end

------------------------------------------NPC头像-------------------------------------------
tNpcFace[3401] = 34
------------------------------------------NPC对话-------------------------------------------

-- //爆竹大师张巧手
tNpcGossip[17416] = tNpcGossip[17416] or DefaultNpc:new{}
tNpcGossip[17416]["OptionHidden"] = 1

-- 【起始对白】
tNpcGossip[17416]["Text1-1"] = {111,112,113} 	-- 活动时间前
tNpcGossip[17416]["Text1-2"] = {121,122,123} 	-- 活动时间中
tNpcGossip[17416]["Text1-3"] = {131,132} 		-- 活动时间后
-- 活动前
tNpcGossip[17416]["Text111"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text111"]
tNpcGossip[17416]["Text112"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text112"]
tNpcGossip[17416]["Text113"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text113"]
tNpcGossip[17416]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tFestivalSpring2015_RemoveFireks_Data["Festival_BefTime"])
end
-- 活动中
tNpcGossip[17416]["Text121"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text121"]
tNpcGossip[17416]["Text122"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text122"]
tNpcGossip[17416]["Text123"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text123"]
tNpcGossip[17416]["ChkFunc1-2"] = function ()
	return Sys_ChkFullTime(tFestivalSpring2015_RemoveFireks_Data["Festival_NowTime"])
end
-- 活动后
tNpcGossip[17416]["Text131"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text131"]
--选项
tNpcGossip[17416]["tOption1-1"] = {11}
tNpcGossip[17416]["tOption1-2"] = {12,13,14,15,16}
tNpcGossip[17416]["tOption1-3"] = {17}
tNpcGossip[17416]["Option11"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option11"]
tNpcGossip[17416]["Option12"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option12"]
tNpcGossip[17416]["OptionChkFunc12"] = function ()
	return FestivalSpring2015_RemoveFireks_ChkStc(2)
end
tNpcGossip[17416]["OptionFunc12"] ="FestivalSpring2015_RemoveFireks_Join</N>17416"
tNpcGossip[17416]["Option13"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option13"]
tNpcGossip[17416]["OptionFunc13"] = "FestivalSpring2015_RemoveFireks_Reward</N>17416"
tNpcGossip[17416]["Option14"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option14"]
tNpcGossip[17416]["OptionFunc14"] = "FestivalSpring2015_RemoveFireks_Exchange</N>17416"
tNpcGossip[17416]["Option15"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option15"]
tNpcGossip[17416]["OptionFunc15"] = "FestivalSpring2015_RemoveFireks_Introduction</N>17416"
tNpcGossip[17416]["Option16"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option16"]
tNpcGossip[17416]["Option17"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option17"]


-- 【我也来帮忙！】
tNpcGossip[17416]["Text2-1"] = {211} --等级不足
tNpcGossip[17416]["Text2-2"] = {221} --已完成10次
tNpcGossip[17416]["Text2-3"] = {231} --已存在拆解器
tNpcGossip[17416]["Text2-4"] = {241} --背包空间不足
tNpcGossip[17416]["Text2-5"] = {251} --报名成功
tNpcGossip[17416]["Text211"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text211"]
tNpcGossip[17416]["Text221"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text221"]
tNpcGossip[17416]["Text231"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text231"]
tNpcGossip[17416]["Text241"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text241"]
tNpcGossip[17416]["Text251"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text251"]
tNpcGossip[17416]["tOption2-1"] = {21}
tNpcGossip[17416]["tOption2-2"] = {22}
tNpcGossip[17416]["tOption2-3"] = {23}
tNpcGossip[17416]["tOption2-4"] = {24}
tNpcGossip[17416]["tOption2-5"] = {25}
tNpcGossip[17416]["Option21"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option21"]
tNpcGossip[17416]["Option22"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option22"]
tNpcGossip[17416]["Option23"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option23"]
tNpcGossip[17416]["Option24"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option24"]
tNpcGossip[17416]["Option25"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option25"]
tNpcGossip[17416]["OptionFunc25"] = "FestivalSpring2015_RemoveFireks_FindWay</S>Fireks"


-- 【领取奖励。】
tNpcGossip[17416]["Text3-1"] = {311} 		--已领取奖励
tNpcGossip[17416]["Text3-2"] = {321} 		--未拆满10个爆竹
tNpcGossip[17416]["Text3-3"] = {331} 		--背包空间不足
tNpcGossip[17416]["Text3-4"] = {341,342} 	--获得节日礼包
tNpcGossip[17416]["Text311"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text311"]
tNpcGossip[17416]["Text321"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text321"]
tNpcGossip[17416]["Text331"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text331"]
tNpcGossip[17416]["Text341"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text341"]
tNpcGossip[17416]["Text342"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text342"]
tNpcGossip[17416]["tOption3-1"] = {31}
tNpcGossip[17416]["tOption3-2"] = {32}
tNpcGossip[17416]["tOption3-3"] = {33}
tNpcGossip[17416]["tOption3-4"] = {34}
tNpcGossip[17416]["Option31"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option31"]
tNpcGossip[17416]["Option32"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option32"]
tNpcGossip[17416]["Option33"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option33"]
tNpcGossip[17416]["Option34"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option34"]


-- 【兑换牙齿。】
tNpcGossip[17416]["Text4-1"] = {411} --背包里没有年兽牙齿
tNpcGossip[17416]["Text4-2"] = {421} --兑换成功
tNpcGossip[17416]["Text411"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text411"]
tNpcGossip[17416]["Text421"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text421"]
tNpcGossip[17416]["tOption4-1"] = {41}
tNpcGossip[17416]["tOption4-2"] = {42}
tNpcGossip[17416]["Option41"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option41"]
tNpcGossip[17416]["Option42"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option42"]


-- 【怎么回事？】
tNpcGossip[17416]["Text5-1"] = {511,512,513} 	--内容
tNpcGossip[17416]["Text511"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text511"]
tNpcGossip[17416]["Text512"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text512"]
tNpcGossip[17416]["Text513"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text513"]
tNpcGossip[17416]["tOption5-1"] = {51,52,53,54}
tNpcGossip[17416]["Option51"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option51"]
tNpcGossip[17416]["OptionPoint51"] = "6"
tNpcGossip[17416]["Option52"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option52"]
tNpcGossip[17416]["OptionPoint52"] = "7"
tNpcGossip[17416]["Option53"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option53"]
tNpcGossip[17416]["OptionPoint53"] = "1"
tNpcGossip[17416]["Option54"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option54"]


-- 【怎么回事？】--爆竹拆解器怎么用？
tNpcGossip[17416]["Text6-1"] = {611,612,613} 	--内容
tNpcGossip[17416]["Text611"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text611"]
tNpcGossip[17416]["Text612"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text612"]
tNpcGossip[17416]["Text613"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text613"]
tNpcGossip[17416]["tOption6-1"] = {61,62}
tNpcGossip[17416]["Option61"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option61"]
tNpcGossip[17416]["OptionPoint61"] = "5"
tNpcGossip[17416]["Option62"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option62"]


-- 【怎么回事？】--怎么找年兽牙齿？
tNpcGossip[17416]["Text7-1"] = {711,712} 	--内容
tNpcGossip[17416]["Text711"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text711"]
tNpcGossip[17416]["Text712"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Text712"]
tNpcGossip[17416]["tOption7-1"] = {71,72}
tNpcGossip[17416]["Option71"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option71"]
tNpcGossip[17416]["OptionPoint71"] = "5"
tNpcGossip[17416]["Option72"] = tFestivalSpring2015_RemoveFireks_Text[17416]["Option72"]


------------------------------------------------------------------------------------
-- //危险的爆竹
tNpcGossip[17417] = tNpcGossip[17417] or DefaultNpc:new{}
tNpcGossip[17418] = tNpcGossip[17417] or DefaultNpc:new{}
tNpcGossip[17419] = tNpcGossip[17417] or DefaultNpc:new{}
tNpcGossip[17420] = tNpcGossip[17417] or DefaultNpc:new{}
tNpcGossip[17421] = tNpcGossip[17417] or DefaultNpc:new{}
tNpcGossip[17422] = tNpcGossip[17417] or DefaultNpc:new{}
tNpcGossip[17423] = tNpcGossip[17417] or DefaultNpc:new{}
tNpcGossip[17424] = tNpcGossip[17417] or DefaultNpc:new{}
tNpcGossip[17417]["OptionHidden"] = 1


-- 【起始对白】
tNpcGossip[17417]["Text1-1"] = {111} 	--活动时间前
tNpcGossip[17417]["Text1-2"] = {121} 	--活动时间后
tNpcGossip[17417]["Text1-3"] = {131} 	--活动时间中（无任务）
tNpcGossip[17417]["Text1-4"] = {141} 	--活动时间中（有任务，已领取奖励）
tNpcGossip[17417]["Text1-5"] = {151} 	--活动时间中（有任务,爆炸）
tNpcGossip[17417]["Text1-6"] = {161} 	--活动时间中（有任务,出选项）
--活动时间前
tNpcGossip[17417]["Text111"] = tFestivalSpring2015_RemoveFireks_Text[17417]["Text111"]
tNpcGossip[17417]["ChkFunc1-1"] = function ()
	return Sys_ChkFullTime(tFestivalSpring2015_RemoveFireks_Data["Festival_BefTime"])
end
--活动时间后
tNpcGossip[17417]["Text121"] = tFestivalSpring2015_RemoveFireks_Text[17417]["Text121"]
tNpcGossip[17417]["ChkFunc1-2"] = function ()
	return not Sys_ChkFullTime(tFestivalSpring2015_RemoveFireks_Data["Festival_NowTime"])
end
--活动时间中（无任务）
tNpcGossip[17417]["Text131"] = tFestivalSpring2015_RemoveFireks_Text[17417]["Text131"]
tNpcGossip[17417]["ChkFunc1-3"] = function ()
	local nEvent = tFestivalSpring2015_RemoveFireks_Stc[1]["Event"]
	local nType = tFestivalSpring2015_RemoveFireks_Stc[1]["Type"]
	return Task_ChkStcValue(nEvent,nType,"==",0)
end
--活动时间中（有任务,已领取奖励）
tNpcGossip[17417]["Text141"] = tFestivalSpring2015_RemoveFireks_Text[17417]["Text141"]
tNpcGossip[17417]["ChkFunc1-4"] = function ()
	return not FestivalSpring2015_RemoveFireks_ChkStc(3)
end
--活动时间中（有任务,爆炸）
tNpcGossip[17417]["ChkFunc1-5"] = function ()
	local sFireksNum = tostring(Get_UserStatisticValue(tFestivalSpring2015_RemoveFireks_Stc[2]["Event"],tFestivalSpring2015_RemoveFireks_Stc[2]["Type"]))
	tNpcGossip[17417]["Text151"] = string.format(tFestivalSpring2015_RemoveFireks_Text[17417]["Text151"],sFireksNum)
	return FestivalSpring2015_RemoveFireks_ChkUserPos(tFestivalSpring2015_RemoveFireks_Data["RangeMin"])
end
--活动时间中（有任务,出选项）
tNpcGossip[17417]["Text161"] = tFestivalSpring2015_RemoveFireks_Text[17417]["Text161"]
--选项
tNpcGossip[17417]["tOption1-1"] = {11}
tNpcGossip[17417]["tOption1-2"] = {12}
tNpcGossip[17417]["tOption1-3"] = {13}
tNpcGossip[17417]["tOption1-4"] = {14}
tNpcGossip[17417]["tOption1-5"] = {15}
tNpcGossip[17417]["tOption1-6"] = {16,17}
tNpcGossip[17417]["Option11"] = tFestivalSpring2015_RemoveFireks_Text[17417]["Option11"]
tNpcGossip[17417]["Option12"] = tFestivalSpring2015_RemoveFireks_Text[17417]["Option12"]
tNpcGossip[17417]["Option13"] = tFestivalSpring2015_RemoveFireks_Text[17417]["Option13"]
tNpcGossip[17417]["Option14"] = tFestivalSpring2015_RemoveFireks_Text[17417]["Option14"]
tNpcGossip[17417]["Option15"] = tFestivalSpring2015_RemoveFireks_Text[17417]["Option15"]
tNpcGossip[17417]["Option16"] = tFestivalSpring2015_RemoveFireks_Text[17417]["Option16"]
tNpcGossip[17417]["OptionFunc16"] ="FestivalSpring2015_RemoveFireks_Remove"
tNpcGossip[17417]["Option17"] = tFestivalSpring2015_RemoveFireks_Text[17417]["Option17"]


-- 【尝试拆解。】
tNpcGossip[17417]["Text2-1"] = {211} 	-- 失败，无处理器
tNpcGossip[17417]["Text2-2"] = {221} 	-- 失败，太远
tNpcGossip[17417]["Text2-3"] = {231} 	-- 失败，背包空间不足
tNpcGossip[17417]["Text2-4"] = {241} 	-- 失败，爆炸
tNpcGossip[17417]["Text2-5"] = {251} 	-- 成功，获得年兽的牙齿
tNpcGossip[17417]["Text2-6"] = {261} 	-- 成功
tNpcGossip[17417]["Text211"] = tFestivalSpring2015_RemoveFireks_Text[17417]["Text211"]
tNpcGossip[17417]["Text221"] = tFestivalSpring2015_RemoveFireks_Text[17417]["Text221"]
tNpcGossip[17417]["Text231"] = tFestivalSpring2015_RemoveFireks_Text[17417]["Text231"]
--以下配空字符的为：变值对白-需实时赋值
tNpcGossip[17417]["Text241"] = ""
tNpcGossip[17417]["Text251"] = ""
tNpcGossip[17417]["Text261"] = ""
tNpcGossip[17417]["tOption2-1"] = {21}
tNpcGossip[17417]["tOption2-2"] = {22}
tNpcGossip[17417]["tOption2-3"] = {23}
tNpcGossip[17417]["tOption2-4"] = {24}
tNpcGossip[17417]["tOption2-5"] = {25}
tNpcGossip[17417]["tOption2-6"] = {26}
tNpcGossip[17417]["Option21"] = tFestivalSpring2015_RemoveFireks_Text[17417]["Option21"]
tNpcGossip[17417]["Option22"] = tFestivalSpring2015_RemoveFireks_Text[17417]["Option22"]
tNpcGossip[17417]["Option23"] = tFestivalSpring2015_RemoveFireks_Text[17417]["Option23"]
tNpcGossip[17417]["Option24"] = tFestivalSpring2015_RemoveFireks_Text[17417]["Option24"]
tNpcGossip[17417]["Option25"] = tFestivalSpring2015_RemoveFireks_Text[17417]["Option25"]
tNpcGossip[17417]["Option26"] = tFestivalSpring2015_RemoveFireks_Text[17417]["Option26"]

------------------------------------------

